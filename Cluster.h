#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"
#include <vector>
#include <forward_list>
#include <unordered_map>
#include <algorithm>

namespace Clustering {

    template<typename T, int dim>
    class Cluster;

    template<typename T, int dim>
    double interClusterEdges(const Cluster<T, dim> &c1, const Cluster<T, dim> &c2);

    template<typename T, int dim>
    double interClusterDistance(Cluster<T, dim> &c1, Cluster<T, dim> &c2);

    template<typename T, int dim>
     std::ostream &operator<<(std::ostream &, const Cluster<T, dim> &);

    template<typename T, int dim>
    std::istream &operator>>(std::istream &, Cluster<T, dim> &);

    template<typename T,int dim>
    const Cluster<T, dim> operator+(const Cluster<T, dim> &lhs, const Cluster<T,dim> &rhs);\

    template<typename T, int dim>
    const Cluster<T, dim> operator-(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs);

    template<typename T,int dim>
    const Cluster<T, dim> operator+(const Cluster<T, dim> &lhs, const T &rhs);

    template<typename T,int dim>
    const Cluster<T, dim> operator-(const Cluster<T, dim> &lhs, const T &rhs);

    template<typename T, int dim>
    bool operator==(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs);





    template<typename T, int dim>
    class Cluster {
        int size;
        std::forward_list<T> __points;
        bool __release_points;
        unsigned int __id;
        static unsigned int __idGenerator;
        T __centroid;
        bool __centroidvalidity;
        unsigned int pointdimensions;
        int numberOfSuccesses;
        int numberOfFailures;

        static std::unordered_map<unsigned int, double> pointDistances;


    public:
        Cluster() : size(0), __id(generateid()), __centroid(pointdimensions = 5), __centroidvalidity(false), numberOfSuccesses(0), numberOfFailures(0) {};
        Cluster(unsigned int dimensions) : size(0), __id(generateid()), pointdimensions(dimensions), __centroid(dimensions), __centroidvalidity(false), numberOfSuccesses(0), numberOfFailures(0) {};
         //The big three: cpy ctor, overloaded operator=, dtor

        Cluster(const Cluster &);
        Cluster<T, dim> &operator=(const Cluster<T, dim> &);
        ~Cluster();
//
//        class Move{
//            Point ptr;
//            Cluster *to, *from;
//        public:
//            void perform();
//            Move(const Point &point, Cluster *cfrom, Cluster *cto) : ptr(point), to(cto), from(cfrom)  {};
//        };
//
        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const T &);
        const T &remove(const T &);
//
//        // Overloaded operators
//
//        // IO
        friend std::ostream &operator<< <T>(std::ostream &, const Cluster &);
        friend std::istream &operator>> <T>(std::istream &, Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        friend bool operator==<T>(const Cluster &lhs, const Cluster &rhs);

        // - Members
        Cluster<T, dim> &operator+=(const Cluster &rhs); // union
        Cluster<T, dim> &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster<T, dim> &operator+=(const T &rhs); // add point
        Cluster<T, dim> &operator-=(const T &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // - Friends
        friend const Cluster operator+<T>(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-<T>(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+<T>(const Cluster &lhs, const T &rhs);
        friend const Cluster operator-<T>(const Cluster &lhs, const T &rhs);

        static unsigned int generateid();
        unsigned int getid()const;

        int getsize();

        void setcentroid(const T &);
//
        const T getcentroid();

        void computecentroid();
//
//        void pickPoints(int, std::vector<Point>&);
//
        double intraClusterDistance();

        friend double interClusterDistance<T>(Cluster &c1, Cluster &c2);

        int getClusterEdges();

        friend double interClusterEdges<T>(const Cluster &c1, const Cluster &c2);

        void setPointDemensions(unsigned int);

        bool checkValidCentroid() {return __centroidvalidity;}

        bool contains(const T &);

        int numberImported() {return numberOfSuccesses;}

        int numberFailed(){return numberOfFailures;}

       typename std::forward_list<T>::iterator getItBegin() {return __points.begin();}

       typename std::forward_list<T>::iterator getItEnd() { return __points.end(); }

        unsigned int CantorFunction(unsigned int id1, unsigned int id2)
        {
            if(id1 > id2)
            {
                std::swap(id1, id2);
            }

            return std::hash<std::size_t>()((id1 + id2) * (id1 + id2 + 1) / 2 + id2);
        }


        void computeMap()
        {

           typename std::forward_list<T>::iterator point1 = __points.begin();
           typename std::forward_list<T>::iterator point2 = __points.begin();
            point2++;

            while(point1 != __points.end())
            {
                while(point2 != __points.end())
                {
                    pointDistances[CantorFunction(point1->getid(), point2->getid())] = point1->distanceTo(*point2);
                    point2++;
                }
                point1++;
                if(point1 == __points.end())
                {
                    break;
                }
                point2 = point1;
                point2++;
            }

        }

    };


}


#include "Cluster.cpp"
#endif //CLUSTERING_CLUSTER_H

