/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_CIRCLECOLLIDER_H_
#define INC_ASPECTS_COLLIDER_CIRCLECOLLIDER_H_

#include "Collider.h"

class CircleCollider : public Collider{
public:
    CircleCollider(Entity381 *entity, int rad);
    ~CircleCollider();

    virtual void OnCollision(Collider *other) const;
    virtual bool IsColliding(Collider *other) const;
    virtual bool IsColliding(const Ray *ray) const;
    virtual Ogre::Vector3 GetClosestPoint(Ogre::Vector3 point) const;

    int radius;
protected:
private:
};

class MovableCircleCollider : public CircleCollider{
public:
    MovableCircleCollider(Entity381 *entity, int rad);
    ~MovableCircleCollider();

    virtual void OnCollision(Collider *other) const;
};

class PlayerMovableCircleCollider : public MovableCircleCollider{
public:
    PlayerMovableCircleCollider(Entity381 *entity, int rad);
    ~PlayerMovableCircleCollider();

    virtual void OnCollision(Collider *other) const;
};

class EnemyMovableCircleCollider : public MovableCircleCollider{
public:
    EnemyMovableCircleCollider(Entity381 *entity, int rad);
    ~EnemyMovableCircleCollider();

    virtual void OnCollision(Collider *other) const;
};

#endif /* INC_ASPECTS_COLLIDER_CIRCLECOLLIDER_H_ */
