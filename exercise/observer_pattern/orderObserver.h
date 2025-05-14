#include<string>

class OrderObserver {
public:
    virtual void update(const std::string& status) = 0;
    virtual ~OrderObserver() = default;
};