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
#ifndef TARGET_H
#define TARGET_H

#include <systemc>
#include <tlm>
#include "report.h"

struct  Target: sc_core::sc_module,  tlm::tlm_fw_transport_if<>
{
  tlm::tlm_target_socket<>  targ_socket{"targ_socket"};

  Target(sc_core::sc_module_name instance_name, size_t mem_size, size_t ns_latency );
  virtual void b_transport( tlm::tlm_generic_payload& trans,  sc_core::sc_time& t );
  virtual tlm::tlm_sync_enum  nb_transport_fw( tlm::tlm_generic_payload& trans, tlm::tlm_phase& p,  sc_core::sc_time& t );
  virtual bool get_direct_mem_ptr( tlm::tlm_generic_payload& gp, tlm::tlm_dmi& dmi );
  virtual unsigned int transport_dbg( tlm::tlm_generic_payload& trans );
private:
  const size_t           m_memsize;
  const sc_core::sc_time m_latency;
  int*                   m_storage;
};

#endif

