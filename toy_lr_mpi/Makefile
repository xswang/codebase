#lr:lr.o
#	mpicxx -fopenmp -g -O3 -o lr lr.o
#lr.o:lr.cpp lr.h
#	mpicxx -fopenmp -g -O3 -c lr.cpp
#clean:
#	rm -f *~ lr lr.o
lr:lr.o
	mpicxx -fopenmp -g -O3 -o lr lr.o /home/xiaoshu.wxs/Documents/DB/hiredis-master/libhiredis.a
lr.o:lr.cpp lr.h
	mpicxx -fopenmp -g -O3 -std=c99 -pedantic -fPIC  -Wall -W -Wstrict-prototypes -Wwrite-strings -c lr.cpp 
clean:
	rm -f *~ lr lr.o
#lr:lr.o
#	mpicxx  -fopenmp -I /home/xiaoshu.wxs/xiaoshu.wxs/software/include -L /home/xiaoshu.wxs/xiaoshu.wxs/software/lib -g -O3 -o lr lr.o
#lr.o:lr.cpp lr.h
#	mpicxx -fopenmp -I /home/xiaoshu.wxs/xiaoshu.wxs/software/include -L /home/xiaoshu.wxs/xiaoshu.wxs/software/lib -g -O3 -c lr.cpp
#clean:
#	rm -f *~ lr lr.o
