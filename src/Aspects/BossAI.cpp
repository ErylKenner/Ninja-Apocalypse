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
        currentState(Track),
        weakPointHits(0){
    bossPhysics = entity->GetAspect<OrientedPhysics>();
    bossLimbs = entity->GetAspect<FirstBossLimbs>();
    std::srand(std::time(nullptr));
}
BossAI::~BossAI(){
}
void BossAI::Tick(float dt){

    switch(currentState) {
        case NoState:
            bossPhysics->desiredSpeed = 0;
            bossPhysics->speed = 0;
            break;
        case Track:
            timer += dt;
            TrackPlayer();
            bossLimbs->mode = None;
            bossLimbs->param = 0;
            bossPhysics->desiredSpeed = trackingSpeed;

            if(CheckTimer(changeStateFromTrackAfter)){
                int rand = std::rand() % 4;
                if(rand == 0){
                    // 1/4 chance of helicopter
                    currentState = HeliA;
                    currentHeliSpeed = 0;
                } else{
                    // 3/4 chance of clap
                    currentState = ClapA;
                    weakPointHits = 0;
                }
            }

            if(entity381->position.distance(player->position) < heliCloseDistance){
                // TODO: create new state in which it just heli's in place once
                currentState = HeliA;
                currentHeliSpeed = heliSpeed;
                timer = 0;
            }

            break;
        case ClapA:
            TrackPlayer();
            bossPhysics->desiredSpeed = 0;
            bossLimbs->mode = Clap;
            bossLimbs->param += windUpSpeed * dt;

            if(weakPointHits >= weakPointCancel){
                currentState = ClapC;
            }

            if(bossLimbs->param >= 0.5){
                currentState = ClapB;
            }

            break;
        case ClapB:
            TrackPlayer();
            bossPhysics->desiredSpeed = bossPhysics->maxSpeed;
            bossLimbs->mode = Clap;

            if(weakPointHits >= weakPointCancel){
                currentState = ClapC;
            }

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

            if(currentHeliSpeed < minHeliResetSpeed){
                currentHeliSpeed = minHeliResetSpeed;
            }

            bossLimbs->mode = Helicopter;
            bossLimbs->param += currentHeliSpeed * dt;

            if(bossLimbs->param >= 1){
                bossLimbs->param = 0;
                if(currentHeliSpeed == minHeliResetSpeed){
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

