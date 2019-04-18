/*
 * WaveMgr.h
 *
 *  Created on: Apr 18, 2019
 *      Author: kylebrain
 */

#ifndef INC_MANAGERS_WAVEMGR_H_
#define INC_MANAGERS_WAVEMGR_H_

#include "Mgr.h"

class WaveMgr : public Mgr {
	WaveMgr(Engine *eng);
	~WaveMgr();

	void Init();
	void Tick(float dt);
	void LoadLevel();
	void Stop();
};

#endif /* INC_MANAGERS_WAVEMGR_H_ */
