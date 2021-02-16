void drawAxes();
double getNearestIntersection(Ray ray);
double* performLighting(Object,Vector point, double *color);
double* getAmbientLighting(Object,double *c);
double* getDiffuseLighting(Object,Vector point, double* col);
int isObjectBetween(Ray ray,int , double light_distance);
void capture();

#define pi (2*acos(0.0))
int drawgrid;
int drawaxes;
double angle;
double image_width=768,image_height=768;
double WINDOW_WIDTH=500, WINDOW_HEIGHT=500;
int reflection_level;
int level=0;
double length;
double radius;
Vector eye;
extern vector<Object*>objects;
extern vector<Vector>lights;
struct Intersection{
   int nearest;
   double t_min;
}intersection;
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

void keyboardListener(unsigned char key, int x,int y){
	double angle=0.03;
	double vector_value;
	switch(key){
        case '0':
            capture();
            break;
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

