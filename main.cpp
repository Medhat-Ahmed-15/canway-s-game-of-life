

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

int status;
int cellNextGeneration;

int column;
int row;

int aliveOrDeadFlag[20][20];
int aliveOrDeadCounter=0;

int tlX;
int tlY;
int trX;
int trY;
int dlX;
int dlY;
int drX;
int drY;

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


void CheckNeighbours(int i,int j)
{

    /*if(aliveOrDeadFlag[i+1][j]==1||
       aliveOrDeadFlag[i+1][j+1]==1||
       aliveOrDeadFlag[i][j+1]==1||
       aliveOrDeadFlag[i-1][j+1]==1||
       aliveOrDeadFlag[i-1][j]==1||
       aliveOrDeadFlag[i-1][j-1]==1||
       aliveOrDeadFlag[i][j-1]==1||
       aliveOrDeadFlag[i+1][j-1]==1)
    {*/
        glColor3f(1,0,0); //
        glBegin(GL_QUADS);
        glVertex2f(i*5,j*5); //down left
        glVertex2f(i*5,j*5+5); //top left
        glVertex2f(i*5+5,j*5+5);//top right
        glVertex2f(i*5+5,j*5);//down right
        glEnd();
    //}

}







void mouseClick(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
 mouseX = x;
 mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
 mouseY = phyHeight- y;
 mouseY=0.5+1.0*mouseY*logHeight/phyHeight;

 for(int i=0;i<600;i=i+5)
 {
 for(int j=0;j<600;j=j+5)
 {

       if( mouseX>=(j) && mouseX<=(j+5) && mouseY >=(i) && mouseY <=(i+5))
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

                      status=1;

                      //set an id=1 for this specific cell
                       aliveOrDeadFlag[dlX/5][dlY/5]=1;


          }


 }
 }





 }

 if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        status=0;
    }




 glutPostRedisplay();
}



void SpecialInput(int key, int x, int y)
{

if(key==GLUT_KEY_RIGHT)
    {
        //exit(1);
        for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
            {
                if(aliveOrDeadFlag[i][j]==1)
                {

                    //CheckNeighbours(j,i);
                    column=i;
                    row=j;
                    cellNextGeneration=1;

                }
            }
        }


    }


    if(key==GLUT_KEY_DOWN)
    {
        for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
            {
                aliveOrDeadFlag[i][j]=0;
            }
        }
    }



}



/***********************************************************************************************************************************************************/
void display (void)
{
//glClear(GL_COLOR_BUFFER_BIT);



/***creating The Grid Screen***/
for(int i=0;i<100;i=i+5)
{
glColor3f(1,1,1);
glBegin(GL_LINES);
glVertex2i(startPointX2+i,startPointY2);
glVertex2i(endPointX2+i,endPointY2);
glEnd();

glColor3f(1,1,1);
glBegin(GL_LINES);
glVertex2i(startPointX,startPointY-i);
glVertex2i(endPointX,endPointY-i);
glEnd();
}
/***creating The Grid Screen***/



if(cellNextGeneration==1)
{

 CheckNeighbours(column,row);

}



/***spotting the alive cell***/
if(status==1)
{
 SpotTheAliveCell( tlX, tlY, trX, trY, dlX, dlY, drX, drY);
}
/***spotting the alive cell***/



        /*glColor3f(0,1,0); //
        glBegin(GL_QUADS);
        glVertex2f(5,10); //down left
        glVertex2f(5,15); //top left
        glVertex2f(10,15);//top right
        glVertex2f(10,10);//down right
        glEnd();*/





glutSwapBuffers();
 glFlush();
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
glutSpecialFunc(SpecialInput);
glutMouseFunc(mouseClick);
glutMainLoop();
}


/*glColor3f(0,1,0); //
        glBegin(GL_QUADS);
        glVertex2f(5,10); //down left
        glVertex2f(5,15); //top left
        glVertex2f(10,15);//top right
        glVertex2f(10,10);//down right
        glEnd();*/
