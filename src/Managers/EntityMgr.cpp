/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "EntityMgr.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Gun.h"
#include "Engine.h"
#include "GfxMgr.h"


EntityMgr::EntityMgr(Engine *eng) :
        Mgr(eng),
        currentEntity(0){
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::Init(){

}

void EntityMgr::Tick(float dt){
    for(unsigned int i = 0; i < entities.size(); ++i){
        entities[i]->Tick(dt);
        entities[i]->ogreSceneNode->showBoundingBox(entities[i]->isSelected);
    }
}

Entity381* EntityMgr::CreateEntity(EntityType type, Ogre::Vector3 pos,
                                                   Ogre::Vector3 scale){
    int id = entities.size();
    Entity381 *newEntity;
    switch(type) {
        case EntityType::Sphere:
        case EntityType::TerrainSphere:
            newEntity = new SphereEntity381(id, pos, scale.x, engine);
            entities.push_back(newEntity);
            return newEntity;
            break;
        case EntityType::Rectangle:
        case EntityType::TerrainRectangle:
            newEntity = new RectangleEntity381(id, pos, scale, engine);
            entities.push_back(newEntity);
            return newEntity;
            break;
        case EntityType::TerrainBorder:
            newEntity = new RectangleBorderEntity381(id, pos, scale, engine);
            entities.push_back(newEntity);
            return newEntity;
            break;
        case EntityType::PlayerType:
            newEntity = new Player(500, engine->gfxMgr->mCameraNode, id, pos, engine);
            entities.push_back(newEntity);
            return newEntity;
            break;
        case EntityType::EnemyType:
            newEntity = new Enemy(id, pos, engine);
            entities.push_back(newEntity);
            return newEntity;
        case EntityType::HandgunType:
            newEntity = new Handgun(id, pos, engine);
            entities.push_back(newEntity);
            return newEntity;
        default:
            return NULL;
            break;
    }
}

void EntityMgr::LoadLevel(){

}

void EntityMgr::Stop(){

}

