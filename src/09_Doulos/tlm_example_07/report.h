//////////////////////////////////////////////////////////////////////////////////
//
//  #####  ##### #####   ####  #####  #######
//  #    # #     #    # #    # #    #    #
//  #    # #     #    # #    # #    #    #
//  #####  ##### #####  #    # #####     #
//  #  #   #     #      #    # #  #      #
//  #   #  #     #      #    # #   #     #
//  #    # ##### #       ####  #    #    #
//
//////////////////////////////////////////////////////////////////////////////////

// This is a trivial extension of the SC_REPORT_* macros to allow
// C++ streaming syntax for more comfortable reporting in SystemC.
// Feel free to use for your own projects.

#ifndef REPORT_H
#define REPORT_H

#include <systemc>
#include <sstream>
#include <string>

#define STREAM_REPORT_INFO(MSGID,message_stream) \
do {\
  std::ostringstream mout;\
  mout << sc_core::sc_time_stamp() << ": " << message_stream;\
  SC_REPORT_INFO(MSGID,mout.str().c_str());\
} while (0)

#define STREAM_REPORT_INFO_VERB(MSGID,message_stream,verbosity) \
do {\
  std::ostringstream mout;\
  mout << sc_core::sc_time_stamp() << ": " << message_stream;\
  SC_REPORT_INFO_VERB(MSGID,mout.str().c_str(),verbosity);\
} while (0)

#define STREAM_REPORT_WARNING(MSGID,message_stream) \
do {\
  std::ostringstream mout;\
  mout << message_stream;\
  SC_REPORT_WARNING(MSGID,mout.str().c_str());\
} while (0)

#define STREAM_REPORT_ERROR(MSGID,message_stream) \
try {\
  std::ostringstream mout;\
  mout << message_stream;\
  SC_REPORT_ERROR(MSGID,mout.str().c_str());\
} catch (sc_core::sc_report e) { }

#define STREAM_REPORT_FATAL(MSGID,message_stream) \
do {\
  std::ostringstream mout;\
  mout << message_stream;\
  SC_REPORT_FATAL(MSGID,mout.str().c_str());\
} while (0)

#endif
