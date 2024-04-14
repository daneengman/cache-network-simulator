#!/bin/bash

set -e

vcs -sverilog cadss_interconnect.sv ring.sv socket_wrappers.cpp
./simv &
sleep 1
gcc socket_tester.c -std=c99 -o socket_tester
./socket_tester