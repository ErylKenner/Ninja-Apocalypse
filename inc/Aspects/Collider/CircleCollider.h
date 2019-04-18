/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */


#ifndef INC_ASPECTS_COLLIDER_CIRCLECOLLIDER_H_
#define INC_ASPECTS_COLLIDER_CIRCLECOLLIDER_H_

#include "Collider.h"

class CircleCollider : public Collider{
public:
    CircleCollider(Entity381 *entity);
    ~CircleCollider();
    void Tick(float dt);
    bool IsColliding() const;
protected:
private:
};

#endif /* INC_ASPECTS_COLLIDER_CIRCLECOLLIDER_H_ */
