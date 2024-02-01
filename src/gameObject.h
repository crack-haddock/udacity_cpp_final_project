#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "direction.h"

class GameObject {
public:
    GameObject(int _id, Direction _direction=Direction::none) :
        id{_id},
        direction{_direction}
        {}

    int GetId() const { return id; }
    int GetScore() { return score; } // will just return zero if below overridden as a no-op.
    // virtual so a class that doesn't need a score can override if need be
    virtual void AddOrSubScore(int _score=1) { score += _score; }

    virtual void Update() = 0;
    virtual int GetObjectCount() const = 0;

    // expecting the controller class to call this, but child class may redefine 
    virtual void SetDirection(Direction input, Direction opposite) {
        direction = input;
    }
protected:
    Direction direction;
private:
    int id; // NOTE: better as some kind of GUID, but beyond spec for this project
    int score{0};
};

#endif