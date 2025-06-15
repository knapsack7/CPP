#include <iostream>
#include <set>

int main(){
    std::set<std::string> names{"Manoj", "Kumar", "Verma"};
    auto it = names.find("Kumar");


    // auto name =  *it;
    // name[0] = 'U';
    // names.erase(it);
    // names.insert(name);
    // for(auto &name : names){
    //     std::cout << name << " ";
    // }


    // c++ 20 feature
    auto node = names.extract(it);
    node.value()[0] = 'U';
    names.insert(std::move(node));
    for(auto &name : names){
        std::cout << name << " ";
    }
    std::cout << "\n";
    return 0;
}