/*
 * Boss.h
 *
 *  Created on: Apr 29, 2019
 *      Author: kylebrain
 */

#ifndef INC_ENTITIES_BOSS_H_
#define INC_ENTITIES_BOSS_H_

#include "Entity381.h"

class Boss : public Entity381{
public:
    Boss(int id, std::string meshName, Ogre::Vector3 sca, Ogre::Vector3 pos, std::string bossName, int health,
         float accel, float turning, float maxSp, Engine * eng);
    virtual ~Boss();

    std::string name;
};

#endif /* INC_ENTITIES_BOSS_H_ */
