NAME1 = sierpinski_gasket_2d_cycle
NAME2 = sierpinski_gasket_2d_recursion
NAME3 = sierpinski_gasket_3d

CC = gcc
RM = rm -f
PKG-CONFIG = $(shell which pkg-config)

CFLAGS = -Wall -Wextra -Werror
CFLAGS_GLUT = $(shell $(PKG-CONFIG) --cflags glut)
LIBS_GLUT = $(shell $(PKG-CONFIG) --libs glut)
LIBS = -lGL

$(NAME1): sierpinski_gasket_2d_cycle.o
	$(CC) $? -o $@ $(LIBS) $(LIBS_GLUT)

$(NAME2): sierpinski_gasket_2d_recursion.o
	$(CC) $? -o $@ $(LIBS) $(LIBS_GLUT)

$(NAME3): sierpinski_gasket_3d.o
	$(CC) $? -o $@ $(LIBS) $(LIBS_GLUT)

sierpiski_gasket_2d_cycle.o: sierpinski_gasket_2d_cycle.c
	$(CC) $(CFLAGS) $(CFLAGS_GLUT) $? -c $@

sierpiski_gasket_2d_recursion.o: sierpinski_gasket_2d_recursion.c
	$(CC) $(CFLAGS) $(CFLAGS_GLUT) $? -c $@

sierpiski_gasket_3d.o: sierpinski_gasket_3d.c
	$(CC) $(CFLAGS) $(CFLAGS_GLUT) $? -c $@

clean:
	$(RM) *.o
	$(RM) $(NAME1)
	$(RM) $(NAME2)
	$(RM) $(NAME3)

.PHONY: clean
