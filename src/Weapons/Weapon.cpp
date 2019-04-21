/*
 * Weapon.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: kylebrain
 */

#include "Weapon.h"
#include "Renderable.h"

Weapon::Weapon(int id, std::string meshName, Ogre::Vector3 _scale, Ogre::Vector3 pos,
               Engine * eng, float useRate, int damageAmount) :
        Entity381(id, meshName, pos, eng),
        UseRate(useRate),
        DamageAmount(damageAmount){
    scale = _scale / 100.0f;
    aspects.push_back(new Renderable(this));

}
Weapon::~Weapon(){
}
void Weapon::InitAspects(){
}

