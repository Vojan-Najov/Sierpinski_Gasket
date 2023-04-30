NAME1 = sierpinski_gasket_2D_cycle

CC = gcc
RM = rm -f
PKG-CONFIG = $(shell which pkg-config)

CFLAGS = -Wall -Wextra -Werror
CFLAGS_GLUT = $(shell $(PKG-CONFIG) --cflags glut)
LIBS_GLUT = $(shell $(PKG-CONFIG) --libs glut)
LIBS = -lGL

$(NAME1) : sierpinski_gasket_2d_cycle.c
	echo $(CFLAGS_GLUT)
	echo $(LIBS_GLUT)
	$(CC) $(CFLAGS) $(CFLAGS_GLUT) $? -o $@ $(LIBS) $(LIBS_GLUT)

clean:
	$(RM) *.o
	$(RM) $(NAME1)
