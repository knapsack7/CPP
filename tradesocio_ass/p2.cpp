#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

struct Order {
    int id;
    double price;
    int quantity;

    Order(int i, double p, int q) : id(i), price(p), quantity(q) {}
};

struct Tick {
    std::string symbol;
    double price;
    std::string timestamp;
};

class OrderBook {
public:
    void addOrder(int id, const std::string& symbol, const std::string& type, double price, int quantity) {
        std::lock_guard<std::mutex> lock(mtx);
        if (type == "BL") { // Buy Limit Order
            buyLimitOrders[symbol].push(Order(id, price, quantity));
        } else if (type == "SL") { // Sell Limit Order
            sellLimitOrders[symbol].push(Order(id, price, quantity));
        } else {
            throw std::invalid_argument("Unsupported order type");
        }
    }

    void newTick(const Tick& tick) {
        std::thread(&OrderBook::processTick, this, tick).detach(); // Create a new thread for each tick
    }

private:
    struct CompareBuyLimit {
        bool operator()(const Order& a, const Order& b) {
            return a.price < b.price; // Higher price has priority
        }
    };

    struct CompareSellLimit {
        bool operator()(const Order& a, const Order& b) {
            return a.price > b.price; // Lower price has priority
        }
    };

    std::unordered_map<std::string, std::priority_queue<Order, std::vector<Order>, CompareBuyLimit> > buyLimitOrders;
    std::unordered_map<std::string, std::priority_queue<Order, std::vector<Order>, CompareSellLimit> > sellLimitOrders;

    std::mutex mtx; // Mutex for protecting shared resources

    void processTick(const Tick& tick) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex for thread safety
        std::cout << "Processing Tick: Symbol=" << tick.symbol
                  << ", Price=" << tick.price
                  << ", Timestamp=" << tick.timestamp << "\n";

        processBuyLimitOrders(tick);
        processSellLimitOrders(tick);
    }

    void processBuyLimitOrders(const Tick& tick) {
        auto& heap = buyLimitOrders[tick.symbol];
        std::vector<Order> executedOrders;

        while (!heap.empty() && heap.top().price >= tick.price) {
            Order order = heap.top();
            heap.pop();
            executedOrders.push_back(order);
        }

        for (const auto& order : executedOrders) {
            std::cout << "Buy Limit Order " << order.id << " executed at " << tick.timestamp
                      << ", Price: " << tick.price
                      << ", Quantity: " << order.quantity << "\n";
        }
    }

    void processSellLimitOrders(const Tick& tick) {
        auto& heap = sellLimitOrders[tick.symbol];
        std::vector<Order> executedOrders;

        while (!heap.empty() && heap.top().price <= tick.price) {
            Order order = heap.top();
            heap.pop();
            executedOrders.push_back(order);
        }

        for (const auto& order : executedOrders) {
            std::cout << "Sell Limit Order " << order.id << " executed at " << tick.timestamp
                      << ", Price: " << tick.price
                      << ", Quantity: " << order.quantity << "\n";
        }
    }
};

// Example Usage
int main() {
    OrderBook orderBook;

    // Adding Pending Orders
    orderBook.addOrder(1, "AAPL", "BL", 100, 10);  // Order 1
    orderBook.addOrder(2, "AAPL", "BL", 105, 5);   // Order 2
    orderBook.addOrder(3, "AAPL", "BL", 102, 15);  // Order 3
    orderBook.addOrder(4, "AAPL", "BL", 98, 15);   // Order 4
    orderBook.addOrder(5, "GOOG", "BL", 200, 10);  // Order 5
    orderBook.addOrder(6, "GOOG", "BL", 201, 15);  // Order 6
    orderBook.addOrder(7, "GOOG", "BL", 198, 10);  // Order 7

    // Ticks
    std::vector<Tick> ticks = {
        {"AAPL", 106, "08:58"},  // No orders executed
        {"AAPL", 104, "09:00"},  // Order 2 executed
        {"AAPL", 102, "09:01"},  // Order 3 executed
        {"AAPL", 98, "09:02"},   // Order 1 and Order 4 executed
        {"GOOG", 200, "09:03"}   // Order 6 executed
    };

    // Measure start time
    auto start = std::chrono::high_resolution_clock::now();

    // Process Ticks
    for (const auto& tick : ticks) {
        orderBook.newTick(tick);
    }

    // Sleep for a while to allow all threads to finish
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Measure end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds.\n";    
    
    return 0;
}
