#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

double length;
double radius;

struct point
{
	double x,y,z;
};


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);

		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}
/*void drawSquare(double a){
   glBegin(GL_QUADS);{
       glVertex3f(0,0,0);
       glVertex3f(a,0,0);
       glVertex3f(a,a,0);
       glVertex3f(0,a,0);
   }
   glEnd();
}*/
void drawCube(){

     glColor3f(0.7,0.6,0.5);
     glPushMatrix();
     {
         glTranslatef(0,0,-length);
     }
     drawSquare(length);
     glPopMatrix();
     glPushMatrix();
     {
         glTranslatef(0,length,0);
         glRotatef(90,1,0,0);
     }
     drawSquare(length);
     glPopMatrix();

     glColor3f(0.5,0.6,0.7);
     glPushMatrix();
     {
         glTranslatef(-length,0,0);
         glRotatef(-90,0,1,0);
     }
     drawSquare(length);
     glPopMatrix();

     glColor3f(0.5,0.6,0.7);
     glPushMatrix();
     {
         glTranslatef(0,0,length);
     }
     drawSquare(length);
     glPopMatrix();

     glColor3f(0.2,0.4,0.3);
     glPushMatrix();
     {
         glTranslatef(0,length,0);
         glRotatef(90,1,0,0);
     }
     drawSquare(length);
     glPopMatrix();

     glColor3f(0.6,0.4,0.8);
     glPushMatrix();
     {
         glTranslatef(length,0,0);
         glRotatef(-90,0,1,0);
     }
     drawSquare(length);
     glPopMatrix();

     glColor3f(1,0,0);
     glPushMatrix();
     {
         glTranslatef(0,-length,0);
         glRotatef(90,1,0,0);
     }
     drawSquare(length);
     glPopMatrix();

}


void drawCylinderPart(double radius,int length,int segments)
{
    int i;
    double shade;
    //radius=20;
    struct point points[100];
    //glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*(pi/2.0));
        points[i].z=radius*sin(((double)i/(double)segments)*(pi/2.0));
    }
    //draw segments using generated points

    for(i=0;i<segments;i++)
    {
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);
        glBegin(GL_POLYGON);
        {
            glVertex3f(points[i].x,-length,points[i].z);
			glVertex3f(points[i].x,length,points[i].z);
			glVertex3f(points[i+1].x,length,points[i+1].z);
			glVertex3f(points[i+1].x,-length,points[i+1].z);
        }
        glEnd();
    }
}

void drawCylinder()
{
    //drawCylinderPart(ra,80,24);
    glPushMatrix();
    {

        glTranslated(length,length,0);
        glRotatef(-90,1,0,0);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(length,-length,0);
        glRotatef(90,1,0,0);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(-length,length,0);
        glRotatef(-90,0,1,0);
        glRotatef(90,0,0,1);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(-length,-length,0);
        glRotatef(-90,0,1,0);
        glRotatef(-90,0,0,1);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(0,length,length);
        glRotatef(90,0,0,1);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(0,-length,length);
        glRotatef(-90,0,0,1);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(length,0,-length);
        glRotatef(90,0,1,0);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(length,0,-length);
        glRotatef(90,0,1,0);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(length,0,length);

    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(0,length,-length);
        glRotatef(-90,1,0,0);
        glRotatef(90,0,0,1);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(0,-length,-length);
        glRotatef(90,1,0,0);
        glRotatef(-90,0,0,1);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(-length,0,length);
        glRotatef(-90,0,1,0);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated(-length,0,-length);
        glRotatef(-180,0,1,0);
    }
    drawCylinderPart(radius,length,24);
    glPopMatrix();


}
void drawWheel(double radius,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*(pi/2.0));
        points[i].z=radius*sin(((double)i/(double)segments)*(pi/2.0));
    }
    //draw segments using generated points

    for(i=0;i<segments;i++)
    {
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);
        glBegin(GL_POLYGON);
        {
            glVertex3f(points[i].x,0,points[i].z);
			glVertex3f(points[i].x,60,points[i].z);
			glVertex3f(points[i+1].x,60,points[i+1].z);
			glVertex3f(points[i+1].x,0,points[i+1].z);
        }
        glEnd();
    }
    /*glBegin(GL_POLYGON);
    {
        glVertex3f(points[0].x,-10,points[0].z);
        glVertex3f(points[0].x,10,points[0].z);
        glVertex3f(points[segments/2].x,10,points[segments/2].z);
        glVertex3f(points[segments/2].x,-10,points[segments/2].z);

        //glVertex3f(points[])
    }
    glEnd();*/

}
void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_POLYGON);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i].x,points[i].y,10);
			glVertex3f(points[i+1].x,points[i+1].y,10);
			glVertex3f(points[i+1].x,points[i+1].y,0);


        }
        glEnd();
    }
}

void drawSpherePart(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*(pi/2.0));
			points[i][j].y=r*sin(((double)j/(double)slices)*(pi/2.0));
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
               /* glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);*/
			}glEnd();
		}
	}

}

void drawSphere()
{
    double angle=90;
    //double radius=20;
    glPushMatrix();
    {

        glTranslated(length,length,length);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated((-1)*length,length,length);
        glRotated(angle,0,0,1);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();


    glPushMatrix();
    {

        glTranslated(length,length,(-1)*length);
        glRotated(2*angle,1,1,0);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();

        glPushMatrix();
    {

        glTranslated((-1)*length,length,(-1)*length);
        glRotated(angle,0,0,1);
        glRotated(2*angle,1,1,0);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();



    glPushMatrix();
    {

        glTranslated(length,(-1)*length,length);
        glRotated((-1)*angle,0,0,1);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();


    glPushMatrix();
    {

        glTranslated(length,(-1)*length,(-1)*length);
        glRotated((-1)*angle,0,0,1);
        glRotated(2*angle,1,1,0);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();

    glPushMatrix();
    {

        glTranslated((-1)*length,(-1)*length,length);
        glRotated(2*angle,0,0,1);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();




    glPushMatrix();
    {

        glTranslated((-1)*length,(-1)*length,(-1)*length);
        glRotated(2*angle,0,0,1);
        glRotated(2*angle,1,1,0);

    }
    drawSpherePart(radius,30,30);
    glPopMatrix();
}
/*void drawSpherePart(double radius, int segments)
{
    //glColor3f(0.7,0.7,0.7);
    struct point points[100];
    for(int i=0;i<=segments;i++){
        points[i].x=radius*cos(((double)i/(double)segments)*(pi/2.0));
        points[i].y=radius*sin(((double)i/(double)segments)*(pi/2.0));
    }
    //draw x-y plane of 1/8-cube
    for(int i=0;i<segments;i++){
        glBegin(GL_POLYGON);{
            glVertex3f(0,0,0);
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i].y,0);
        }
        glEnd();
    }
}*/
void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}
/*void drawCylinder(double radius, double height, double segments)
{
    struct point points[100];
    double shade;
    for(int i=0;i<=segments;i++){
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    for(int i=0;i<segments;i++){
        glBegin(GL_LINES);
        {
            if(i<segments/2)shade=2*(double)i/(double)segments;
            else shade=2*(1.0-(double)i/(double)segments);
             glColor3f(shade,shade,shade);

            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i].x,points[i].y,height);

            glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);

			glVertex3f(points[i].x,points[i].y,height);
			glVertex3f(points[i+1].x,points[i+1].y,height);
        }
        glEnd();
    }
}
*/

/*void drawCube(){
// White side - BACK
glBegin(GL_POLYGON);
glColor3f(   1.0,  1.0, 1.0 );
glVertex3f(  35, -35, 35 );
glVertex3f(  35,  35, 35 );
glVertex3f( -35,  35, 35 );
glVertex3f( -35, -35, 35 );
glEnd();

// Purple side - RIGHT
glBegin(GL_POLYGON);
glColor3f(  1.0,  0.0,  1.0 );
glVertex3f( 35, -35, -35 );
glVertex3f( 35,  35, -35 );
glVertex3f( 35,  35,  35 );
glVertex3f( 35, -35,  35 );
glEnd();

// Green side - LEFT
glBegin(GL_POLYGON);
glColor3f(   0.0,  1.0,  0.0 );
glVertex3f( -35, -35,  35 );
glVertex3f( -35,  35,  35 );
glVertex3f( -35,  35, -35 );
glVertex3f( -35, -35, -35 );
glEnd();

// Blue side - TOP
glBegin(GL_POLYGON);
glColor3f(   0.0,  0.0,  1.0 );
glVertex3f(  35,  35,  35 );
glVertex3f(  35,  35, -35 );
glVertex3f( -35,  35, -35 );
glVertex3f( -35,  35,  35 );
glEnd();

// Red side - BOTTOM
glBegin(GL_POLYGON);
glColor3f(   1.0,  0.0,  0.0 );
glVertex3f(  35, -35, -35 );
glVertex3f(  35, -35,  35 );
glVertex3f( -35, -35,  35 );
glVertex3f( -35, -35, -35 );
glEnd();
}*/
/*void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}*/
void drawWireSphere(){
    glPushMatrix();
        glTranslatef(0.0,0,-50);
        glScalef(1,1,5);
        glutWireSphere(10,16,16);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0,0,-130);
        glScalef(1,1,5);
        glutWireSphere(6,16,16);
    glPopMatrix();
}


void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
		    if(length>0)
            {
                length=length-5;
                radius = radius+5;
            }
			break;
		case GLUT_KEY_END:

                length=length+5;
                radius = radius -5;

			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight-70,		0,0,0,		0,0,1);
	//gluLookAt(100,100,100,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

    glColor3f(1,0,0);
    //drawSquare(length);
    //drawCylinderPart(30,30,24);
    //drawSS();
    //drawWheel(30,14);
    //drawCircle(30,14);
    //drawWireSphere();
    //drawSpherePart(30,24,20);

    //drawCone(20,50,24);
    //drawCylinder(20,20,98);
    drawCylinder();
    drawSphere();
    drawCube();







	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	length=40;
	radius=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
