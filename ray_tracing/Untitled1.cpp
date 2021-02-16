// virtual members
#include <iostream>
#include "file.h"
using namespace std;


int main () {
    CRectangle rect;
    CTriangle trgl;
    CPolygon poly;

    CPolygon * ppoly1 = &rect;
    CPolygon * ppoly2 = &trgl;
    CPolygon * ppoly3 = &poly;

    ppoly1->set_values (4,5);
    ppoly2->set_values (4,5);
    ppoly3->set_values (4,5);

    cout << ppoly1->area() << endl;
    cout << ppoly2->area() << endl;
    cout << ppoly3->area() << endl;

    return 0;
}
