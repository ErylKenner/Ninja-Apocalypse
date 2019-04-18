/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_H_
#define INC_ASPECTS_COLLIDER_H_

#include <vector>
#include "Aspect.h"

class Collider : public Aspect{
public:
    Collider(Entity381 *entity);
    ~Collider();
    virtual void Tick(float dt) = 0;
    virtual bool IsColliding() const = 0;
protected:
    static std::vector<Collider *> colliders;
private:
};

#endif /* INC_ASPECTS_COLLIDER_H_ */
