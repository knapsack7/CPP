#include "order.h"
using namespace std;

int main() {
    unique_ptr<Order> order = make_unique<Order>();
    unique_ptr<Customer> customer = make_unique<Customer>();
    unique_ptr<Seller> seller = make_unique<Seller>();
    unique_ptr<Logistics> logistics =  make_unique<Logistics>();

    order->addObserver(std::move(customer));
    order->addObserver(std::move(seller));
    order->addObserver(std::move(logistics));

    order->updateStatus("Shipped");  // Notifies all observers

    return 0;
}