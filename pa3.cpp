#include "Point.h"
#include "Cluster.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>


using namespace Clustering;
using namespace std;

int main() {
//    int k = 3;
//    string line;
//    ifstream csv("points.txt");

    float temparray[5] = {3.0,5.4,8.7,9.0,11.2};
    double temparray2[5] = {6.0,3.1,2.87,22.0,7.2};
    double temparray3[5] = {22.0,65.1,12.87,103.0, 44};

    Point<float,5> testp(5, temparray);
    Point<float,5> test2(testp);
    Cluster<Point<float, 5>, 5> test(5);
    Cluster<Point<float, 5>, 5> testc2(5);
    test.add(testp);
    test.add(test2);

test += testp;
    cout << test;
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

