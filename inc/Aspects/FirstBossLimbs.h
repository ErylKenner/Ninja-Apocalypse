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

class FirstBossLimbs : public Aspect {
public:
    FirstBossLimbs(Entity381 * entity);
    ~FirstBossLimbs();

    virtual void Tick(float dt);

    Entity381 * rectLeft;
    Entity381 * rectRight;
    Entity381 * weakPoint;

private:
    void SetParent(Ogre::SceneNode * attaching, Ogre::SceneNode * newParent);
};



#endif /* INC_ASPECTS_FIRSTBOSSLIMBS_H_ */
