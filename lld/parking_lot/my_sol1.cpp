#include<iostream>
using namespace std;
class ParkingSpot{
private:
    string spot_id;
    int vehicle_type;
    bool is_spot_parked;
public: 
    ParkingSpot(string id, int type) : spot_id(id), vehicle_type(type), is_spot_parked(false){}
    bool is_parked(){return is_spot_parked;}
    void park_vehicle(){is_spot_parked = true;}
    void remove_vehicle(){is_spot_parked = false;}
    string get_spot_id(){return spot_id;}
    int get_vehicle_type(){return vehicle_type;}
};

class ParkingFloor{
private:
    vector<vector<ParkingSpot*>> parking_spots;
    unordered_map<int, int> free_spots_count;
    int floor_id;
public:
    ParkingFloor(int id, vector<vector<string>>& parking_floor){
        parking_spots.resize(parking_floor.size(), vector<ParkingSpot*>(parking_floor[0].size(), nullptr));
        floor_id = id;
        for (int row = 0; row < parking_floor.size(); ++row) {
            for (int col = 0; col < parking_floor[row].size(); ++col) {
                if (parking_floor[row][col].back() == '1') {
                    int vehicle_type = stoi(parking_floor[row][col].substr(0, 1));
                    parking_spots[row][col] = new ParkingSpot(to_string(floor_id) + "-" + to_string(row) + "-" + to_string(col), vehicle_type);
                    free_spots_count[vehicle_type]++;
                }
            }
        }
    }
    string park(int vehicle_type){
        if (free_spots_count[vehicle_type] == 0 ) return "";
        for (auto& row : parking_spots){
            for(auto& spot : row){
                if (spot && !spot->is_parked() == false && spot->get_vehicle_type() == vehicle_type){
                    spot->park_vehicle();
                    free_spots_count[vehicle_type]--;
                    return spot->get_spot_id();
                }
            }
        }
        return "";
    }
    int get_free_spots_count(int vehicle_type){
        return free_spots_count[vehicle_type];
    }
    int remove_vehicle(int row, int col){
        if (parking_spots[row][col] == nullptr || parking_spots[row][col]->is_parked() == false){
            return 404;
        }
        int parked_vehicle_type = parking_spots[row][col]->get_vehicle_type();
        free_spots_count[parked_vehicle_type]++;
        parking_spots[row][col]->remove_vehicle();
        return 200;
    }
};


class SearchManager{
private:
    unordered_map<string, string> cache;
public:
    string search_vehicle(string vehicle_number, string ticket_id){
        if(!vehicle_number.empty()) return cache[vehicle_number];
        if(!ticket_id.empty()) return cache[ticket_id];
        return "";
    }
    void index(string vehicle_number, string ticket_id, string spot_id){
        cache[vehicle_number] = spot_id;
        cache[ticket_id] = spot_id;
    }
};

class Solution{
private:
    vector<ParkingFloor*> floors;
    SearchManager search_manager;
public:
    Solution(vector<vector<vector<string>>>& parking){
        for(int floor = 0; floor < parking.size(); ++floor){
            floors.push_back(new ParkingFloor(floor, parking[floor]));
        }
    }
    string park(string vehicle_number, string ticket_id, int vehicle_type){
        for (auto& floor : floors) {
            string result_spot_id = floor->park(vehicle_type);
            if (!result_spot_id.empty()) {
                search_manager.index(vehicle_number, ticket_id, result_spot_id);
                return result_spot_id;
            }
        }
        return "";
    }
    int removeVehicle(string spot_id, string vehicle_number, string ticket_id) {
        string search_spot_id = !spot_id.empty() ? spot_id : search_manager.search_vehicle(vehicle_number, ticket_id);
        if (search_spot_id.empty()) return 404;
        
        int floor = search_spot_id[0] - '0';
        int row = search_spot_id[2] - '0';
        int col = search_spot_id[4] - '0';
        return floors[floor]->remove_vehicle(row, col);
    }

    int getFreeSpotsCount(int floor, int vehicle_type) {
        if (floor < 0 || floor >= floors.size()) return 0;
        return floors[floor]->get_free_spots_count(vehicle_type);
    }
};


int main(){
    return 0;
}