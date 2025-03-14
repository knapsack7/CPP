#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>

// Include the source to test
#include "sol1.cpp"

// Simple test framework
class TestFramework {
private:
    int passed = 0;
    int total = 0;

public:
    void runTest(bool condition, const std::string& testName) {
        total++;
        if (condition) {
            passed++;
            std::cout << "✓ " << testName << " - PASSED" << std::endl;
        } else {
            std::cout << "✗ " << testName << " - FAILED" << std::endl;
        }
    }

    void printSummary() {
        std::cout << "\n===== Test Summary =====" << std::endl;
        std::cout << "Passed: " << passed << "/" << total << std::endl;
        std::cout << "======================" << std::endl;
    }
};

// Test ParkingSpot class
void testParkingSpot(TestFramework& tf) {
    std::cout << "\n----- Testing ParkingSpot -----" << std::endl;
    
    // Test creation
    ParkingSpot spot("0-1-2", 4);
    tf.runTest(spot.getSpotId() == "0-1-2", "ParkingSpot initialization - spot ID");
    tf.runTest(spot.getVehicleType() == 4, "ParkingSpot initialization - vehicle type");
    tf.runTest(!spot.isParked(), "ParkingSpot initialization - not parked");
    
    // Test parking a vehicle
    spot.parkVehicle();
    tf.runTest(spot.isParked(), "ParkingSpot parkVehicle");
    
    // Test removing a vehicle
    spot.removeVehicle();
    tf.runTest(!spot.isParked(), "ParkingSpot removeVehicle");
}

// Test ParkingFloor class
void testParkingFloor(TestFramework& tf) {
    std::cout << "\n----- Testing ParkingFloor -----" << std::endl;
    
    // Create a test parking floor layout
    std::vector<std::vector<std::string>> floorLayout = {
        {"41", "21", "00"},
        {"41", "21", "00"},
        {"41", "21", "00"}
    };
    
    // Test initialization
    ParkingFloor floor(0, floorLayout);
    tf.runTest(floor.getFreeSpotsCount(4) == 3, "ParkingFloor initialization - 4-wheeler spots");
    tf.runTest(floor.getFreeSpotsCount(2) == 3, "ParkingFloor initialization - 2-wheeler spots");
    
    // Test parking a vehicle
    std::string spotId = floor.park(4);
    tf.runTest(!spotId.empty(), "ParkingFloor park - returned valid spot ID");
    tf.runTest(floor.getFreeSpotsCount(4) == 2, "ParkingFloor park - free spots count updated");
    
    // Parse the spot ID to get row and col
    int row = spotId[2] - '0';
    int col = spotId[4] - '0';
    
    // Test removing a vehicle
    int removeStatus = floor.removeVehicle(row, col);
    tf.runTest(removeStatus == 201, "ParkingFloor removeVehicle - status code");
    tf.runTest(floor.getFreeSpotsCount(4) == 3, "ParkingFloor removeVehicle - free spots count updated");
    
    // Test parking multiple vehicles
    floor.park(4);
    floor.park(4);
    floor.park(4);
    tf.runTest(floor.getFreeSpotsCount(4) == 0, "ParkingFloor park - all spots filled");
    
    // Test parking when no spots available
    std::string emptySpot = floor.park(4);
    tf.runTest(emptySpot.empty(), "ParkingFloor park - no spots available returns empty string");
}

// Test SearchManager class
void testSearchManager(TestFramework& tf) {
    std::cout << "\n----- Testing SearchManager -----" << std::endl;
    
    SearchManager searchManager;
    
    // Test indexing
    searchManager.index("0-1-2", "MH01AB1234", "T12345");
    
    // Test searching by vehicle number
    std::string spotByVehicle = searchManager.searchVehicle("MH01AB1234", "");
    tf.runTest(spotByVehicle == "0-1-2", "SearchManager search by vehicle number");
    
    // Test searching by ticket ID
    std::string spotByTicket = searchManager.searchVehicle("", "T12345");
    tf.runTest(spotByTicket == "0-1-2", "SearchManager search by ticket ID");
    
    // Test searching with invalid inputs
    std::string invalidSearch = searchManager.searchVehicle("", "");
    tf.runTest(invalidSearch.empty(), "SearchManager search with invalid inputs");
}

// Test Solution class (integration tests)
void testSolution(TestFramework& tf) {
    std::cout << "\n----- Testing Solution -----" << std::endl;
    
    // Create a test parking setup with multiple floors
    std::vector<std::vector<std::vector<std::string>>> parkingSetup = {
        // Floor 0
        {
            {"41", "21", "00"},
            {"41", "21", "00"}
        },
        // Floor 1
        {
            {"41", "21", "00"},
            {"41", "21", "00"}
        }
    };
    
    Solution solution(parkingSetup);
    
    // Test getting free spots count
    tf.runTest(solution.getFreeSpotsCount(0, 4) == 2, "Solution getFreeSpotsCount - floor 0, 4-wheelers");
    tf.runTest(solution.getFreeSpotsCount(0, 2) == 2, "Solution getFreeSpotsCount - floor 0, 2-wheelers");
    tf.runTest(solution.getFreeSpotsCount(1, 4) == 2, "Solution getFreeSpotsCount - floor 1, 4-wheelers");
    
    // Test parking a vehicle
    std::string spotId1 = solution.park(4, "MH01AB1234", "T12345");
    tf.runTest(!spotId1.empty(), "Solution park - 4-wheeler");
    tf.runTest(solution.getFreeSpotsCount(0, 4) == 1, "Solution park - updates free spots count");
    
    // Test parking another vehicle
    std::string spotId2 = solution.park(2, "MH01CD5678", "T67890");
    tf.runTest(!spotId2.empty(), "Solution park - 2-wheeler");
    
    // Test removing a vehicle by spot ID
    int removeStatus1 = solution.removeVehicle(spotId1, "", "");
    tf.runTest(removeStatus1 == 201, "Solution removeVehicle - by spot ID");
    tf.runTest(solution.getFreeSpotsCount(0, 4) == 2, "Solution removeVehicle - updates free spots count");
    
    // Test removing a vehicle by vehicle number
    solution.park(4, "MH01EF9012", "T24680");
    int removeStatus2 = solution.removeVehicle("", "MH01EF9012", "");
    tf.runTest(removeStatus2 == 201, "Solution removeVehicle - by vehicle number");
    
    // Test removing a vehicle by ticket ID
    solution.park(2, "MH01GH3456", "T13579");
    int removeStatus3 = solution.removeVehicle("", "", "T13579");
    tf.runTest(removeStatus3 == 201, "Solution removeVehicle - by ticket ID");
    
    // Test trying to remove a non-existent vehicle
    int removeStatus4 = solution.removeVehicle("", "INVALID", "");
    tf.runTest(removeStatus4 == 404, "Solution removeVehicle - non-existent vehicle");
    
    // Test fill all spots and try parking more
    solution.park(4, "Car1", "T1");
    solution.park(4, "Car2", "T2");
    solution.park(4, "Car3", "T3");
    solution.park(4, "Car4", "T4");
    std::string noSpot = solution.park(4, "Car5", "T5");
    tf.runTest(noSpot.empty(), "Solution park - no spots available returns empty string");
}

int main() {
    TestFramework tf;
    
    // Run all tests
    testParkingSpot(tf);
    testParkingFloor(tf);
    testSearchManager(tf);
    testSolution(tf);
    
    // Print test summary
    tf.printSummary();
    
    return 0;
}

