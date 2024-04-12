cmake .
make
./cadss-engine -v -n 4 -s ex_proc.config -t traces/coher/simple -c simpleCache -i interconnect
