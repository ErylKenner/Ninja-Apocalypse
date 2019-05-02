/*
 * Enemy.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#include "Enemy.h"
#include "Renderable.h"
#include "Health.h"
#include "OrientedPhysics3D.h"
#include "UnitAI.h"
#include "Command.h"
#include "GameMgr.h"
#include "CircleCollider.h"
#include "WaveMgr.h"
#include "EntityMgr.h"

#include <cstdlib>
#include <ctime>

Enemy::Enemy(int id, Ogre::Vector3 pos, Engine * eng) :
        Entity381(id, "ninja.mesh", pos, eng),
        hitDamage(20){
    // TODO: add 0 heading to Renderable aspect to make enemies face the right direction
    aspects.push_back(new Health(this, 100, -1));
    anim = new Animation(this);
    aspects.push_back(anim);
    anim->SetAnimation("Walk", true, 1.2);

    aspects.push_back(new OrientedPhysics3D(this, 200, 180, 180));
    UnitAI * ai = new UnitAI(this);
    aspects.push_back(ai);

    ai->SetCommand(new Intercept(this, eng->gameMgr->MainPlayer));
    aspects.push_back(new EnemyMovableCircleCollider(this, 30));
    aspects.push_back(new Renderable(this, 90));

    std::srand(std::time(nullptr));
}

Enemy::~Enemy(){
}

void Enemy::OnDeath(){
    int rand = std::rand() % 100;
        if(rand < 12) {
            engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::HandgunType, position);
        }
    Ogre::Vector3 newPos = Ogre::Vector3(0,0, 25e6);
    position = newPos;
    GetAspect<UnitAI>()->SetCommand(new MoveTo(this, newPos));
    anim->DisableAnimation();
    engine->waveMgr->OnEnemyKilled(this);
}

