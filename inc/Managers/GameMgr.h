/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_



#include "Mgr.h"
#include "Player.h"

class GameMgr : public Mgr{
public:
    GameMgr(Engine *eng);
    ~GameMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    Ogre::Plane mPlane;
    float surfaceHeight = -100;
    Player * MainPlayer;
protected:
private:
};

#endif /* INC_GAMEMGR_H_ */
