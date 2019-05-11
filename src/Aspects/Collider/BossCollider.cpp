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
#include "Health.h"

BossCircleCollider::BossCircleCollider(Entity381 *entity, Boss * boss, int r) :
        CircleCollider(entity, r),
        bossEntity(boss){
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
