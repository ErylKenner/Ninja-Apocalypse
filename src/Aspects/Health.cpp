/*
 * Health.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: kylebrain
 */

#include "Health.h"

Health::Health(Entity381 * entity, int startingHealth) : Aspect(entity), CurrentHealth(startingHealth) {}

Health::~Health() {

}

bool Health::IsAlive() {
	return CurrentHealth > 0;
}

// returns true if attached entity is still alive
bool Health::TakeDamage(int damageAmount) {
	CurrentHealth -= damageAmount;

	if(!IsAlive()) {
		// health is never below zero
		CurrentHealth = 0;
		return false;
	} else {
		return true;
	}
}

void Health::Tick(float dt) {

}

