/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_
#define INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_

#include "Collider.h"

class RectangleCollider : public Collider{
public:
    RectangleCollider(Entity381 *entity);
    RectangleCollider(Entity381 *entity, int w, int h);
    ~RectangleCollider();

    virtual void OnCollision(Collider *other) const;
    virtual bool IsColliding(Collider *other) const;

    int width;
    int height;
protected:
private:
};

#endif /* INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_ */
