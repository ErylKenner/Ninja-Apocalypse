/*
 * WeaponHolder.h
 *
 *  Created on: Apr 19, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_WEAPONHOLDER_H_
#define INC_ASPECTS_WEAPONHOLDER_H_

#include "Aspect.h"
#include "Weapon.h"

class WeaponHolder : public Aspect{
public:


    Weapon * heldWeapon;
    WeaponHolder(Entity381 * entity);
    ~WeaponHolder();

    void SetWeapon(Weapon * weapon);
    void UseWeapon();
    void ThrowWeapon();

    virtual void Tick(float dt);

private:
    float timeSinceLastShot;

};




#endif /* INC_ASPECTS_WEAPONHOLDER_H_ */
