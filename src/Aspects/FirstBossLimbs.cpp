/*
 * FirstBossLimbs.cpp
 *500
 *  Created on: Apr 30, 2019
 *      Author: kylebrain
 */

#include "FirstBossLimbs.h"
#include "Entity381.h"
#include "Collider.h"
#include "BossCollider.h"

FirstBossLimbs::FirstBossLimbs(Entity381 * entity) :
        Aspect(entity){

    // create left limb
    rectLeft = new RectangleEntity381(entity381->entityId, Ogre::Vector3::ZERO,
            Ogre::Vector3(limbWidth, limbHeight, limbLength), entity381->engine);
    SetParent(rectLeft->ogreSceneNode, entity->ogreSceneNode);

    rectLeft->position = Ogre::Vector3(limbForward, 0, -limbSides);
    rectLeft->ogreSceneNode->yaw(Ogre::Degree(-limbAngle));

    // replace default left Collider with LimbCollider
    Collider * defaultLeftCol = rectLeft->GetAspect<Collider>();
    rectLeft->aspects.erase(
            std::remove(rectLeft->aspects.begin(), rectLeft->aspects.end(),
                    defaultLeftCol));
    delete defaultLeftCol;
    defaultLeftCol = NULL;
    rectLeft->aspects.push_back(
            new BossLimbRectangleCollider(rectLeft, static_cast<Boss*>(entity381),
                    limbWidth, limbLength, limbDamageAmount));

    // create right limb
    rectRight = new RectangleEntity381(entity381->entityId, Ogre::Vector3::ZERO,
            Ogre::Vector3(limbWidth, limbHeight, limbLength), entity381->engine);
    SetParent(rectRight->ogreSceneNode, entity->ogreSceneNode);

    rectRight->position = Ogre::Vector3(limbForward, 0, limbSides);
    rectRight->ogreSceneNode->yaw(Ogre::Degree(limbAngle));

    // replace default right Collider with LimbCollider
    Collider * defaultRightCol = rectRight->GetAspect<Collider>();
    rectRight->aspects.erase(
            std::remove(rectRight->aspects.begin(), rectRight->aspects.end(),
                    defaultRightCol));
    delete defaultRightCol;
    defaultRightCol = NULL;
    rectRight->aspects.push_back(
            new BossLimbRectangleCollider(rectRight, static_cast<Boss*>(entity381),
                    limbWidth, limbLength, limbDamageAmount));

    weakPoint = new SphereEntity381(entity381->entityId, Ogre::Vector3::ZERO,
            weakPointRadius, entity381->engine);
    SetParent(weakPoint->ogreSceneNode, entity->ogreSceneNode);

    weakPoint->position = Ogre::Vector3(weakPointForward, 0, 0);

}
FirstBossLimbs::~FirstBossLimbs(){

}

void FirstBossLimbs::Tick(float dt){
    rectLeft->Tick(dt);
    rectRight->Tick(dt);
    weakPoint->Tick(dt);

    param += dt * armMovementSpeed;
    if(param >= 1){
        param = 0;
    }

    float clap = ComputeClapParam(param, 0.235);

    float actualParam = param;

    float angleLeft = GetLimbAngle(1 - actualParam, limbAngle);
    float angleRight = GetLimbAngle(actualParam, -limbAngle);
    rectLeft->ogreSceneNode->resetOrientation();
    rectRight->ogreSceneNode->resetOrientation();

    rectLeft->ogreSceneNode->yaw(Ogre::Degree(90 + angleLeft));
    rectRight->ogreSceneNode->yaw(Ogre::Degree(90 + angleRight));

    rectLeft->position = (GetLimbPosition(angleLeft, Ogre::Vector2(limbForward, -limbSides)));
    rectRight->position = (GetLimbPosition(angleRight, Ogre::Vector2(limbForward, limbSides)));
}

void FirstBossLimbs::SetParent(Ogre::SceneNode * attaching, Ogre::SceneNode * newParent){
    attaching->getParentSceneNode()->removeChild(attaching);
    newParent->addChild(attaching);
    attaching->setInheritScale(false);
    attaching->setOrientation(Ogre::Quaternion());

}

float FirstBossLimbs::GetLimbAngle(float t, float zeroAngle){
    return 360 * t + zeroAngle;
}
Ogre::Vector3 FirstBossLimbs::GetLimbPosition(float angle, Ogre::Vector2 center){
    float radius = limbLength / 2.0;
    return Ogre::Vector3(
            center.x
                    + radius * Ogre::Math::Cos(Ogre::Degree(angle)) / entity381->scale.x,
            0,
            center.y
                    + -radius * Ogre::Math::Sin(Ogre::Degree(angle)) / entity381->scale.z);
}

float FirstBossLimbs::ComputeClapParam(float param, float clapAmount) {
    if(param < 0.5) {
        return 2 * clapAmount * param;
    } else {
        return 2 * clapAmount - 2 * clapAmount * param;
    }
}

