////////////////////////////////////////////////////////////////////////////////
//
//  ####### #     #     #      #######
//     #    #     ##   ##         #                               #
//     #    #     # # # #         #                  ###          #
//     #    #     #  #  #         #     ###  # ###  #   #  ###   ###
//     #    #     #     #         #    #   # ##      #### #####   #
//     #    #     #     #         #    #  ## #          # #       # #
//     #    ##### #     #         #     ## # #       ###   ###     #
//
////////////////////////////////////////////////////////////////////////////////

#include "target.h"
#include "report.h"

using namespace sc_core;
using namespace tlm;

static const char* MSGID = "/Doulos/example/tlm-2.0/target";

Target::Target( sc_module_name instance_name, size_t mem_size, size_t ns_latency, size_t offset)
: m_memsize(mem_size), m_latency(static_cast<double>(ns_latency),SC_NS), m_offset(offset)
{
  targ_socket.bind( *this );
  m_storage = new int[m_memsize];
}

void  Target::b_transport( tlm_generic_payload& trans,  sc_core::sc_time& t )
{
  tlm_command  cmd = trans.get_command();
  sc_dt::uint64     adr = trans.get_address() - m_offset;
  unsigned char*    ptr = trans.get_data_ptr();
  unsigned int      len = trans.get_data_length();
  unsigned char*    byt = trans.get_byte_enable_ptr();
  unsigned int      wid = trans.get_streaming_width();

  if( ((adr&3) != 0) || (adr+len > m_memsize) )
  {
    trans.set_response_status( TLM_ADDRESS_ERROR_RESPONSE );
    return;
  }
  if( byt != 0 || len > 4 || wid < len || adr+len > m_memsize )
  {
    trans.set_response_status( TLM_GENERIC_ERROR_RESPONSE );
    return;
  }

  wait(m_latency); // Model transport latency - merged read/write

  if( cmd == TLM_WRITE_COMMAND ) {
    STREAM_REPORT_INFO( MSGID, "b_transport processing WRITE to address " << adr );
    memcpy( &m_storage[adr], ptr, len );
  } else if( cmd == TLM_READ_COMMAND ) {
    STREAM_REPORT_INFO( MSGID, "b_transport processing READ from address " << adr );
    memcpy( ptr, &m_storage[adr], len );
  }

  trans.set_response_status( TLM_OK_RESPONSE );
}

tlm_sync_enum  Target::nb_transport_fw( tlm_generic_payload& trans, tlm_phase& p,  sc_core::sc_time& t )
{
  /* implementation not provided */
  SC_REPORT_FATAL( MSGID, "Unsupported/Incomplete" ); // Technically insufficient
  return TLM_ACCEPTED;
}
bool Target::get_direct_mem_ptr( tlm_generic_payload& gp, tlm_dmi& dmi )
{
  /* implementation not supported*/
  return false;
}
unsigned int Target::transport_dbg( tlm_generic_payload& trans )
{
  /* implementation not supported */
  return 0;
}

