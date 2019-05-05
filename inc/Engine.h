/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef ENGINE_H_
#define ENGINE_H_

namespace OgreSND {
class SoundMgr;
}

using namespace OgreSND;

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
class WaveMgr;
class UiMgr;
class AiMgr;

class Engine{

public:
    Engine();
    virtual ~Engine();

    EntityMgr *entityMgr;
    GameMgr *gameMgr;
    GfxMgr *gfxMgr;
    InputMgr *inputMgr;
    WaveMgr *waveMgr;
    UiMgr *uiMgr;
    SoundMgr *soundMgr;
    AiMgr *aiMgr;

    void Init();
    void Run();
    void TickAll(float dt);
    void Cleanup();

    bool keepRunning;
    int fps;

private:
    void UpdateFPS(float dt);
    int fpsBuffer[10];
    float timeInterval;
};

#endif /* ENGINE_H_ */
