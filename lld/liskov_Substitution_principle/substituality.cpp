#include <iostream>

using namespace std;


class Router{
    public:
        Router() = default;
        virtual void transmit() = 0;
        virtual ~Router() = default;
};


class Router2G: public Router{
    public:
        Router2G() = default;
        void transmit() override{
            cout << "Transmitting data at 2G speed" << endl;
        }

};

class Router5G: public Router{
    public:
        Router5G() = default;
        void transmit() override{
            cout << "Transmitting data at 5G speed" << endl;
        }
};

class Router6G: public Router{
    public:
        Router6G() = default;
        void transmit() override{
            cout << "Transmitting data at 6G speed" << endl;
        }
};

int main(){
    Router* router = new Router2G();
    router->transmit();
    router = new Router5G();
    router->transmit();
    router = new Router6G();
    router->transmit();
    delete router;
}

