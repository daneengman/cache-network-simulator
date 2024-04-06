vcs -sverilog test.sv

gcc -c -fPIC test.c -o c_file.o
gcc -shared -o test.c c_file.o

vcs -sv_lib c_file.so test.sv