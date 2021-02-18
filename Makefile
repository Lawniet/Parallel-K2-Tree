# .c files
CPP_SOURCE=$(wildcard ./src/*.c)

# Object files
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

# Compiler and linker
CXX=g++ -std=c++11

# Libraries
LIBS= -lsdsl -ldivsufsort -ldivsufsort64

# Flags for compiler
CPPFLAGS=-O3 -g -funroll-loops -fomit-frame-pointer -ffast-math

# Command used at clean target
RM = rm -rf

# Number of Threads
THREADS=1

# OpenMP environment variable
OMP_CANCELLATION=true
export OMP_CANCELLATION

# Run all test cases
all: write0 write1 write2 write3 write4 write5 write6 write7

# Running the sequential test case
write0:  k2tree0
	./k2tree0 ./data/INDOCHINA.mtx  >> results.txt
	./k2tree0 ./data/DELAUNAY.mtx  >> results.txt
	./k2tree0 ./data/NASASRB.mtx  >> results.txt
	./k2tree0 ./data/UK.mtx >> results.txt
	./k2tree0 ./data/ARABIC.mtx  >> results.txt

# Running the parallel test case
write1:  k2tree1
	./k2tree1 ./data/INDOCHINA.mtx $(THREADS) >> results.txt
	./k2tree1 ./data/DELAUNAY.mtx $(THREADS) >> results.txt
	./k2tree1 ./data/NASASRB.mtx $(THREADS) >> results.txt
	./k2tree1 ./data/UK.mtx $(THREADS)  >> results.txt
	./k2tree1 ./data/ARABIC.mtx  $(THREADS) >> results.txt

# Running the sequential test case with Loop tiling
write2:  k2tree2
	./k2tree2 ./data/INDOCHINA.mtx  >> results.txt
	./k2tree2 ./data/DELAUNAY.mtx  >> results.txt
	./k2tree2 ./data/NASASRB.mtx >> results.txt
	./k2tree2 ./data/UK.mtx  >> results.txt
	./k2tree2 ./data/ARABIC.mtx  >> results.txt

# Running the parallel test case with Loop tiling 
write3:  k2tree3
	./k2tree3 ./data/INDOCHINA.mtx $(THREADS) >> results.txt
	./k2tree3 ./data/DELAUNAY.mtx $(THREADS) >> results.txt
	./k2tree3 ./data/NASASRB.mtx $(THREADS) >> results.txt
	./k2tree3 ./data/UK.mtx $(THREADS)  >> results.txt
	./k2tree3 ./data/ARABIC.mtx $(THREADS) >> results.txt

# Running the sequential test case with Loop unrolling
write4:  k2tree4
	./k2tree4 ./data/INDOCHINA.mtx  >> results.txt
	./k2tree4 ./data/DELAUNAY.mtx  >> results.txt
	./k2tree4 ./data/NASASRB.mtx >> results.txt
	./k2tree4 ./data/UK.mtx  >> results.txt
	./k2tree4 ./data/ARABIC.mtx  >> results.txt

# Running the parallel test case with Loop unrolling
write5:  k2tree5
	./k2tree5 ./data/INDOCHINA.mtx $(THREADS) >> results.txt
	./k2tree5 ./data/DELAUNAY.mtx  $(THREADS) >> results.txt
	./k2tree5 ./data/NASASRB.mtx $(THREADS) >> results.txt
	./k2tree5 ./data/UK.mtx $(THREADS)  >> results.txt
	./k2tree5 ./data/ARABIC.mtx $(THREADS)  >> results.txt

# Running the hybrid test case
write6:  k2tree6
	./k2tree6 ./data/INDOCHINA.mtx  >> results.txt
	./k2tree6 ./data/DELAUNAY.mtx  >> results.txt
	./k2tree6 ./data/NASASRB.mtx >> results.txt
	./k2tree6 ./data/UK.mtx  >> results.txt
	./k2tree6 ./data/ARABIC.mtx  >> results.txt

# Running the parallel hybrid test case
write7:  k2tree7
	./k2tree7 ./data/INDOCHINA.mtx $(THREADS) >> results.txt
	./k2tree7 ./data/DELAUNAY.mtx $(THREADS) >> results.txt
	./k2tree7 ./data/NASASRB.mtx $(THREADS) >> results.txt
	./k2tree7 ./data/UK.mtx $(THREADS)  >> results.txt
	./k2tree7 ./data/ARABIC.mtx $(THREADS) >> results.txt

# Compiling all versions
k2tree0:
	$(CXX) $(CPPFLAGS) ./src/ChangeOver.cpp -o k2tree0 $(LIBS)
k2tree1:
	$(CXX) $(CPPFLAGS) ./src/Parallel_ChangeOver.cpp-o k2tree1 $(LIBS) -fopenmp
k2tree2:
	$(CXX) $(CPPFLAGS) ./src/LoopTiling.cpp -o k2tree2 $(LIBS)
k2tree3:
	$(CXX) $(CPPFLAGS) ./src/Parallel_LoopTiling.cpp -o k2tree3 $(LIBS) -fopenmp
k2tree4:
	$(CXX) $(CPPFLAGS) ./src/LoopUnrolling.cpp -o k2tree4 $(LIBS)
k2tree5:
	$(CXX) $(CPPFLAGS) ./src/Parallel_LoopUnrolling.cpp -o k2tree5 $(LIBS) -fopenmp
k2tree6:
	$(CXX) $(CPPFLAGS) ./src/Hybrid.cpp -o k2tree6 $(LIBS)
k2tree7:
	$(CXX) $(CPPFLAGS) ./src/Parallel_Hybrid.cpp -o k2tree7 $(LIBS) -fopenmp

# Cleaning the project
clean:
	@ $(RM) *.o k2tree0  k2tree1  k2tree2  k2tree3  k2tree4  k2tree5 k2tree6  k2tree7
.PHONY: all clean
