/*
 * FirstBossLimbs.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: kylebrain
 */

#include "FirstBossLimbs.h"
#include "Entity381.h"
#include "Collider.h"
#include "BossCollider.h"

FirstBossLimbs::FirstBossLimbs(Entity381 * entity) :
        Aspect(entity){

    const int limbWidth = 100;
    const int limbLength = 300;

    // create left limb
    rectLeft = new RectangleEntity381(entity381->entityId, Ogre::Vector3::ZERO,
            Ogre::Vector3(limbWidth, 50, limbLength), entity381->engine);
    SetParent(rectLeft->ogreSceneNode, entity->ogreSceneNode);

    rectLeft->position = Ogre::Vector3(48, 0, -200);
    rectLeft->ogreSceneNode->yaw(Ogre::Degree(-20));

    // replace default left Collider with LimbCollider
    Collider * defaultLeftCol = rectLeft->GetAspect<Collider>();
    rectLeft->aspects.erase(
            std::remove(rectLeft->aspects.begin(), rectLeft->aspects.end(),
                    defaultLeftCol));
    delete defaultLeftCol;
    defaultLeftCol = NULL;
    rectLeft->aspects.push_back(
            new BossLimbRectangleCollider(rectLeft, static_cast<Boss*>(entity381),
                    limbWidth, limbLength, 20));

    // create right limb
    rectRight = new RectangleEntity381(entity381->entityId, Ogre::Vector3::ZERO,
            Ogre::Vector3(limbWidth, 50, limbLength), entity381->engine);
    SetParent(rectRight->ogreSceneNode, entity->ogreSceneNode);

    rectRight->position = Ogre::Vector3(48, 0, 200);
    rectRight->ogreSceneNode->yaw(Ogre::Degree(20));

    // replace default right Collider with LimbCollider
    Collider * defaultRightCol = rectRight->GetAspect<Collider>();
    rectRight->aspects.erase(
            std::remove(rectRight->aspects.begin(), rectRight->aspects.end(),
                    defaultRightCol));
    delete defaultRightCol;
    defaultRightCol = NULL;
    rectRight->aspects.push_back(
            new BossLimbRectangleCollider(rectRight, static_cast<Boss*>(entity381),
                    limbWidth, limbLength, 20));

    weakPoint = new SphereEntity381(entity381->entityId, Ogre::Vector3::ZERO, 20,
            entity381->engine);
    SetParent(weakPoint->ogreSceneNode, entity->ogreSceneNode);

    weakPoint->position = Ogre::Vector3(105, 0, 0);

}
FirstBossLimbs::~FirstBossLimbs(){

}

void FirstBossLimbs::Tick(float dt){
    rectLeft->Tick(dt);
    rectRight->Tick(dt);
    weakPoint->Tick(dt);
}

void FirstBossLimbs::SetParent(Ogre::SceneNode * attaching, Ogre::SceneNode * newParent){
    attaching->getParentSceneNode()->removeChild(attaching);
    newParent->addChild(attaching);
    attaching->setInheritScale(false);
    attaching->setOrientation(Ogre::Quaternion());

}

