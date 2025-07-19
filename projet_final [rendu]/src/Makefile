DEBUG	= yes

ifeq ($(DEBUG),yes)
	CFLAGS	= -Wall
else
	CFLAGS	= 
endif

EXEC	= test.exe

CC	= gcc

LDFLAGS	= `sdl2-config --cflags --libs` -lSDL2_gfx\
	  `xml2-config --cflags --libs`

SRC	= main.c \
	  \
	  Affichage/main.c \
	  Affichage/util2.c \
	  \
	  XML/main.c \
	  XML/util1.c \
	  \
	  Affichage/Coordonnees/convert_coordonnees.c \
	  \
	  XML/Parser/liste.c \
	  XML/Parser/parser.c \
	  XML/Parser/struct.c

RM	= rm -f 

OBJS	= $(SRC:.c=.o)

all: all_normal
#all: all_normal clean
	@rm -f *~
	@rm -f .*~
	@rm -f \#*\#

all_normal: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

clean :
	$(RM) $(OBJS)
	@rm -f *~
	@rm -f .*~
	@rm -f \#*\#

fclean : clean
	$(RM) $(EXEC)

re : fclean all
