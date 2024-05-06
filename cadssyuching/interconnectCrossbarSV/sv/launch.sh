#!/bin/bash

set -e

vcs -sverilog -debug interconnectCrossbarSV/sv/cadss_interconnect.sv central_sv_files/socket_wrappers.cpp central_sv_files/Network.svh central_sv_files/NetworkPkg.svg interconnectCrossbarSV/sv/crossbar.sv


if [[ "$1" == "-gui" ]]; then
    ./simv -gui &
else
    ./simv &
fi

sleep 1