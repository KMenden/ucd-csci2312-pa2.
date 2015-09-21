## Cluster Program Introduction

The following is a cluster program that contains two classes (both their definition and implementation files) named cluster and point. The program is a clustering program where the user is able to create their own points of a user defined number of demensions (X,Y,Z and above, stored in a dynamic array) and then create clusters that contain these points. In order to utilize this program you must include the cluster.h and point.h header into your program using #include "point.h" (include the quotes), you also must use the clustering namespace that the program is written into using "using namespace clustering" (without the quotes).

## Point Class Documentaion

The point class is capable of creating points with a user given number of demensions. In order to create a new point, you define a point data type such as "Point p1" but you must pass in the number of demensions as a function argument such as "Point p1(3)" for a point that has three coordinates for three demensions. Should you only pass the number of demensions, then each coordinate will be set to 0 and can be set later using the getvalue and setvalue functions. Should you define an array that is the same size as your demensions, you can pass the array into your point as well to initialize it as it is created. From there, it is possible to utilize the comparison, arithmetic, and assiment operators on two points such as +, -, +=, and -=, which will take two points and add/subtract them (and in the case of += and -=, assign them to another point), and ==, <=, >=, <, >, which will check for each comparison and return a bool result. Comparisons between two points is done in a lexicographic order (point (1,2,3) is less than (4,5,2) and (4,2,1) is greater than (4,1,4)). However, the *, /, *=, and /=, operators can ONLY be done with whole numbers (Such as    (1,2,3) * 2 is (2,4,6)).

##Cluster Class Documentation
#ucd-csci2312-pa2.
