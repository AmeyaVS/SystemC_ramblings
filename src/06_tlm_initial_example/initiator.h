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
#ifndef INITIATOR_H
#define INITIATOR_H

#include <systemc>
#include <tlm>

struct  Initiator: sc_core::sc_module,  tlm::tlm_bw_transport_if<>
{
  tlm::tlm_initiator_socket<>  init_socket{"init_socket"};

  Initiator( sc_core::sc_module_name instance_name, size_t run_length, size_t max_address );

  void thread_process( void );
  // Connects to target via one or more of the following:
  //   init_socket->b_transport( trans, delay );
  //   init_socket->nb_transport_fw( trans, phase, delay );
  //   init_socket->get_direct_mem_ptr( trans, dmi_data );
  //   init_socket->transport_dbg( trans );

  virtual tlm::tlm_sync_enum  nb_transport_bw( tlm::tlm_generic_payload& trans, tlm::tlm_phase& p,  sc_core::sc_time& t );
  virtual void  invalidate_direct_mem_ptr( sc_dt::uint64 start_range, sc_dt::uint64 end_range );
private:
  const size_t RUN_LENGTH;
  const size_t MAX_ADDRESS;
};
#endif

