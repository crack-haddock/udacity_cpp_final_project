#ifndef FOOD_H
#define FOOD_H

#include "gameObject.h"

// TODO my intention (but will probably run out of time) is to
// a) replace the very hazy references to food with a proper encapsulated class
// b) have food as a playable character
class Food : public GameObject {
public:
    Food() : GameObject(++Food::count) {}

    void Update() {} // TODO if I ever get around to using this class in anger
    int GetScore() = delete; // won't need this unless class used AND as a playable character
    int GetObjectCount() const { return count; }
private:
    static int count;
};

#endif