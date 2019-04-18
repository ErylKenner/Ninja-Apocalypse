/*
 * Player.h
 *
 *  Created on: Apr 17, 2019
 *      Author: kylebrain
 */

#ifndef INC_PLAYER_H_
#define INC_PLAYER_H_

#include "Entity381.h"

using Ogre::Vector3;

class Player : public Entity381 {

public:
	float Speed;

	Player(float speed, Ogre::SceneNode * camera, int id, Vector3 pos, EntityMgr *entMgr);
    ~Player();
    virtual void InitAspects();

    void LookAt(Vector3 pos);
    void Move(Vector3 direction, float dt);

};



#endif /* INC_PLAYER_H_ */
