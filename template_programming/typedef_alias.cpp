#include <iostream>
#include <list>
#include <vector>
#include <string>


/*
 * Type Definition (typedef)
 *  Introduces a name for an existing type
 *  this name becomes a synonym of that type
 *  useful to construct shorter or more meaningful names for existing types
 *  simplifies declaration of some types(e.g. function pointers & templates)
 *  Implementation details that may change can be encapsulated
 * Examples:
 *  typedef unsigned int UINT;
 *  UINT val{};
 * 
 * typedef long long LLONG;
 * LLONG val{};
 * 
 * typedef std::vector<std::list<Employee>> Teams;
 * Teams testingteams;
 * Teams::iterator it = testingteams.begin();
 * 
 * typedef const char* (&func)(int, int);;
 * func f = GetErrorFunction;
 */



/*
 * Type ALIAS
 *  creates a name that is synonym of existing type
 *  does not introduce a new type
 *  same as a typedef declaration
 *  created through the using keyword
 * 
 * Examples:
 *  using UINT = unsigned int;
 *  using LLONG = long long;
 *  using Teams = std::vector<std::list<Employee>>;
 *  using func = const char* (&)(int, int);
 *  func f = GetErrorFunction;
 * 
 */


const char* GetErrorFunction(int a, int b){
    return "Error";
}

//typedef const char* (*func)(int, int);
using func = const char* (*)(int, int);
void showError(func f){}

typedef std::vector < std::list<std::string> > names;

// we cant templatise the typedef 
// but we can use the using keyword to create a type alias
// for a template


template<typename T>
using names = std::vector<std::list<T>>;


int main(){
    //names<Player> players;
    names<std::string> nameList;
    names<names<std::string>> nestedNames;
    func f = GetErrorFunction;
    showError(f);
    return 0;
}