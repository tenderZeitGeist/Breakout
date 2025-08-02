
#include <Engine/PerformanceMetrics.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>

namespace {

constexpr std::size_t kTimingsSize = 1000;

std::tuple<double, double, double> calculateMetrics(const std::vector<double>& timings) {
    const auto min = *std::ranges::min_element(timings);
    const auto max = *std::ranges::max_element(timings);
    const auto average = std::reduce(timings.begin(), timings.end()) / timings.size();
    return {min, max, average};
}

}

PerformanceMetrics::~PerformanceMetrics() {
    writeResults("performance.txt");
}

void PerformanceMetrics::start(std::string_view identifier) {
    m_measurements[identifier].start = clock::now();
}

void PerformanceMetrics::stop(std::string_view identifier) {
    const auto now = clock::now();
    const auto& it = m_measurements.find(identifier);
    if (it == m_measurements.end()) {
        std::cerr << "Warning: Timer '" << identifier << "' not found" << '\n';
        return;
    }

    auto& [start, timings] = it->second;
    const auto duration = std::chrono::duration<double, std::nano>(now - start).count();
    timings.push_back(duration);
    if (timings.size() > kTimingsSize) {
        timings.erase(timings.begin());
    }
}

void PerformanceMetrics::writeResults(std::string_view fileName) {
    std::filesystem::path filePath{fileName};
    if (std::filesystem::exists(filePath)) {
        std::cerr << "Results file already exists. Overwriting." << '\n';
    }

    std::ofstream out(filePath);
    if (!out) {
        std::cerr << "Unable to write result at path (" << filePath << ")" << '\n';
        return;
    }

    for (const auto& [identifier, measurement] : m_measurements) {
        const auto& timings = measurement.timings;
        const auto [min, max, average] = calculateMetrics(timings);

        out << std::setw(12) << identifier << '\n' << "========================" << '\n';
        for (const auto& duration: timings) {
            out << std::right << std::setw(12) << duration << " ns" << '\n';
        }
        out << "========================" << '\n';
        out << std::setw(12) << "Summary:" << '\n'
            << " Min: " << std::setw(8) << min << " ns "
            << " Max: " << std::setw(8) << max << " ns "
            << " Average: " << std::setw(8) << average << " ns " << "\n\n";
    }
}

void PerformanceMetrics::print() {
    std::cout << "\nPerformance Metrics: " << '\n';
    std::cout << "====================" << '\n';

    for (const auto& [name, measurements] : m_measurements) {
        const auto& timings = measurements.timings;
        if (measurements.timings.empty()) {
            continue;
        }

        const auto [min, max, average] = calculateMetrics(timings);
        constexpr auto unit = " ns ";

        std::cout << std::left << std::setw(30) << name << ": Avg = " << std::setw(8) << average << unit
                  << "Min = " << std::setw(8) << min << unit << "Max = " << std::setw(8) << max << unit
                  << "Samples = " << timings.size() << "\n";
    }

    std::cout << "====================" << '\n';
}

void PerformanceMetrics::reset() {
    m_measurements.clear();
}
