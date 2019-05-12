/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_ORIENTEDPHYSICS_H_
#define INC_ASPECTS_ORIENTEDPHYSICS_H_

#include "Aspect.h"
#include "OgreVector3.h"

class OrientedPhysics : public Aspect{
public:
    OrientedPhysics(Entity381 *entity, float accel, float turning, float maxSp);
    ~OrientedPhysics();
    void Tick(float dt);

    Ogre::Vector3 velocity;
    float desiredSpeed;
    float desiredHeading;

    const float acceleration;
    const float turningRate;
    const float maxSpeed;

    float speed;
    float heading;
private:
    void UpdateOrientation(float dt);
    void UpdateSpeed(float dt);
};

#endif /* INC_ASPECTS_ORIENTEDPHYSICS_H_ */
