// @directory extensible
// g++ -std=c++17 main.cpp IGameObjects.cpp Factory.cpp -o prog
#include <vector>
#include <memory>
#include <fstream>
#include <string>

#include "Factory.h"
#include "IGameObject.h"

// for fun, create a new type

class Ant : public IGameObject{
public:
    Ant(int x, int y){}
    
    void objectPlayDefaultAnimation(){/*......*/}
	void objectMoveInGame() {/*......*/}
	void update() {/*......*/}
	void render() {/*.......*/}
	static IGameObject* create() {	
		return new Ant(0, 0);
	}
private:
	static int objectsCreated;
};

int Ant::objectsCreated = 0;

int main() {
    //Register a different type
    MyGameObjectFactory::registerObject("plane", Plane::create);
    MyGameObjectFactory::registerObject("boat", Boat::create);
    MyGameObjectFactory::registerObject("ant", Ant::create);

    std::vector<IGameObject*> gameObjectCollection;

    // Add the correct object to our collection
    // based on a .txt file

    std::string line;
    std::ifstream myFile("level1.txt");
    if(myFile.is_open()){
        while(std::getline(myFile, line)){
            // for each line that is read in, then create a game object for that type
            IGameObject* object = MyGameObjectFactory::createSingleObject(line);
            //Add the object to the collection
            gameObjectCollection.push_back(object);
        }
    } 

    //Run our game...
    while(true){
        for(auto& e: gameObjectCollection){
            e->update();
            e->render();
        }
    }
    return 0;
}