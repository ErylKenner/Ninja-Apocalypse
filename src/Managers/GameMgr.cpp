/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include <OgreEntity.h>

#include "Engine.h"
#include "GameMgr.h"
#include "GfxMgr.h"
#include "EntityMgr.h"
#include "Weapon.h"
#include "WeaponHolder.h"

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
    //std::cout << "FPS: " << (int)(1 / dt);
}

void GameMgr::LoadLevel(){
    //Lighting
    engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
    engine->gfxMgr->mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

    Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
    light->setPosition(0, 15000, 0);

    //Ground Plane
    Ogre::MeshManager::getSingleton().createPlane("ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mPlane, 100000,
            100000, 10, 10, true, 1, mapWidth + 0.5 * borderWallThickness,
            mapHeight + 0.5 * borderWallThickness, Ogre::Vector3::UNIT_Z);
    Ogre::Entity *groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
    Ogre::SceneNode *groundNode =
            engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(
                    "GroundNode");
    groundNode->attachObject(groundEntity);
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(
            "Examples/Rockwall");
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(10.4,
            10.4);
    groundEntity->setMaterial(material);
    groundEntity->setCastShadows(false);

    //Create player
    MainPlayer = static_cast<Player*>(engine->entityMgr->CreateEntityOfTypeAtPosition(
            EntityType::PlayerType, Ogre::Vector3(0, surfaceHeight, -400)));

    //Create gun
    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::HandgunType,
            Ogre::Vector3(0, surfaceHeight, -700));

    //--------------------CREATE MAP--------------------
    //Borders
    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Rectangle,
            Ogre::Vector3(-mapWidth * 0.5, surfaceHeight, 0),
            Ogre::Vector3(borderWallThickness, borderWallThickness,
                    mapHeight + borderWallThickness));
    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Rectangle,
            Ogre::Vector3(mapWidth * 0.5, surfaceHeight, 0),
            Ogre::Vector3(borderWallThickness, borderWallThickness,
                    mapHeight + borderWallThickness));
    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Rectangle,
            Ogre::Vector3(0, surfaceHeight, -mapHeight * 0.5),
            Ogre::Vector3(mapWidth + borderWallThickness, borderWallThickness,
                    borderWallThickness));
    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Rectangle,
            Ogre::Vector3(0, surfaceHeight, mapHeight * 0.5),
            Ogre::Vector3(mapWidth + borderWallThickness, borderWallThickness,
                    borderWallThickness));

}

void GameMgr::Stop(){

}

