CPLUS   = g++
CFLAGS  = -g2 -O2 -Wall -I/usr/local/include -I/opt/local/include -I/sw/include

SRCS   =  $(wildcard *.cpp)
OBJS   =  $(patsubst %.cpp,%.o,$(SRCS))
PROGS  =  $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

.cpp.o :
	$(CPLUS) $(CFLAGS) -c $< -o $@

${PROGS} : % : %.o
	$(CPLUS) $(CFLAGS) $< -o $@ -lThea -lboost_filesystem -lboost_system -lm

clean :
	-rm -f $(PROGS) $(OBJS)
