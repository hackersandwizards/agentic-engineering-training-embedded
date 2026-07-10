#include "app/telemetry_store.h"

#include <gtest/gtest.h>

#include <thread>

namespace {

using culina::app::TelemetryStore;

TelemetryStore::Sample sample_at(culina::Millis t_ms, float celsius) {
    TelemetryStore::Sample s;
    s.t_ms = t_ms;
    s.deci_celsius = culina::from_celsius(celsius);
    return s;
}

TEST(TelemetryStore, EmptyStoreIsSafe) {
    TelemetryStore store;
    EXPECT_FALSE(store.has_data());
    EXPECT_EQ(store.average_temp_c(1000), 0.0f);
    EXPECT_EQ(store.latest().rpm, 0u);
}

TEST(TelemetryStore, LatestReturnsNewestSample) {
    TelemetryStore store;
    store.append(sample_at(10, 20.0f));
    store.append(sample_at(20, 21.0f));
    EXPECT_EQ(store.latest().t_ms, 20u);
    EXPECT_EQ(store.size(), 2u);
}

TEST(TelemetryStore, AverageRespectsTheWindow) {
    TelemetryStore store;
    for (culina::Millis t = 100; t <= 1000; t += 100) {
        store.append(sample_at(t, t <= 700 ? 50.0f : 80.0f));
    }
    // Window of 300 ms ending at t=1000 covers t=700..1000: 50, 80, 80, 80.
    EXPECT_NEAR(store.average_temp_c(300), (50.0f + 80.0f * 3.0f) / 4.0f, 0.01f);
    // A window longer than the history covers everything.
    EXPECT_NEAR(store.average_temp_c(60000), (50.0f * 7 + 80.0f * 3) / 10.0f, 0.01f);
}

TEST(TelemetryStore, MaxTempFindsThePeakInWindow) {
    TelemetryStore store;
    store.append(sample_at(100, 90.0f));
    store.append(sample_at(200, 61.5f));
    store.append(sample_at(300, 55.0f));
    EXPECT_NEAR(store.max_temp_c(150), 61.5f, 0.01f);
    EXPECT_NEAR(store.max_temp_c(60000), 90.0f, 0.01f);
}

TEST(TelemetryStore, SurvivesConcurrentProducerAndReader) {
    TelemetryStore store;
    for (culina::Millis t = 0; t < 10000; ++t) {
        store.append(sample_at(t, 20.0f));
    }
    std::thread producer([&store] {
        for (culina::Millis t = 10000; t < 10100; ++t) {
            store.append(sample_at(t, 60.0f));
        }
    });
    float last_avg = 0.0f;
    for (int i = 0; i < 200; ++i) {
        last_avg = store.average_temp_c(5000);
    }
    producer.join();
    EXPECT_GT(last_avg, 0.0f);
    EXPECT_EQ(store.size(), 10100u);
}

} // namespace
