#include "Point.h"
#include "Cluster.h"
#include <cassert>

using namespace Clustering;
using namespace std;


int main()
{
    double testarray[5] = {4,3,6,8,5};
    double testarray2[5] = {5,2,8,3,9};
    double testarray3[5] = {8,2,1,5,7};
    Point p1(5);
    Point p5(5);
    Point p2(5, testarray);
    Point p3(5, testarray2);
    Point p4(5, testarray3);

    Cluster c1;
    c1.add(&p1);
    c1.add(&p2);
    c1.add(&p3);
    Cluster c2;
    c2.add(&p4);
    c2.add(&p2);
    cout << c1 << endl;
    cout << c1 - c2;

    return 0;

}

