/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_RAY_H_
#define INC_ASPECTS_COLLIDER_RAY_H_

#include "Collider.h"

class Ray{
public:
    Ray();
    ~Ray();
    Collider* GetIntersectedCollider() const;

    Ogre::Vector2 origin;
    Ogre::Vector2 secondPoint;
private:
};

#endif /* INC_ASPECTS_COLLIDER_RAY_H_ */
