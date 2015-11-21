#include "KMeans.h"
#include "Point.h"
#include "Cluster.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace Clustering;
using namespace std;


template<int k, int dim>
double KMeans<k ,dim >::mindistance(Point<double, dim> &point, Point<double, dim> centroid)
{

    double distance = point.distanceTo(centroid);
    return distance;
}


template<int k, int dim>
void KMeans<k, dim>::run()
{
    vector<Cluster<Point<double, dim>, dim>> clusterarray;
    clusterarray.reserve(k);
    for (int i = 0; i < k; i++)
    {
        clusterarray.emplace_back(pointdemensions);
    }
    int score = 0;
    double scorediff = SCORE_DIFF_THRESHOLD + 1;
    Cluster<Point<double, dim>, dim> point_space(dim);
    ifstream csv(filename);
    csv >> point_space;
    csv.close();
    clusterarray[0] = point_space;

    point_space.computeMap();

    vector<Point<double, dim>> pointarray;
    pointarray.reserve(k);
    for (int i = 0; i < k; i++)
    {
        pointarray.emplace_back(pointdemensions);
    }
    point_space.pickPoints(k, pointarray);

    for (int i = 0; i < k; i++)
    {
        clusterarray[i].setcentroid(pointarray[i]);
    }


    while (scorediff > SCORE_DIFF_THRESHOLD)
    {
        for (int i = 0; i < k; i++)
        {

           typename std::forward_list<Point<double, dim>>::iterator currentit = clusterarray[i].getItBegin();
            double minimaldistance = 99999;
            while (currentit != clusterarray[i].getItEnd())
            {
                bool checkswap = false;
                bool swap = false;
                int clusterindex = -1;
                for (int i2 = 0; i2 < k; i2++)
                {

                    double distance = mindistance(*currentit, clusterarray[i2].getcentroid());
                    if (distance < minimaldistance)
                    {
                        minimaldistance = distance;
                        clusterindex = i2;
                        checkswap = true;
                    }

                }
                if (clusterindex != clusterarray[i].getid() - 1 && checkswap)
                {
                  typename Cluster<Point<double, 5>, dim>::Move moveclusters(*currentit, &clusterarray[i], &clusterarray[clusterindex]);
                    moveclusters.perform();
                    currentit = clusterarray[i].getItBegin();
                    swap = true;
                }

                if (swap == false)
                {
                    currentit++;
                }
                minimaldistance = 99999;
            }
        }

        for (int index = 0; index < k; index++)
        {
            if (!clusterarray[index].checkValidCentroid())
            {
                clusterarray[index].computecentroid();
            }
        }

        int betaCV = computeClusteringScore(clusterarray);

        scorediff = abs(score - betaCV);
        score = betaCV;
    }

    ofstream output("results.txt");
    for (int i = 0; i < k; i++)
    {
        output << clusterarray[i];
    }
    for (int i = 0; i < k; i++)
    {
        cout << clusterarray[i];
    }
    output.close();
}

template<int k, int dim>
double KMeans<k, dim>::computeClusteringScore(vector<Cluster<Point<double, 5>, dim>> &clusterarray)
{
        double dIn = 0;

        for (int index = 0; index < k; index++)
        {
            double sum = clusterarray[index].intraClusterDistance();
            dIn += sum;
        }



        double dOut = 0;

        int i = 0;
        int i2 = 1;

        while (i < k)
        {
            while (i2 < k)
            {
                double sum = interClusterDistance(clusterarray[i], clusterarray[i2]);
                dOut += sum;
                i2++;
            }
            i++;
            i2 = i + 1;
        }
        double pIn = 0;
        for (int index = 0; index < k; index++)
        {
            double sum = clusterarray[index].getClusterEdges();
            pIn += sum;
        }
        double pOut = 0;

        int cindex = 0;
        int cindex2 = 0;

        while (cindex < k)
        {
            while (cindex2 < k)
            {
                double sum = interClusterEdges(clusterarray[cindex], clusterarray[cindex2]);
                pOut += sum;
                cindex2++;
            }
            cindex++;
            cindex2 = i + 1;
        }
        int computedscore = (dIn / pIn) / (dOut / pOut);

        return computedscore;
}

template<int k ,int dim>
const int KMeans<k, dim>::SCORE_DIFF_THRESHOLD = 20;
