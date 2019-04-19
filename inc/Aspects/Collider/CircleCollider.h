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

#endif /* INC_ASPECTS_COLLIDER_CIRCLECOLLIDER_H_ */
