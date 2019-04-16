/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "Entity381.h"
#include "EntityMgr.h"
#include "Engine.h"
#include "GfxMgr.h"

#include "Physics.h"
#include "Renderable.h"
#include "Rotator.h"
#include "OrientedPhysics.h"
#include "OrientedPhysics3D.h"
#include "UnitAI.h"

void Entity381::Tick(float dt){
    for(unsigned int i = 0; i < aspects.size(); ++i){
        aspects[i]->Tick(dt);
    }
}

Entity381::Entity381(int id, std::string mesh, Ogre::Vector3 pos, EntityMgr *entMgr, float accel, float tr, float maxSp, float cr) :
        entityId(id),
        meshName(mesh),
        position(pos),
        entityMgr(entMgr),
        acceleration(accel),
        turningRate(tr),
        climbRate(cr),
        maxSpeed(maxSp){
    velocity = Ogre::Vector3::ZERO;
    isSelected = false;

    ogreEntity = entityMgr->engine->gfxMgr->mSceneMgr->createEntity(meshName);
    ogreEntity->setCastShadows(true);
    ogreSceneNode = entMgr->engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreSceneNode->attachObject(ogreEntity);
    ogreSceneNode->setPosition(position);

    speed = 0;
    heading = 0;
    altitude = pos.y;
    desiredSpeed = 0;
    desiredHeading = 0;
    desiredAltitude = pos.y;
}

Entity381::Entity381(int id, std::string mesh, Ogre::Vector3 pos, EntityMgr *entMgr, float accel, float tr, float maxSp) :
        entityId(id),
        meshName(mesh),
        position(pos),
        entityMgr(entMgr),
        acceleration(accel),
        turningRate(tr),
        climbRate(0),
        maxSpeed(maxSp){
    velocity = Ogre::Vector3::ZERO;
    isSelected = false;

    ogreEntity = entityMgr->engine->gfxMgr->mSceneMgr->createEntity(meshName);
    ogreEntity->setCastShadows(true);
    ogreSceneNode = entMgr->engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreSceneNode->attachObject(ogreEntity);
    ogreSceneNode->setPosition(position);

    speed = 0;
    heading = 0;
    altitude = 0;
    desiredSpeed = 0;
    desiredHeading = 0;
    desiredAltitude = 0;
}

Entity381::Entity381(int id, std::string mesh, Ogre::Vector3 pos, EntityMgr *entMgr) :
        entityId(id),
        meshName(mesh),
        position(pos),
        entityMgr(entMgr),
        acceleration(0),
        turningRate(0),
        climbRate(0),
        maxSpeed(0){
    velocity = Ogre::Vector3::ZERO;
    isSelected = false;

    ogreEntity = entityMgr->engine->gfxMgr->mSceneMgr->createEntity(meshName);
    ogreEntity->setCastShadows(true);
    ogreSceneNode = entMgr->engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreSceneNode->attachObject(ogreEntity);
    ogreSceneNode->setPosition(position);

    speed = 0;
    heading = 0;
    altitude = 0;
    desiredSpeed = 0;
    desiredHeading = 0;
    desiredAltitude = 0;
}

Entity381::~Entity381(){
}

SphereEntity381::SphereEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "sphere.mesh", pos, entMgr){
    InitAspects();
}

void SphereEntity381::InitAspects(){
    aspects.push_back(new Physics(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new Rotator(this));
    aspects.push_back(new UnitAI(this));
}

SphereEntity381::~SphereEntity381(){
}

CubeEntity381::CubeEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "cube.mesh", pos, entMgr){
    InitAspects();
}

void CubeEntity381::InitAspects(){
    aspects.push_back(new Physics(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new Rotator(this));
    aspects.push_back(new UnitAI(this));
}

CubeEntity381::~CubeEntity381(){
}

DDG51Entity381::DDG51Entity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "ddg51.mesh", pos, entMgr, 8, 8, 80){
    InitAspects();
}

void DDG51Entity381::InitAspects(){
    aspects.push_back(new OrientedPhysics(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

DDG51Entity381::~DDG51Entity381(){
}

CVN681Entity381::CVN681Entity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "cvn68.mesh", pos, entMgr, 7, 5, 100){
    InitAspects();
}

void CVN681Entity381::InitAspects(){
    aspects.push_back(new OrientedPhysics(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

CVN681Entity381::~CVN681Entity381(){
}

SailboatEntity381::SailboatEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "sailboat.mesh", pos, entMgr, 15, 50, 30){
    InitAspects();
}

void SailboatEntity381::InitAspects(){
    aspects.push_back(new OrientedPhysics(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

SailboatEntity381::~SailboatEntity381(){
}

AlienEntity381::AlienEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "alienship.mesh", pos, entMgr, 100, 50, 200){
    InitAspects();
}

void AlienEntity381::InitAspects(){
    aspects.push_back(new OrientedPhysics(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

AlienEntity381::~AlienEntity381(){
}

CigaretteEntity381::CigaretteEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "cigarette.mesh", pos, entMgr, 20, 50, 30){
    InitAspects();
}

void CigaretteEntity381::InitAspects(){
    aspects.push_back(new OrientedPhysics(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

CigaretteEntity381::~CigaretteEntity381(){
}

BansheeEntity381::BansheeEntity381(int id, Ogre::Vector3 pos, EntityMgr *entMgr) :
        Entity381(id, "banshee.mesh", pos, entMgr, 20, 50, 30, 10){
    InitAspects();
}

void BansheeEntity381::InitAspects(){
    aspects.push_back(new OrientedPhysics3D(this));
    aspects.push_back(new Renderable(this));
    aspects.push_back(new UnitAI(this));
}

BansheeEntity381::~BansheeEntity381(){
}

