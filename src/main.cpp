/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include <Engine.h>
int main(int argc, char *argv[]){
   Engine *engine = new Engine();
    engine->Init();
    engine->Run();
    engine->Cleanup();
    return 0;
}

