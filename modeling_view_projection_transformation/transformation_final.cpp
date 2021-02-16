#include <bits/stdc++.h>


using namespace std;

#define pi (2*acos(0.0))

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

class Matrix{
private:
    double **matrix;
    int row,column;
public:
    Matrix()
    {

        matrix = new double *[4];
        for(int r=0;r<4;r++){
            matrix[r]=new double[4];
            for(int c=0;c<4;c++){
                if(r==c){
                    matrix[r][c]=1;
                }
                else{
                    matrix[r][c]=0;
                }
            }
        }
        row = 4;
        column = 4;

    }

    Matrix(double x,double y,double z)
    {
        matrix = new double *[4]; //array of pointer of 4 element

        matrix[0]=new double[1];
        matrix[1]=new double[1];
        matrix[2]=new double[1];
        matrix[3]=new double[1];

        //assign value
        matrix[0][0]=x;
        matrix[1][0]=y;
        matrix[2][0]=z;
        matrix[3][0]=1;

        row=4;
        column=1;

    }

    Matrix(double **mat,int r,int c){
        matrix=mat;
        row=r;
        column=c;
    }
    void translationMatrix(double tx,double ty,double tz)
    {
        matrix[0][3] = tx;
        matrix[1][3] = ty;
        matrix[2][3] = tz;
    }
    void scalingMatrix(double sx,double sy,double sz)
    {
        matrix[0][0] = sx;
        matrix[1][1] = sy;
        matrix[2][2] = sz;
    }
    void rotationMatrix(double c1_x,double c1_y,double c1_z,
                        double c2_x,double c2_y,double c2_z,
                        double c3_x,double c3_y,double c3_z
                        )
    {
        matrix[0][0] = c1_x;
        matrix[1][0] = c1_y;
        matrix[2][0] = c1_z;

        matrix[0][1] = c2_x;
        matrix[1][1] = c2_y;
        matrix[2][1] = c2_z;

        matrix[0][2] = c3_x;
        matrix[1][2] = c3_y;
        matrix[2][2] = c3_z;
    }
    void projectionMatrix(double near, double far,double t,double r)
    {
        matrix[0][0] = near/r;
        matrix[1][1] = near/t;
        matrix[2][2] = -(far+near)/(far-near);
        matrix[3][3] = 0;

        matrix[2][3] = -(2*far*near)/(far-near);
        matrix[3][2] = -1;

    }
    double** getMatrix(){
        return matrix;
    }

    int getRow(){
        return row;
    }
    int getColumn(){
        return column;
    }


    Matrix multiplyMatrix(Matrix multiplier)
    {
        double **result = new double *[row];
        for(int r=0; r<row ; r++){
            result[r] = new double[multiplier.getColumn()];
            for(int c=0 ; c< multiplier.getColumn() ; c++){
                result[r][c]=0.0;
                for(int k=0 ; k< multiplier.getRow() ; k++){
                    result[r][c] += matrix[r][k]*multiplier.getMatrix()[k][c];
                }
            }
        }
        Matrix res(result, row, multiplier.getColumn());
        //print();
        return res;
    }
    /*bool operator!= (const Matrix m1)
    {
        int flag=0;
        for(int i=0;i<m1.row;i++){
            for(int j=0;j<m1.column;j++){
                    if((!matrix[i][j] == m1[i][j]))
                           return false

                if(matrix[i][j] != m1[i][j])
                    return false;
            }
        }
        return true;
    }*/
    void print(){
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

};

Vector eye,look,up;
double fovY,aspectRatio,near,far;
stack<Matrix>S;
Matrix identityMatrix;
int triangle_number=0;


void modelingTransformation()
{
    S.push(identityMatrix);
    string command;
    freopen("out.txt","w",stdout);

    vector<int>pushMatrix;
    int push_index =0;
    while(cin>>command)
    {
        if(command=="triangle"){
            int n=3;
            triangle_number++;
            while(n>0){

                double x,y,z;
                cin>>x>>y>>z;

                Matrix p(x,y,z);

                double **point = S.top().multiplyMatrix(p).getMatrix();

                x = point[0][0]/point[3][0];
                y = point[1][0]/point[3][0];
                z = point[2][0]/point[3][0];

                printf("%.3lf  %.3lf  %.3lf\n",x,y,z);
                n--;
            }
            printf("\n");

        }
         else if(command=="translate"){
            double tx,ty,tz;
            cin>>tx>>ty>>tz;

            Matrix T;
            T.translationMatrix(tx,ty,tz);
            S.push(S.top().multiplyMatrix(T));
        }
        else if(command == "scale"){
            double sx,sy,sz;
            cin>>sx>>sy>>sz;

            Matrix s;
            s.scalingMatrix(sx,sy,sz);
            S.push(S.top().multiplyMatrix(s));
        }
        else if(command=="rotate"){
            double angle,ax,ay,az;
            cin>>angle>>ax>>ay>>az;

            Vector I,J,K,a;
            I.setX(1);
            I.setY(0);
            I.setZ(0);

            J.setX(0);
            J.setY(1);
            J.setZ(0);

            K.setX(0);
            K.setY(0);
            K.setZ(1);

            a.setX(ax);
            a.setY(ay);
            a.setZ(az);

            a.normalize();

            Vector C1, C2, C3,cross;
            angle = angle*(pi/180.0);

            double temp;
            //1st Column of Rotation Matrix

            C1 = I.scaleVector(cos(angle));

            temp = a.dotProduct(I);
            temp = (1-cos(angle))*temp;
            C1 = C1.addition(a.scaleVector(temp));

            cross = a.crossProduct(I);

            C1 = C1.addition(cross.scaleVector(sin(angle)));
            //printf("%lf %lf %lf \n",C1.getX(),C1.getY(),C1.getZ());

            //2nd column of rotation matrix
            C2 = J.scaleVector(cos(angle));

            temp = a.dotProduct(J);
            temp = (1-cos(angle))*temp;
            C2 = C2.addition(a.scaleVector(temp));

            cross = a.crossProduct(J);
            C2 = C2.addition(cross.scaleVector(sin(angle)));
           // printf("%lf %lf %lf \n",C2.getX(),C2.getY(),C2.getZ());

            //3rd column of rotation matrix

            C3 = K.scaleVector(cos(angle));

            temp = a.dotProduct(K);
            temp = (1-cos(angle))*temp;

            C3 = C3.addition(a.scaleVector(temp));

            cross = a.crossProduct(K);
            C3 = C3.addition(cross.scaleVector(sin(angle)));
           // printf("%lf %lf %lf \n",C3.getX(),C3.getY(),C3.getZ());
            Matrix R;
            R.rotationMatrix(C1.getX(),C1.getY(),C1.getZ(),
                                          C2.getX(),C2.getY(),C2.getZ(),
                                          C3.getX(),C3.getY(),C3.getZ());
            //R.print();
            //S.top().print();
            S.push(S.top().multiplyMatrix(R));
            //S.top().print();
         }
         else if(command=="push"){
            //pushMatrix.push_back(S.top());
            push_index = S.size();
            pushMatrix.push_back(push_index);
         }
         else if(command=="pop"){
            /*while( pushMatrix.back() != S.top()){
                S.pop();
            }
            pushMatrix.pop_back();*/
            int delete_size = S.size()-pushMatrix.back();
            while(delete_size>0){
                S.pop();
                delete_size--;
            }
            pushMatrix.pop_back();

         }
         else if(command=="end"){
            break;
         }

    }

      while(S.size()>1)  //empty the Stack
        S.pop();

}

void viewTransformation()
{
    Vector l,r,u;

    l.setX(look.getX() - eye.getX());
    l.setY(look.getY() - eye.getY());
    l.setZ(look.getZ() - eye.getZ());
    l.normalize();

    r = l.crossProduct(up);
    r.normalize();

    u = r.crossProduct(l);

    Matrix translation;
    translation.translationMatrix(-eye.getX(), -eye.getY(), -eye.getZ());

    Matrix rotation;
    rotation.rotationMatrix(r.getX(),u.getX(),-l.getX(),
                            r.getY(),u.getY(),-l.getY(),
                            r.getZ(),u.getZ(),-l.getZ());
    Matrix viewTansformMatrix;
    viewTansformMatrix = rotation.multiplyMatrix(translation);


    S.push(S.top().multiplyMatrix(viewTansformMatrix));

    ifstream cin("out.txt");
    freopen("out1.txt","w",stdout);
    int triangle = triangle_number;
    while(triangle>0){
        int n=3;
        while(n>0){
                double x,y,z;
                cin>>x>>y>>z;
                //printf("%lf %lf %lf\n",x,y,z);
                Matrix p(x,y,z);

                double **point = S.top().multiplyMatrix(p).getMatrix();

                x = point[0][0]/point[3][0];
                y = point[1][0]/point[3][0];
                z = point[2][0]/point[3][0];

                printf("%.3lf %.3lf %.3lf\n",x,y,z);
                n--;

        }
        printf("\n");
        triangle--;

    }
    S.pop();


}

void projectionTransformation()
{
    double fovX,t,r;
    fovX = fovY * aspectRatio;
    t = near * tan((fovY/2.0)*(pi/180.0));
    r = near * tan((fovX/2.0)*(pi/180.0));

    Matrix projectionTransfromMatrix;
    projectionTransfromMatrix.projectionMatrix(near,far,t,r);

    S.push(S.top().multiplyMatrix(projectionTransfromMatrix));

    ifstream cin("out1.txt");
    freopen("out2.txt","w",stdout);

    int triangle = triangle_number;
    while(triangle>0){
        int n=3;
        while(n>0){
                double x,y,z;
                cin>>x>>y>>z;
                //printf("%.3lf %.3lf %.3lf\n",x,y,z);

                //printf("%lf %lf %lf\n",x,y,z);
                Matrix p(x,y,z);

                double **point = S.top().multiplyMatrix(p).getMatrix();

                x = point[0][0]/point[3][0];
                y = point[1][0]/point[3][0];
                z = point[2][0]/point[3][0];

                printf("%.7lf %.7lf %.7lf\n",x,y,z);
                n--;

        }
        printf("\n");
        triangle--;

    }
    S.pop();

}
int main()
{
    freopen("scene.txt","r",stdin);

    double x,y,z;
    cin>>x>>y>>z;
    eye.setX(x);
    eye.setY(y);
    eye.setZ(z);

    cin>>x>>y>>z;
    look.setX(x);
    look.setY(y);
    look.setZ(z);

    cin>>x>>y>>z;
    up.setX(x);
    up.setY(y);
    up.setZ(z);

    cin>>fovY>>aspectRatio>>near>>far;

    modelingTransformation();
    viewTransformation();
    projectionTransformation();

    return 0;
}
