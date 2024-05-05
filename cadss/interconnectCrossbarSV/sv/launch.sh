#!/bin/bash

set -e

vcs -sverilog -debug interconnectCrossbarSV/sv/cadss_interconnect.sv interconnectCrossbarSV/sv/socket_wrappers.cpp interconnectCrossbarSV/sv/Network.svh interconnectCrossbarSV/sv/NetworkPkg.svg interconnectCrossbarSV/sv/crossbar.sv


if [[ "$1" == "-gui" ]]; then
    ./simv -gui &
else
    ./simv &
fi

sleep 1