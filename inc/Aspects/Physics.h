/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_PHYSICS_H_
#define INC_ASPECTS_PHYSICS_H_

#include "Aspect.h"

class Physics : public Aspect{
public:
    Physics(Entity381 *entity);
    ~Physics();
    void Tick(float dt);
private:
};

#endif /* INC_ASPECTS_PHYSICS_H_ */
