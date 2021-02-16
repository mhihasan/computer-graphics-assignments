#include<bits/stdc++.h>
#include "bitmap_image.hpp"
using namespace std;


struct Point{
   double x,y,z;
};
struct xz_Value{
    double x,z;
};
class Triangle{
    public:
    Point points[3];
    int color[3];

    Triangle(Point p1,Point p2,Point p3){
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;


        color[0] = rand()%256;
        color[1] = rand()%256;
        color[2] = rand()%256;
    }
};


int screen_height,screen_width;
double x_left_limit, x_right_limit, y_bottom_limit, y_top_limit, z_front,z_max;
double** z_buffer;
bitmap_image frame_buffer(800,800);
double top_y,left_x;
double dx, dy; // length and width of a cell

vector<Triangle>triangles;

void read_data()
{
   srand(time(NULL)); // for random RGB generator.
   freopen("config.txt","r",stdin);
   cin>>screen_width>>screen_height;
   cin>>x_left_limit;
   cin>>y_bottom_limit;
   cin>>z_front>>z_max;
//   printf("%d %d\n",screen_width,screen_height);
//   printf("%.3lf\n",x_left_limit);
//   printf("%.3lf\n",y_bottom_limit);
//   printf("%.3lf %.3lf\n",z_front,z_rear);

   ifstream cin("stage3.txt");

   while(!cin.eof()){

      int n =3,i=0;
      //Triangle triangle();
      Point p[3];
      while(n>0){

         double x,y,z;
         cin>>x>>y>>z;
         //cout<<x<<" "<<y<<" "<<z<<endl;
          p[i].x = x;
          p[i].y = y;
          p[i].z = z;
          i++;

          n--;
      }
      //cout<<endl;
     // number_of_triangle++;
      triangles.push_back(Triangle(p[0],p[1],p[2]));
   }

//   for(int i=0;i<triangles.size();i++){
//        for(int j=0;j<3;j++){
//            cout<<triangles[i].points[j].x <<" "<<triangles[i].points[j].y<<" "<<triangles[i].points[j].z<<endl;
//        }
//        for(int k=0;k<3;k++)
//            cout<<triangles[i].color[k]<<" ";
//            cout<<endl;
//            cout<<endl;
//   }
}

void initialize_z_buffer_and_frame_buffer()
{

    // Allocate Memory for Z_buffer.
    z_buffer = new double*[screen_height];
    for(int i=0;i<screen_height;i++){
         z_buffer[i] = new double[screen_width];
    }

    for(int i=0;i<screen_height;i++){
        for(int j=0;j<screen_width;j++){
            z_buffer[i][j] = z_max;
        }
    }

    //Initialize Frame buffer
    //bitmap_image frame_buffer(screen_width,screen_height);
    for(int i=0;i<screen_width;i++){
        for(int j=0;j<screen_height;j++){
            frame_buffer.set_pixel(i,j,0,0,0);
        }
    }


     y_top_limit=-y_bottom_limit;
     x_right_limit=-x_left_limit;

     dx = (x_right_limit - x_left_limit)/screen_width;
     dy = (y_top_limit - y_bottom_limit)/screen_height;

     top_y = y_top_limit - dy/2.0;
     left_x = x_left_limit + dx/2.0;


}
void depthBuffer()
{

     for(int i=0;i<triangles.size();i++){
        double top_scanline, bottom_scanline;
        double max_y,min_y;
        // find min_y and max_y of triangle.

        max_y = max(max(triangles[i].points[0].y, triangles[i].points[1].y),triangles[i].points[2].y);
        min_y = min(min(triangles[i].points[0].y, triangles[i].points[1].y),triangles[i].points[2].y);

        //check whether triangle is outside of view plane.
        if(min_y > y_top_limit || max_y < y_bottom_limit )
              continue;

        //check for clipping

        double y_min,y_max;
        y_min = max(-top_y, min_y);
        bottom_scanline = (top_y - y_min)/dy; //mapping to z buffer

        y_max= min(top_y , max_y);
        top_scanline = (top_y - y_max)/dy;
        cout<<bottom_scanline<<" "<<top_scanline<<endl; //mapping to z buffer

        for(double row=top_scanline; row<=bottom_scanline; row += dy){
             double x1,z1,x2,z2;
              //check if 0-1 point is active or not
             double y = top_y - row*dy ;
             vector< xz_Value > xz;
             //vector< double > z;
             //cout<<y<<endl;

             // checking p0-p1 line
             if(y>=triangles[i].points[0].y && y<=triangles[i].points[1].y  ||
                y<=triangles[i].points[0].y && y>=triangles[i].points[1].y){
                  double tempx,temp1,temp2,tempz;
                  //xL = (x0-x1)*(y-y0)/(y0-y1) + x0
                   tempx  = (triangles[i].points[0].x - triangles[i].points[1].x);
                   temp1 = (triangles[i].points[0].y - triangles[i].points[1].y);
                   temp2 = (y - triangles[i].points[0].y);
                  x1 = (temp2/temp1)*tempx + triangles[i].points[0].x;

                  xz_Value xz_val;
                  xz_val.x=x1;
                  //x.push_back(x1);
                  //zL = (z0-z1)*(y-y0)/(y0-y1) + z0
                   tempz = (triangles[i].points[0].z - triangles[i].points[1].z);
                  z1 = (temp2/temp1)*tempz + triangles[i].points[0].z;

                  xz_val.z= z1;
                  xz.push_back(xz_val);
                 // cout<<x1 <<" "<<z1<<endl;
              }

              //checking p0-p2 line
             if(y>=triangles[i].points[0].y && y<=triangles[i].points[2].y  ||
                y<=triangles[i].points[0].y && y>=triangles[i].points[2].y){
                  double tempx,temp1,temp2,tempz;
                  //xR = (x0-x2)*(y-y0)/(y0-y2) + x0
                   tempx  = (triangles[i].points[0].x - triangles[i].points[2].x);
                   temp1 = (triangles[i].points[0].y - triangles[i].points[2].y);
                   temp2 = (y - triangles[i].points[0].y);
                  x1 = (temp2/temp1)*tempx + triangles[i].points[0].x;
                  xz_Value xz_val;
                  xz_val.x=x1;
                  //x.push_back(x1);
                  //zR = (z0-z2)*(y-y0)/(y0-y2) + z0
                   tempz = (triangles[i].points[0].z - triangles[i].points[2].z);
                  z1 = (temp2/temp1)*tempz + triangles[i].points[0].z;
                  xz_val.z = z1;
                  xz.push_back(xz_val);
                  //cout<<x1 <<" "<<z1<<endl;

                }
                //checking p1-p2 line
                if(y>=triangles[i].points[1].y && y<=triangles[i].points[2].y  ||
                y<=triangles[i].points[1].y && y>=triangles[i].points[2].y){
                    double tempx,temp1,temp2,tempz;
                  //xR = (x1-x2)*(y-y1)/(y1-y2) + x1
                   tempx  = (triangles[i].points[1].x - triangles[i].points[2].x);
                   temp1 = (triangles[i].points[1].y - triangles[i].points[2].y);
                   temp2 = (y - triangles[i].points[1].y);
                  x1 = (temp2/temp1)*tempx + triangles[i].points[1].x;
                  xz_Value xz_val;
                  xz_val.x=x1;
                  //x.push_back(x1);
                  //zR = (z0-z2)*(y-y0)/(y0-y2) + z0
                   tempz = (triangles[i].points[1].z - triangles[i].points[2].z);
                  z1 = (temp2/temp1)*tempz + triangles[i].points[1].z;
                  xz_val.z=z1;
                  xz.push_back(xz_val);
                  //cout<<x1 <<" "<<z1<<endl;
                }

                // double max_x = max(xz[0].x,xz[1].x);
                 //double min_x = min(xz[0].x,xz[1].z);


                double max_x,min_x;
                double x_min,x_max,z_left,z_right;
                if(xz[0].x<xz[1].x){
                    min_x = xz[0].x;
                    max_x = xz[1].x;
                    z_left = xz[0].z;
                    z_right = xz[1].z;
                }
                else if(xz[0].x > xz[1].x){
                    min_x = xz[1].x;
                    max_x = xz[0].x;
                    z_left = xz[1].z;
                    z_right = xz[0].z;
                }
                //cout<<z_left<<" "<<z_right<<endl;

                //check whether the triangle is ouside of view plane
                 if(min_x > x_right_limit || max_x < x_left_limit)
                    continue;
                //clipping purpose
                x_min = max(left_x,min_x);
                x_max = min(-left_x, max_x);

                //corresponding left column and right column
                double left_column,right_column;
                left_column = (-left_x + x_min)/dx;
                right_column = (-left_x + x_max)/dx;
                //cout<<left_column<<" "<<right_column<<endl;
                for(double col= left_column;col<=right_column;col+=dx){
                    double x,z;
                    x = dx*col + left_x;
                    z = (x-x_min)/(x_max-x_min)*(z_right-z_left)+ z_left;
                    //cout<<z<<endl;
                    if(z<z_front)
                        z=z_front;
                    if(z<z_buffer[int(row)][int(col)]){
                        z_buffer[int(row)][int(col)]=z;
                        frame_buffer.set_pixel(int(col),int(row),triangles[i].color[0],triangles[i].color[1],triangles[i].color[2]);
                    }

                }

       }



     }

}

void save()
{
    frame_buffer.save_image("image.bmp");
    freopen("z_buffer.txt","w",stdout);
    for(int i=0;i<screen_height;i++){
        for(int j=0;j<screen_width;j++){
            if(z_buffer[i][j]<z_max){
                cout<<z_buffer[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}
void free_memory()
{
    //free z_buffer_memory
    for(int i=0;i<screen_height;i++)
        delete [] z_buffer[i];
    delete [] z_buffer;

     //free frame_buffer_memory
     //free(void(frame_buffer);

    //free objects memory
    triangles.clear();

}
int main()
{
    read_data();
    initialize_z_buffer_and_frame_buffer();
    depthBuffer();
    save();
    free_memory();
    return 0;
}
