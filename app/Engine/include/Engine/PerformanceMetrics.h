#include <chrono>
#include <string_view>
#include <unordered_map>

class PerformanceMetrics {
    using clock = std::chrono::high_resolution_clock;

    struct Measurements {
        clock::time_point start;
        std::vector<double> timings;
    };

public:
    ~PerformanceMetrics();
    void start(std::string_view identifier);
    void stop(std::string_view identifier);
    void writeResults(std::string_view fileName);
    void print();
    void reset();

private:
    std::unordered_map<std::string_view, Measurements> m_measurements;
};