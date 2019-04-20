/*
 * Weapon.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: kylebrain
 */

#include "Weapon.h"
#include "Renderable.h"

Weapon::Weapon(int id, std::string meshName, Ogre::Vector3 _scale, Ogre::Vector3 pos,
               Engine * eng) :
        Entity381(id, meshName, pos, eng),
        FireRate(0.25f),
        BulletMax(20),
        DamageAmount(20){
    scale = _scale / 100.0f;
    aspects.push_back(new Renderable(this));
    ogreEntity->setMaterialName("Examples/BumpyMetal");

    CurrentBulletNumber =  BulletMax;
}
Weapon::~Weapon(){
}
void Weapon::InitAspects(){
}

void Weapon::Fire() {
    if(CurrentBulletNumber > 0) {
        CurrentBulletNumber--;
        std::cout << "Bang! " << CurrentBulletNumber << " bullets left." << std::endl;
        // create a ray from the player's position (perhaps pass in a ray?)
        // selected the closest intersected collider
        // if it's an enemy, deal damage to it
        // check if it's dead
           // if so, call onKilled
    }

}

