#!/bin/bash

handle_error() {
    pkill simv
}

# Trap any error and run handle_error function
trap 'handle_error' ERR

set -e

# pkill simv

sleep 1

rm -rf simv
rm -rf simv.daidir

cmake .
make

interconnect="Ring"


# ./interconnectBusSV/sv/launch.sh
# ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnectBusSV

# ./interconnectRingSV/sv/launch.sh

# if [[ "$1" == "-gui" ]]; then
#     "./interconnect${interconnect}SV/sv/launch.sh" -gui
#     echo "./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnect${interconnect}SV"
# else
#     "./interconnect${interconnect}SV/sv/launch.sh"
#     ./cadss-engine -v -n 4 -s ex_proc.config -t traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnect${interconnect}SV
# fi

"./interconnect${interconnect}SV/sv/launch.sh" -gui
# ./cadss-engine -v -n 4 -s ex_proc.config -t ../traces/blackscholes_4_simsmall.taskgraph -c simpleCache -i interconnect${interconnect}SV
echo "./cadss-engine -v -n 4 -s ex_proc.config -t ../traces/coher/splash2x.volrend_4_simsmall.taskgraph -c simpleCache -i interconnect${interconnect}SV"


# ./interconnectBusSV/sv/launch.sh
# ./cadss-engine -v -n 8 -s ex_proc.config -t traces/coher/splash2x.volrend_8_simsmall.taskgraph -c simpleCache -i interconnectBusSV
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
