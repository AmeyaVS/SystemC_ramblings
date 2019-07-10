////////////////////////////////////////////////////////////////////////////////
//
//  #     #    #    ### #     #
//  ##   ##   # #    #  ##    #
//  # # # #  #   #   #  # #   #
//  #  #  # #     #  #  #  #  #
//  #     # #######  #  #   # #
//  #     # #     #  #  #    ##
//  #     # #     # ### #     #
//
////////////////////////////////////////////////////////////////////////////////

// Note: This example of sc_main is more sophisticated than most and illustrates
// catching exceptions (errors and fatals) from elaboration and simulation. It
// also illustrates summarization of results and proper exit.

#include "top.h"
#include "report.h"
#include <string>
using namespace sc_core;
using namespace std;

static const char* MSGID = "/Doulos/example/tlm-2.0/sc_main";

int sc_main(int argc, char* argv[])
{
  Top *top;
  try {
    top = new Top("top");
  } catch (std::exception& e) {
    SC_REPORT_ERROR("sc_main",(string(e.what())+" Please fix elaboration errors and retry.").c_str());
    return 1;
  } catch (...) {
    SC_REPORT_ERROR(MSGID,"Caught exception during elaboration");
    return 1;
  }//endtry

  // Simulate
  try {
    SC_REPORT_INFO(MSGID,"Starting kernal");
    sc_start();
    SC_REPORT_INFO(MSGID,"Exited kernal");
  } catch (std::exception& e) {
    SC_REPORT_WARNING(MSGID,(string("Caught exception ")+e.what()).c_str());
  } catch (...) {
    SC_REPORT_ERROR(MSGID,"Caught exception during simulation.");
  }//endtry
  if (! sc_end_of_simulation_invoked()) {
    SC_REPORT_INFO(MSGID,"ERROR: Simulation stopped without explicit sc_stop()");
    sc_stop();
  }//endif

  // Summarize
  size_t errors = sc_report_handler::get_count(SC_ERROR) + sc_report_handler::get_count(SC_FATAL);
  if (errors == 0) {
    STREAM_REPORT_INFO(MSGID, "Simulation PASSED.");
  } else {
    STREAM_REPORT_INFO(MSGID, "Simulation FAILED with " << errors << " errors!");
  }

  return errors>0 ? 1 : 0;
}

//EOF
