#!/bin/bash

set -e

vcs -sverilog cadss_interconnect.sv ring.sv socket_wrappers.cpp
./simv &
sleep 1
python3 socket_tester.py