#include "Renderable.h"
#include "Entity381.h"
#include "OrientedPhysics3D.h"

Renderable::Renderable(Entity381 *entity, float AngleOff) :
        Aspect(entity),
        AngleOffset(AngleOff){
}

void Renderable::Tick(float dt){
    entity381->ogreSceneNode->setPosition(entity381->position);
    OrientedPhysics3D *physics = entity381->GetAspect<OrientedPhysics3D>();
    if(physics != NULL){
        entity381->ogreSceneNode->resetOrientation();
        entity381->ogreSceneNode->yaw(Ogre::Degree(-physics->heading - AngleOffset),
                Ogre::Node::TransformSpace::TS_WORLD);
    }
}

Renderable::~Renderable(){
}

