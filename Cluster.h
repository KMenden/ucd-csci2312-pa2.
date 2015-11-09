#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"
#include <vector>
#include <forward_list>

namespace Clustering {

    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

//    struct LNode;
//    typedef LNode *LNodePtr;

    struct LNode {
        PointPtr p;
        LNodePtr next;
    };



    class Cluster {
        int size;
        LNodePtr points;
        std::forward_list<Point> __points;
        bool __release_points;
        unsigned int __id;
        static unsigned int __idGenerator;
        Point __centroid;
        bool __centroidvalidity;
        unsigned int pointdimensions;

    public:
        Cluster() : size(0), points(nullptr), __id(generateid()), __centroid(pointdimensions = 5), __centroidvalidity(false) {};
        Cluster(unsigned int dimensions) : size(0), points(nullptr), __id(generateid()), pointdimensions(dimensions), __centroid(dimensions), __centroidvalidity(false) {};
        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        class Move{
            Point ptr;
            Cluster *to, *from;
        public:
            void perform();
            Move(const Point &point, Cluster *cfrom, Cluster *cto) : ptr(point), to(cto), from(cfrom)  {};
        };

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const Point &);
        const Point &remove(const Point &);

        // Overloaded operators

        // IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        // - Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // - Friends
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const Point &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Point &rhs);

        static unsigned int generateid();
        unsigned int getid()const;

        int getsize();

        void setcentroid(const Point &);

        const Point getcentroid();

        void computecentroid();

        void pickPoints(int, std::vector<Point>&);

        double intraClusterDistance() const;

        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);

        int getClusterEdges();

        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);

        void setPointDemensions(unsigned int);

        LNodePtr getheadpointer() { return points; }

        bool checkValidCentroid() {return __centroidvalidity;}

        bool contains(const Point &);

    };



}
#endif //CLUSTERING_CLUSTER_H

