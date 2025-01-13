#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <memory>
#include <chrono>
#include <random>

// Third-party library
#include <SFML/Graphics.hpp>

// Global variables
static std::vector<int> grid;               // Grid representing cell states
std::vector<std::unique_ptr<sf::Shape>> shapes; // Shapes representing grid cells
bool isRunning = true;                      // Flag for program execution
std::mutex gridMutex;                       // Mutex for thread-safe grid updates

const int gridWidth = 4;                    // Grid width
const int gridHeight = 4;                   // Grid height
const int cellSize = 100;                   // Cell size in pixels

// Function to update grid cells
void update_grid(int x, int y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Safely update the grid
        {
            std::lock_guard<std::mutex> lock(gridMutex);
            grid[y * gridWidth + x] = dist(gen);
        }
    }
}

int main() {
    // Initialize the grid with default values
    grid.resize(gridWidth * gridHeight, 0);

    // Create shapes for each grid cell
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(cellSize, cellSize));
            shape->setPosition(sf::Vector2f(x * cellSize, y * cellSize)); // Fix here
            shape->setOutlineThickness(1);
            shape->setOutlineColor(sf::Color::Black);
            shapes.push_back(std::move(shape));
        }
    }

    // Launch threads to update each grid cell
    std::vector<std::thread> threads;
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            threads.emplace_back(update_grid, x, y);
        }
    }

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(gridWidth * cellSize, gridHeight * cellSize)), "Enhanced SFML Grid");
    window.setFramerateLimit(60);

    // Main game loop
    while (window.isOpen() && isRunning) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                isRunning = false;
            } else if (event->is<sf::Event::MouseButtonPressed>()) {
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == sf::Mouse::Button::Left) {
                        // Get mouse position and toggle cell color
                        int x = mouseEvent->position.x / cellSize;
                        int y = mouseEvent->position.y / cellSize;
                        
                        if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                            std::lock_guard<std::mutex> lock(gridMutex);
                            grid[y * gridWidth + x] = (grid[y * gridWidth + x] + 1) % 4;
                        }
                    }
                }
            }
        }

        // Render the grid
        window.clear();
        {
            std::lock_guard<std::mutex> lock(gridMutex);
            for (int y = 0; y < gridHeight; ++y) {
                for (int x = 0; x < gridWidth; ++x) {
                    int index = y * gridWidth + x;

                    // Set color based on grid value
                    switch (grid[index]) {
                        case 0: shapes[index]->setFillColor(sf::Color::Red); break;
                        case 1: shapes[index]->setFillColor(sf::Color::Green); break;
                        case 2: shapes[index]->setFillColor(sf::Color::Blue); break;
                        case 3: shapes[index]->setFillColor(sf::Color::White); break;
                    }

                    window.draw(*shapes[index]);
                }
            }
        }
        window.display();
    }

    // Join all threads before program exits
    for (auto& th : threads) {
        th.join();
    }

    std::cout << "Program Terminating" << std::endl;
    return 0;
}