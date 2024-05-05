#!/bin/bash

handle_error() {
    pkill simv
}

# Trap any error and run handle_error function
trap 'handle_error' ERR

set -e

pkill simv

rm -rf simv
rm -rf simv.daidir

cmake .
make


./interconnectBusSV/sv/launch.sh 
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnectBusSV

# ./interconnectBusSV/sv/launch.sh 
./cadss-engine -v -n 8 -s ex_proc.config -t traces/coher/splash2x.volrend_8_simsmall.taskgraph -c simpleCache -i interconnectBusSV
# pkill simv


# ./interconnectRingSV/sv/launch.sh 
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnectRingSV

# ./interconnectRingSV/sv/launch.sh 
# echo "Running interconnected process"
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/4proc_migratory -c simpleCache -i interconnectRingSV

# echo "Running default process"
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/4proc_migratory -c simpleCache

# echo "Running default process"
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache
# ./cadss-engine -v -n 8 -s ex_coher.config -t traces/coher/x264_8_simsmall.taskgraph -c simpleCache -i interconnectRingSV

# ./interconnectRingSV/sv/launch.sh 
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnectRingSV
