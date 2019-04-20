/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_GFXMGR_H_
#define INC_GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include "Mgr.h"

class GfxMgr : public Mgr,
               public Ogre::WindowEventListener
{
public:
    GfxMgr(Engine *eng);
    ~GfxMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    Ogre::Root* mRoot;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::SceneNode *mCameraNode;
    Ogre::Viewport *mViewport;
    Ogre::Camera* mCamera;
private:
};

#endif /* INC_GFXMGR_H_ */
