#include "Renderable.h"
#include "Entity381.h"
#include "OrientedPhysics3D.h"

Renderable::Renderable(Entity381 *entity) :
        Aspect(entity){
}

void Renderable::Tick(float dt){
    entity381->ogreSceneNode->setPosition(entity381->position);
    entity381->ogreSceneNode->resetOrientation();
    OrientedPhysics3D *physics = entity381->GetAspect<OrientedPhysics3D>();
    if(physics != NULL){
        entity381->ogreSceneNode->yaw(Ogre::Degree(-physics->heading), Ogre::Node::TransformSpace::TS_WORLD);
    }
}

Renderable::~Renderable(){
}

