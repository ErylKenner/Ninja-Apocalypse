/*
 * BossAI.h
 *
 *  Created on: May 11, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_BOSSAI_H_
#define INC_ASPECTS_BOSSAI_H_

#include "Aspect.h"
#include "OrientedPhysics.h"
#include "FirstBossLimbs.h"

enum BossState {Track, ClapA, ClapB, ClapC, HeliA, HeliB, HeliC};

class BossAI : public Aspect{
public:
    BossAI(Entity381 *entity, Entity381 * plyr);
    ~BossAI();
    void Tick(float dt);

    Entity381 * player;
    BossState currentState;
    OrientedPhysics * bossPhysics;
    FirstBossLimbs * bossLimbs;

    int weakPointHits;

private:
    float timer = 0;
    bool CheckTimer(float target);

    const int changeStateFromTrackAfter = 5;
    const int trackingSpeed = 50;
    const int heliCloseDistance = 300;

    const int clapDistance = 575;
    const float windUpSpeed = 0.5;
    const int clapSpeed = 5;
    const int weakPointCancel = 10;

    const float heliChargeSpeed = 10;
    const float heliDischargeSpeed = 8;
    const float minHeliResetSpeed = 0.5;
    const float heliSpeed = 5;
    const int rushDuration = 2;

    float currentHeliSpeed = 0;

    void TrackPlayer();
};


#endif /* INC_ASPECTS_BOSSAI_H_ */
