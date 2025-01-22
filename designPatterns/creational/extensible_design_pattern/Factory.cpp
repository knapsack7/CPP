#include "Factory.h"
#include "IGameObject.h"
#include <iostream>
//Initialize our static
MyGameObjectFactory::callbackMap MyGameObjectFactory::objects;
void MyGameObjectFactory::registerObject(const std::string& type, createObjectCallback cb){
    objects[type] = cb;
}

// unregister a user created object type
// remove from our map

void MyGameObjectFactory::unregisterObject(const std::string& type){
    objects.erase(type);
}

// our previous 'Factory Method'

IGameObject* MyGameObjectFactory::createSingleObject(const std::string& type){
    callbackMap::iterator it = objects.find(type);
    if(it!=objects.end()){
        //call the callback function
        return (it->second)();
    } else {
        std::cout<<"OBJECT MISSING IN THE MAP"<<std::endl;
        return nullptr;
    }
}