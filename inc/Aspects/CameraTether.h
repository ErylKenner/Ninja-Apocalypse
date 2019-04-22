/*
 * CameraTether.h
 *
 *  Created on: Apr 17, 2019
 *      Author: kylebrain
 */

#ifndef INC_ASPECTS_CAMERATETHER_H_
#define INC_ASPECTS_CAMERATETHER_H_

#include "Aspect.h"
#include "OgreSceneNode.h"

class CameraTether : public Aspect{
public:

    Ogre::SceneNode * CameraNode;
    float Height;
    CameraTether(Entity381 * entity, float height, Ogre::SceneNode * camNode = NULL);
    ~CameraTether();

    void SetCameraNode(Ogre::SceneNode * camNode);

    virtual void Tick(float dt);

private:
    void SetCameraPosition();
};

#endif /* INC_ASPECTS_CAMERATETHER_H_ */
