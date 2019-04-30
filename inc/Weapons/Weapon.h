/*
 * Weapon.h
 *
 *  Created on: Apr 19, 2019
 *      Author: kylebrain
 */

#ifndef INC_WEAPON_H_
#define INC_WEAPON_H_

#include "Entity381.h"
#include "WeaponMgr.h"

class Weapon : public Entity381{
public:
    Weapon(int id, std::string meshName, Ogre::Vector3 _scale, Ogre::Vector3 pos,
           Engine * eng, float useRate, int damageAmount);
    virtual ~Weapon();

    float UseRate;
    int DamageAmount;
    WeaponSpawnPoint * spawnedFrom;

    virtual void Use() = 0;
};

#endif /* INC_WEAPON_H_ */
