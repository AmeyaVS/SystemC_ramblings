#ifndef TOP_H
#define TOP_H

#include "initiator.h"
#include "bus.h"
#include "target.h"

// *****************************************************************************************
// Top-level module instantiates 4 initiators, a bus, and 4 targets
// *****************************************************************************************

SC_MODULE(Top)
{
  Initiator* init[4];
  Bus*       bus;
  Target*    target[4];

  SC_CTOR(Top)
  {
    bus   = new Bus("bus");

    // ***************************************************************************
    // bus->init_socket and bus->targ_socket are multi-sockets, each bound 4 times
    // ***************************************************************************

    for (int i = 0; i < 4; i++)
    {
      char txt[20];
      sprintf(txt, "init_%d", i);
      init[i] = new Initiator(txt);
      init[i]->socket.bind( bus->targ_socket );
    }

    for (int i = 0; i < 4; i++)
    {
      char txt[20];
      sprintf(txt, "target_%d", i);
      target[i] = new Target(txt);

      bus->init_socket.bind( target[i]->socket );
    }
  }
};

#endif

