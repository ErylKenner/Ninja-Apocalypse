/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

#include "GfxMgr.h"

GfxMgr::GfxMgr(Engine *eng) :
        Mgr(eng),
        mRoot(0),
        mResourcesCfg(Ogre::StringUtil::BLANK),
        mPluginsCfg(Ogre::StringUtil::BLANK),
        mWindow(0),
        mSceneMgr(0),
        mCameraNode(0),
        mViewport(0),
        mCamera(0){

}

GfxMgr::~GfxMgr(){
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

void GfxMgr::Init(){
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";

    mRoot = new Ogre::Root(mPluginsCfg);

    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    Ogre::String name, locType;
    Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

    while(secIt.hasMoreElements()){
        Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;

        for(it = settings->begin(); it != settings->end(); ++it){
            locType = it->first;
            name = it->second;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
        }
    }

    mRoot->showConfigDialog();

    mWindow = mRoot->initialise(true, "Application 381 Render Window");

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

    mCamera = mSceneMgr->createCamera("MainCam");
    mCamera->setNearClipDistance(5);

    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    mCamera->setAspectRatio(
            Ogre::Real(mViewport->getActualWidth())
                    / Ogre::Real(mViewport->getActualHeight()));

    mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    mCameraNode->attachObject(mCamera);
    mCameraNode->setPosition(Ogre::Vector3(0, 120, 400));
}

void GfxMgr::Tick(float dt){
    mRoot->renderOneFrame(dt);
}

void GfxMgr::LoadLevel(){

}

void GfxMgr::Stop(){

}

