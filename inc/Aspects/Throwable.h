/*
 * Throwable.h
 *
 *  Created on: Apr 21, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_THROWABLE_H_
#define INC_ASPECTS_THROWABLE_H_

#include "Aspect.h"
#include "OgreVector3.h"

class Throwable : public Aspect {
public:
    Throwable(Entity381 *entity, float speed);
    ~Throwable();
    void Tick(float dt);

    void Throw(float direction);

    float Speed;
    bool Thrown = false;

private:
    Ogre::Vector3 thrownDirection;
};

#endif /* INC_ASPECTS_THROWABLE_H_ */
