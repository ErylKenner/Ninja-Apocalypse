/*
 * BossCollider.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: kylebrain
 */

#include "BossCollider.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Ray.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "WeaponHolder.h"
#include "Weapon.h"

BossCircleCollider::BossCircleCollider(Entity381 *entity, Boss * boss, int r) :
        CircleCollider(entity, r),
        bossEntity(boss){
}

void BossCircleCollider::OnCollision(Collider *other) const{
    WeaponCollider *castToWeapon = dynamic_cast<WeaponCollider *>(other);
    if(castToWeapon != NULL){
        Throwable *throwable = castToWeapon->entity381->GetAspect<Throwable>();
        if(throwable != NULL && throwable->Thrown){
            Weapon *weapon = dynamic_cast<Weapon *>(castToWeapon->entity381);
            if(weapon != NULL){
                if(!bossEntity->GetAspect<Health>()->TakeDamage(
                        weapon->ThrownDamageAmount)){
                    bossEntity->OnDeath();
                }
                castToWeapon->entity381->position = Ogre::Vector3(0, 0, 25e6);
                castToWeapon->entity381->GetAspect<Throwable>()->Thrown = false;
            }
        }
    }
}

BossCircleCollider::~BossCircleCollider(){
}

BossRectangleCollider::BossRectangleCollider(Entity381 *entity, Boss * boss, int w, int l) :
        RectangleCollider(entity, w, l),
        bossEntity(boss){
}
BossRectangleCollider::~BossRectangleCollider(){
}

BossLimbRectangleCollider::BossLimbRectangleCollider(Entity381 *entity, Boss * boss,
                                                     int w, int l, int damage) :
        BossRectangleCollider(entity, boss, w, l),
        damageAmount(damage){

}
BossLimbRectangleCollider::~BossLimbRectangleCollider(){

}

void BossLimbRectangleCollider::OnCollision(Collider *other) const{
}

BossWeakpointCircleCollider::BossWeakpointCircleCollider(Entity381 *entity, Boss * boss,
                                                         int r, float mult) :
        BossCircleCollider(entity, boss, r),
        damageMultiplier(mult){

}
BossWeakpointCircleCollider::~BossWeakpointCircleCollider(){

}
