/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "OrientedPhysics.h"
#include "Entity381.h"

OrientedPhysics::OrientedPhysics(Entity381 *entity) :
        Aspect(entity){
}

void OrientedPhysics::Tick(float dt){
    UpdateOrientation(dt);

    entity381->velocity.x = entity381->speed * cos(entity381->heading * 3.1416 / 180);
    entity381->velocity.y = 0;
    entity381->velocity.z = entity381->speed * -sin(-entity381->heading * 3.1416 / 180);

    entity381->position += entity381->velocity * dt;
}

void OrientedPhysics::UpdateOrientation(float dt){
    //Calculate speed
    if(entity381->speed < entity381->desiredSpeed){
        entity381->speed += entity381->acceleration * dt;
    } else{
        entity381->speed -= entity381->acceleration * dt;
    }

    //Fix speed
    if(entity381->speed < 0){
        entity381->speed = 0;
    } else if(entity381->speed > entity381->maxSpeed){
        entity381->speed = entity381->maxSpeed;
    }

    //Fix desired heading
    if(entity381->desiredHeading < 0){
        entity381->desiredHeading += 360;
    } else if(entity381->desiredHeading > 360){
        entity381->desiredHeading -= 360;
    }

    //Calculate heading
    float difference = entity381->desiredHeading - entity381->heading;
    if(difference < 0){
        difference += 360;
    }
    if(difference <= entity381->turningRate * dt || (360 - difference) <= entity381->turningRate * dt){
        entity381->heading = entity381->desiredHeading;
    } else if(difference > 180){
        entity381->heading -= entity381->turningRate * dt;
    } else{
        entity381->heading += entity381->turningRate * dt;
    }

    //Fix heading
    if(entity381->heading < 0){
        entity381->heading += 360;
    } else if(entity381->heading > 360){
        entity381->heading -= 360;
    }
}

OrientedPhysics::~OrientedPhysics(){
}


