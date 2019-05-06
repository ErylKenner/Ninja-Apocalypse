/*
 * WaveMgr.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#include "WaveMgr.h"
#include "EntityMgr.h"
#include "GameMgr.h"
#include "GfxMgr.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

WaveMgr::WaveMgr(Engine *eng) :
        Mgr(eng),
        enemiesPerWave(20),
        waveNumber(1),
        spawnDelay(1),
        timeElapsed(0),
        timeSinceLastSpawn(0){
    enemiesRemaining = enemiesPerWave;
}
WaveMgr::~WaveMgr(){
}

void WaveMgr::Init(){
    std::srand(std::time(nullptr));
}
void WaveMgr::Tick(float dt){
    // adds dt to timeElapsed
    timeElapsed += dt;
    // add dt to timeSinceLastSpawn
    timeSinceLastSpawn += dt;
    // if timeSinceSpawn >= spawnDelay
    if(timeSinceLastSpawn >= spawnDelay){
        // reset timeSinceSpawn
        timeSinceLastSpawn = 0;
        // SpawnEnemy
        SpawnEnemy();
        std::cout << "# of spawned enemies: " << spawnedEnemyList.size() << std::endl;
    }
    /*std::cout << " # enemies: " << spawnedEnemyList.size() << ", fps: " << (int)(1 / dt)
     << std::endl;*/
}
void WaveMgr::LoadLevel(){
}
void WaveMgr::Stop(){
}

int WaveMgr::deltaValue(int minimum, int radius){
    int randomVal = std::rand() % (2 * radius);
    if(randomVal >= radius){
        return minimum + (randomVal - radius);
    } else{
        return -minimum - randomVal;
    }
}

void WaveMgr::SpawnEnemy(){
    Ogre::Vector3 spawnPosition;
    bool continueTrying;
    do{
        // Figures out where to spawn the enemy
        int deltaX = deltaValue(800, 500);
        int deltaZ = deltaValue(800, 500);
        spawnPosition = engine->gameMgr->MainPlayer->position;
        spawnPosition.x += deltaX;
        spawnPosition.z += deltaZ;
        continueTrying = spawnPosition.x >= 0.5 * engine->gameMgr->mapWidth
                || spawnPosition.x <= -0.5 * engine->gameMgr->mapWidth
                || spawnPosition.z >= 0.5 * engine->gameMgr->mapHeight
                || spawnPosition.z <= -0.5 * engine->gameMgr->mapHeight;
        for(unsigned int i = 0; i < Collider::colliders.size(); ++i){
            if(Collider::colliders[i] != NULL
                    && Collider::colliders[i]->Contains(spawnPosition)){
                continueTrying = true;
                break;
            }
        }
    } while(continueTrying);

    if(deadList.empty()){
        Enemy * newEnemy = static_cast<Enemy *>(engine->entityMgr->CreateEntity(
                EntityType::EnemyType, spawnPosition));
        // Adds it to spawned enemy list
        spawnedEnemyList.push_back(newEnemy);
    } else{
        Enemy *newEnemy = deadList.back();
        deadList.pop_back();
        newEnemy->position = spawnPosition;
        newEnemy->InitAspects();
        spawnedEnemyList.push_back(newEnemy);
    }
}
void WaveMgr::OnEnemyKilled(Enemy * enemy){
    // Decrements enemiesRemaining
    if(std::find(spawnedEnemyList.begin(), spawnedEnemyList.end(), enemy)
            != spawnedEnemyList.end()){
        spawnedEnemyList.erase(
                std::remove(spawnedEnemyList.begin(), spawnedEnemyList.end(), enemy));
        deadList.push_back(enemy);
        enemiesRemaining--;
        // Checks if <= 0, and decides to start the next wave
        if(enemiesRemaining <= 0){
            NextWave();
        }
    }

}
void WaveMgr::NextWave(){
    // Resets enemiesRemaining
    enemiesRemaining = enemiesPerWave;
    // Increments waveNumber
    waveNumber++;
}
