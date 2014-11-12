main.out:main.c
	gcc -o $@ $^ -framework GLUT -framework OpenGL -Wno-deprecated
