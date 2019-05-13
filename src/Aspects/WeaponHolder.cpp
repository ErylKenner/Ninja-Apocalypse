/*
 * WeaponHolder.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: kylebrain
 */

#include "WeaponHolder.h"
#include "GfxMgr.h"
#include "Throwable.h"
#include "GameMgr.h"
#include "Renderable.h"
#include "EntityMgr.h"

WeaponHolder::WeaponHolder(Entity381 * entity) :
        Aspect(entity),
        heldWeapon(0),
        timeSinceLastShot(0){

}
WeaponHolder::~WeaponHolder(){
}

void WeaponHolder::Tick(float dt){
    timeSinceLastShot += dt;
}

void WeaponHolder::UseWeapon(){
    if(heldWeapon != NULL && timeSinceLastShot >= heldWeapon->UseRate){
        timeSinceLastShot = 0;
        heldWeapon->Use();
    }
}

void WeaponHolder::SetWeapon(Weapon * weapon){
    heldWeapon = weapon;
    //Ogre::Vector3 resultPosition = entity381->ogreSceneNode->convertWorldToLocalPosition(heldWeapon->ogreSceneNode->getPosition());
    //Ogre::Quaternion resultOrientation = entity381->ogreSceneNode->convertWorldToLocalOrientation(heldWeapon->ogreSceneNode->getOrientation());

    // if the picked up weapon had a spawnPoint
    if(heldWeapon->spawnedFrom != NULL){
        heldWeapon->spawnedFrom->ClearWeapon();
    }

    timeSinceLastShot = heldWeapon->UseRate;
    heldWeapon->ogreSceneNode->getParentSceneNode()->removeChild(
            heldWeapon->ogreSceneNode);
    entity381->ogreSceneNode->addChild(heldWeapon->ogreSceneNode);
    heldWeapon->ogreSceneNode->setOrientation(Ogre::Quaternion());
    heldWeapon->position = Ogre::Vector3(45, 35, -15);
    heldWeapon->ogreSceneNode->yaw(Ogre::Degree(-90));
    heldWeapon->ogreSceneNode->pitch(Ogre::Degree(-90));

    heldWeapon->ogreSceneNode->setInheritScale(false);
}

void WeaponHolder::ThrowWeapon(){
    if(heldWeapon != NULL){
        Ogre::SceneNode * root = entity381->engine->gfxMgr->mSceneMgr->getRootSceneNode();
        Ogre::Vector3 resultPosition =
                entity381->ogreSceneNode->convertLocalToWorldPosition(
                        heldWeapon->position);
        Ogre::Quaternion resultOrientation =
                entity381->ogreSceneNode->convertLocalToWorldOrientation(
                        heldWeapon->ogreSceneNode->getOrientation());

        heldWeapon->ogreSceneNode->getParentSceneNode()->removeChild(
                heldWeapon->ogreSceneNode);
        root->addChild(heldWeapon->ogreSceneNode);
        heldWeapon->ogreSceneNode->setOrientation(resultOrientation);
        heldWeapon->position = resultPosition;

        heldWeapon->ogreSceneNode->setInheritScale(false);

        //std::cout << heldWeapon->position << std::endl;

        heldWeapon->GetAspect<Throwable>()->Throw(
                entity381->engine->gameMgr->MainPlayer->GetCurrentAngle());
        heldWeapon = NULL;

        // for testing purposes
        //entity381->engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::HandgunType,
        //Ogre::Vector3(0, entity381->engine->gameMgr->surfaceHeight, -300));
    }
}

