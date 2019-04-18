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
    ~RectangleCollider();
    void Tick(float dt);
    bool IsColliding() const;
protected:
private:
};

#endif /* INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_ */
