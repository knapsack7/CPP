#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

class IGameObject{
public:
    // Ensure derived classes call
    // the correct destructor (i.e. top of the chain)
    virtual ~IGameObject() {}
    // Pure Virtual functions that must be
    // implemented by derived class
    virtual void objectPlayDefaultAnimation() = 0;
    virtual void objectMoveInGame() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

class Plane : public IGameObject{
public:
    Plane(int x, int y);
    void objectPlayDefaultAnimation();
    void objectMoveInGame();
    void update();
    void render();
    static IGameObject* create();
private:
    static int objectsCreated;
};

class Boat : public IGameObject{
public:
    Boat(int x, int y);
    void objectPlayDefaultAnimation();
    void objectMoveInGame();
    void update();
    void render();
    static IGameObject* create();
private:
    static int objectsCreated;
};

#endif

