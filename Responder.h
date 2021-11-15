#pragma once
#ifndef RESPONDER_H
#define RESPONDER_H
//#include <Vector2.hpp>

class Responder
{
public:
    Responder();
    // Commented out Vector2f for now until sfml libraries are present
    //Vector2f getPosition();
    void getSprite();
    //void moveTo(Float, Vector2f);
    void spawn(float);
    void update();
    float getLeft();
    float getRight();
    float getUp();
    float getDown();
    void stopLeft(float);
    void stopRight(float);
    void stopUp(float);
    void stopDown(float);

protected:

};
#endif