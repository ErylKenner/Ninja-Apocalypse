/*
 * Enemy.h
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#ifndef INC_ENEMY_H_
#define INC_ENEMY_H_

#include "Entity381.h"
#include "Animation.h"

class Enemy : public Entity381{
public:
    Enemy(int id, Ogre::Vector3 pos, Engine * eng);
    virtual ~Enemy();

    void OnDeath();
    int hitDamage;
private:
    Animation * anim;
};

#endif /* INC_ENEMY_H_ */
