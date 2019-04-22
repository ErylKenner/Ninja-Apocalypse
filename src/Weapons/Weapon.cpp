/*
 * Weapon.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: kylebrain
 */

#include "Weapon.h"
#include "Renderable.h"
#include "CircleCollider.h"
#include "Throwable.h"

Weapon::Weapon(int id, std::string meshName, Ogre::Vector3 _scale, Ogre::Vector3 pos,
               Engine * eng, float useRate, int damageAmount) :
        Entity381(id, meshName, pos, eng),
        UseRate(useRate),
        DamageAmount(damageAmount){
    scale = _scale / 100.0f;
    aspects.push_back(new Throwable(this, 600));
    aspects.push_back(new WeaponCollider(this, 25));
    aspects.push_back(new Renderable(this));

}
Weapon::~Weapon(){
    for(unsigned int i = 0; i < aspects.size(); i++) {
        if(aspects[i] != NULL) {
            delete aspects[i];
        }
    }
}
