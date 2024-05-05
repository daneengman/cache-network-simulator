#!/bin/bash

set -e

cmake .
make


# ./interconnectBusSV/sv/launch.sh 
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/coher/simple -c simpleCache -i interconnectBusSV

./interconnectRingSV/sv/launch_gui.sh 
echo ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnectRingSV

# ./interconnectRingSV/sv/launch.sh 
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnectRingSV
