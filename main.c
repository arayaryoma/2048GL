#include <GL/glut.h>
#include <stdio.h>
#include<time.h>
#include<stdlib.h>

int mapFlag[3][3];
double x[3][3],y[3][3];
double pr_x,pr_y;
int elementNum=3;
void frame( void )
{
  //glClear( GL_COLOR_BUFFER_BIT );
  glColor3f(255,255,255);
  glBegin( GL_LINES );
  //frame 
  glVertex2d( -0.8, -0.8 );
  glVertex2d( 0.8, -0.8 );
  glVertex2d( -0.8, -0.8 );
  glVertex2d( -0.8, 0.8 );
  glVertex2d( 0.8, -0.8 );
  glVertex2d( 0.8, 0.8 );
  glVertex2d( -0.8, 0.8 );
  glVertex2d( 0.8, 0.8 );
  //line
  glVertex2d(-0.4,-0.8);
  glVertex2d(-0.4,0.8);
  glVertex2d(0.0,-0.8);
  glVertex2d(0.0,0.8);
  glVertex2d(0.4,-0.8);
  glVertex2d(0.4,0.8);
  glVertex2d(-0.8,-0.4);
  glVertex2d(0.8,-0.4);
  glVertex2d(-0.8,0.0);
  glVertex2d(0.8,0.0);
  glVertex2d(-0.8,0.4);
  glVertex2d(0.8,0.4);
  glEnd();
  glFlush();
  }

void resize( int w, int h )
{
  double x=w, y=h;

  glViewport( 0, 0, w, h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  if( w > h ){
    x = x / y;
    y = y / y;
  }else{
    y = y / x;
    x = x / x;
  }
  gluOrtho2D(-x,x,-y,y);
  
}

void init( void )
{
  glClearColor( 0.0, 0.0, 0.0, 1.0 );
}

void appearance(){
  int i;
  
  glColor3f(0.87,0.8,0.01);
  srand( (unsigned)time(NULL));
  for(i=1;i<=elementNum;i++){
    pr_x=-0.8+(0.4*( rand()%4) );
    pr_y=-0.8+(0.4*( rand()%4) );
    printf("%f,%f\n",pr_x,pr_y);
    glBegin(GL_POLYGON);
    glVertex2f(pr_x+0.01,pr_y+0.01);
    glVertex2f(pr_x+0.39,pr_y+0.01);
    glVertex2f(pr_x+0.39,pr_y+0.39);
    glVertex2f(pr_x+0.01,pr_y+0.39);
    glEnd();
    glFlush();
  }

  frame();
  }

void move(){
glClear( GL_COLOR_BUFFER_BIT );
  glColor3f(0.87,0.8,0.01);
  glBegin(GL_POLYGON);
  glVertex2f(x+0.01,y+0.01);
  glVertex2f(x+0.39,y+0.01);
  glVertex2f(x+0.39,y+0.39);
  glVertex2f(x+0.01,y+0.39);
  glEnd();
  frame();
  appearance();
  glFlush();

}

void keys(unsigned char key ,int dummy1,int dummy2){
  switch(key){
    case 'k':
      y=0.4;
      move();
      break;
    case 'j':
      y=-0.8;
      move();
      break;
    case 'h':
      x=-0.8;
      move();
      break;
    case 'l':
      x=0.4;
       move();
      break;
  }

}



int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA );
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( argv[0] );
  //glutKeyboardFunc(keys);
  glutDisplayFunc(appearance);
  //appearance();
  glutReshapeFunc( resize );
  init();
  glutMainLoop();

  return( 0 );
}
