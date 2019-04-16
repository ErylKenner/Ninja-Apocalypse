/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "Command.h"
#include "Entity381.h"
#include "UnitAI.h"

Command::Command(Entity381* ent) :
        entity(ent),
        unitAI(NULL){
}

Command::~Command(){
}

//-----------------------------------

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location) :
        Command(ent),
        targetLocation(location){
}

MoveTo::~MoveTo(){
}

void MoveTo::Init(){
    unitAI = entity->GetAspect<UnitAI>();
}

void MoveTo::Tick(float dt){
    Ogre::Vector3 diff = targetLocation - entity->position;
    entity->desiredHeading = 180 / 3.1415 * atan2f(diff.z, diff.x);
    float dist = diff.length();
    if(dist > (entity->maxSpeed * entity->maxSpeed) / (2 * entity->acceleration)){
        entity->desiredSpeed = entity->maxSpeed;
    } else if(unitAI != NULL && unitAI->NumCommands() > 1){
        entity->desiredSpeed = entity->maxSpeed;
    } else{
        entity->desiredSpeed = 0;
    }
}

bool MoveTo::Done(){
    return entity->position.distance(targetLocation) <= moveDistanceThreshold;
}

void MoveTo::Finish(){
    if(unitAI != NULL && unitAI->NumCommands() > 1){
        entity->desiredSpeed = entity->maxSpeed;
    } else{
        entity->desiredSpeed = 0;
        entity->desiredHeading = entity->heading;
    }
}

//-----------------------------------

Intercept::Intercept(Entity381* ent, Entity381 *target) :
        Command(ent),
        targetObject(target){
}

void Intercept::Init(){

}

void Intercept::Tick(float dt){
    float timeNeeded = (targetObject->position - entity->position).length() / (targetObject->velocity - entity->velocity).length();
    Ogre::Vector3 interceptLocation = targetObject->position + targetObject->velocity * timeNeeded;
    Ogre::Vector3 diff = interceptLocation - entity->position;
    entity->desiredHeading = 180 / 3.1415 * atan2f(diff.z, diff.x);
    float dist = diff.length();
    if(dist > (entity->maxSpeed * entity->maxSpeed) / (2 * entity->acceleration)){
        entity->desiredSpeed = entity->maxSpeed;
    } else{
        entity->desiredSpeed = 0;
    }
}

bool Intercept::Done(){
    return entity->position.distance(targetObject->position) <= moveDistanceThreshold;
}

void Intercept::Finish(){
    if(unitAI != 0 && unitAI->NumCommands() > 1){
        entity->desiredSpeed = entity->maxSpeed;
    } else{
        entity->desiredSpeed = 0;
        entity->desiredHeading = entity->heading;
    }
}

Intercept::~Intercept(){
}

