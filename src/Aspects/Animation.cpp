/*
 * Animation.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#include "Animation.h"
#include "Entity381.h"
#include "OrientedPhysics3D.h"

Animation::Animation(Entity381 * entity) :
        Aspect(entity),
        animState(0),
        animSpeed(1){
}
Animation::~Animation(){
}

std::string Animation::GetAnimationName(){
    if(animState != NULL){
        return animState->getAnimationName();
    } else{
        return "";
    }
}

void Animation::SetAnimation(std::string newState, bool looped, float newAnimSpeed){
    animState = entity381->ogreEntity->getAnimationState(newState);
    animState->setLoop(looped);
    animState->setEnabled(true);
    animSpeed = newAnimSpeed;
}

void Animation::DisableAnimation(){
    animState->setEnabled(false);
}

void Animation::Tick(float dt){
    if(animState != NULL && animState->getEnabled()){
        animState->addTime(animSpeed * dt);
    }
    OrientedPhysics3D *physics = entity381->GetAspect<OrientedPhysics3D>();
    if(physics != NULL && physics->speed == 0){
        DisableAnimation();
    } else if(animState != NULL){
        if(animState->getEnabled()){
            animState->addTime(animSpeed * dt);
        } else{
            SetAnimation("Walk", true, 1.2);
        }
    }
}
