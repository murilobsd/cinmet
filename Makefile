INCLUDES	=-I/usr/local/include

CFLAGS		+= -Wall -Wstrict-prototypes -Wmissing-prototypes
CFLAGS		+= -Wmissing-declarations
CFLAGS		+= -Wshadow -Wpointer-arith -Wcast-qual
CFLAGS		+= -Wsign-compare
CFLAGS		+= -Werror-implicit-function-declaration

LFLAGS		=-L/usr/local/lib

LIBS		=-lcurl

SRCS		= util.c \
		  request.c \
		  station.c \
		  inmet.c \
		  main.c

OBJS 		= $(SRCS:.c=.o)

MAIN 		= inmet

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	rm -f *.o *~ $(MAIN)
