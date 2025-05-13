#include<iostream>
#include<algorithm>
using namespace std;


int main(){
    std::vector<std::pair<int, int>> tasks = {{1, 3}, {2, 2}, {3, 1}, {4, 2}};
    sort(tasks.begin(), tasks.end(), [](const std::pair<int, int>& p1, const pair<int, int>& p2){
        return p1.second  > p2.second;
    });
    for(auto pr : tasks){
        cout<<"{"<<pr.first<<", "<<pr.second<<"}"<<std::endl;
    }
    return 0;
}