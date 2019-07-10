////////////////////////////////////////////////////////////////////////////////
//
//  ####### #     #     #      ###
//     #    #     ##   ##       #             #              #
//     #    #     # # # #       #         #   #    #         #
//     #    #     #  #  #       #  ####      ###       ###  ###   ####  # ###
//     #    #     #     #       #  #   # ##   #   ##  #   #  #   #    # ##
//     #    #     #     #       #  #   #  #   # #  #  #  ##  # # #    # #
//     #    ##### #     #      ### #   # ###   #  ###  ## #   #   ####  #
//
////////////////////////////////////////////////////////////////////////////////

#include "initiator.h"
#include "report.h"
#include <cstdlib>

using namespace sc_core;
using namespace tlm;
using namespace std;

static const char* MSGID = "/Doulos/example/tlm-2.0/initiator";

Initiator::Initiator( sc_module_name instance_name, size_t run_length, size_t max_address )
: RUN_LENGTH(run_length), MAX_ADDRESS(max_address)
{
    SC_HAS_PROCESS( Initiator );
    SC_THREAD( thread_process );
    init_socket.bind( *this );
}

void Initiator::thread_process( void )
{
  tlm_generic_payload  trans;
  sc_time  delay = SC_ZERO_TIME;

  trans.set_data_length( 4 );
  trans.set_streaming_width( 4 );
  trans.set_byte_enable_ptr( 0 );

  for ( int i = 0; i < RUN_LENGTH; i += 4 )
  {
    int  word = 0xBEEF0000 | i;
    int  addr = (rand() % MAX_ADDRESS) & ~0x3; // random word aligned address
    tlm_command  cmnd = ( rand()&1 ) ? TLM_READ_COMMAND : TLM_WRITE_COMMAND;
    trans.set_command( cmnd );
    trans.set_address( addr );
    trans.set_data_ptr( (unsigned char*)( &word ) );
    trans.set_dmi_allowed( false );
    trans.set_response_status( TLM_INCOMPLETE_RESPONSE );

    STREAM_REPORT_INFO( MSGID, "Transaction " << i
                        << " initiating blocking " << ((cmnd == TLM_READ_COMMAND)?"READ":"WRITE")
                        << " to address " << addr );
    init_socket->b_transport( trans, delay );

    if( trans.is_response_error() ) {
      STREAM_REPORT_ERROR( "TLM-Initiator", trans.get_response_string().c_str() );
    }
    if (trans.get_command() == TLM_READ_COMMAND) {
      STREAM_REPORT_INFO( MSGID, "Received 0x" << hex << word );
    }
  }//endfor
  sc_stop();
}

tlm_sync_enum Initiator::nb_transport_bw( tlm_generic_payload& trans, tlm_phase& p,  sc_core::sc_time& t )
{
  /* implementation not provided */
  SC_REPORT_FATAL( MSGID, "Unsupported" );
  return TLM_ACCEPTED;
}

void Initiator::invalidate_direct_mem_ptr( sc_dt::uint64 start_range, sc_dt::uint64 end_range )
{
  /* implementation void - unsupported and simply ignored */
}

