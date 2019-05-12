#include <OrientedPhysics.h>
#include "Renderable.h"
#include "Entity381.h"

Renderable::Renderable(Entity381 *entity, float AngleOff) :
        Aspect(entity),
        AngleOffset(AngleOff){
}

void Renderable::Tick(float dt){
    entity381->ogreSceneNode->setPosition(entity381->position);
    entity381->ogreSceneNode->setScale(entity381->scale);
    OrientedPhysics *physics = entity381->GetAspect<OrientedPhysics>();
    if(physics != NULL){
        entity381->ogreSceneNode->resetOrientation();
        entity381->ogreSceneNode->yaw(Ogre::Degree(-physics->heading - AngleOffset),
                Ogre::Node::TransformSpace::TS_WORLD);
    }
}

Renderable::~Renderable(){
}

