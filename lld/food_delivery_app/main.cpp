#include "TomatoApp.h"
#include <iostream>

using namespace std;

int main() {
    // Create a new user
    User* user = new User(1, "John Doe", "123 Main St, Delhi");
    
    // Initialize the application
    TomatoApp app;
    
    // Search for restaurants in Delhi
    cout << "Searching restaurants in Delhi..." << endl;
    vector<Restaurant*> delhiRestaurants = app.searchRestaurants("Delhi");
    
    if (delhiRestaurants.empty()) {
        cout << "No restaurants found in Delhi" << endl;
        return 1;
    }
    
    // Select the first restaurant
    cout << "\nSelecting restaurant: " << delhiRestaurants[0]->getName() << endl;
    app.selectRestaurant(user, delhiRestaurants[0]);
    
    // Add items to cart
    cout << "\nAdding items to cart..." << endl;
    app.addToCart(user, "P1");  // Chole Bhature
    app.addToCart(user, "P2");  // Samosa
    
    // Print cart contents
    cout << "\nCart contents:" << endl;
    app.printUserCart(user);
    
    // Create payment strategy
    PaymentStrategy* paymentStrategy = new UpiPaymentStrategy("john@upi");
    
    // Checkout with delivery order
    cout << "\nProcessing order..." << endl;
    Order* order = app.checkoutNow(user, "DELIVERY", paymentStrategy);
    
    if (order) {
        // Process payment
        cout << "\nProcessing payment..." << endl;
        app.payForOrder(user, order);
        
        cout << "\nOrder completed successfully!" << endl;
    } else {
        cout << "Failed to create order" << endl;
    }
    
    // Cleanup
    delete user;
    delete paymentStrategy;
    
    return 0;
} 