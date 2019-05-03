/*
 * FirstBossLimbs.h
 *
 *  Created on: Apr 30, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_FIRSTBOSSLIMBS_H_
#define INC_ASPECTS_FIRSTBOSSLIMBS_H_

#include "Aspect.h"
#include "OgreSceneNode.h"

enum ParameterMode { None, Helicopter, Clap };

class FirstBossLimbs : public Aspect{
public:
    FirstBossLimbs(Entity381 * entity);
    ~FirstBossLimbs();

    virtual void Tick(float dt);

    ParameterMode mode;
    bool repeat;
    float armMovementSpeed;

    void SetParameterMode(ParameterMode _mode);
    void SetNextParameterMode(ParameterMode _nextMode);

    Entity381 * rectLeft;
    Entity381 * rectRight;
    Entity381 * weakPoint;

private:
    void SetParent(Ogre::SceneNode * attaching, Ogre::SceneNode * newParent);

    const int limbWidth = 100;
    const int limbLength = 400;
    const int limbHeight = 50;

    const int limbForward = 125;
    const int limbSides = 125;

    const int limbAngle = 60;

    const int limbDamageAmount = 5;

    const int weakPointRadius = 20;
    const int weakPointForward = 105;

    float GetLimbAngle(float t, float zeroAngle);
    Ogre::Vector3 GetLimbPosition(float angle, Ogre::Vector2 center);
    float ComputeClapParam(float param, float clapAmount);

    float param = 0;
    ParameterMode nextMode = None;
    bool limbAnimEnabled = false;
};

#endif /* INC_ASPECTS_FIRSTBOSSLIMBS_H_ */
