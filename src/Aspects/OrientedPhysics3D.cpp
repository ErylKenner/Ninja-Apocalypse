/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "OrientedPhysics3D.h"
#include "Entity381.h"

OrientedPhysics3D::OrientedPhysics3D(Entity381 *entity, float accel, float turning, float maxSp) :
        Aspect(entity),
        desiredSpeed(0),
        desiredHeading(entity->ogreSceneNode->getOrientation().getYaw().valueDegrees()),
        desiredAltitude(entity->position.y),
        acceleration(accel),
        turningRate(turning),
        climbRate(0),
        maxSpeed(maxSp),
        speed(0),
        heading(entity->ogreSceneNode->getOrientation().getYaw().valueDegrees()),
        altitude(entity->position.y){
}

void OrientedPhysics3D::UpdateSpeed(float dt){
    if(speed < desiredSpeed){
        speed += acceleration * dt;
    } else{
        speed -= acceleration * dt;
    }

    //Fix speed
    if(speed < 0){
        speed = 0;
    } else if(speed > maxSpeed){
        speed = maxSpeed;
    }
}

void OrientedPhysics3D::UpdateOrientation(float dt){
    //Fix desired heading
    if(desiredHeading < 0){
        desiredHeading += 360;
    } else if(desiredHeading > 360){
        desiredHeading -= 360;
    }

    //Calculate heading
    float difference = desiredHeading - heading;
    if(difference < 0){
        difference += 360;
    }
    if(difference <= turningRate * dt || (360 - difference) <= turningRate * dt){
        heading = desiredHeading;
    } else if(difference > 180){
        heading -= turningRate * dt;
    } else{
        heading += turningRate * dt;
    }

    //Fix heading
    if(heading < 0){
        heading += 360;
    } else if(heading > 360){
        heading -= 360;
    }
}

void OrientedPhysics3D::Tick(float dt){
    UpdateSpeed(dt);
    UpdateOrientation(dt);

    velocity.x = speed * cos(heading * 3.1416 / 180);
    velocity.y = (desiredAltitude - altitude) < 0 ? -climbRate : climbRate;
    velocity.z = speed * -sin(-heading * 3.1416 / 180);

    entity381->position += velocity * dt;
    //entity381->position.y = altitude;
}

OrientedPhysics3D::~OrientedPhysics3D(){
}

