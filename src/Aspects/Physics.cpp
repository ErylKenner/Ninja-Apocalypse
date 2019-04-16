
#include "Physics.h"
#include "Entity381.h"

Physics::Physics(Entity381 *entity) :
        Aspect(entity){
}

void Physics::Tick(float dt){
    entity381->position += entity381->velocity * dt;
}

Physics::~Physics(){
}
