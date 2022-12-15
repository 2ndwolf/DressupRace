#define _DR_NPCBUFFER_h
#ifndef _DR_NPCBUFFER_h

#include <string>
#include <SDL.h>

// #include "buffer.h"
// #include "window.h"
// #include "gameobjects.h"

class NPCUpdater{
  GameObjects::Npc* npc;
  bool updated = false;

  NPCUpdater(GameObjects::Npc* pNpc, int delta, int lastUpdate) : npc(pNpc) {
    updated = npc->update(delta);
    if(lastUpdate > SDL_GetTicks() - 4){
      npc->createWorkerThread();
      // IF LAGGY, CREATE WORKER THREAD
    }
  };

  ~NPCUpdater(){
    if(updated){ // If hasWorkerThread
      // Write npc stuff to window buffer

    }
  };

};



#endif