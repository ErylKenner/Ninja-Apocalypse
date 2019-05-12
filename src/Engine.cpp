/*
 * Engine.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include "Engine.h"
#include "EntityMgr.h"
#include "GameMgr.h"
#include "GfxMgr.h"
#include "InputMgr.h"
#include "SoundMgr.h"
#include "WaveMgr.h"
#include "UiMgr.h"
#include "AiMgr.h"

Engine::Engine() :
        entityMgr(0),
        gameMgr(0),
        gfxMgr(0),
        inputMgr(0),
        waveMgr(0),
        uiMgr(0),
        soundMgr(0),
        aiMgr(0),
        fps(0){
    timeInterval = 0;
    keepRunning = true;
    for(int i = 0; i < 10; ++i){
        fpsBuffer[i] = 0.0;
    }
}

Engine::~Engine(){

}

void Engine::Init(){

    entityMgr = new EntityMgr(this);
    gameMgr = new GameMgr(this);
    gfxMgr = new GfxMgr(this);
    inputMgr = new InputMgr(this);
    waveMgr = new WaveMgr(this);
    uiMgr = new UiMgr(this);
    soundMgr = new OgreSND::SoundMgr(this);
    aiMgr = new AiMgr(this);

    //--------------------------------------------------------------
    entityMgr->Init();
    gfxMgr->Init();
    inputMgr->Init(); // must initialize AFTER gfx manager
    gameMgr->Init();
    waveMgr->Init();
    uiMgr->Init();
    soundMgr->init();
    aiMgr->Init();

    //--------------------------------------------------------------
    entityMgr->LoadLevel();
    gfxMgr->LoadLevel();
    inputMgr->LoadLevel();
    waveMgr->LoadLevel();
    uiMgr->LoadLevel();
    soundMgr->loadLevel();
    aiMgr->LoadLevel();
    gameMgr->LoadLevel();
}

void Engine::UpdateFPS(float dt){
    for(int i = 8; i >= 0; --i){
        fpsBuffer[i + 1] = fpsBuffer[i];
    }
    fpsBuffer[0] = (int)(1 / (double)dt);

    timeInterval += dt;
    if(timeInterval >= 0.5){
        timeInterval = 0.0;
        fps = 0;
        for(int i = 0; i < 10; ++i){
            fps += fpsBuffer[i];
        }
        fps /= 10;
    }
}

void Engine::TickAll(float dt){
    UpdateFPS(dt);
    gfxMgr->Tick(dt);
    inputMgr->Tick(dt);
    entityMgr->Tick(dt);
    gameMgr->Tick(dt);
    waveMgr->Tick(dt);
    uiMgr->Tick(dt);
    soundMgr->Tick(dt);
    aiMgr->Tick(dt);
}

void Engine::Run(){
    const float MICROSECONDS_PER_SECOND = 1000000.0f;
    Ogre::Timer* timer = new Ogre::Timer();

    float oldTime = timer->getMicroseconds() / MICROSECONDS_PER_SECOND;
    float newTime = timer->getMicroseconds() / MICROSECONDS_PER_SECOND;
    float dt = newTime - oldTime;

    while(keepRunning){

        TickAll(dt);

        newTime = timer->getMicroseconds() / MICROSECONDS_PER_SECOND;
        dt = newTime - oldTime;
        oldTime = newTime;

    }
    // main must call cleanup or bad stuff happens->Cleanup()
}

void Engine::Cleanup(){
    inputMgr->Stop();
    gfxMgr->Stop();
    entityMgr->Stop();
    gameMgr->Stop();
    waveMgr->Stop();
    uiMgr->Stop();
    soundMgr->Stop();
    aiMgr->Stop();
}
