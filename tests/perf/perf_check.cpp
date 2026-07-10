// Control-loop timing for a long cook. The application tick queries the
// telemetry store every 10 ms; those queries share the tick's time budget
// with the link pump and the UI, so they get 50 microseconds. This harness
// simulates a 30 minute sous-vide hold and reports how the queries behave as
// history accumulates.

#include "app/cooking/sous_vide_mode.h"
#include "system/system_sim.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <memory>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;

double to_us(Clock::duration d) {
    return std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(d).count();
}

} // namespace

int main() {
    constexpr std::uint32_t kSimMinutes = 30;
    constexpr double kQueryBudgetUs = 50.0;

    culina::system::SystemSim sim;
    sim.board().add_mass(1500.0f);
    sim.controller().start_program(
        std::make_unique<culina::app::SousVideMode>(650, kSimMinutes * 60));

    std::vector<double> query_us;
    query_us.reserve(kSimMinutes * 60 * 100);

    const auto wall_start = Clock::now();
    for (std::uint32_t tick = 0; tick < kSimMinutes * 60 * 100; ++tick) {
        sim.step_ms(10);

        // The same pair of queries the cooking tick issues for its display
        // metrics, timed in isolation.
        const auto t0 = Clock::now();
        const float avg = sim.store().average_temp_c(2000);
        const float peak = sim.store().max_temp_c(2000);
        const auto t1 = Clock::now();
        query_us.push_back(to_us(t1 - t0));
        (void)avg;
        (void)peak;
    }
    const double wall_s =
        std::chrono::duration_cast<std::chrono::duration<double>>(Clock::now() - wall_start)
            .count();

    std::sort(query_us.begin(), query_us.end());
    const auto at = [&](double q) { return query_us[static_cast<std::size_t>(
                                        q * static_cast<double>(query_us.size() - 1))]; };
    const std::size_t misses = static_cast<std::size_t>(
        query_us.end() - std::lower_bound(query_us.begin(), query_us.end(), kQueryBudgetUs));

    std::printf("simulated cook:            %u min sous-vide\n", kSimMinutes);
    std::printf("samples in telemetry store: %zu\n", sim.store().size());
    std::printf("control ticks executed:     %zu\n", query_us.size());
    std::printf("query time p50/p95/max:     %.1f us / %.1f us / %.1f us\n", at(0.50), at(0.95),
                query_us.back());
    std::printf("budget (%.0f us) misses:      %zu\n", kQueryBudgetUs, misses);
    std::printf("wall time:                  %.1f s\n", wall_s);
    return 0;
}
