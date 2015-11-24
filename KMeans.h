#ifndef KELLEN_CSCI2312_PA2_KMEANS_H
#define KELLEN_CSCI2312_PA2_KMEANS_H
#include "Point.h"
#include "Cluster.h"
#include <string>
#include <vector>

using namespace Clustering;

template<int k, int dim>
class KMeans {



public:

    KMeans(std::string file ) : filename(file) {};

    unsigned int pointdemensions;

    static const int SCORE_DIFF_THRESHOLD;
    double betacv;
    std::string filename;



    double mindistance(Point<double, dim> &, Point<double, dim> );

    double computeClusteringScore(std::vector<Cluster<Point<double, dim>, dim>>&);

    void run();
};



#include "KMeans.cpp"

#endif //KELLEN_CSCI2312_PA2_KMEANS_H
