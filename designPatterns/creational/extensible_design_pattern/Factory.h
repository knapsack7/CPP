#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <map>
#include <string>

//Declare our one interface type

class IGameObject;

// Once change is that I have removed our 'enum class'
// This is bz during run-time I want to be able to
// create different types

class MyGameObjectFactory{
    // callback Function for creating an object
    typedef IGameObject *(*createObjectCallback)();
public:
    //Register a new user created object type
    //Again, we also have to pass in how to 'create' an object
    static void registerObject(const std::string& type, createObjectCallback cb);
    // Unregister a user created object type
    // remove from our map
    static void unregisterObject(const std::string& type);

    //Our previous 'Factory Method'
    static IGameObject* createSingleObject(const std::string& type);
private:
    // convenience typedef
    typedef std::map<std::string, createObjectCallback> callbackMap;
    // Map of all the different objects that we can create
    static callbackMap objects;
};

#endif