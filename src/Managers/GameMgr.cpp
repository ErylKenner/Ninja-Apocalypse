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
#include "AiMgr.h"
#include "WaveMgr.h"

GameMgr::GameMgr(Engine *eng) :
        Mgr(eng),
        LevelBoss(0),
        weaponMgr(0),
        MainPlayer(0),
        groundNode(0),
        groundEntity(0),
        line(0),
        lineNode(0){
    weaponMgr = new WeaponMgr(engine);
    mPlane = Ogre::Plane(Ogre::Vector3::UNIT_Y, surfaceHeight);

}

GameMgr::~GameMgr(){

}

void GameMgr::Init(){
    weaponMgr->Init();
}

void GameMgr::Tick(float dt){
    float prev = timer;
    timer -= dt;
    if(timer <= 0 && prev >= 0){
        timer = -1;
        line->clear();
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
    groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
    groundNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(
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
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0.6, 0.6, 0.6);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0.1, 0.1,
            0.1);
    lineNode->attachObject(line);
    //lineNode->setInheritScale(false);

    //Create player
    MainPlayer = static_cast<Player*>(engine->entityMgr->CreateEntity(
            EntityType::PlayerType, Ogre::Vector3(0, surfaceHeight, -400)));

    weaponMgr->LoadLevel();

    LoadLevelOne();

}

void GameMgr::LoadLevelOne(){
    ResetLevel();
    engine->aiMgr->LoadLevel("LevelOneNodes.txt");
    engine->waveMgr->disabledSpawning = false;

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(
            "MetalFloor");
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(16, 8);
    groundEntity->setMaterial(material);

    Entity381 *temp;
    //Borders
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.5 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.92 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.5 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.92 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0, surfaceHeight, -0.5 * mapHeight),
            Ogre::Vector3(1.04 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0, surfaceHeight, 0.5 * mapHeight),
            Ogre::Vector3(1.04 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Top left corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.4 * mapWidth, surfaceHeight, -0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.275 * mapWidth, surfaceHeight, -0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Bottom left corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.4 * mapWidth, surfaceHeight, 0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.275 * mapWidth, surfaceHeight, 0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Top right corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.4 * mapWidth, surfaceHeight, -0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.275 * mapWidth, surfaceHeight, -0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Bottom right corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.4 * mapWidth, surfaceHeight, 0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.275 * mapWidth, surfaceHeight, 0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Left large center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.275 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.075 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);

    //Left top center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.1 * mapWidth, surfaceHeight, -0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Left bottom center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.1 * mapWidth, surfaceHeight, 0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Right large center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.275 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.075 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);

    //Right top center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.1 * mapWidth, surfaceHeight, -0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Right bottom center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.1 * mapWidth, surfaceHeight, 0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Bottom center circle
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainSphere,
            Ogre::Vector3(0, surfaceHeight, 0.275 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, 1, 1));
    currentScene.push_back(temp);

    //Top center circle
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainSphere,
            Ogre::Vector3(0, surfaceHeight, -0.275 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, 1, 1));
    currentScene.push_back(temp);

    //Center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.15 * mapHeight));
    currentScene.push_back(temp);
}

void GameMgr::LoadLevelBoss(){
    ResetLevel();
    engine->aiMgr->LoadLevel("LevelOneNodes.txt");
    engine->waveMgr->disabledSpawning = true;

    Entity381 *temp;
    //Borders
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(-0.5 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.92 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0.5 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.92 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0, surfaceHeight, -0.5 * mapHeight),
            Ogre::Vector3(1.04 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle,
            Ogre::Vector3(0, surfaceHeight, 0.5 * mapHeight),
            Ogre::Vector3(1.04 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);
}

void GameMgr::LoadLevelTwo(){
    ResetLevel();
    engine->aiMgr->LoadLevel("LevelOneNodes.txt");
    engine->waveMgr->disabledSpawning = false;

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(
            "MetalFloor");
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(16, 8);
    groundEntity->setMaterial(material);

    Entity381 *temp;
    //Borders
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.5 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.92 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.5 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.92 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0, surfaceHeight, -0.5 * mapHeight),
            Ogre::Vector3(1.04 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0, surfaceHeight, 0.5 * mapHeight),
            Ogre::Vector3(1.04 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Top left corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.4 * mapWidth, surfaceHeight, -0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.275 * mapWidth, surfaceHeight, -0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Bottom left corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.4 * mapWidth, surfaceHeight, 0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.275 * mapWidth, surfaceHeight, 0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Top right corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.4 * mapWidth, surfaceHeight, -0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.275 * mapWidth, surfaceHeight, -0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Bottom right corner
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.4 * mapWidth, surfaceHeight, 0.225 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.275 * mapWidth, surfaceHeight, 0.31 * mapHeight),
            Ogre::Vector3(0.21 * mapWidth, borderWallThickness, 0.08 * mapHeight));
    currentScene.push_back(temp);

    //Left large center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.275 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.075 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);

    //Left top center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.1 * mapWidth, surfaceHeight, -0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Left bottom center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(-0.1 * mapWidth, surfaceHeight, 0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Right large center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.275 * mapWidth, surfaceHeight, 0),
            Ogre::Vector3(0.075 * mapWidth, borderWallThickness, 0.25 * mapHeight));
    currentScene.push_back(temp);

    //Right top center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.1 * mapWidth, surfaceHeight, -0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Right bottom center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0.1 * mapWidth, surfaceHeight, 0.2 * mapHeight),
            Ogre::Vector3(0.025 * mapWidth, borderWallThickness, 0.275 * mapHeight));
    currentScene.push_back(temp);

    //Bottom center circle
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainSphere2,
            Ogre::Vector3(0, surfaceHeight, 0.275 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, 1, 1));
    currentScene.push_back(temp);

    //Top center circle
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainSphere2,
            Ogre::Vector3(0, surfaceHeight, -0.275 * mapHeight),
            Ogre::Vector3(0.04 * mapWidth, 1, 1));
    currentScene.push_back(temp);

    //Center block
    temp = engine->entityMgr->CreateEntity(EntityType::TerrainRectangle2,
            Ogre::Vector3(0, surfaceHeight, 0),
            Ogre::Vector3(0.04 * mapWidth, borderWallThickness, 0.15 * mapHeight));
    currentScene.push_back(temp);
}

bool GameMgr::InBounds(Ogre::Vector3 pos){
    return Ogre::Math::Abs(pos.x) < mapWidth / 2 && Ogre::Math::Abs(pos.z) < mapHeight / 2;
}

void GameMgr::Stop(){
    weaponMgr->Stop();
}

void GameMgr::DrawLine(Ogre::Vector3 start, Ogre::Vector3 end){
    timer = lineVisibleTime;
    line->clear();
    line->begin("lineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    line->position(start.x, start.y, start.z);
    line->position(end.x, end.y, end.z);
    line->end();
}

void GameMgr::ResetLevel(){
    for(unsigned int i = 0; i < currentScene.size(); ++i){
        delete currentScene[i];
    }
    currentScene.clear();
    MainPlayer->position = Ogre::Vector3(0, surfaceHeight, -400);
}
