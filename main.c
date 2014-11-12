#include <GL/glut.h>
#include <stdio.h>
void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );
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
  gluOrtho2D(
      -x, x,
      -y, y
      );
  printf( "%d, %d \r", w, h );
}

void init( void )
{
  glClearColor( 0.0, 0.0, 0.0, 1.0 );
}

int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA );
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( argv[0] );
  glutDisplayFunc( display);
  glutReshapeFunc( resize );
  init();
  glutMainLoop();

  return( 0 );
}
