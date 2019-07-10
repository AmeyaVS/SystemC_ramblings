////////////////////////////////////////////////////////////////////////////////
//
//  ####### #     #     #      #######
//     #    #     ##   ##         #
//     #    #     # # # #         #
//     #    #     #  #  #         #     ####  ####
//     #    #     #     #         #    #    # #   #
//     #    #     #     #         #    #    # ####
//     #    ##### #     #         #     ####  #
//
////////////////////////////////////////////////////////////////////////////////
#ifndef TOP_H
#define TOP_H

#include "initiator.h"
#include "target.h"
#include "router.h"
#include <systemc>
#include <tlm>

struct Top : sc_core::sc_module
{
    Initiator  *init;
    Router *router;
    Target     *targ;
    SC_CTOR( Top );
};

#endif

