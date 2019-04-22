/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_RAY_H_
#define INC_ASPECTS_COLLIDER_RAY_H_

#include "Collider.h"

class Ray{
public:
    Ray(Ogre::Vector2 start, Ogre::Vector2 dir);
    Ray(Ogre::Vector3 start, Ogre::Vector2 dir);
    ~Ray();
    Collider* GetClosestIntersectedCollider() const;

    Ogre::Vector2 origin;
    Ogre::Vector2 directionVector;
private:
};

#endif /* INC_ASPECTS_COLLIDER_RAY_H_ */
