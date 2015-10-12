#include "Point.h"
#include "Cluster.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace Clustering;
using namespace std;


int main() {
    string line;
    ifstream csv("points.txt");
    Point p(5);
    double temparray[5] = {3.0,5.4,8.7,9.0,11.2};
    Point p2(5, temparray);
    Cluster c1;

    c1.setcentroid(p2);
    cout << c1.getcentroid() << endl << endl;

    if (csv.is_open())
    {
        csv >> c1;

    }
    else
    {
        cout << "Error, opening failed" << endl;
    }
    csv.close();



    cout << "The size of the cluster is " << c1.getsize() << endl;

    cout << c1 << endl << endl;

    c1.computecentroid();
    cout << c1.getcentroid();
    return 0;

}

