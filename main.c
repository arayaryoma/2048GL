#include <GL/glut.h>
#include <stdio.h>
#include<time.h>
#include<stdlib.h>

//prototype declarations

void frame();
void resize();
void init();
void appearance();
void move();
void keys(unsigned char key ,int dummy1,int dummy2);
void substituteCordinates();

int mapFlag[4][4];
double x[4][4],y[4][4];
int pr_x,pr_y;
int elementNum=3;

void frame() {
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

//resize window
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

void paint(){
  int i,j;
glClear( GL_COLOR_BUFFER_BIT );
  for(i=0;i<4;i++){ //全探索
    for(j=0;j<4;j++){
      if(mapFlag[i][j]==1){
        glColor3f(0.87,0.8,0.01);
        glBegin(GL_POLYGON);
        glVertex2f(x[i][j]+0.01,y[i][j]+0.01);
        glVertex2f(x[i][j]+0.39,y[i][j]+0.01);
        glVertex2f(x[i][j]+0.39,y[i][j]+0.39);
        glVertex2f(x[i][j]+0.01,y[i][j]+0.39);
        glEnd();
      }
      glFlush();
      frame();

    }
  }
}


void appearance(){
  int i,j;
  srand( (unsigned)time(NULL));
  pr_x=rand()%4;
  pr_y=rand()%4;
  mapFlag[pr_x][pr_y]=1;
  paint();
}

void move(){
glClear( GL_COLOR_BUFFER_BIT );
  glColor3f(0.87,0.8,0.01);
  glBegin(GL_POLYGON);
//  glVertex2f(x+0.01,y+0.01);
//  glVertex2f(x+0.39,y+0.01);
//  glVertex2f(x+0.39,y+0.39);
//  glVertex2f(x+0.01,y+0.39);
  glEnd();
  frame();
  appearance();
  glFlush();

}

void keys(unsigned char key ,int dummy1,int dummy2){
  int i,j,k;
  switch(key){
//    case 'k':
//      y=0.4;
//      move();
//      break;
//    case 'j':
//      y=-0.8;
//      move();
//      break;
    case 'h':
      for(i=0;i<4;i++){
        for(j=0;j<4;j++){
          if(mapFlag[i][j]==1){
            mapFlag[i][j]=0;
            for(k=0;k<4;k++){
              if(mapFlag[k][j]==0){
                mapFlag[k][j]=1;
                break;
              }
              }
            //glutDisplayFunc(paint);
            glutPostRedisplay();
          }
        }
      }
      break;
//    case 'l':
//      x=0.4;
//       move();
//      break;
  }

}

void substituteCordinates(){
  int i,j;
  for (i=0;i<4;i++){
    for(j=0;j<4;j++){
      x[i][j]=-0.8+(0.4*i);
      y[i][j]=-0.8+(0.4*j);
     //printf("%f,%f\n",x[i][j],y[i][j]);
    }
  }
}


int main( int argc, char** argv ) {
  int i,j;
  substituteCordinates();
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA );
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( argv[0] );
  glutDisplayFunc(appearance);
  //glutDisplayFunc(paint);
  glutKeyboardFunc(keys);
  // glutPostRedisplay();
  //appearance();
  glutReshapeFunc( resize );
  init();
  glutMainLoop();

  return( 0 );
}
