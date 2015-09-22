#include "Point.h"
#include "Cluster.h"
#include <cassert>

using namespace Clustering;
using namespace std;


bool test1(const Cluster &testcluster)
{
    assert(cout << testcluster);
    cout << "Cout Test:Pass" << endl;
}


int main()
{
    double testarray[5] = {4,3,6,8,5};
    double testarray2[5] = {5,2,8,3,9};
    double testarray3[5] = {8,2,1,5,7};
    Point p1(5);
    Point p2(5, testarray);
    Point p3(5, testarray2);
    Point p4(5, testarray3);

    Cluster c1;
    Cluster c2;
    c1.add(&p2);
    c1 += (p3);
    test1(c1);
    return 0;

}

