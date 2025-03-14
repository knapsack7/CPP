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
    std::string spotId1 = solution.park(4, "MH01AB1234", "T12345", strategy::NEARESTFLOORFIRST);
    tf.runTest(!spotId1.empty(), "Solution park - 4-wheeler");
    tf.runTest(solution.getFreeSpotsCount(0, 4) == 1, "Solution park - updates free spots count");
    
    // Test parking another vehicle
    std::string spotId2 = solution.park(2, "MH01CD5678", "T67890", strategy::NEARESTFLOORFIRST);
    tf.runTest(!spotId2.empty(), "Solution park - 2-wheeler");
    
    // Test removing a vehicle by spot ID
    int removeStatus1 = solution.removeVehicle(spotId1, "", "");
    tf.runTest(removeStatus1 == 201, "Solution removeVehicle - by spot ID");
    tf.runTest(solution.getFreeSpotsCount(0, 4) == 2, "Solution removeVehicle - updates free spots count");
    
    // Test removing a vehicle by vehicle number
    solution.park(4, "MH01EF9012", "T24680", strategy::NEARESTFLOORFIRST);
    int removeStatus2 = solution.removeVehicle("", "MH01EF9012", "");
    tf.runTest(removeStatus2 == 201, "Solution removeVehicle - by vehicle number");
    
    // Test removing a vehicle by ticket ID
    solution.park(2, "MH01GH3456", "T13579", strategy::NEARESTFLOORFIRST);
    int removeStatus3 = solution.removeVehicle("", "", "T13579");
    tf.runTest(removeStatus3 == 201, "Solution removeVehicle - by ticket ID");
    
    // Test trying to remove a non-existent vehicle
    int removeStatus4 = solution.removeVehicle("", "INVALID", "");
    tf.runTest(removeStatus4 == 404, "Solution removeVehicle - non-existent vehicle");
    
    // Test fill all spots and try parking more
    solution.park(4, "Car1", "T1", strategy::NEARESTFLOORFIRST);
    solution.park(4, "Car2", "T2", strategy::NEARESTFLOORFIRST);
    solution.park(4, "Car3", "T3", strategy::NEARESTFLOORFIRST);
    solution.park(4, "Car4", "T4", strategy::NEARESTFLOORFIRST);
    std::string noSpot = solution.park(4, "Car5", "T5", strategy::NEARESTFLOORFIRST);
    tf.runTest(noSpot.empty(), "Solution park - no spots available returns empty string");
}


// Test ParkingStrategy implementations
void testParkingStrategy(TestFramework& tf) {
    std::cout << "\n----- Testing ParkingStrategy -----" << std::endl;
    
    // Create a test parking setup with multiple floors
    std::vector<std::vector<std::vector<std::string>>> parkingSetup = {
        // Floor 0 - 2 spots for 4-wheelers, 2 spots for 2-wheelers
        {
            {"41", "21", "00"},
            {"41", "21", "00"}
        },
        // Floor 1 - 3 spots for 4-wheelers, 1 spot for 2-wheelers
        {
            {"41", "41", "21"},
            {"41", "00", "00"}
        }
    };
    
    Solution solution(parkingSetup);
    
    // Test NearestFloorFirst strategy
    strategy nearestFloorStrategy = strategy::NEARESTFLOORFIRST;
    
    // Park a 4-wheeler using NearestFloorFirst strategy
    std::string spotId1 = solution.park(4, "MH01AB1234", "T12345", nearestFloorStrategy);
    // Should park in floor 0 (nearest floor)
    tf.runTest(spotId1[0] == '0', "NearestFloorFirst strategy - parks in nearest floor");
    
    // Park another 4-wheeler using NearestFloorFirst strategy
    std::string spotId2 = solution.park(4, "MH01CD5678", "T67890", nearestFloorStrategy);
    // Should still park in floor 0 as it has free spots
    tf.runTest(spotId2[0] == '0', "NearestFloorFirst strategy - continues to use nearest floor while spots available");
    
    // Fill remaining spots in floor 0
    solution.removeVehicle(spotId1, "", "");
    solution.removeVehicle(spotId2, "", "");
    
    // Test MostVacantSpot strategy
    strategy mostVacantStrategy = strategy::MOSTVACANTSPOT;
    
    // Floor 1 has more 4-wheeler spots than Floor 0
    std::string spotId3 = solution.park(4, "MH01EF9012", "T24680", mostVacantStrategy);
    // Should park in floor 1 (more vacant spots)
    tf.runTest(spotId3[0] == '1', "MostVacantSpot strategy - parks in floor with most vacant spots");
    
    // Park another vehicle with most vacant strategy
    std::string spotId4 = solution.park(4, "MH01GH3456", "T13579", mostVacantStrategy);
    // After the first vehicle is parked, both floors may have equal spots
    // Verify that the strategy selects a floor with the maximum vacant spots
    int floor0Spots = solution.getFreeSpotsCount(0, 4);
    int floor1Spots = solution.getFreeSpotsCount(1, 4);
    int selectedFloor = spotId4[0] - '0';
    int selectedFloorSpots = (selectedFloor == 0) ? floor0Spots : floor1Spots;
    int otherFloorSpots = (selectedFloor == 0) ? floor1Spots : floor0Spots;
    tf.runTest(selectedFloorSpots >= otherFloorSpots, "MostVacantSpot strategy - selects floor with maximum vacant spots");
    
    // Test with 2-wheelers (floor 0 has more 2-wheeler spots)
    std::string spotId5 = solution.park(2, "MH01IJ7890", "T97531", mostVacantStrategy);
    // Should park in floor 0 for 2-wheelers
    tf.runTest(spotId5[0] == '0', "MostVacantSpot strategy - correctly identifies floor with most spots for different vehicle types");
    
    // Test edge case: no available spots
    // Fill all 4-wheeler spots
    solution.park(4, "Car1", "T1", nearestFloorStrategy);
    solution.park(4, "Car2", "T2", nearestFloorStrategy);
    solution.park(4, "Car3", "T3", nearestFloorStrategy);
    // Try to park when all spots are full
    std::string noSpot = solution.park(4, "Car4", "T4", nearestFloorStrategy);
    tf.runTest(noSpot.empty(), "Parking strategies - handle no available spots correctly");
}


int main() {
    TestFramework tf;
    
    // Run all tests
    testParkingSpot(tf);
    testParkingFloor(tf);
    testSearchManager(tf);
    testSolution(tf);
    testParkingStrategy(tf);
    
    // Print test summary
    tf.printSummary();
    
    return 0;
}

