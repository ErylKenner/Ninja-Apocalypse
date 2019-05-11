/*
 * BossAI.cpp
 *
 *  Created on: May 11, 2019
 *      Author: kylebrain
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

#include "BossAI.h"
#include "Entity381.h"

BossAI::BossAI(Entity381 *entity, Entity381 * plyr) :
        Aspect(entity),
        player(plyr),
        currentState(Track){
    bossPhysics = entity->GetAspect<OrientedPhysics3D>();
    bossLimbs = entity->GetAspect<FirstBossLimbs>();
    std::srand(std::time(nullptr));
}
BossAI::~BossAI(){
}
void BossAI::Tick(float dt){

    switch(currentState) {
        case Track:
            timer += dt;
            TrackPlayer();
            bossLimbs->mode = None;
            bossPhysics->desiredSpeed = trackingSpeed;
            if(CheckTimer(changeStateFromTrackAfter)){
                int rand = std::rand() % 4;
                if(rand < 2){
                    currentState = HeliA;
                    currentHeliSpeed = 0;
                    // 1/2 chance of helicopter
                } else{
                    // 1/2 chance of clap
                    currentState = ClapA;
                }
            }
            break;
        case ClapA:
            // TODO: reset to track if weakpoint is hit enough
            TrackPlayer();
            bossPhysics->desiredSpeed = 0;
            bossLimbs->mode = Clap;
            bossLimbs->param += windUpSpeed * dt;

            if(bossLimbs->param >= 0.5){
                currentState = ClapB;
            }
            break;
        case ClapB:
            // TODO: reset to track if weakpoint is hit enough
            TrackPlayer();
            bossPhysics->desiredSpeed = bossPhysics->maxSpeed;
            bossLimbs->mode = Clap;

            if(entity381->position.distance(player->position) < clapDistance){
                currentState = ClapC;
            }
            break;
        case ClapC:
            bossPhysics->desiredSpeed = 0;
            bossLimbs->mode = Clap;
            bossLimbs->param += clapSpeed * dt;

            if(bossLimbs->param >= 1){
                bossLimbs->param = 0;
                currentState = Track;
            }
            break;
        case HeliA:
            bossPhysics->desiredSpeed = 0;
            currentHeliSpeed += heliChargeSpeed * dt;
            bossLimbs->mode = Helicopter;
            bossLimbs->param += currentHeliSpeed * dt;

            if(bossLimbs->param >= 1){
                bossLimbs->param = 0;
            }

            if(currentHeliSpeed >= heliSpeed){
                currentState = HeliB;
            }

            break;
        case HeliB:

            bossPhysics->desiredSpeed = bossPhysics->maxSpeed;

            bossLimbs->mode = Helicopter;
            bossLimbs->param += heliSpeed * dt;

            if(bossLimbs->param >= 1){
                bossLimbs->param = 0;
            }

            timer += dt;

            if(CheckTimer(rushDuration)){
                currentState = HeliC;
            }

            break;
        case HeliC:
            bossPhysics->desiredSpeed = 0;
            currentHeliSpeed -= heliDischargeSpeed * dt;

            if(currentHeliSpeed < minHeliResetSpeed) {
                currentHeliSpeed = minHeliResetSpeed;
            }

            bossLimbs->mode = Helicopter;
            bossLimbs->param += currentHeliSpeed * dt;

            if(bossLimbs->param >= 1){
                bossLimbs->param = 0;
                if(currentHeliSpeed == minHeliResetSpeed) {
                    currentState = Track;
                }
            }
            break;
        default:
            std::cerr << "Boss state enum not implemented in BossAI Tick!" << std::endl;
            break;
    }
}

bool BossAI::CheckTimer(float target){
    if(timer >= target){
        timer = 0;
        return true;
    } else{
        return false;
    }
}

void BossAI::TrackPlayer(){
    Ogre::Vector3 diff = player->position - entity381->position;
    bossPhysics->desiredHeading = Ogre::Math::fRad2Deg * atan2f(diff.z, diff.x);
}

