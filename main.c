#include <GL/glut.h>
#include <stdio.h>
#include<time.h>
#include<stdlib.h>

//prototype declarations

void frame();//draw frame
void resize();
void init();
void appearance();//create a new object
void keys(unsigned char key ,int dummy1,int dummy2);
void substituteCordinates();
int magnitude[4][4];
int mapFlag[4][4];
double x[4][4],y[4][4];
int pr_x,pr_y;
int elementNum=3;
int score=0;
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
        if(magnitude[i][j]==2) glColor3f(1,0,0.912);
        if(magnitude[i][j]==4) glColor3f(0.668,0,1);
        if(magnitude[i][j]==8) glColor3f(0.2,0,1);
        if(magnitude[i][j]==16) glColor3f(0,0.66,1);
        if(magnitude[i][j]==32) glColor3f(0,0.972,1);
        if(magnitude[i][j]==64) glColor3f(0,1,0.532);
        if(magnitude[i][j]==128) glColor3f(0,1,0.18);
        if(magnitude[i][j]==256) glColor3f(0.736,1,0);
        if(magnitude[i][j]==512) glColor3f(1,0.964,0);
        if(magnitude[i][j]==1024) glColor3f(1,0.66,0);
        if(magnitude[i][j]==2048) glColor3f(1,0.26,0);
        if(magnitude[i][j]==4096) glColor3f(1,0,0);
        if(magnitude[i][j]==8192) glColor3f(1,1,1);
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
  do{
    pr_x=rand()%4;
    pr_y=rand()%4;
    if(mapFlag[pr_x][pr_y]!=1){
      mapFlag[pr_x][pr_y]=1;
      magnitude[pr_x][pr_y]=2;
      break;
    }
  }while(1);
  paint();
}


void keys(unsigned char key ,int dummy1,int dummy2){
  int i,j,k,l,m;
  switch(key){

    case 'k':
      for(i=0;i<4;i++){
        for(j=3;j>=0;j--){
          if(mapFlag[i][j]==1){
            for(l=j+1;l<4;l++){
              if(mapFlag[i][l]==0){  //上が空いていたら詰める
                mapFlag[i][l]=1;
                mapFlag[i][l-1]=0;
                magnitude[i][l]=magnitude[i][l-1];
                magnitude[i][l-1]=0;
              }
            }

            for(m=j,k=m-1;k>=0;k--,m--){
              if(magnitude[i][m]==magnitude[i][k]){ 
                //上からみて一番近い数値が同じなら足し合わせる
                magnitude[i][m]+=magnitude[i][k];
                score+=magnitude[i][k];
                magnitude[i][k]=mapFlag[i][k]=0;
               } 
              if(magnitude[i][k]==0) m++; //一個したが空きなら視点を動かさない
            } 
          }
        }
      }
      appearance();
      break;

    case 'j':
      for(i=0;i<4;i++){
        for(j=0;j<4;j++){
          if(mapFlag[i][j]==1){
            for(l=j-1;l>=0;l--){
              if(mapFlag[i][l]==0){  //下が空いていたら詰める
                mapFlag[i][l]=1;
                mapFlag[i][l+1]=0;
                magnitude[i][l]=magnitude[i][l+1];
                magnitude[i][l+1]=0;
              }
            }

            for(m=j,k=m+1;k<4;k++,m++){
              if(magnitude[i][m]==magnitude[i][k]){ 
                //上からみて一番近い数値が同じなら足し合わせる
                magnitude[i][m]+=magnitude[i][k];
                score+=magnitude[i][k];
                magnitude[i][k]=mapFlag[i][k]=0;
              } 
              if(magnitude[i][k]==0) m--; //一個上が空きなら視点を動かさない
            } 
          }
        }
        }
      appearance();
      break;   

    case 'h':
      for(i=0;i<4;i++){
        for(j=0;j<4;j++){
          if(mapFlag[i][j]==1){
            for(l=i-1;l>=0;l--){
              if(mapFlag[l][j]==0){  //左が空いていたら詰める
                mapFlag[l][j]=1;
                mapFlag[l+1][j]=0;
                magnitude[l][j]=magnitude[l+1][j];
                magnitude[l+1][j]=0;
              }
            }

            for(m=i,k=m+1;k<4;k++,m++){
              if(magnitude[m][j]==magnitude[k][j]){ 
                //上からみて一番近い数値が同じなら足し合わせる
                magnitude[m][j]+=magnitude[k][j];
                score+=magnitude[k][j];
                magnitude[k][j]=mapFlag[k][j]=0;
              } 
              if(magnitude[k][j]==0) m--; //一個上が空きなら視点を動かさない
            } 
          }
        }
      }
      appearance();
      break;

    case 'l':
      for(i=3;i>=0;i--){
        for(j=0;j<4;j++){
          if(mapFlag[i][j]==1){
            for(l=i+1;l<4;l++){
              if(mapFlag[l][j]==0){  //右が空いていたら詰める
                mapFlag[l][j]=1;
                mapFlag[l-1][j]=0;
                magnitude[l][j]=magnitude[l-1][j];
                magnitude[l-1][j]=0;
              }
            }

            for(m=i,k=m-1;k>=0;k--,m--){
              if(magnitude[m][j]==magnitude[k][j]){ 
                //上からみて一番近い数値が同じなら足し合わせる
                magnitude[m][j]+=magnitude[k][j];
                score+=magnitude[k][j];
                magnitude[k][j]=mapFlag[k][j]=0;
              } 
              if(magnitude[k][j]==0) m++; //一個上が空きなら視点を動かさない
            } 
          }
        }
      }
      appearance();
      break;
      
 

  }
  printf("\n\nscore=%d\n\n",score);
 
  puts("magnitude");
      for(j=3;j>=0;j--){
        for(i=0;i<4;i++){
          printf("%4d",magnitude[i][j]);
        }
        puts("");
      }
      puts("\nFlag");
      for(j=3;j>=0;j--){
        for(i=0;i<4;i++){
          printf("%3d",mapFlag[i][j]);
        }
        puts("");
      }
      puts("");

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
