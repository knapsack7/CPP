#include "IGameObject.h"

int Plane::objectsCreated = 0;
int Boat::objectsCreated = 0;

Plane::Plane(int x, int y) {
    objectsCreated++;
}

void Plane::objectPlayDefaultAnimation() {/*......*/}
void Plane::objectMoveInGame() {/*......*/}
void Plane::update() {/*......*/}
void Plane::render() {/*.......*/}

IGameObject* Plane::create() {
    return new Plane(0, 0);
}

Boat::Boat(int x, int y) {
    objectsCreated++;
}

void Boat::objectPlayDefaultAnimation() {/*......*/}
void Boat::objectMoveInGame() {/*......*/}
void Boat::update() {/*......*/}
void Boat::render() {/*.......*/}

IGameObject* Boat::create() {
    return new Boat(0, 0);
}
