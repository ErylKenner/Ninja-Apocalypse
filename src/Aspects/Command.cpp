/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "Command.h"
#include "Entity381.h"
#include "UnitAI.h"
#include "OrientedPhysics3D.h"

Command::Command(Entity381* ent) :
        entity(ent),
        unitAI(NULL),
        orientedPhysics3D(NULL){
}

Command::~Command(){
}

void Command::GoTo(Ogre::Vector3 diff, float dt){
    orientedPhysics3D->desiredHeading = Ogre::Math::fRad2Deg * atan2f(diff.z, diff.x);
    float dist = diff.length();
    float stoppingRadius = (orientedPhysics3D->maxSpeed * orientedPhysics3D->maxSpeed)
            / (2 * orientedPhysics3D->acceleration);
    //if(dist > stoppingRadius){
    orientedPhysics3D->desiredSpeed = orientedPhysics3D->maxSpeed;
    /*} else if(unitAI != NULL && unitAI->NumCommands() > 1){
     orientedPhysics3D->desiredSpeed = orientedPhysics3D->maxSpeed;
     } else{
     orientedPhysics3D->desiredSpeed = Ogre::Math::Sqrt(
     2 * dist * orientedPhysics3D->acceleration);
     }*/
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
    orientedPhysics3D = entity->GetAspect<OrientedPhysics3D>();
}

void MoveTo::Tick(float dt){
    if(orientedPhysics3D != NULL){
        Ogre::Vector3 diff = targetLocation - entity->position;
        diff.y = 0;
        GoTo(diff, dt);
    }
}

bool MoveTo::Done(){
    return entity->position.distance(targetLocation) <= moveDistanceThreshold;
}

void MoveTo::Finish(){
    if(orientedPhysics3D != NULL){
        if(unitAI != NULL && unitAI->NumCommands() > 1){
            orientedPhysics3D->desiredSpeed = orientedPhysics3D->maxSpeed;
        } else{
            orientedPhysics3D->desiredSpeed = 0;
            orientedPhysics3D->desiredHeading = orientedPhysics3D->heading;
        }
    }
}

//-----------------------------------

Intercept::Intercept(Entity381* ent, Entity381 *target) :
        Command(ent),
        targetObject(target){
}

void Intercept::Init(){
    unitAI = entity->GetAspect<UnitAI>();
    orientedPhysics3D = entity->GetAspect<OrientedPhysics3D>();
}

void Intercept::Tick(float dt){
    OrientedPhysics3D *targetPhysics = targetObject->GetAspect<OrientedPhysics3D>();
    if(orientedPhysics3D != NULL && targetPhysics != NULL){
        float timeNeeded = (targetObject->position - entity->position).length()
                / (targetPhysics->velocity - orientedPhysics3D->velocity).length();
        Ogre::Vector3 interceptLocation = targetObject->position
                + targetPhysics->velocity * timeNeeded;
        Ogre::Vector3 diff = interceptLocation - entity->position;
        diff.y = 0;
        GoTo(diff, dt);
    } else{
        GoTo(targetObject->position - entity->position, dt);
    }
}

bool Intercept::Done(){
    //return entity->position.distance(targetObject->position) <= moveDistanceThreshold;
    return false;
}

void Intercept::Finish(){
    if(orientedPhysics3D != NULL){
        if(unitAI != 0 && unitAI->NumCommands() > 1){
            orientedPhysics3D->desiredSpeed = orientedPhysics3D->maxSpeed;
        } else{
            orientedPhysics3D->desiredSpeed = 0;
            orientedPhysics3D->desiredHeading = orientedPhysics3D->heading;
        }
    }
}

Intercept::~Intercept(){
}

