#include <iostream>
#include <memory>

// Subsystems
class Light {
public:
    void turnOn() const {
        std::cout << "Lights are turned ON" << std::endl;
    }

    void turnOff() const {
        std::cout << "Lights are turned OFF" << std::endl;
    }
};

class MusicSystem {
public:
    void playMusic() const {
        std::cout << "Playing music" << std::endl;
    }

    void stopMusic() const {
        std::cout << "Music stopped" << std::endl;
    }
};

class SecuritySystem {
public:
    void arm() const {
        std::cout << "Security system armed" << std::endl;
    }

    void disarm() const {
        std::cout << "Security system disarmed" << std::endl;
    }
};

// Facade Class
class HomeAutomationFacade {
private:
    std::shared_ptr<Light> light;
    std::shared_ptr<MusicSystem> musicSystem;
    std::shared_ptr<SecuritySystem> securitySystem;

public:
    HomeAutomationFacade()
        : light(std::make_shared<Light>()),
          musicSystem(std::make_shared<MusicSystem>()),
          securitySystem(std::make_shared<SecuritySystem>()) {}

    void startDay() const {
        light->turnOn();
        musicSystem->playMusic();
        securitySystem->disarm();
        std::cout << "Good morning! Your home is ready." << std::endl;
    }

    void endDay() const {
        musicSystem->stopMusic();
        light->turnOff();
        securitySystem->arm();
        std::cout << "Good night! Your home is secure." << std::endl;
    }
};

// Client Code
int main() {
    HomeAutomationFacade home;

    std::cout << "Starting the day..." << std::endl;
    home.startDay();

    std::cout << "\nEnding the day..." << std::endl;
    home.endDay();

    return 0;
}

