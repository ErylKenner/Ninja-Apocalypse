/*
 * WaveMgr.h
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#ifndef INC_MANAGERS_WAVEMGR_H_
#define INC_MANAGERS_WAVEMGR_H_

#include <vector>
#include "Mgr.h"
#include "Enemy.h"

class WaveMgr : public Mgr{

public:
    bool disabledSpawning;
    int enemiesPerWave;
    int enemiesRemaining;
    int waveNumber;
    float spawnDelay;
    float timeElapsed;

    std::vector<Enemy*> spawnedEnemyList;

    WaveMgr(Engine *eng);
    ~WaveMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    void SpawnEnemy();
    void OnEnemyKilled(Enemy * enemy);
    void NextWave();

private:
    float timeSinceLastSpawn;

    int deltaValue(int minimum, int radius);
    std::vector<Enemy *> deadList;

    const int bossWave = 4;

    bool bossSpawned = false;
};

#endif /* INC_MANAGERS_WAVEMGR_H_ */
