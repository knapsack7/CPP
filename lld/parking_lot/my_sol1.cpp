#include <iostream>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <thread>
using namespace std;

class ParkingSpot {
private:
    string spot_id;
    int vehicle_type;
    bool is_spot_parked;

public:
    ParkingSpot(string id, int type) : spot_id(id), vehicle_type(type), is_spot_parked(false) {}

    bool isParked() { return is_spot_parked; }
    void parkVehicle() { is_spot_parked = true; }
    void removeVehicle() { is_spot_parked = false; }
    string getSpotId() { return spot_id; }
    int getVehicleType() { return vehicle_type; }
};

class ParkingFloor {
private:
    vector<vector<unique_ptr<ParkingSpot>>> parking_spots;
    unordered_map<int, int> free_spots_count;
    int floor_id;
    std::mutex floor_mutex;

public:
    ParkingFloor(int floor, vector<vector<string>>& parking_floor) {
        parking_spots.resize(parking_floor.size()); 
        for (size_t i = 0; i < parking_spots.size(); i++) {
            parking_spots[i].resize(parking_floor[i].size());
        }
        floor_id = floor;
        for (int row = 0; row < parking_floor.size(); ++row) {
            for (int col = 0; col < parking_floor[row].size(); ++col) {
                if (parking_floor[row][col].back() == '1') {
                    int vehicle_type = stoi(parking_floor[row][col].substr(0, 1));
                    parking_spots[row][col] = make_unique<ParkingSpot>(to_string(floor_id) + "-" + to_string(row) + "-" + to_string(col), vehicle_type);
                    free_spots_count[vehicle_type]++;
                }
            }
        }
    }

    int getFreeSpotsCount(int vehicle_type) {
        return free_spots_count[vehicle_type];
    }

    int removeVehicle(int row, int col) {
        std::lock_guard<std::mutex> lock(floor_mutex);
        if (!parking_spots[row][col] || !parking_spots[row][col]->isParked()) {
            return 404;
        }
        int parked_vehicle_type = parking_spots[row][col]->getVehicleType();
        parking_spots[row][col]->removeVehicle();
        free_spots_count[parked_vehicle_type]++;
        return 201;
    }

    string park(int vehicle_type) {
        std::lock_guard<std::mutex> lock(floor_mutex);
        if (free_spots_count[vehicle_type] == 0) return "";
        for (auto& row : parking_spots) {
            for (auto& spot : row) {
                if (spot && !spot->isParked() && spot->getVehicleType() == vehicle_type) {
                    free_spots_count[vehicle_type]--;
                    spot->parkVehicle();
                    return spot->getSpotId();
                }
            }
        }
        return "";
    }
};

class SearchManager {
private:
    unordered_map<string, string> cache;
    std::mutex cache_mutex;

public:
    string searchVehicle(string vehicle_number, string ticket_id) {
        std::lock_guard<std::mutex> lock(cache_mutex);
        if (!vehicle_number.empty()) return cache[vehicle_number];
        if (!ticket_id.empty()) return cache[ticket_id];
        return "";
    }
    void index(string spot_id, string vehicle_number, string ticket_id) {
        std::lock_guard<std::mutex> lock(cache_mutex);
        cache[vehicle_number] = spot_id;
        cache[ticket_id] = spot_id;
    }
};

class ParkingStrategy{
public:
    virtual shared_ptr<ParkingFloor> strategy(vector<shared_ptr<ParkingFloor>>& floors, int vehicle_type) = 0;
};

enum class strategy {
    NEARESTFLOORFIRST = 0,
    MOSTVACANTSPOT
};

class NearestFloorFirst : public ParkingStrategy{
public:
    shared_ptr<ParkingFloor> strategy(vector<shared_ptr<ParkingFloor>>& floors, int vehicle_type) override {
        for (auto& floor : floors) {
            int free_spot_count = floor->getFreeSpotsCount(vehicle_type);
            if (free_spot_count) {
                return floor;
            }
        }
        return nullptr;
    }
};

class MostVacantSpot : public ParkingStrategy{
public:
    shared_ptr<ParkingFloor> strategy(vector<shared_ptr<ParkingFloor>>& floors, int vehicle_type) override {
        shared_ptr<ParkingFloor> floor_with_max_free_spot = nullptr;
        int max_free_spot_count = 0;
        for (auto& floor : floors) {
            int free_spot_count = floor->getFreeSpotsCount(vehicle_type);
            if(free_spot_count > max_free_spot_count) {
                floor_with_max_free_spot = floor;
                max_free_spot_count = free_spot_count;
            }
        }
        return floor_with_max_free_spot;
    }
};

class Solution {
private:
    vector<shared_ptr<ParkingFloor>> floors;
    SearchManager search_manager;
    shared_ptr<ParkingStrategy> parking_strategy;
public:
    Solution(vector<vector<vector<string>>>& parking) {
        for (int i = 0; i < parking.size(); ++i) {
            floors.push_back(make_shared<ParkingFloor>(i, parking[i]));
        }
    }

    string park(int vehicle_type, string vehicle_number, string ticket_id, strategy strat) {
        shared_ptr<ParkingFloor> floor_to_park = nullptr; 
        if (strat == strategy::MOSTVACANTSPOT){
            parking_strategy = make_shared<MostVacantSpot>();
            
        }
        else {
            parking_strategy = make_shared<NearestFloorFirst>();
        }
        if (parking_strategy == nullptr){
            cout<<"Parking strategy can't be applied\n";
            return "";
        }
        floor_to_park = parking_strategy->strategy(floors, vehicle_type);
        string result_spot_id = floor_to_park->park(vehicle_type);
        if (!result_spot_id.empty()) {
            search_manager.index(result_spot_id, vehicle_number, ticket_id);
            return result_spot_id;
        }
        return "";
    }

    int removeVehicle(string spot_id, string vehicle_number, string ticket_id) {
        string search_spot_id = !spot_id.empty() ? spot_id : search_manager.searchVehicle(vehicle_number, ticket_id);
        if (search_spot_id.empty()) return 404;
        
        int floor = search_spot_id[0] - '0';
        int row = search_spot_id[2] - '0';
        int col = search_spot_id[4] - '0';
        return floors[floor]->removeVehicle(row, col);
    }

    int getFreeSpotsCount(int floor, int vehicle_type) {
        if (floor < 0 || floor >= floors.size()) return 0;
        return floors[floor]->getFreeSpotsCount(vehicle_type);
    }
};

int main() {
    // Initialize parking lot
    std::vector<std::vector<std::vector<std::string>>> parking = {
        {{"1-1", "2-1"}, {"1-1", "2-1"}},
        {{"1-1", "2-1"}, {"1-1", "2-1"}}
    };
    Solution solution(parking);

    // Create threads for parking and removing vehicles
    std::thread t1(&Solution::park, &solution, 1, "ABC123", "TICKET1", strategy::NEARESTFLOORFIRST);
    std::thread t2(&Solution::park, &solution, 2, "XYZ456", "TICKET2", strategy::MOSTVACANTSPOT);
    std::thread t3(&Solution::park, &solution, 1, "ABC123", "TICKET1", strategy::NEARESTFLOORFIRST);

    // Join threads
    t1.join();
    t2.join();
    t3.join();

    return 0;
}