/*
 * BossCollider.h
 *
 *  Created on: Apr 30, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_COLLIDER_BOSSCOLLIDER_H_
#define INC_ASPECTS_COLLIDER_BOSSCOLLIDER_H_

#include "Collider.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Boss.h"

class BossCircleCollider : public CircleCollider{
public:
    BossCircleCollider(Entity381 *entity, Boss * boss, int r);
    ~BossCircleCollider();

    Boss * bossEntity;
};

class BossRectangleCollider : public RectangleCollider{
public:
    BossRectangleCollider(Entity381 *entity, Boss * boss, int w, int l);
    ~BossRectangleCollider();

    Boss * bossEntity;
};

class BossLimbRectangleCollider : public BossRectangleCollider{
public:
    BossLimbRectangleCollider(Entity381 *entity, Boss * boss, int w, int l, int damage);
    ~BossLimbRectangleCollider();

    int damageAmount;

    virtual void OnCollision(Collider *other) const;
};

/*
 class BodyBossCollider : public BossCircleCollider{
 public:
 BodyBossCollider(Entity381 *entity, int r);
 ~BodyBossCollider();

 virtual void OnCollision(Collider *other) const;
 };
 */

#endif /* INC_ASPECTS_COLLIDER_BOSSCOLLIDER_H_ */
