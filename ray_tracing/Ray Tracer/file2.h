#include<math.h>
#include <windows.h>
#include <glut.h>
using namespace std;

class Vector{
private:
    double x,y,z;
public:
    void normalize()
    {
        double value=sqrt(x*x + y*y + z*z);
        x = x/value;
        y = y/value;
        z = z/value;
    }
    Vector addition(Vector v)
    {
        Vector result;
        result.x = x + v.x;
        result.y = y + v.y;
        result.z = z + v.z;

        return result;
    }
    double length(){
        return sqrt(x*x +y*y +z*z);
    }
    Vector operator +(Vector const &v){
        Vector result;
        result.x = x + v.x;
        result.y = y + v.y;
        result.z = z + v.z;

        return result;
    }
    Vector operator -(Vector const &v){
        Vector result;
        result.x = x - v.x;
        result.y = y - v.y;
        result.z = z - v.z;

        return result;
    }
    Vector scaleVector(double scaleValue)
    {
        Vector result;
        result.x = scaleValue * x;
        result.y = scaleValue * y;
        result.z = scaleValue * z;

        return result;
    }
    double dotProduct(Vector v)
    {
        return (x*v.x + y*v.y + z*v.z);
    }
    Vector crossProduct(Vector v)
    {
        Vector result;
        result.x = y*v.z - z*v.y;
        result.y = z*v.x - x*v.z;
        result.z = x*v.y - y*v.x;

        return result;
    }
    Vector operator /(double val){
        Vector result;
        result.x = x/val;
        result.y = y/val;
        result.z = z/val;

        return result;
    }
    Vector &operator +=(Vector const &v){

        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }

    void setX(double a)
    {
        x=a;
    }
    void setY(double b)
    {
        y=b;
    }
    void setZ(double c)
    {
        z=c;
    }
    double getX()
    {
        return x;
    }
    double getY()
    {
        return y;
    }
    double getZ()
    {
        return z;
    }

};
class Ray{
 public:
    Vector origin,direction;
 public:
    Ray(Vector eye, Vector dir):origin(eye),direction(dir){
         direction.normalize();
         //cout<<direction.getX()<<" "<<direction.getY()<<" "<<direction.getZ()<<endl;
         origin += direction.scaleVector(1.0/1000.0);
         //cout<<origin.getX()<<" "<<origin.getY()<<" "<<origin.getZ()<<endl;
    }
};
class Object{
 public:
     Vector reference_point;
     double height, width,length;
     int shine;
     double color[3];
     double co_efficient[4];
public:
     void setColor(int r,int g,int b){
         color[0]=r;
         color[1]=g;
         color[2]=b;
         //cout<<"Color: "<<color[0]<<" "<<color[1]<<" "<<color[2]<<endl;
     }
     void setShine(int s){
         shine =s;
         //cout<<"Shine: "<<shine<<endl;
     }
     void setCoEfficient(double a,double b, double c,double d){
         co_efficient[0]=a;
         co_efficient[1]=b;
         co_efficient[2]=c;
         co_efficient[3]=d;

        // cout<<"co-efficient: "<<co_efficient[0]<<" "<<co_efficient[1]<<" "<<co_efficient[2]<<" "<<co_efficient[3]<<endl;
     }
     virtual void draw(){
         cout<<"Base is running"<<endl;
     }
     virtual double getIntersectingT(Ray ray){
         //cout<<"Base class intersection"<<endl;
          return DBL_MAX;
     }
     virtual double* getColorAt(Vector intersectionPoint){
         return Object::getColor();
     }
     virtual double* getColor(){
         return color;
     }
     virtual Vector getNormal(Vector point){
         point.setX(0);
         point.setY(0);
         point.setZ(0);
         return point;
     }
     double intersect(Ray r, double *current_color, int level){
         return -1;
     }
};

class Sphere : public Object{
   public:
       Sphere(Vector center, double radius){
          reference_point = center;
          length = radius;
       }
       void draw(){
        // cout<<"Sphere is drawing"<<endl;
          glColor3f(color[0],color[1],color[2]);
          glTranslatef(reference_point.getX(),reference_point.getY(),reference_point.getZ());
          glutSolidSphere(length,30,24);

       }
      double getIntersectingT(Ray ray){
          //cout<<"Sphere class intersection"<<endl;
          Vector R0 = ray.origin - reference_point;
          double a = ray.direction.dotProduct(ray.direction);
          double b = ray.direction.dotProduct(R0)*2;
          double c = R0.dotProduct(R0) - length*length;
          double disc = b*b - 4*a*c;
          if(disc<0) return DBL_MAX; //no intersection
          disc = sqrt(disc);
          double t1 = (-b - disc)*0.5*a;
          double t2 = (-b + disc)*0.5*a;
          t1 = min(t1,t2);
          //cout<<t1<<endl;
          return t1;
      }
      double* getColor(Vector intersection_point){
          return color;
      }
      double intersect(Ray r, double *current_color, int level){
          double t = getIntersectingT(r);
          if(t<=0) return -1;
          if(level ==0)return t;

          Vector intersectionPoint = r.origin + r.direction.scaleVector(t);
          double *colorAt;
          colorAt = getColorAt(intersectionPoint);
          setColor(colorAt[0],colorAt[1],colorAt[2]);
          return t;

      }
      Vector getNormal(Vector intersect_point){
          Vector normal;
          normal = (intersect_point-reference_point);
          normal.normalize();

          return normal;
      }

};
class Floor : public Object{
   private:
        double floorWidth, tileWidth;
   public:
       Floor(double floor_width,double tile_width){
            floorWidth = floor_width;
            tileWidth = tile_width;
            Vector v;
            v.setX(-floor_width/2);
            v.setY(-floor_width/2);
            v.setZ(0);
            reference_point= v;
            length = tile_width;
       }
       void draw(){
           //cout<<"Floor is drawing"<<endl;
           glTranslatef(reference_point.getX(),reference_point.getY(),0);
	       glBegin(GL_QUADS);
	       for (unsigned int x =0;x<floorWidth;++x)
		        for (unsigned int y =0;y<floorWidth;++y)
		        {
                    if ((x+y)%2==0) //modulo 2
				         glColor3f(1.0f,1.0f,1.0f); //white
			        else
                         glColor3f(0.0f,0.0f,0.0f); //black

			        glVertex2f(    x*tileWidth,    y*tileWidth);
			        glVertex2f((x+1)*tileWidth,    y*tileWidth);
			        glVertex2f((x+1)*tileWidth,(y+1)*tileWidth);
			        glVertex2f(    x*tileWidth,(y+1)*tileWidth);

		       }
	        glEnd();
           }
};

vector<Object*>objects;
vector<Vector>lights;
