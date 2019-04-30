/*
 * Gun.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: kylebrain
 */

#include "Gun.h"
#include "Ray.h"
#include "GameMgr.h"
#include "InputMgr.h"
#include "CircleCollider.h"
#include "Enemy.h"
#include "Health.h"

Gun::Gun(int id, std::string meshName, Ogre::Vector3 _scale, Ogre::Vector3 pos,
         Engine * eng, float useRate, int damageAmount, int bulletMax) :
        Weapon(id, meshName, _scale, pos, eng, useRate, damageAmount),
        BulletMax(bulletMax){
    CurrentBulletNumber = BulletMax;
}
Gun::~Gun(){

}

void Gun::Use(){
    if(CurrentBulletNumber > 0){
        CurrentBulletNumber--;
        const Ogre::Vector2 playerPos = Ogre::Vector2(
                engine->gameMgr->MainPlayer->position.x,
                engine->gameMgr->MainPlayer->position.z);
        const Ogre::Vector2 dir = Ogre::Vector2(engine->inputMgr->mouseLocation.second.x,
                engine->inputMgr->mouseLocation.second.z) - playerPos;
        Ray ray(playerPos, dir);
        float dist = Ogre::Math::POS_INFINITY;
        Collider *closest = ray.GetClosestIntersectedCollider(&dist);
        if(closest != NULL){
            if(dist != Ogre::Math::POS_INFINITY){
                Ogre::Vector2 endPos = playerPos + dir.normalisedCopy() * dist;
                engine->gameMgr->DrawLine(playerPos, endPos);
            }

            EnemyMovableCircleCollider *enemyCollider =
                    dynamic_cast<EnemyMovableCircleCollider *>(closest);
            if(enemyCollider != NULL){
                Enemy * enemy = static_cast<Enemy *>(enemyCollider->entity381);
                if(!enemy->GetAspect<Health>()->TakeDamage(DamageAmount)){
                    enemy->OnDeath();
                }
            }
        }
    }
}

Handgun::Handgun(int id, Ogre::Vector3 pos, Engine * eng) :
        Gun(id, "cube.mesh", Ogre::Vector3(10, 10, 40), pos, eng, 1 / 10.0, 20, 80){
    ogreEntity->setMaterialName("Examples/BumpyMetal");

}
Handgun::~Handgun(){

}
