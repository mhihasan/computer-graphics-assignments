#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

//double cameraHeight;
//double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

double length;
double radius;
struct lookDirection
{
    double x,y,z;
}lookDir;
struct upDirection
{
    double x,y,z;
}upDir;
struct rightDirection
{
    double x,y,z;
}rightDir;
struct cameraPosition
{
    double x,y,z;
}cameraPos;

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

void keyboardListener(unsigned char key, int x,int y){
	double angle=0.03;
	double vector_value;
	switch(key){

		case '1'://rotate right
            lookDir.x=lookDir.x*cos(angle) + rightDir.x*sin(angle);
			lookDir.y=lookDir.y*cos(angle) + rightDir.y*sin(angle);

			rightDir.x=lookDir.y*upDir.z - lookDir.z*upDir.y;
			rightDir.y=lookDir.z*upDir.x - lookDir.x*upDir.z;
			rightDir.z=lookDir.x*upDir.y - lookDir.y*upDir.x;

			vector_value= sqrt(rightDir.x*rightDir.x + rightDir.y*rightDir.y + rightDir.z*rightDir.z);
			rightDir.x/=vector_value;
			rightDir.y/=vector_value;
			rightDir.z/=vector_value;

			break;
        case '2': //rotate left
            lookDir.x=lookDir.x*cos(angle) - rightDir.x*sin(angle);
            lookDir.y=lookDir.y*cos(angle) - rightDir.y*sin(angle);
            //r=l X u
            rightDir.x=lookDir.y*upDir.z - lookDir.z*upDir.y;
			rightDir.y=lookDir.z*upDir.x - lookDir.x*upDir.z;
			rightDir.z=lookDir.x*upDir.y - lookDir.y*upDir.x;

			vector_value= sqrt(rightDir.x*rightDir.x + rightDir.y*rightDir.y + rightDir.z*rightDir.z);
			rightDir.x/=vector_value;
			rightDir.y/=vector_value;
			rightDir.z/=vector_value;
			break;
        case '3':
            lookDir.x=lookDir.x*cos(angle)+upDir.x*sin(angle);
            lookDir.z=lookDir.z*cos(angle)+upDir.z*sin(angle);
            //u = r X l
            upDir.x=rightDir.y*lookDir.z - rightDir.z*lookDir.y;
            upDir.y=rightDir.z*lookDir.x - rightDir.x*lookDir.z;
            upDir.z=rightDir.x*lookDir.y - rightDir.y*lookDir.x;

            vector_value= sqrt(upDir.x*upDir.x + upDir.y*upDir.y + upDir.z*upDir.z);
            upDir.x/=vector_value;
            upDir.y/=vector_value;
            upDir.z/=vector_value;
            break;

        case '4':
            lookDir.x=lookDir.x*cos(angle)-upDir.x*sin(angle);
            lookDir.z=lookDir.z*cos(angle)-upDir.z*sin(angle);
            //u=r X l
            upDir.x=rightDir.y*lookDir.z - rightDir.z*lookDir.y;
            upDir.y=rightDir.z*lookDir.x - rightDir.x*lookDir.z;
            upDir.z=rightDir.x*lookDir.y - rightDir.y*lookDir.x;

            vector_value= sqrt(upDir.x*upDir.x + upDir.y*upDir.y + upDir.z*upDir.z);
            upDir.x/=vector_value;
            upDir.y/=vector_value;
            upDir.z/=vector_value;
            break;
        case '5':
            upDir.z=upDir.z*cos(angle) + rightDir.z*sin(angle);
            upDir.y=upDir.y*cos(angle) + rightDir.y*sin(angle);

            rightDir.x= lookDir.y*upDir.z - lookDir.z*upDir.y;
            rightDir.y= lookDir.z*upDir.x - lookDir.x*upDir.z;
            rightDir.z= lookDir.x*upDir.y - lookDir.y*upDir.x;

            vector_value=sqrt(rightDir.x*rightDir.x + rightDir.y*rightDir.y + rightDir.z*rightDir.z);
		    rightDir.x/=vector_value;
		    rightDir.y/=vector_value;
		    rightDir.z/=vector_value;
		    break;
        case '6':
            upDir.z=upDir.z*cos(angle) - rightDir.z*sin(angle);
            upDir.y=upDir.y*cos(angle) - rightDir.y*sin(angle);

            rightDir.x= lookDir.y*upDir.z - lookDir.z*upDir.y;
            rightDir.y= lookDir.z*upDir.x - lookDir.x*upDir.z;
            rightDir.z= lookDir.x*upDir.y - lookDir.y*upDir.x;

            vector_value=sqrt(rightDir.x*rightDir.x + rightDir.y*rightDir.y + rightDir.z*rightDir.z);
		    rightDir.x/=vector_value;
		    rightDir.y/=vector_value;
		    rightDir.z/=vector_value;
		    break;
		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){

		case GLUT_KEY_UP:		// up arrow key
			cameraPos.x+=2*lookDir.x;
			cameraPos.y+=2*lookDir.y;
			cameraPos.z+=2*lookDir.z;
			break;
        case GLUT_KEY_DOWN:		//down arrow key
			cameraPos.x-=2*lookDir.x;
			cameraPos.y-=2*lookDir.y;
			cameraPos.z-=2*lookDir.z;
			break;
		case GLUT_KEY_RIGHT:
			cameraPos.x+=2*rightDir.x;
			cameraPos.y+=2*rightDir.y;
			cameraPos.z+=2*rightDir.z;
			break;
		case GLUT_KEY_LEFT:
			cameraPos.x-=2*rightDir.x;
			cameraPos.y-=2*rightDir.y;
			cameraPos.z-=2*rightDir.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    cameraPos.x+=2*upDir.x;
			cameraPos.y+=2*upDir.y;
			cameraPos.z+=2*upDir.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
		    cameraPos.x-=2*upDir.x;
			cameraPos.y-=2*upDir.y;
			cameraPos.z-=2*upDir.z;
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
             if(length<40){
                length=length+5;
                radius = radius -5;
             }
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

	gluLookAt(cameraPos.x,cameraPos.y,cameraPos.z,cameraPos.x+lookDir.x, cameraPos.y+lookDir.y, cameraPos.z+lookDir.z, upDir.x,upDir.y,upDir.z);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight-70,		0,0,0,		0,0,1);
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
//	cameraHeight=150.0;
	//cameraAngle=1.0;
	angle=0;
	length=40;
	radius=0;

    upDir.x=0;
    upDir.y=0;
    upDir.z=1;

    rightDir.x=-1.0/sqrt(2);
    rightDir.y= 1.0/sqrt(2);
    rightDir.z=0;

    lookDir.x=-1.0/sqrt(2);
    lookDir.y=-1.0/sqrt(2);
    lookDir.z=0;

    cameraPos.x=100;
    cameraPos.y=100;
    cameraPos.z=0;
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
