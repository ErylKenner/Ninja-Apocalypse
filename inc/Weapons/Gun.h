/*
 * Gun.h
 *
 *  Created on: Apr 21, 2019
 *      Author: kylebrain
 */

#ifndef INC_WEAPONS_GUN_H_
#define INC_WEAPONS_GUN_H_

#include "Weapon.h"

class Gun : public Weapon{
public:
    Gun(int id, std::string meshName, Ogre::Vector3 _scale, Ogre::Vector3 pos,
        Engine * eng, float useRate, int damageAmount, int bulletMax,
        int thrownDamageAmount);
    virtual ~Gun();
    virtual void Use();

    int BulletMax;
    int CurrentBulletNumber;
};

class Handgun : public Gun{
public:
    Handgun(int id, Ogre::Vector3 pos, Engine * eng);
    virtual ~Handgun();
};

#endif /* INC_WEAPONS_GUN_H_ */
