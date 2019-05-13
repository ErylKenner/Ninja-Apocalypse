/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <time.h>
#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <SdkTrays.h>
#include <GameMgr.h>
#include <Health.h>
#include "WeaponHolder.h"
#include "Gun.h"
#include "WaveMgr.h"
#include "Boss.h"

UiMgr::UiMgr(Engine* eng) :
        Mgr(eng),
        waitTime(0),
        currentTime(0),
        splashScreenDisable(false){
    waveNum = "";
    ammoNum = "";
    timeElapsed = "";
    fps = "";
    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){


    // UiMgr Init MUST be called after GfxMgr Init because mOverlaySystem is created there (see GfxMgr Init comment for info)
    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

    // init sdktrays
    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow,
            mInputContext, this);


}

void UiMgr::stop(){

}

void UiMgr::LoadLevel() {
	waitTime = 3;
	mTrayMgr->showBackdrop("Backdrop");
	StartButton = mTrayMgr->createButton(OgreBites::TL_LEFT, "StartButton",
			"Start Game");
}


void UiMgr::splashScreen(float dt){
    currentTime += dt;
    if(currentTime >= waitTime){
        mTrayMgr->hideBackdrop();
        EnableHud();
        splashScreenDisable = true;
    }
}


void UiMgr::EnableHud(){

	bossHealth = mTrayMgr->createProgressBar(OgreBites::TL_TOP, "BHealthBar", "Boss Health",
			300, 170);
	bossHealth->setProgress(1);

	playerHealth = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMRIGHT,
			"PHealthBar", "Player Health", 250, 120);

	playerHealth->setProgress(1);

	waveLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "waveLabel",
			"Wave #", 130);

	timeLabel = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "timeLabel",
			"Time:", 120);

	weaponLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "weaponLabel",
			"Weapon:", 120);

	ammoLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "ammoLabel",
			"Ammo", 120);
	fpsLabel = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "fpsLabel",
			"FPS", 120);

}

void UiMgr::ClosingScreen() {

	screenClosed = true;
	mTrayMgr->destroyAllWidgets();
	mTrayMgr->showBackdrop("ClosingScreen");

	time_survived = mTrayMgr->createLabel(OgreBites::TL_CENTER,"timesurvived","Time Elapsed: " + timeElapsed,200);

	waves_survived = mTrayMgr->createLabel(OgreBites::TL_CENTER,"wavesurvived","Waves Survived: " + waveNum,200);

	EndButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "EndButton", "End Game",200);

}

void UiMgr::Menu() {

}

void UiMgr::Tick(float dt) {
	if (startGame == false) {
		mTrayMgr->showBackdrop("Backdrop");
		mTrayMgr->refreshCursor();
	} else {
		if (gameStarted == false) {
			gameStarted = true;
			EnableHud();
			mTrayMgr->hideBackdrop();
			mTrayMgr->destroyWidget(StartButton);
		}
        if (screenClosed == false){
            mTrayMgr->refreshCursor();
            UpdateLabels();
        } else{
            mTrayMgr->refreshCursor();
        }
	}
}

void UiMgr::UpdateLabels(){
    currentHealth = engine->gameMgr->MainPlayer->GetAspect<Health>()->CurrentHealth;
    Weapon* heldWeapon =
            engine->gameMgr->MainPlayer->GetAspect<WeaponHolder>()->heldWeapon;
    if(heldWeapon != NULL){
        Gun* gun = dynamic_cast<Gun*>(heldWeapon);
        if(gun != NULL){
            ammoNum = std::to_string(gun->CurrentBulletNumber);
        } else{
            ammoNum = "inf";
        }
    } else{
        ammoNum = "0";
    }
    waveNum = std::to_string(engine->waveMgr->waveNumber);
    timeElapsed = std::to_string((int)engine->waveMgr->timeElapsed);
    fps = std::string("FPS: ") + std::to_string(engine->fps);

    playerHealth->setProgress((float)currentHealth / 100);
    timeLabel->setCaption(std::string("Time: ") +  timeElapsed);
    waveLabel->setCaption(std::string("Wave: ") + waveNum);
//	weaponLabel->setCaption("timeElapsed");
	ammoLabel->setCaption(std::string("Ammo: ") + ammoNum);

	Boss * levelBoss = engine->gameMgr->LevelBoss;
	if(levelBoss != NULL && bossHealth != NULL) {
	    Health * bossHealthAspect = levelBoss->GetAspect<Health>();
	    //std::cout << bossHealthAspect->CurrentHealth / (float)bossHealthAspect->StartingHealth << std::endl;
	    bossHealth->setProgress(bossHealthAspect->CurrentHealth / (float)bossHealthAspect->StartingHealth);
	}
    fpsLabel->setCaption(fps);
}

void UiMgr::windowResized(Ogre::RenderWindow* rw){


    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
    ms.width = width;
    ms.height = height;


}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg){
    std::cout << "Key Pressed: " << arg.key << std::endl;
    return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
    return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if(mTrayMgr->injectMouseMove(arg))
        return true;
    return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid){
    std::cout << "mouse clicked" << std::endl;
    if(mTrayMgr->injectMouseDown(me, mid))
        return true;
    return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if(mTrayMgr->injectMouseUp(arg, id))
        return true;
    /* normal mouse processing here... */
    return false;
}

void UiMgr::itemSelected(OgreBites::SelectMenu *m) {

}


void UiMgr::buttonHit(OgreBites::Button *b) {
	if (b->getName() == "StartButton") {
		if (startGame == false) {
			startGame = true;
		}
		if (startGame == true) {

		}

	}

	if (b->getName() == "EndButton") {
			engine->keepRunning = false;
	}
}
