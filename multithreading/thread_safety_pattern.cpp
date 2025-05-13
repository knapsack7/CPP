// Double-Checked Locking Pattern
class Singleton {
private:
    static std::atomic<Singleton*> instance;
    static std::mutex mtx;

public:
    static Singleton* getInstance() {
        // First check without lock
        Singleton* p = instance.load(std::memory_order_acquire);
        if (p == nullptr) {
            // Lock only if instance might be null
            std::lock_guard<std::mutex> lock(mtx);
            p = instance.load(std::memory_order_relaxed);
            if (p == nullptr) {
                p = new Singleton();
                instance.store(p, std::memory_order_release);
            }
        }
        return p;
    }
};