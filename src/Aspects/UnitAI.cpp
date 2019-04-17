/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "UnitAI.h"
#include "Entity381.h"

UnitAI::UnitAI(Entity381 *entity) :
        Aspect(entity){
}

void UnitAI::Tick(float dt){
    if(!commands.empty()){
        if(commands.front()->Done()){
            commands.front()->Finish();
            delete commands.front();
            commands.pop_front();
        }
        if(!commands.empty()){
            commands.front()->Tick(dt);
        }
    }
}

void UnitAI::SetCommand(Command *c){
    while(!commands.empty()){
        commands.front()->Finish();
        delete commands.front();
        commands.pop_front();
    }
    commands.push_front(c);
    c->Init();
}

void UnitAI::AddCommand(Command *c){
    commands.push_back(c);
    c->Init();
}

int UnitAI::NumCommands() const{
    return commands.size();
}

UnitAI::~UnitAI(){
}

