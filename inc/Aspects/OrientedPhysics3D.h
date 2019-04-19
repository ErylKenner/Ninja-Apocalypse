/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_ORIENTEDPHYSICS3D_H_
#define INC_ASPECTS_ORIENTEDPHYSICS3D_H_

#include "Aspect.h"
#include "OgreVector3.h"

class OrientedPhysics3D : public Aspect{
public:
    OrientedPhysics3D(Entity381 *entity, float accel, float turning, float maxSp);
    ~OrientedPhysics3D();
    void Tick(float dt);

    Ogre::Vector3 velocity;
    float desiredSpeed;
    float desiredHeading;
    float desiredAltitude;

    const float acceleration;
    const float turningRate;
    const float climbRate;
    const float maxSpeed;

    float speed;
    float heading;
    float altitude;
private:
    void UpdateOrientation(float dt);
    void UpdateSpeed(float dt);
};

#endif /* INC_ASPECTS_ORIENTEDPHYSICS3D_H_ */
