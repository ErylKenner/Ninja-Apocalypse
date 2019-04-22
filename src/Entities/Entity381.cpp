/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "Entity381.h"
#include "EntityMgr.h"
#include "Engine.h"
#include "GfxMgr.h"

#include "Renderable.h"
#include "UnitAI.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"

void Entity381::Tick(float dt){
    for(unsigned int i = 0; i < aspects.size(); ++i){
        aspects[i]->Tick(dt);
    }
}

Entity381::Entity381(int id, std::string mesh, Ogre::Vector3 pos, Engine * eng) :
        entityId(id),
        meshName(mesh),
        position(pos),
        engine(eng){
    isSelected = false;

    ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshName);
    ogreEntity->setCastShadows(true);
    ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreSceneNode->attachObject(ogreEntity);
    ogreSceneNode->setPosition(position);
    scale = Ogre::Vector3(1, 1, 1);
}

Entity381::~Entity381(){
}

SphereEntity381::SphereEntity381(int id, Ogre::Vector3 pos, int r, Engine * eng) :
        Entity381(id, "sphere.mesh", pos, eng),
        radius(r){
    scale = 0.01 * Ogre::Vector3(r, r, r);
    InitAspects();
}

void SphereEntity381::InitAspects(){
    aspects.push_back(new UnitAI(this));
    aspects.push_back(new CircleCollider(this, radius));
    aspects.push_back(new Renderable(this));
}

SphereEntity381::~SphereEntity381(){
}

RectangleEntity381::RectangleEntity381(int id, Ogre::Vector3 pos, Ogre::Vector3 sc,
                                       Engine * eng) :
        Entity381(id, "cube.mesh", pos, eng),
        width(sc.x),
        height(sc.y),
        length(sc.z){
    scale = 0.01 * sc;
    InitAspects();
}

void RectangleEntity381::InitAspects(){
    aspects.push_back(new UnitAI(this));
    aspects.push_back(new RectangleCollider(this, width, length));
    aspects.push_back(new Renderable(this));
}

RectangleEntity381::~RectangleEntity381(){
}

