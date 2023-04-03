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

#include "top.h"
#include "initiator.h"
#include "target.h"
#include "report.h"
//
using namespace sc_core;
using namespace tlm;
using namespace tlm;

Top::Top( sc_module_name n )
{
  const int mem_size = 64;
  const int run_length = 256;
  init  = new Initiator( "init", run_length, mem_size );
  targ = new Target( "targ", mem_size, 60 );
  init->init_socket.bind( targ->targ_socket );
  STREAM_REPORT_INFO("TLM-Top","Simulating " << run_length << " transactions in memory of size " << mem_size);
}

