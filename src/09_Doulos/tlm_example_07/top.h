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
#include <systemc>
#include <tlm>

struct Top : sc_core::sc_module
{
    Initiator  *init;
    Target     *targ;
    SC_CTOR( Top );
};

#endif

