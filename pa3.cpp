#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace Clustering;
using namespace std;


int main() {
    int k = 3;
    string line;
    ifstream csv("points.txt");
    Point p(5);
    double temparray[5] = {3.0,5.4,8.7,9.0,11.2};
    double temparray2[5] = {6.0,3.1,2.87,22.0,7.2};
    double temparray3[5] = {22.0,65.1,12.87,103.0, 44};
    Point* p2 = new Point(5, temparray);
    Cluster c1(5);
    Cluster c2(5);
    Point p3(*p2);
    Point* p4 = new Point(5, temparray2);
    Point* p5 = new Point(5, temparray3);
    c2 += *p5;
    c2.add(*p2);
    c1 += *p4;
    c1 += p3;

cout << c1.contains(*p5);


//    *p4 == *p5;
//    *p4 != *p5;
//    *p4 < *p5;
//    *p4 > *p5;
//    *p4 <= *p5;
//    *p4 >= *p5;
//    *p4 += *p5;
//    *p4 + *p5;
//    *p4 - *p5;
//    cout << *p4 << endl;

















//    KMeans test(3, 5, "points.txt");
//    test.start();

//    c1.add(p2);
//    c1.add(p3);
//    c1.add(p4);
//    c1.add(p5);
//    cout << c1 << endl;
//    cout << c2 << endl;


//    cout << c1;

//    Point pointarray[k];
//
//    c1.pickPoints(k, pointarray);
//
//    for(int i = 0; i< k; i++)
//    {
//        cout << pointarray[i];
//    }




//    Cluster::Move c1toc2(p3,&c1,&c2);
//
//    c1toc2.perform();
//
//    cout << c1 << endl << endl;
//    cout << c2 << endl;





//    c1.setcentroid(p2);
//    cout << c1.getcentroid() << endl << endl;
//
//    if (csv.is_open())
//    {
//        csv >> c1;
//
//    }
//    else
//    {
//        cout << "Error, opening failed" << endl;
//    }
//    csv.close();
//
//
//
//    cout << "The size of the cluster is " << c1.getsize() << endl;
//
//    cout << c1 << endl << endl;
//
//    c1.computecentroid();
//    cout << c1.getcentroid();
    return 0;

}

