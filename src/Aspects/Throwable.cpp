/*
 * Throwable.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: kylebrain
 */

#include "Throwable.h"
#include "Entity381.h"

Throwable::Throwable(Entity381 *entity, float speed) :
        Aspect(entity),
        Speed(speed){
}
Throwable::~Throwable(){
}
void Throwable::Tick(float dt){
    if(Thrown){
        entity381->position += Speed * thrownDirection * dt;
    }
}

void Throwable::Throw(float direction){
    Thrown = true;
    thrownDirection = Ogre::Vector3(Ogre::Math::Cos(Ogre::Degree(direction)), 0,
            -Ogre::Math::Sin(Ogre::Degree(direction)));
}
