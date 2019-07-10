#ifndef ROUTER_H
#define ROUTER_H

#include <systemc>
#include <tlm>

struct Router: sc_core::sc_module,
               tlm::tlm_fw_transport_if<>,
               tlm::tlm_bw_transport_if<>
{
  tlm::tlm_target_socket<> targ_socket{"targ_socket"};
  tlm::tlm_initiator_socket<> init_socket{"init_socket"};

  Router(sc_core::sc_module_name instance_name, size_t offset);

  // TLM FW Interface
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);// override;
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& p, sc_core::sc_time& t);// override;
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& gp, tlm::tlm_dmi& dmi);// override;
  virtual uint32_t transport_dbg(tlm::tlm_generic_payload& trans);// override;

  // TLM BW Interface
  virtual tlm::tlm_sync_enum  nb_transport_bw( tlm::tlm_generic_payload& trans, tlm::tlm_phase& p,  sc_core::sc_time& t);// override;
  virtual void  invalidate_direct_mem_ptr( sc_dt::uint64 start_range, sc_dt::uint64 end_range );// override;

  private:
    const size_t m_offset;
}; //< Router

#endif //< ROUTER_H
