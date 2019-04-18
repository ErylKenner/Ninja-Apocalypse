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
        Mgr(eng), MainPlayer(0){

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

    //Ground plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, surfaceHeight);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 100000, 100000,
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

    /*
    Entity381 *ent;
    ent = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Banshee, Ogre::Vector3(0, surfaceHeight, -300));
    ent = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::DDG51, Ogre::Vector3(-600, surfaceHeight, -600));
    ent = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::CVN68, Ogre::Vector3(-300, surfaceHeight, -600));
    ent = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Cigarette, Ogre::Vector3(0, surfaceHeight, -600));
    ent = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Alienship, Ogre::Vector3(300, surfaceHeight, -600));
    ent = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Sailboat, Ogre::Vector3(600, surfaceHeight, -600));
    engine->entityMgr->currentEntity = ent->entityId;
    ent->isSelected = true;
	*/

    MainPlayer = static_cast<Player*>(engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::PlayerType, Ogre::Vector3(0, surfaceHeight + 50, -400)));
}

void GameMgr::Stop(){

}

