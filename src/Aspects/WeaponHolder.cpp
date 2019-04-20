/*
 * WeaponHolder.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: kylebrain
 */

#include "WeaponHolder.h"

WeaponHolder::WeaponHolder(Entity381 * entity) : Aspect(entity), heldWeapon(0) {
}
WeaponHolder::~WeaponHolder(){
}

void WeaponHolder::Tick(float dt){
}

void WeaponHolder::SetWeapon(Weapon * weapon) {
    heldWeapon = weapon;
    heldWeapon->ogreSceneNode->getParentSceneNode()->removeChild(heldWeapon->ogreSceneNode);
    entity381->ogreSceneNode->addChild(heldWeapon->ogreSceneNode);
}

