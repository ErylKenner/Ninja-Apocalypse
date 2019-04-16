/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "OrientedPhysics3D.h"
#include "Entity381.h"

OrientedPhysics3D::OrientedPhysics3D(Entity381 *entity) :
        OrientedPhysics(entity){
}

void OrientedPhysics3D::Tick(float dt){
    UpdateOrientation(dt);

    float difference = entity381->desiredAltitude - entity381->altitude;
    if(difference < 0){
        difference = -difference;
    }
    if(difference <= entity381->climbRate * dt){
        entity381->altitude = entity381->desiredAltitude;
    } else if(entity381->altitude < entity381->desiredAltitude){
        entity381->altitude += entity381->climbRate * dt;
    } else{
        entity381->altitude -= entity381->climbRate * dt;
    }

    entity381->velocity.x = entity381->speed * cos(entity381->heading * 3.1416 / 180);
    entity381->velocity.y = 0;
    entity381->velocity.z = entity381->speed * -sin(-entity381->heading * 3.1416 / 180);

    entity381->position += entity381->velocity * dt;
    entity381->position.y = entity381->altitude;
}

OrientedPhysics3D::~OrientedPhysics3D(){
}


