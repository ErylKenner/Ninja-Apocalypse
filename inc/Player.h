/*
 * Player.h
 *
 *  Created on: Apr 17, 2019
 *      Author: kylebrain
 */

#ifndef INC_PLAYER_H_
#define INC_PLAYER_H_

#include "Entity381.h"
#include "OgreAnimationState.h"
#include "Animation.h"
#include "Collider.h"

using Ogre::Vector3;

class Player : public Entity381 {

public:
	float Speed;
	std::string walkAnimName = "Walk";
	std::string idleAnimName = "Idle3";

	float walkAnimSpeed = 1.5;

	Player(float speed, Ogre::SceneNode * camera, int id, Vector3 pos, Engine *eng);
    ~Player();
    virtual void InitAspects();

    void LookAt(Vector3 pos);
    void Move(Vector3 direction, float dt);

private:
    Animation * anim;

    //static void OnCollisionCallback(Collider *other);

};



#endif /* INC_PLAYER_H_ */
