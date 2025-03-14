#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <atomic>
#include <mutex>

using namespace std;

class ParkingResult {
public:
    int status;
    string spotId, vehicleNumber, ticketId;

    ParkingResult() : status(404), spotId(""), vehicleNumber(""), ticketId("") {}

    ParkingResult(int status, string spotId, string vehicleNumber, string ticketId)
        : status(status), spotId(spotId), vehicleNumber(vehicleNumber), ticketId(ticketId) {}
};

class Helper01 {
public:
    void print(const string& s) { cout << s; }
    void println(const string& s) { cout << s << endl; }
    
    string getSpotId(int floor, int row, int column) {
        return to_string(floor) + "-" + to_string(row) + "-" + to_string(column);
    }
    
    vector<int> getSpotLocation(const string& spotId) {
        vector<int> location(3, -1);
        sscanf(spotId.c_str(), "%d-%d-%d", &location[0], &location[1], &location[2]);
        return location;
    }
};

class ParkingSpot {
    string spotId;
    int vehicleType;
    bool isParked;

public:
    ParkingSpot(string spotId, int vehicleType) : spotId(spotId), vehicleType(vehicleType), isParked(false) {}
    
    bool isOccupied() { return isParked; }
    void parkVehicle() { isParked = true; }
    void removeVehicle() { isParked = false; }
    string getSpotId() { return spotId; }
    int getVehicleType() { return vehicleType; }
};

class ParkingFloor {
    unordered_map<int, atomic<int>> freeSpotsCount;
    vector<vector<ParkingSpot*>> parkingSpots;
    
public:
    ParkingFloor(int floor, vector<vector<string>>& parkingFloor, vector<int>& vehicleTypes, Helper01& helper) {
        parkingSpots.resize(parkingFloor.size(), vector<ParkingSpot*>(parkingFloor[0].size(), nullptr));
        for (int type : vehicleTypes) freeSpotsCount[type] = 0;
        
        for (int row = 0; row < parkingFloor.size(); row++) {
            for (int col = 0; col < parkingFloor[row].size(); col++) {
                if (parkingFloor[row][col].back() == '1') {
                    int vehicleType = stoi(parkingFloor[row][col].substr(0, 1));
                    parkingSpots[row][col] = new ParkingSpot(helper.getSpotId(floor, row, col), vehicleType);
                    freeSpotsCount[vehicleType]++;
                }
            }
        }
    }
    
    int getFreeSpotsCount(int vehicleType) {
        return freeSpotsCount[vehicleType].load();
    }
    
    int removeVehicle(int row, int col) {
        if (!parkingSpots[row][col] || !parkingSpots[row][col]->isOccupied()) return 404;
        parkingSpots[row][col]->removeVehicle();
        freeSpotsCount[parkingSpots[row][col]->getVehicleType()]++;
        return 201;
    }
    
    ParkingResult park(int vehicleType, string vehicleNumber, string ticketId) {
        for (auto& row : parkingSpots) {
            for (auto& spot : row) {
                if (spot && !spot->isOccupied() && spot->getVehicleType() == vehicleType) {
                    freeSpotsCount[vehicleType]--;
                    spot->parkVehicle();
                    return ParkingResult(201, spot->getSpotId(), vehicleNumber, ticketId);
                }
            }
        }
        return ParkingResult(404, "", vehicleNumber, ticketId);
    }
};

class SearchManager {
    unordered_map<string, ParkingResult> cache;
    
public:
    ParkingResult searchVehicle(string spotId, string vehicleNumber, string ticketId) {
        if (!spotId.empty() && cache.count(spotId)) return cache[spotId];
        if (!vehicleNumber.empty() && cache.count(vehicleNumber)) return cache[vehicleNumber];
        if (!ticketId.empty() && cache.count(ticketId)) return cache[ticketId];
        return ParkingResult(404, spotId, vehicleNumber, ticketId);
    }
    
    void index(ParkingResult result) {
        cache[result.spotId] = result;
        cache[result.vehicleNumber] = result;
        cache[result.ticketId] = result;
    }
};

class Solution {
    Helper01* helper;
    vector<ParkingFloor*> floors;
    SearchManager searchManager;
    vector<int> vehicleTypes = {2, 4};
    
public:
    void init(Helper01* helper, vector<vector<vector<string>>>& parking) {
        this->helper = helper;
        for (int i = 0; i < parking.size(); i++)
            floors.push_back(new ParkingFloor(i, parking[i], vehicleTypes, *helper));
    }
    
    ParkingResult park(int vehicleType, string vehicleNumber, string ticketId) {
        for (auto& floor : floors) {
            ParkingResult result = floor->park(vehicleType, vehicleNumber, ticketId);
            if (result.status == 201) {
                searchManager.index(result);
                return result;
            }
        }
        return ParkingResult(404, "", vehicleNumber, ticketId);
    }
    
    int removeVehicle(string spotId, string vehicleNumber, string ticketId) {
        ParkingResult search = searchManager.searchVehicle(spotId, vehicleNumber, ticketId);
        if (search.status >= 400) return 404;
        vector<int> location = helper->getSpotLocation(search.spotId);
        return floors[location[0]]->removeVehicle(location[1], location[2]);
    }
    
    int getFreeSpotsCount(int floor, int vehicleType) {
        if (floor < 0 || floor >= floors.size()) return 0;
        return floors[floor]->getFreeSpotsCount(vehicleType);
    }
    
    ParkingResult searchVehicle(string spotId, string vehicleNumber, string ticketId) {
        return searchManager.searchVehicle(spotId, vehicleNumber, ticketId);
    }
};

int main() {
    // Create a helper object
    Helper01 helper;
    
    // Define a simple parking structure with 2 floors
    // Format: floor -> row -> column -> "vehicleType+availability"
    // For example "21" means a spot for vehicle type 2 and it's available (1)
    vector<vector<vector<string>>> parkingStructure = {
        { // Floor 0
            {"21", "21", "41"}, 
            {"21", "41", "41"}
        },
        { // Floor 1
            {"21", "41", "41"}, 
            {"21", "21", "41"}
        }
    };
    
    // Create and initialize Solution object
    Solution parkingLot;
    parkingLot.init(&helper, parkingStructure);
    
    // Display initial free spots count
    helper.println("Initial free spots count:");
    helper.println("Floor 0, 2-wheelers: " + to_string(parkingLot.getFreeSpotsCount(0, 2)));
    helper.println("Floor 0, 4-wheelers: " + to_string(parkingLot.getFreeSpotsCount(0, 4)));
    helper.println("Floor 1, 2-wheelers: " + to_string(parkingLot.getFreeSpotsCount(1, 2)));
    helper.println("Floor 1, 4-wheelers: " + to_string(parkingLot.getFreeSpotsCount(1, 4)));
    
    // Park some vehicles
    helper.println("\nParking vehicles:");
    ParkingResult result1 = parkingLot.park(2, "KA01HH1234", "T001");
    if (result1.status == 201) {
        helper.println("Successfully parked 2-wheeler with number KA01HH1234 at spot " + result1.spotId);
    } else {
        helper.println("Failed to park 2-wheeler with number KA01HH1234");
    }
    
    ParkingResult result2 = parkingLot.park(4, "KA01MH5678", "T002");
    if (result2.status == 201) {
        helper.println("Successfully parked 4-wheeler with number KA01MH5678 at spot " + result2.spotId);
    } else {
        helper.println("Failed to park 4-wheeler with number KA01MH5678");
    }
    
    // Display updated free spots count
    helper.println("\nUpdated free spots count:");
    helper.println("Floor 0, 2-wheelers: " + to_string(parkingLot.getFreeSpotsCount(0, 2)));
    helper.println("Floor 0, 4-wheelers: " + to_string(parkingLot.getFreeSpotsCount(0, 4)));
    
    // Search for a parked vehicle
    helper.println("\nSearching for vehicle:");
    ParkingResult searchResult = parkingLot.searchVehicle("", "KA01HH1234", "");
    if (searchResult.status == 201) {
        helper.println("Found vehicle KA01HH1234 at spot " + searchResult.spotId);
    } else {
        helper.println("Vehicle KA01HH1234 not found");
    }
    
    // Remove a parked vehicle
    helper.println("\nRemoving vehicle:");
    int removeStatus = parkingLot.removeVehicle("", "KA01HH1234", "");
    if (removeStatus == 201) {
        helper.println("Successfully removed vehicle KA01HH1234");
    } else {
        helper.println("Failed to remove vehicle KA01HH1234");
    }
    
    // Check free spots count after removal
    helper.println("\nFree spots count after removal:");
    helper.println("Floor 0, 2-wheelers: " + to_string(parkingLot.getFreeSpotsCount(0, 2)));
    
    return 0;
}
