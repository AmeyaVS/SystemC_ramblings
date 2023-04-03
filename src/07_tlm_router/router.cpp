#include "router.h"
#include "report.h"

//using namespace sc_core;
//using namespace tlm;

static const char* MSGID = "/trial/example/TML-2.0/router";

Router::Router(sc_core::sc_module_name instance_name, size_t offset):
  m_offset(offset)
{
  init_socket.bind(*this);
  targ_socket.bind(*this);
}

void Router::b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t) {
  trans.set_address(trans.get_address() + m_offset);
  init_socket->b_transport(trans, t);
  trans.set_address(trans.get_address() - m_offset);
}

tlm::tlm_sync_enum Router::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& p, sc_core::sc_time& t)
{
  trans.set_address(trans.get_address() + m_offset);
  auto ret = init_socket->nb_transport_fw(trans, p, t);
  trans.set_address(trans.get_address() - m_offset);
  return ret;
  //SC_REPORT_FATAL( MSGID, "Unsupported/Incomplete"); // Technically insufficient
  //return tlm::TLM_ACCEPTED;
}

bool Router::get_direct_mem_ptr(tlm::tlm_generic_payload& gp, tlm::tlm_dmi& dmi)
{
  ///* implementation not supported */
  //return false;
  // Passthrough
  return init_socket->get_direct_mem_ptr(gp, dmi);
}

uint32_t Router::transport_dbg(tlm::tlm_generic_payload& trans) {
  /* implementation not supported */
  // Passthrough
  return init_socket->transport_dbg(trans);
}

tlm::tlm_sync_enum Router::nb_transport_bw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& p, sc_core::sc_time& t) {
  //SC_REPORT_FATAL( MSGID, "Unsupported");
  //return tlm::TLM_ACCEPTED;
  // Passthrough
  trans.set_address(trans.get_address() - m_offset);
  auto ret = targ_socket->nb_transport_bw(trans, p, t);
  trans.set_address(trans.get_address() + m_offset);
  return ret;
}

void Router::invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
  /* implementation void - unsupported and simply ignored */
  // Passthrough
  targ_socket->invalidate_direct_mem_ptr(start_range, end_range);
}
