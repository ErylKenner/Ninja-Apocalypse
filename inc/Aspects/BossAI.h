/*
 * BossAI.h
 *
 *  Created on: May 11, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_BOSSAI_H_
#define INC_ASPECTS_BOSSAI_H_

#include "Aspect.h"
#include "OrientedPhysics3D.h"
#include "FirstBossLimbs.h"

enum BossState {Track, ClapA, ClapB, ClapC, HeliA, HeliB, HeliC};

class BossAI : public Aspect{
public:
    BossAI(Entity381 *entity, Entity381 * plyr);
    ~BossAI();
    void Tick(float dt);

    Entity381 * player;
    BossState currentState;
    OrientedPhysics3D * bossPhysics;
    FirstBossLimbs * bossLimbs;

private:
    float timer = 0;
    bool CheckTimer(float target);

    const int changeStateFromTrackAfter = 5;
    const int trackingSpeed = 50;

    const int clapDistance = 550;
    const float windUpSpeed = 0.5;
    const int clapSpeed = 5;

    const float heliChargeSpeed = 5;
    const float heliDischargeSpeed = 3;
    const float minHeliResetSpeed = 0.5;
    const float heliSpeed = 5;
    const int rushDuration = 2;

    float currentHeliSpeed = 0;

    void TrackPlayer();
};


#endif /* INC_ASPECTS_BOSSAI_H_ */
