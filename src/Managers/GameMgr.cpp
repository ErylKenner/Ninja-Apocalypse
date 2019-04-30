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
#include "WeaponMgr.h"

GameMgr::GameMgr(Engine *eng) :
        Mgr(eng),
        MainPlayer(0), weaponMgr(0){
    weaponMgr = new WeaponMgr(engine);
    mPlane = Ogre::Plane(Ogre::Vector3::UNIT_Y, surfaceHeight);

}

GameMgr::~GameMgr(){

}

void GameMgr::Init(){
    weaponMgr->Init();
}

void GameMgr::Tick(float dt){
    timer -= dt;
    if(timer <= 0){
        timer = 0;
        DrawLine(Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0));
    }
    //std::cout << "FPS: " << (int)(1 / dt);
    weaponMgr->Tick(dt);
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
            "Examples/GrassFloor");
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(20,
            20);
    groundEntity->setMaterial(material);
    groundEntity->setCastShadows(false);

    //Create line stump
    line = engine->gfxMgr->mSceneMgr->createManualObject("line");
    lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(
            "lineNode");
    Ogre::MaterialPtr myManualObjectMaterial =
            Ogre::MaterialManager::getSingleton().create("lineMaterial", "General");
    myManualObjectMaterial->setReceiveShadows(false);
    myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0.2, 0.2, 0.2, 0);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0, 0, 0);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0.1, 0.1, 0.1);
    lineNode->attachObject(line);
    lineNode->setInheritScale(false);

    //Create player
    MainPlayer = static_cast<Player*>(engine->entityMgr->CreateEntityOfTypeAtPosition(
            EntityType::PlayerType, Ogre::Vector3(0, surfaceHeight, -400)));
    //MainPlayer->ogreSceneNode->addChild(lineNode);

    //Create gun
    //engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::HandgunType,
            //Ogre::Vector3(0, surfaceHeight, -300));

    engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::FirstBossType, Ogre::Vector3(200, surfaceHeight + 100, -400));

    weaponMgr->LoadLevel();

    //LoadLevelOne();
}

void GameMgr::LoadLevelOne(){
    Entity381 *temp;
    //Borders
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainBorder,
            Ogre::Vector3(-mapWidth * 0.5, surfaceHeight, 0),
            Ogre::Vector3(borderWallThickness, borderWallThickness,
                    mapHeight - borderWallThickness));
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainBorder,
            Ogre::Vector3(mapWidth * 0.5, surfaceHeight, 0),
            Ogre::Vector3(borderWallThickness, borderWallThickness,
                    mapHeight - borderWallThickness));
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainBorder,
            Ogre::Vector3(0, surfaceHeight, -mapHeight * 0.5),
            Ogre::Vector3(mapWidth + borderWallThickness, borderWallThickness,
                    borderWallThickness));
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainBorder,
            Ogre::Vector3(0, surfaceHeight, mapHeight * 0.5),
            Ogre::Vector3(mapWidth + borderWallThickness, borderWallThickness,
                    borderWallThickness));

    //Top left corner
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(-mapWidth * 0.4, surfaceHeight, -mapHeight * 0.225),
            Ogre::Vector3(borderWallThickness, borderWallThickness, 0.25 * mapHeight));
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(-mapWidth * 0.275, surfaceHeight,
                    -mapHeight * 0.35 + 0.5 * borderWallThickness),
            Ogre::Vector3(mapWidth * 0.25 - borderWallThickness, borderWallThickness,
                    borderWallThickness));

    //Bottom left corner
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(-mapWidth * 0.4, surfaceHeight, mapHeight * 0.225),
            Ogre::Vector3(borderWallThickness, borderWallThickness, 0.25 * mapHeight));
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(-mapWidth * 0.275, surfaceHeight,
                    mapHeight * 0.35 - 0.5 * borderWallThickness),
            Ogre::Vector3(mapWidth * 0.25 - borderWallThickness, borderWallThickness,
                    borderWallThickness));

    //Top right corner
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(mapWidth * 0.4, surfaceHeight, -mapHeight * 0.225),
            Ogre::Vector3(borderWallThickness, borderWallThickness, 0.25 * mapHeight));
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(mapWidth * 0.275, surfaceHeight,
                    -mapHeight * 0.35 + 0.5 * borderWallThickness),
            Ogre::Vector3(mapWidth * 0.25 - borderWallThickness, borderWallThickness,
                    borderWallThickness));

    //Bottom right corner
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(mapWidth * 0.4, surfaceHeight, mapHeight * 0.225),
            Ogre::Vector3(borderWallThickness, borderWallThickness, 0.25 * mapHeight));
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(mapWidth * 0.275, surfaceHeight,
                    mapHeight * 0.35 - 0.5 * borderWallThickness),
            Ogre::Vector3(mapWidth * 0.25 - borderWallThickness, borderWallThickness,
                    borderWallThickness));

    //Left large center block
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(-mapWidth * 0.275, surfaceHeight, 0),
            Ogre::Vector3(mapWidth * 0.075, borderWallThickness, mapHeight * 0.25));

    //Left top center block
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(-mapWidth * 0.1, surfaceHeight, -mapHeight * 0.2),
            Ogre::Vector3(mapWidth * 0.025, borderWallThickness, mapHeight * 0.275));

    //Left bottom center block
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(-mapWidth * 0.1, surfaceHeight, mapHeight * 0.2),
            Ogre::Vector3(mapWidth * 0.025, borderWallThickness, mapHeight * 0.275));

    //Right large center block
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(mapWidth * 0.275, surfaceHeight, 0),
            Ogre::Vector3(mapWidth * 0.075, borderWallThickness, mapHeight * 0.25));

    //Right top center block
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(mapWidth * 0.1, surfaceHeight, -mapHeight * 0.2),
            Ogre::Vector3(mapWidth * 0.025, borderWallThickness, mapHeight * 0.275));

    //Right bottom center block
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(mapWidth * 0.1, surfaceHeight, mapHeight * 0.2),
            Ogre::Vector3(mapWidth * 0.025, borderWallThickness, mapHeight * 0.275));

    //Bottom center circle
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainSphere,
            Ogre::Vector3(0, surfaceHeight, mapHeight * 0.275),
            Ogre::Vector3(borderWallThickness, 1, 1));

    //Top center circle
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainSphere,
            Ogre::Vector3(0, surfaceHeight, -mapHeight * 0.275),
            Ogre::Vector3(borderWallThickness, 1, 1));

    //Center block
    temp = engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::TerrainRectangle,
            Ogre::Vector3(0, surfaceHeight, 0),
            Ogre::Vector3(borderWallThickness, borderWallThickness, mapHeight * 0.15));

}

void GameMgr::Stop(){
    weaponMgr->Stop();
}

void GameMgr::DrawLine(Ogre::Vector3 start, Ogre::Vector3 end){
    timer = lineVisibleTime;
    line->clear();
    line->begin("lineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
    line->position(start.x, start.y + 1, start.z);
    line->position(end.x, end.y + 1, end.z);
    line->end();
}
