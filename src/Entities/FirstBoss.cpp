/*
 * FirstBoss.cpp
 *
 *  Created on: Apr 29, 2019
 *      Author: kylebrain
 */

#include "FirstBoss.h"
#include "GameMgr.h"
#include "UnitAI.h"
#include "CircleCollider.h"
#include "Entity381.h"

FirstBoss::FirstBoss(int id, Ogre::Vector3 pos, Engine * eng) :
        Boss(id, "sphere.mesh", Ogre::Vector3(1, 0.8, 1.3), // scale
        pos, "Googalog", 1000, // Health
                50, 45, 100, // OrientedPhysics values
                eng){
    ogreEntity->setMaterialName("Stone");
    GetAspect<UnitAI>()->SetCommand(new Intercept(this, eng->gameMgr->MainPlayer));

    aspects.push_back(new CircleCollider(this, scale.x * 100));

    RectangleEntity381 * rectLeft = new RectangleEntity381(id, Ogre::Vector3::ZERO,
            Ogre::Vector3(100, 50, 300), eng);

    rectLeft->ogreSceneNode->getParentSceneNode()->removeChild(rectLeft->ogreSceneNode);
    ogreSceneNode->addChild(rectLeft->ogreSceneNode);
    rectLeft->ogreSceneNode->setOrientation(Ogre::Quaternion());
    rectLeft->position = Ogre::Vector3(48, 0, -200);
    rectLeft->ogreSceneNode->yaw(Ogre::Degree(-20));

    rectLeft->ogreSceneNode->setInheritScale(false);

    rectLeft->Tick(0);

    RectangleEntity381 * rectRight = new RectangleEntity381(id, Ogre::Vector3::ZERO,
            Ogre::Vector3(100, 50, 300), eng);

    rectRight->ogreSceneNode->getParentSceneNode()->removeChild(rectRight->ogreSceneNode);
    ogreSceneNode->addChild(rectRight->ogreSceneNode);
    rectRight->ogreSceneNode->setOrientation(Ogre::Quaternion());
    rectRight->position = Ogre::Vector3(48, 0, 200);
    rectRight->ogreSceneNode->yaw(Ogre::Degree(20));

    rectRight->ogreSceneNode->setInheritScale(false);

    rectRight->Tick(0);

    SphereEntity381 * weakPoint = new SphereEntity381(id, Ogre::Vector3::ZERO,
            20, eng);

    weakPoint->ogreSceneNode->getParentSceneNode()->removeChild(weakPoint->ogreSceneNode);
    ogreSceneNode->addChild(weakPoint->ogreSceneNode);
    weakPoint->ogreSceneNode->setOrientation(Ogre::Quaternion());
    weakPoint->position = Ogre::Vector3(105, 0, 0);
    weakPoint->ogreSceneNode->yaw(Ogre::Degree(20));

    weakPoint->ogreSceneNode->setInheritScale(false);

    weakPoint->Tick(0);

}
FirstBoss::~FirstBoss(){
}
