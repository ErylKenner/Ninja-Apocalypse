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
#include "SoundMgr.h"
#include "WeaponHolder.h"

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
        engine->soundMgr->playGunshot();
        CurrentBulletNumber--;
        const Ogre::Vector2 mousePos = Ogre::Vector2(
                engine->inputMgr->mouseLocation.second.x,
                engine->inputMgr->mouseLocation.second.z);
        const Ogre::Vector3 gunPos =
                engine->gameMgr->MainPlayer->ogreSceneNode->convertLocalToWorldPosition(
                        Ogre::Vector3(50 * Ogre::Math::Sin(20) * scale.x, 0,
                                -50 * Ogre::Math::Cos(20) * scale.z) + position);
        const Ogre::Vector2 dir = mousePos - Ogre::Vector2(gunPos.x, gunPos.z);
        Ray ray(gunPos, dir);
        float dist = Ogre::Math::POS_INFINITY;
        Collider *closest = ray.GetClosestIntersectedCollider(&dist);
        if(closest != NULL){
            if(dist != Ogre::Math::POS_INFINITY){
                Ogre::Vector2 endPos = ray.origin + dir.normalisedCopy() * dist;
                engine->gameMgr->DrawLine(Ogre::Vector3(ray.origin.x, 30, ray.origin.y),
                        Ogre::Vector3(endPos.x, 30, endPos.y));
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
        Gun(id, "cube.mesh", Ogre::Vector3(10, 10, 40), pos, eng, 1 / 10.0, 20, 60){
    ogreEntity->setMaterialName("Examples/BumpyMetal");

}
Handgun::~Handgun(){

}
