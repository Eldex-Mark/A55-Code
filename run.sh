#./TestBench
#build/TestBench
gdb  -ex=r  build/TestBench  -ex='bt'  --batch  # -ex='bt'  -ex=quit
#valgrind  build/TestBench  --leak-check=full
