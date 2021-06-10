

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include <stdlib.h>

int status;
int cellNextGeneration;

GLubyte pixel;

int column;
int row;

int nextGeneration=0;
int alivesCount=0;
int alivesNeighboursCount=0;

int aliveOrDeadCells[20][20];
int aliveCells[20][20];
int deadCells[20][20];



int neighborCells[8];
int aliveOrDeadCounter=0;

int tlX;
int tlY;
int trX;
int trY;
int dlX;
int dlY;
int drX;
int drY;
int option=0;

int startPointX=0;
int startPointY=95;
int endPointX=100;
int endPointY=95;

int startPointX2=5;
int startPointY2=0;
int endPointX2=5;
int endPointY2=100;

int phyWidth= 700;
int phyHeight= 700;
int logWidth=100;
int logHeight=100;

int centerX=logWidth/2;
int centerY=logHeight/2;
int mouseX=centerX, mouseY=centerY;



void printSome(char *str,int x,int y,int r,int g,int b) {
 glColor3f (r, g,b);
 glRasterPos2d(x,y);
 for (int i=0;i<strlen(str);i++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
 glFlush();
}



void init2D(float r, float g, float b)
{
glClearColor(r,g,b,0);
glMatrixMode (GL_PROJECTION);
gluOrtho2D (0.0, logWidth, 0.0, logHeight);
}



void SpotTheAliveCell(int tlX,int tlY,int trX,int trY,int dlX,int dlY,int drX,int drY)
{
glColor3f(0,0,1); //
glBegin(GL_QUADS);
glVertex2f(dlX,dlY); //down left
glVertex2f(tlX,tlY); //top left
glVertex2f(trX,trY);//top right
glVertex2f(drX,drY);//down right
glEnd();
}

//i=row
//j=coloumn
void CheckNeighbours(int i,int j)
{

neighborCells[0]=aliveOrDeadCells[i+1][j];//top
neighborCells[1]=aliveOrDeadCells[i+1][j-1];//top left corner
neighborCells[2]=aliveOrDeadCells[i][j-1];//left
neighborCells[3]=aliveOrDeadCells[i-1][j-1];//down left corner
neighborCells[4]=aliveOrDeadCells[i+1][j+1];//top right corner
neighborCells[5]=aliveOrDeadCells[i-1][j];//bottom
neighborCells[6]=aliveOrDeadCells[i-1][j+1];//down right corner
neighborCells[7]=aliveOrDeadCells[i][j+1];//right



   for(int i=0;i<8;i++)
         {

          //printf("%d",neighborCells[i]);

           if(neighborCells[i]==1)
           {

               alivesNeighboursCount++;
           }

         }
        printf("%d",alivesNeighboursCount);
        printf("\n");


       if(alivesNeighboursCount==1||alivesNeighboursCount>3||alivesNeighboursCount==0)
      {

         deadCells[i][j]=0;


      }


      else if(alivesNeighboursCount==2||alivesNeighboursCount==3)
        {
            aliveCells[i][j]=1;
        }


        for(int i=0;i<20;i++)
                {
            for(int j=0;j<20;j++)
                         {

                             if(aliveOrDeadCells[i][j]==1&&aliveOrDeadCells[i][j-1]==1&&aliveOrDeadCells[i][j+1]==1)
                             {

                                    aliveCells[i+1][j]=1;




                                    aliveCells[i-1][j]=1;



                             }




                             if(aliveOrDeadCells[i][j]==1&&aliveOrDeadCells[i+1][j]==1&&aliveOrDeadCells[i-1][j]==1)
                             {

                                    aliveCells[i][j-1]=1;




                                    aliveCells[i][j+1]=1;



                             }


                         }
                 }





}






/***Mouse Function***/
void mouseClick(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
 mouseX = x;
 mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
 mouseY = phyHeight- y;
 mouseY=0.5+1.0*mouseY*logHeight/phyHeight;


 if(option==1)
 {
    status=1;
 }

 if(option==0)
 {
     if(mouseX>=35&&mouseX<=65&&mouseY>=50&&mouseY<=60)
     {
         option=1;
     }

     if(mouseX>=35&&mouseX<=65&&mouseY>=30&&mouseY<=40)
     {
         exit(1);
     }

 }




 }

glutPostRedisplay();

}





/***Keyboard Function***/
void specialKeyboard(int key, int x, int y)
{

if(key== GLUT_KEY_RIGHT)
    {
         nextGeneration=1;

    }

    if(key== GLUT_KEY_F2)
    {
         option=0;

    }

    if(key== GLUT_KEY_F1)
    {
         for(int i=0;i<=20;i++)
     {
           for(int j=0;j<=20;j++)
                  {
                    aliveOrDeadCells[j][i]=0;


                  }
     }

    }

glutPostRedisplay();
}



/***********************************************************************************************************************************************************/
void display (void)
{
    if(option==1)
    {


glClear(GL_COLOR_BUFFER_BIT);



/***creating The Grid Screen***/
for(int i=0;i<100;i=i+5)
{
glColor3f(0,0,0);
glBegin(GL_LINES);
glVertex2i(startPointX2+i,startPointY2);
glVertex2i(endPointX2+i,endPointY2);
glEnd();

glColor3f(0,0,0);
glBegin(GL_LINES);
glVertex2i(startPointX,startPointY-i);
glVertex2i(endPointX,endPointY-i);
glEnd();
}







/***spotting the alive cell***/
if(status==1)
{

  for(int i=0;i<100;i=i+5)
 {
 for(int j=0;j<100;j=j+5)
 {

       if( mouseX>(j) && mouseX<(j+5) && mouseY >(i) && mouseY <(i+5))
          {



              tlX=j;
               tlY=i+5;
                trX=j+5;
                  trY=i+5;

                  /***/
                   dlX=j;
                    dlY=i;
                    /***/

                     drX=j+5;
                      drY=i;

                     SpotTheAliveCell( tlX, tlY, trX, trY, dlX, dlY, drX, drY);


                     aliveOrDeadCells[dlY/5][dlX/5]=1;



          }

 }
 }
  for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
            {
                if(aliveOrDeadCells[j][i]==1)
                {

                    row=j;
                    column=i;

                     int tlX=i*5;
                     int tlY=j*5+5;
                     int trX=i*5+5;
                     int trY=j*5+5;
                     int dlX=i*5;
                     int dlY=j*5;
                     int drX=i*5+5;
                     int drY=j*5;

                     glColor3f(0,0,1); //
                     glBegin(GL_QUADS);
                     glVertex2f(dlX,dlY); //down left
                     glVertex2f(tlX,tlY); //top left
                     glVertex2f(trX,trY);//top right
                     glVertex2f(drX,drY);//down right
                     glEnd();





                }



            }
        }

}




if(nextGeneration==1)
{

     glClear(GL_COLOR_BUFFER_BIT);
/***creating The Grid Screen***/
for(int i=0;i<100;i=i+5)
{
glColor3f(0,0,0);
glBegin(GL_LINES);
glVertex2i(startPointX2+i,startPointY2);
glVertex2i(endPointX2+i,endPointY2);
glEnd();

glColor3f(0,0,0);
glBegin(GL_LINES);
glVertex2i(startPointX,startPointY-i);
glVertex2i(endPointX,endPointY-i);
glEnd();
}

 for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
            {
                if(aliveOrDeadCells[j][i]==1)
                {
                    alivesCount++;

                    row=j;
                    column=i;
                    CheckNeighbours(j,i);
                    alivesNeighboursCount=0;


                }

            }
        }
        alivesCount=0;






                   for(int i=0;i<20;i++)
                           {
                             for(int j=0;j<20;j++)
                                     {

                                         aliveOrDeadCells[i][j]=deadCells[i][j];
                                         aliveOrDeadCells[i][j]=aliveCells[i][j];


                                     }
                          }


for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
            {
                if(aliveOrDeadCells[i][j]==1)
                {

                    row=j;
                    column=i;

                     int tlX=j*5;
                     int tlY=i*5+5;
                     int trX=j*5+5;
                     int trY=i*5+5;
                     int dlX=j*5;
                     int dlY=i*5;
                     int drX=j*5+5;
                     int drY=i*5;

                     glColor3f(0,0,1); //
                     glBegin(GL_QUADS);
                     glVertex2f(dlX,dlY); //down left
                     glVertex2f(tlX,tlY); //top left
                     glVertex2f(trX,trY);//top right
                     glVertex2f(drX,drY);//down right
                     glEnd();





                }


            }
        }


for(int i=0;i<20;i++)
     {
 for(int j=0;j<20;j++)
       {
           printf("%d ", aliveOrDeadCells[j][i]);
           if(j==20){
            printf("\n");
         }

       }
     }


  nextGeneration=0;

}







glutSwapBuffers();
 glFlush();
}


if(option==0)
    {
        glClear(GL_COLOR_BUFFER_BIT);



        printSome("conway's Game Of Life",30,80,0,0,0);


                     glColor3f(0,0,1); //
                     glBegin(GL_QUADS);
                     glVertex2f(35,50); //down left
                     glVertex2f(35,60); //top left
                     glVertex2f(65,60);//top right
                     glVertex2f(65,50);//down right
                     glEnd();


                     printSome("START",44,54,1,1,1);



                     glColor3f(0,0,1); //
                     glBegin(GL_QUADS);
                     glVertex2f(35,30); //down left
                     glVertex2f(35,40); //top left
                     glVertex2f(65,40);//top right
                     glVertex2f(65,30);//down right
                     glEnd();


                     printSome("EXIT",44,34,1,1,1);





 glutSwapBuffers();
 glFlush();
    }

    }
/***********************************************************************************************************************************************************/
int main(int argc,char *argv[])
{



glutInit(&argc,argv);
glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE );
glutInitWindowSize (phyWidth, phyHeight);
glutInitWindowPosition (100, 100);
glutCreateWindow ("Conway's Game Of Life");
init2D(253/100, 254/100, 254/100);
glutDisplayFunc(display);
glutSpecialFunc(specialKeyboard);
glutMouseFunc(mouseClick);
glutMainLoop();
}

/*
for(int i=0;i<20;i++)
     {
 for(int j=0;j<20;j++)
       {
           printf("%d ", aliveOrDeadFlag[j][i]);
           if(j==20){
            printf("\n");
         }

       }
     }*/

