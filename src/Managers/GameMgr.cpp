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
    engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.35, 0.35, 0.35));
    engine->gfxMgr->mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

    Ogre::MeshManager::getSingleton().createPlane("ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mPlane, 100000,
            100000, 10, 10, true, 1, 4000, 4000, Ogre::Vector3::UNIT_Z);
    Ogre::Entity *groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
    Ogre::SceneNode *groundNode =
            engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(
                    "GroundNode");
    groundNode->attachObject(groundEntity);
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(
            "Examples/Rockwall");
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(8, 8);

    groundEntity->setMaterial(material);
    groundEntity->setCastShadows(false);

    engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

    Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
    light->setPosition(0, 8000, 0);

    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Sphere,
            Ogre::Vector3(0, surfaceHeight, 0));
    Entity381* wall_1 = engine->entityMgr->CreateEntityOfTypeAtPosition(
            EntityType::Rectangle, Ogre::Vector3(600, surfaceHeight, 200));
    wall_1->ogreSceneNode->resetOrientation();
    wall_1->ogreSceneNode->yaw(Ogre::Degree(10));

    MainPlayer = static_cast<Player*>(engine->entityMgr->CreateEntityOfTypeAtPosition(
            EntityType::PlayerType, Ogre::Vector3(0, surfaceHeight, -400)));

    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::HandgunType,
                Ogre::Vector3(0, surfaceHeight, -700));

    //MainPlayer->GetAspect<WeaponHolder>()->SetWeapon(weapon);


}

void GameMgr::Stop(){

}

