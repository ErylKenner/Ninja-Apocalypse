/*
 * Animation.h
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_ANIMATION_H_
#define INC_ASPECTS_ANIMATION_H_

#include "Aspect.h"
#include "OgreAnimationState.h"

class Animation : public Aspect{
public:

    Animation(Entity381 * entity);
    ~Animation();

    std::string GetAnimationName();
    void SetAnimation(std::string newState, bool looped, float newAnimSpeed = 1);
    void DisableAnimation();

    virtual void Tick(float dt);

private:
    Ogre::AnimationState * animState;
    float animSpeed;
};

#endif /* INC_ASPECTS_ANIMATION_H_ */
