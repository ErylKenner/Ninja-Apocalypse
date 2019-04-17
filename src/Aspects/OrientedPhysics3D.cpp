/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "OrientedPhysics3D.h"
#include "Entity381.h"

OrientedPhysics3D::OrientedPhysics3D(Entity381 *entity, float accel, float turning, float maxSp) :
        Aspect(entity),
        desiredSpeed(0),
        desiredHeading(0),
        desiredAltitude(0),
        acceleration(accel),
        turningRate(turning),
        climbRate(0),
        maxSpeed(maxSp),
        speed(0),
        heading(0),
        altitude(0){
}

void OrientedPhysics3D::UpdateOrientation(float dt){
    //Calculate speed
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
    UpdateOrientation(dt);

    float difference = desiredAltitude - altitude;
    if(difference < 0){
        difference = -difference;
    }
    if(difference <= climbRate * dt){
        altitude = desiredAltitude;
    } else if(altitude < desiredAltitude){
        altitude += climbRate * dt;
    } else{
        altitude -= climbRate * dt;
    }

    velocity.x = speed * cos(heading * 3.1416 / 180);
    velocity.y = 0;
    velocity.z = speed * -sin(-heading * 3.1416 / 180);

    entity381->position += velocity * dt;
    //entity381->position.y = altitude;
}

OrientedPhysics3D::~OrientedPhysics3D(){
}

