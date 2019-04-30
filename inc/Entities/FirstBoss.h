/*
 * FirstBoss.h
 *
 *  Created on: Apr 29, 2019
 *      Author: kylebrain
 */

#ifndef INC_ENTITIES_FIRSTBOSS_H_
#define INC_ENTITIES_FIRSTBOSS_H_

#include "Boss.h"

class FirstBoss : public Boss {
public:
    FirstBoss(int id, Ogre::Vector3 pos, Engine * eng);
    virtual ~FirstBoss();
};



#endif /* INC_ENTITIES_FIRSTBOSS_H_ */
