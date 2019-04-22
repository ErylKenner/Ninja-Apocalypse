/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <SdkTrays.h>

UiMgr::UiMgr(Engine* eng) :
		Mgr(eng) {

	//Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr() { // before gfxMgr destructor

}

void UiMgr::Init() {

    // UiMgr Init MUST be called after GfxMgr Init because mOverlaySystem is created there (see GfxMgr Init comment for info)
	engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	// init sdktrays
	mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
	mInputContext.mMouse = engine->inputMgr->mMouse;
	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName",
			engine->gfxMgr->mWindow, mInputContext, this);

}

void UiMgr::stop() {

}

void UiMgr::LoadLevel() {

    std::cout << "Loading UiMgr" << std::endl;
	OgreBites::ProgressBar * pbar;
	pbar = mTrayMgr->createProgressBar(OgreBites::TL_TOP, "HealthBar", "Health",
			300, 200);
	pbar->setProgress(100);

}

void UiMgr::Tick(float dt) {
	mTrayMgr->refreshCursor();
}

void UiMgr::windowResized(Ogre::RenderWindow* rw) {

	 unsigned int width, height, depth;
	 int left, top;
	 rw->getMetrics(width, height, depth, left, top);

	 const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	 ms.width = width;
	 ms.height = height;

}

void UiMgr::windowClosed(Ogre::RenderWindow* rw) {

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg) {
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg) {
	if (mTrayMgr->injectMouseMove(arg))
		return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid))
		return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	if (mTrayMgr->injectMouseUp(arg, id))
		return true;
	/* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m) {

}
