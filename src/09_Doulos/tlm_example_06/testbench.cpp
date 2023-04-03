//----------------------------------------------------------------------
//  Copyright (c) 2007-2008 by Doulos Ltd.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//----------------------------------------------------------------------

// Version 1, 26-June-2008
// Version 2,  7-July-2008  Remove N_INITIATORS, N_TARGETS template parameters from Bus
// Version 3   8-March-2010 Replaced target end_req_pending pointer with a queue

// Getting Started with TLM-2.0, Example 6

// Shows the use of multi-sockets in an interconnect component,
// that is, multi_passthrough_initiator_socket and multi_passthrough_target_socket

// This example combines the AT initiator and target from example 4 with the bus from
// example 5, modified to use multi-sockets instead of tagged sockets
// Uses the forward and backward non-blocking transport interfaces of the bus interconnect

#include "top.h"

int sc_main(int argc, char* argv[])
{
  Top top("top");
  sc_start();

  cout << "\n***** Messages have been written to file output.txt                    *****\n";
  cout << "***** Select 'Download files after run' to read file in EDA Playground *****\n\n";

  return 0;
}

