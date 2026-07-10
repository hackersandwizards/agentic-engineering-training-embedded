#pragma once

#include <cstdint>
#include <random>

namespace culina::sim {

// Load cell with slow drift, gaussian noise, and vibration coupling that grows
// with the square of motor speed. All randomness comes from a seeded engine so
// runs are reproducible.
class ScaleModel {
public:
    explicit ScaleModel(std::uint32_t seed);

    void step(float dt_seconds, float motor_rpm);

    void add_mass(float grams) { true_mass_g_ += grams; }
    void clear_mass() { true_mass_g_ = 0.0f; }
    float true_mass_g() const { return true_mass_g_; }

    std::int32_t read_raw_counts();

    static constexpr float kCountsPerGram = 10.0f;

private:
    float true_mass_g_ = 0.0f;
    float drift_g_ = 0.0f;
    float vibration_rpm_ = 0.0f;
    std::mt19937 rng_;
    std::normal_distribution<float> noise_{0.0f, 0.4f};
};

} // namespace culina::sim
