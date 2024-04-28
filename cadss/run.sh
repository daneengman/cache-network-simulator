#!/bin/bash

set -e

cmake .
make
./interconnectBusSV/sv/launch.sh 
./cadss-engine -v -n 4 -s ex_proc.config -t traces/coher/simple -c simpleCache -i interconnectBusSV
