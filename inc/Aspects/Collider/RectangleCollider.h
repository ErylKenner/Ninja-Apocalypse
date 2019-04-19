/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_
#define INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_

#include "Collider.h"

class RectangleCollider : public Collider{
public:
    RectangleCollider(Entity381 *entity, int w, int l);
    ~RectangleCollider();

    virtual void OnCollision(Collider *other) const;
    virtual bool IsColliding(Collider *other) const;
protected:
    int width;
    int length;
private:
};

#endif /* INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_ */
