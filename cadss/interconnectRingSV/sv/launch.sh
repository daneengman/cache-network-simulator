#!/bin/bash

set -e

# vcs -sverilog interconnectBusSV/sv/cadss_interconnect.sv interconnectBusSV/sv/bus.sv interconnectBusSV/sv/socket_wrappers.cpp 
vcs -sverilog interconnectRingSV/sv/Network.svh interconnectRingSV/sv/NetworkPkg.svg interconnectRingSV/sv/cadss_interconnect.sv interconnectRingSV/sv/ring.sv interconnectRingSV/sv/socket_wrappers.cpp 
./simv &
sleep 1