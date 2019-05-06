/*
 * Enemy.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#include <OrientedPhysics.h>
#include "Enemy.h"
#include "Renderable.h"
#include "Health.h"
#include "UnitAI.h"
#include "Command.h"
#include "GameMgr.h"
#include "CircleCollider.h"
#include "WaveMgr.h"
#include "EntityMgr.h"
#include "PotentialField.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>

Enemy::Enemy(int id, Ogre::Vector3 pos, Engine * eng) :
        Entity381(id, "ninja.mesh", pos, eng),
        hitDamage(20){
    aspects.push_back(new Renderable(this, 90));
    InitAspects();
    std::srand(std::time(nullptr));
}

Enemy::~Enemy(){
}

void Enemy::InitAspects(){
    anim = new Animation(this);
    aspects.push_back(anim);
    anim->SetAnimation("Walk", true, 1.2);
    aspects.push_back(new OrientedPhysics(this, 200, 180, 180));
    aspects.push_back(new PotentialField(this, PotentialFieldType::Enemy));
    aspects.push_back(new EnemyMovableCircleCollider(this, 50));
    aspects.push_back(new Health(this, 100, -1));
}

void Enemy::ResetAspects(){
    Renderable *renderable = GetAspect<Renderable>();
    for(unsigned int i = 0; i < aspects.size(); ++i){
        if(aspects[i] == renderable){
            continue;
        }
        delete aspects[i];
    }
    aspects.clear();
    aspects.push_back(renderable);
}

void Enemy::OnDeath(){
    int rand = std::rand() % 100;
    if(rand < 12){
        engine->entityMgr->CreateEntity(EntityType::HandgunType, position);
    }
    Ogre::Vector3 newPos = Ogre::Vector3(0, 0, 25e6);
    position = newPos;
    anim->DisableAnimation();
    ResetAspects();
    engine->waveMgr->OnEnemyKilled(this);
}

