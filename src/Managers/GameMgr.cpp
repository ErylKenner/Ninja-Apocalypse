/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include <OgreEntity.h>

#include "Engine.h"
#include "GameMgr.h"
#include "GfxMgr.h"
#include "EntityMgr.h"

GameMgr::GameMgr(Engine *eng) :
        Mgr(eng),
        MainPlayer(0){
    mPlane = Ogre::Plane(Ogre::Vector3::UNIT_Y, surfaceHeight);

}

GameMgr::~GameMgr(){

}

void GameMgr::Init(){

}

void GameMgr::Tick(float dt){

}

void GameMgr::LoadLevel(){
    engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.35, 0.35, 0.35));
    engine->gfxMgr->mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mPlane, 100000, 100000,
            10, 10, true, 1, 4000, 4000, Ogre::Vector3::UNIT_Z);
    Ogre::Entity *groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
    Ogre::SceneNode *groundNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode("GroundNode");
    groundNode->attachObject(groundEntity);
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("Examples/Rockwall");
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(8, 8);

    groundEntity->setMaterial(material);
    groundEntity->setCastShadows(false);

    engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

    Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
    light->setPosition(20, 8000, 50);

    MainPlayer = static_cast<Player*>(engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::PlayerType,
            Ogre::Vector3(0, surfaceHeight, -400)));
}

void GameMgr::Stop(){

}

