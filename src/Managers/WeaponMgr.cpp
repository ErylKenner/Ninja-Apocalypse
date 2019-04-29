/*
 * WeaponManager.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: kylebrain
 */

#include <WeaponMgr.h>
#include "EntityMgr.h"
#include "GameMgr.h"
#include "Weapon.h"

using Ogre::Vector3;

WeaponMgr::WeaponMgr(Engine *eng) : Mgr(eng), weaponCooldown(30) {

}
WeaponMgr::~WeaponMgr(){

}

void WeaponMgr::Init(){
}
void WeaponMgr::Tick(float dt){
    for(unsigned int i = 0; i < spawnPoints.size(); i++) {
        spawnPoints[i]->Tick(dt);
    }
}
void WeaponMgr::LoadLevel(){
    float ground = engine->gameMgr->surfaceHeight;
    spawnPoints.push_back(new WeaponSpawnPoint(Vector3(-2000, ground, 0), weaponCooldown, engine));
    spawnPoints.push_back(new WeaponSpawnPoint(Vector3(2000, ground, 0), weaponCooldown, engine));
    spawnPoints.push_back(new WeaponSpawnPoint(Vector3(0, ground, 1000), weaponCooldown, engine));
    spawnPoints.push_back(new WeaponSpawnPoint(Vector3(0, ground, -1000), weaponCooldown, engine));
}
void WeaponMgr::Stop(){
}

WeaponSpawnPoint::WeaponSpawnPoint(Ogre::Vector3 pos, float coolDown, Engine * eng) :
        position(pos),
        respawnCooldown(coolDown),
        engine(eng),
        currentTimer(0),
        spawnedWeapon(0){
    SpawnWeapon();
}

void WeaponSpawnPoint::Tick(float dt){
    if(spawnedWeapon == NULL){
        currentTimer += dt;

        if(currentTimer >= respawnCooldown){
            SpawnWeapon();
        }
    }
}

void WeaponSpawnPoint::SpawnWeapon(){
    currentTimer = 0;
    spawnedWeapon = static_cast<Weapon*>(engine->entityMgr->CreateEntityOfTypeAtPosition(
            EntityType::HandgunType, position));
    spawnedWeapon->spawnedFrom = this;
}

void WeaponSpawnPoint::ClearWeapon() {
    spawnedWeapon = NULL;
    currentTimer = 0;
}

