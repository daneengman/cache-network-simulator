#!/bin/bash

set -e

vcs -sverilog -debug interconnectBusSV/sv/cadss_interconnect.sv interconnectBusSV/sv/bus.sv central_sv_files/socket_wrappers.cpp 
./simv &
sleep 1