MYCC	= g++

CC	= $(MYCC) -std=c++11 -Wall -O9		\
		-MMD -MP			\
		-c

LINK	= $(MYCC) -o
LIBS	= -lstdc++

SRC	= $(wildcard *.cc)

TARGETS	=			\
	search

all:	$(TARGETS)

clean:
	rm -f *.o *.d		\
			$(TARGETS)

search: search.o
	$(LINK) $@ $^		$(LIBS)

%.o: %.cc
	$(CC) $<

-include $(SRC:%.cc=%.d)

