/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_



#include "Mgr.h"

class GameMgr : public Mgr{
public:
    GameMgr(Engine *eng);
    ~GameMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    float surfaceHeight = -100;
protected:
private:
};

#endif /* INC_GAMEMGR_H_ */
