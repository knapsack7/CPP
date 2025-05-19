#ifndef WEBPAGE_COUNTER_H
#define WEBPAGE_COUNTER_H

#include <array>
#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

// Forward declarations
class ILogger;

// Configuration structure
struct Config {
    bool enableLogging = true;
    bool useAtomicOperations = false;
    size_t maxPages = 1000;
};

// Metrics structure
struct Metrics {
    std::atomic<size_t> totalIncrements{0};
    std::atomic<size_t> totalQueries{0};
    std::atomic<size_t> errorCount{0};

    Metrics() = default;
    Metrics(const Metrics& other);
    Metrics& operator=(const Metrics& other);
};

// WebpageCounter class declaration
class WebpageCounter {
private:
    static constexpr size_t MAX_PAGES = 1000;
    std::array<std::atomic<size_t>, MAX_PAGES> visitCounts;
    std::array<std::unique_ptr<std::mutex>, MAX_PAGES> mutexes;
    std::shared_ptr<ILogger> logger;
    size_t totalPages;
    mutable Metrics metrics;
    Config config;

public:
    WebpageCounter(size_t totalPages, std::shared_ptr<ILogger> logger, const Config& config = Config{});
    void incrementVisitCount(size_t pageIndex);
    void batchIncrement(const std::vector<size_t>& indices);
    size_t getVisitCount(size_t pageIndex) const;
    Metrics getMetrics() const;
    void reset();
};

#endif // WEBPAGE_COUNTER_H 