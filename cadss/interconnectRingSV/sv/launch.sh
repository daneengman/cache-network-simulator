#!/bin/bash

set -e

vcs -sverilog -debug interconnectRingSV/sv/cadss_interconnect.sv interconnectRingSV/sv/socket_wrappers.cpp interconnectRingSV/sv/Network.svh interconnectRingSV/sv/NetworkPkg.svg interconnectRingSV/sv/ring.sv


if [[ "$1" == "-gui" ]]; then
    ./simv -gui &
else
    ./simv &
fi

sleep 1