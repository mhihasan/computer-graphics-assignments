#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "file2.h"
#include <windows.h>
#include <glut.h>
#include "bitmap_image.hpp"
#include "main.h"

void makeBackground(bitmap_image image, int width){
     for(int i=0;i<width;i++){
        for(int j=0;j<width;j++){
            image.set_pixel(i,j,0,0,255);
        }
    }
}
Intersection getNearestObjectIndex(Ray ray){
     Intersection inter;
     inter.nearest =-1;
     inter.t_min = 100000;
     for(int k=0;k<objects.size();k++){

         double t = objects[k]->getIntersectingT(ray);

         if(t<=0)continue;
         if(t<inter.t_min){
             inter.nearest =k;
             inter.t_min =t;
             //cout<<inter.nearest<<" "<<inter.t_min<<endl;
        }
    }
    return inter;
}

double *check(double *col){
    if(col[0]>1)
        col[0]=1;
    if(col[1]>1)
        col[1]=1;
    if(col[2]>0)
        col[2]=1;
    if(col[0]<0)
        col[0]=0;
    if(col[1]<0)
        col[1]=0;
    if(col[2]<0)
        col[2]=0;
    return col;
}
double* trace(Ray ray,int level){
     double *color = new double[3];
     for(int i=0;i<3;i++)color[i]=0.0;
     if(level>reflection_level)
        return color;

     intersection = getNearestObjectIndex(ray);
     if(intersection.nearest==-1)
        return color;

     Vector intersect_point;
     Vector reflect;

        double t_min = intersection.t_min;
        int nearest = intersection.nearest;

        double *dummyColor;
        intersect_point = ray.origin + ray.direction.scaleVector(t_min);
        //cout<<intersect_point.getX()<<" "<<intersect_point.getY()<<" "<<intersect_point.getZ()<<endl;

        dummyColor = objects[nearest]->getColor();
        Vector normal = objects[nearest]->getNormal(intersect_point);

        double* ambient_color = new double[3];

        //Ambient Lighting
        for(int i=0;i<3;i++){
            ambient_color[i]=dummyColor[i] * objects[nearest]->co_efficient[0];
        }

        //diffuse and specular Lighting
        double *diffuse_color = new double[3];
        double *specular_color = new double[3];
        for(int i=0;i<3;i++){
            diffuse_color[i]=0.0;
            specular_color[i]=0.0;
        }

        for(int i=0;i<lights.size();i++){
            Vector lightDir = lights[i] - intersect_point;
            double light_distance = lightDir.length();

            lightDir.normalize();
            intersect_point += lightDir.scaleVector(1.0/100.0);

            double NL = normal.dotProduct(lightDir);

            if(NL<0)
                continue;

            Ray r(intersect_point,lightDir);
            if(isObjectBetween(r,nearest,light_distance)){
                       cout<<"yes"<<endl;
                       continue;
                       }

            for(int i=0;i<3;i++){
                diffuse_color[i] += dummyColor[i]* NL* objects[nearest]->co_efficient[1];
            }

            //specular Lighting
            Vector view = eye - intersect_point;
            view.normalize();

            normal.normalize();
            reflect = normal.scaleVector(2*lightDir.dotProduct(normal)) - lightDir;
            double RV = view.dotProduct(reflect);
           // if(RV<0)continue;
            //cout<<pow(RV,objects[nearest]->shine)<<" "<<objects[nearest]->co_efficient[2]<<endl;
            double spec_component =pow(RV,objects[nearest]->shine)*objects[nearest]->co_efficient[2];
            for(int i=0;i<3;i++){
                specular_color[i] += spec_component*dummyColor[i];
            }
            //cout<<reflect.getX()<<" "<<reflect.getY()<<" "<<reflect.getZ()<<endl;

            for(int i=0;i<3;i++){
            color[i] = ambient_color[i] + diffuse_color[i] + specular_color[i];
            }
        }


      Ray new_ray(intersect_point,reflect);
      double* reflect_color = trace(new_ray,level+1);

      for(int i=0;i<3;i++)
         color[i] +=reflect_color[i]* objects[nearest]->co_efficient[3];


      return check(color);
}
void loadActualData(){
      freopen("scene.txt","r",stdin);
      cin>>reflection_level;
      cin>>image_width;
      image_height = image_width;
      int objects_num;
      cin>>objects_num;
      string name;
      for(int i=0;i<objects_num;i++){
            cin>>name;
            double r,g,b;
            double a,d,s,re;
            double shine;

            if(name =="sphere"){
                double x,y,z;
                cin>>x>>y>>z;
                //cout<<x<<" "<<y<<" "<<z<<endl;
                Vector center;
                center.setX(x);
                center.setY(y);
                center.setZ(z);

                double radius;
                cin>>radius;
                //cout<<radius<<endl;
                Object *temp= new Sphere(center,radius);

                cin>>r>>g>>b;
                //cout<<r<<" "<<g<<" "<<b<<endl;
                temp->setColor(r,g,b);

                cin>>a>>d>>s>>re;
                //cout<<a<<" "<<d<<" "<<s<<" "<<re<<endl;
                temp->setCoEfficient(a, d,s,re);

                cin>>shine;
                //cout<<shine<<endl;
                temp->setShine(shine);
                objects.push_back(temp);
            }
            if(name=="triangle"){
                 double x1,y1,z1;
                 cin>>x1>>y1>>z1;
                 double x2,y2,z2;
                 cin>>x2>>y2>>z2;
                 double x3,y3,z3;
                 cin>>x3>>y3>>z3;

                 cin>>r>>g>>b;
                 cin>>a>>d>>s>>re;
                 cin>>shine;

            }
            if(name =="general"){
                 double co_eff[10];
                 for(int i=0;i<10;i++){cin>>co_eff[i];
                // cout<<co_eff[i]<<" ";
                 }
                 cout<<endl;
                 double x[6];
                 for(int i=0;i<6;i++){
                    cin>>x[i];
                   // cout<<x[i]<<" ";
                 }
                 //cout<<endl;
                 cin>>r>>g>>b;
                 //cout<<r<<" "<<g<<" "<<b<<endl;

                 cin>>a>>d>>s>>re;
                // cin>>a>>d>>s>>re;
                 //cout<<a<<" "<<d<<" "<<s<<" "<<re<<endl;
                 cin>>shine;
                 //cout<<shine<<endl;
            }
      }

       int light_number;
       cin>>light_number;
      // cout<<light_number<<endl;
       for(int i=0;i<light_number;i++){
           double x,y,z;
           cin>>x>>y>>z;
           cout<<x<<" "<<y<<" "<<z<<endl;;
           Vector light1;
           light1.setX(x);
           light1.setY(y);
           light1.setZ(z);
           lights.push_back(light1);
       }

}
void freeMemory(){
     objects.clear();
     lights.clear();
}
void capture(){
     bitmap_image image(image_width,image_width);
     makeBackground(image,image_width);

     double VIEW_ANGLE = 80;
     double plane_distance= abs((WINDOW_HEIGHT/2)/tan(VIEW_ANGLE/2));
     //cout<<plane_distance;
     Vector l,r,u;

     l.setX(lookDir.x - cameraPos.x);
     l.setY(lookDir.y - cameraPos.y);
     l.setZ(lookDir.z - cameraPos.z);
     l.normalize();
     //cout<<l.getX()<<" "<<l.getY()<<" "<<l.getZ()<<endl;
     Vector up;
     up.setX(upDir.x);
     up.setY(upDir.y);
     up.setZ(upDir.z);
     r = l.crossProduct(up);
     r.normalize();
     //cout<<r.getX()<<" "<<r.getY()<<" "<<r.getZ()<<endl;
     u = r.crossProduct(l);
     //cout<<u.getX()<<" "<<u.getY()<<" "<<u.getZ()<<endl;
     eye.setX(cameraPos.x);
     eye.setY(cameraPos.y);
     eye.setZ(cameraPos.z);

     Vector top_left = eye + l.scaleVector(plane_distance)-r.scaleVector(WINDOW_WIDTH/2.0)+u.scaleVector(WINDOW_HEIGHT/2.0);
     //cout<<top_left.getX()<<" "<<top_left.getY()<<" "<<top_left.getZ()<<endl;
     double pixel_width = WINDOW_WIDTH/image_width;
     double pixel_height = WINDOW_HEIGHT/image_height;

     for(int i=0;i<image_width;i++){
        for(int j=0;j<image_height;j++){
            Vector poin_on_image = eye + l.scaleVector(plane_distance)-
                                    r.scaleVector(WINDOW_WIDTH/2.0-i*pixel_width)+
                                    u.scaleVector(WINDOW_HEIGHT/2.0-j*pixel_height);

            Ray ray(eye, poin_on_image-eye);
            double* pixel_color = trace(ray,0);

            image.set_pixel(i,j,pixel_color[0]*255,pixel_color[1]*255,pixel_color[2]*255);
        }
    }
     image.save_image("hasan.bmp");
     cout<<"Finish"<<endl;
}
int isObjectBetween(Ray ray,int nearest,double light_distance){
      double min_t=100000;
      Vector intersect_point;
      int flag =0;
      for(int i=0;i<objects.size();i++){
          if(i==nearest)
             continue;
          double t = objects[i]->getIntersectingT(ray);
          if(t<min_t)
            min_t=t;
      }
      intersect_point = ray.origin + ray.direction.scaleVector(min_t);
      double distance = intersect_point.length();
      //cout<<distance<<" "<<light_distance<<endl;
      if(distance<light_distance)
               flag = 1;
      return flag;
}

void loadTestData(){
    reflection_level = 5;
    Vector center;
    center.setX(0);
    center.setY(0);
    center.setZ(10);
    double radius = 10;

    Object *temp= new Sphere(center,radius);
    temp->setColor(1,0,0);
    temp->setCoEfficient(0.4, 0.2, 0.2 , 0.2);
    temp->setShine(5);
    objects.push_back(temp);

    Vector center1;
    center1.setX(0);
    center1.setY(20);
    center1.setZ(20);
    double radius1 = 10;

    Object *temp2= new Sphere(center1,radius1);
    temp2->setColor(0,1,0);
    temp2->setCoEfficient(0.4, 0.2, 0.2 , 0.2);
    temp2->setShine(1);
    objects.push_back(temp2);

    Object *temp1=new Floor(1000.0, 20.0);
    temp1->setCoEfficient(0.4,0.2,0.2,0.2);
    temp1->setShine(1);
    objects.push_back(temp1);

    Vector light1;
    light1.setX(50);
    light1.setY(-50);
    light1.setZ(50);
    lights.push_back(light1);

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

	gluLookAt(cameraPos.x,cameraPos.y,cameraPos.z,lookDir.x, lookDir.y, lookDir.z, upDir.x,upDir.y,upDir.z);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight-70,		0,0,0,		0,0,1);
	//gluLookAt(50,-100,30,0,0,0,	0,0,1);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

    glColor3f(1,0,0);
    //draw objects
    for(int i=0;i<objects.size();i++){
       glPushMatrix();
       objects[i]->draw();
       glPopMatrix();
    }
    //draw lights
    for(int i=0;i<lights.size();i++){
        glColor3f(1,1,1);
        glPushMatrix();
        glTranslatef(lights[i].getX(),lights[i].getY(),lights[i].getZ());
        glutSolidSphere(1.5,30,24);
        glPopMatrix();
    }


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}



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



void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;

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

    cameraPos.x=50;
    cameraPos.y=-100;
    cameraPos.z=10;
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
    //loadTestData();
    loadActualData();
	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
