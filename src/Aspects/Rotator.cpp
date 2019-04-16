/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "Rotator.h"
#include "Entity381.h"

Rotator::Rotator(Entity381 *entity) :
        Aspect(entity){
}

void Rotator::Tick(float dt){
    entity381->ogreSceneNode->yaw(Ogre::Degree(30 * dt));
}

Rotator::~Rotator(){
}


