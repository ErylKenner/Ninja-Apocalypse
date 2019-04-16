
#include "Renderable.h"
#include "Entity381.h"

Renderable::Renderable(Entity381 *entity) :
        Aspect(entity){
}

void Renderable::Tick(float dt){
    entity381->ogreSceneNode->setPosition(entity381->position);
    entity381->ogreSceneNode->resetOrientation();
    entity381->ogreSceneNode->yaw(Ogre::Degree(-entity381->heading), Ogre::Node::TransformSpace::TS_WORLD);
}

Renderable::~Renderable(){
}

