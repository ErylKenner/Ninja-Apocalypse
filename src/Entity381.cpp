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

Entity381::Entity381(int id, std::string mesh, Ogre::Vector3 pos, EntityMgr *entMgr) :
        entityId(id),
        meshName(mesh),
        position(pos),
        entityMgr(entMgr){
    isSelected = false;

    ogreEntity = entityMgr->engine->gfxMgr->mSceneMgr->createEntity(meshName);
    ogreEntity->setCastShadows(true);
    ogreSceneNode = entMgr->engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreSceneNode->attachObject(ogreEntity);
    ogreSceneNode->setPosition(position);
}

Entity381::~Entity381(){
}

SphereEntity381::SphereEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "sphere.mesh", pos, entMgr){
    InitAspects();
}

void SphereEntity381::InitAspects(){
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

SphereEntity381::~SphereEntity381(){
}

CubeEntity381::CubeEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "cube.mesh", pos, entMgr){
    InitAspects();
}

void CubeEntity381::InitAspects(){
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

CubeEntity381::~CubeEntity381(){
}

