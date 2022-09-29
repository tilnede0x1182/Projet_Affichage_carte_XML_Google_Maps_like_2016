DEBUG	= no

ifeq ($(DEBUG),yes)
	CFLAGS	= -Wall
else
	CFLAGS	= 
endif

EXEC	= test.exe

CC	= gcc

LDFLAGS	= `sdl2-config --cflags --libs` -lSDL2_gfx\
	  `xml2-config --cflags --libs`

SRC	= $(wildcard *.c)

RM	= rm -f 

OBJS	= $(SRC:.c=.o)

all: $(EXEC)
	@rm -f *~
	@rm -f .*~

$(EXEC): $(OBJS)

*.o: *.h

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(EXEC)

re : fclean all
