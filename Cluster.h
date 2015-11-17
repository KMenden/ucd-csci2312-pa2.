//#ifndef CLUSTERING_CLUSTER_H
//#define CLUSTERING_CLUSTER_H
//
//#include "Point.h"
//#include <vector>
//#include <forward_list>
//#include <unordered_map>
//#include <algorithm>
//
//namespace Clustering {
//
//     typedef Point *PointPtr;
//    typedef struct LNode *LNodePtr;
//
////    struct LNode;
////    typedef LNode *LNodePtr;
//
//    struct LNode {
//        PointPtr p;
//        LNodePtr next;
//    };
//
//
//
//    class Cluster {
//        int size;
//        LNodePtr points;
//        std::forward_list<Point> __points;
//        bool __release_points;
//        unsigned int __id;
//        static unsigned int __idGenerator;
//        Point __centroid;
//        bool __centroidvalidity;
//        unsigned int pointdimensions;
//        int numberOfSuccesses;
//        int numberOfFailures;
//
//        static std::unordered_map<unsigned int, double> pointDistances;
//
//
//    public:
//        Cluster() : size(0), points(nullptr), __id(generateid()), __centroid(pointdimensions = 5), __centroidvalidity(false), numberOfSuccesses(0), numberOfFailures(0) {};
//        Cluster(unsigned int dimensions) : size(0), points(nullptr), __id(generateid()), pointdimensions(dimensions), __centroid(dimensions), __centroidvalidity(false), numberOfSuccesses(0), numberOfFailures(0) {};
//        // The big three: cpy ctor, overloaded operator=, dtor
//        Cluster(const Cluster &);
//        Cluster &operator=(const Cluster &);
//        ~Cluster();
//
//        class Move{
//            Point ptr;
//            Cluster *to, *from;
//        public:
//            void perform();
//            Move(const Point &point, Cluster *cfrom, Cluster *cto) : ptr(point), to(cto), from(cfrom)  {};
//        };
//
//        // Set functions: They allow calling c1.add(c2.remove(p));
//        void add(const Point &);
//        const Point &remove(const Point &);
//
//        // Overloaded operators
//
//        // IO
//        friend std::ostream &operator<<(std::ostream &, const Cluster &);
//        friend std::istream &operator>>(std::istream &, Cluster &);
//
//        // Set-preserving operators (do not duplicate points in the space)
//        // - Friends
//        friend bool operator==(const Cluster &lhs, const Cluster &rhs);
//
//        // - Members
//        Cluster &operator+=(const Cluster &rhs); // union
//        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference
//
//        Cluster &operator+=(const Point &rhs); // add point
//        Cluster &operator-=(const Point &rhs); // remove point
//
//        // Set-destructive operators (duplicate points in the space)
//        // - Friends
//        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
//        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);
//
//        friend const Cluster operator+(const Cluster &lhs, const Point &rhs);
//        friend const Cluster operator-(const Cluster &lhs, const Point &rhs);
//
//        static unsigned int generateid();
//        unsigned int getid()const;
//
//        int getsize();
//
//        void setcentroid(const Point &);
//
//        const Point getcentroid();
//
//        void computecentroid();
//
//        void pickPoints(int, std::vector<Point>&);
//
//        double intraClusterDistance();
//
//        friend double interClusterDistance(Cluster &c1, Cluster &c2);
//
//        int getClusterEdges();
//
//        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);
//
//        void setPointDemensions(unsigned int);
//
//        LNodePtr getheadpointer() { return points; }
//
//        bool checkValidCentroid() {return __centroidvalidity;}
//
//        bool contains(const Point &);
//
//        int numberImported() {return numberOfSuccesses;}
//
//        int numberFailed(){return numberOfFailures;}
//
//        std::forward_list<Point>::iterator getItBegin() {return __points.begin();}
//
//        std::forward_list<Point>::iterator getItEnd() { return __points.end(); }
//
//        unsigned int CantorFunction(unsigned int id1, unsigned int id2)
//        {
//            if(id1 > id2)
//            {
//                std::swap(id1, id2);
//            }
//
//            return std::hash<std::size_t>()((id1 + id2) * (id1 + id2 + 1) / 2 + id2);
//        }
//
//
//        void computeMap()
//        {
//
//            std::forward_list<Point>::iterator point1 = __points.begin();
//            std::forward_list<Point>::iterator point2 = __points.begin();
//            point2++;
//
//            while(point1 != __points.end())
//            {
//                while(point2 != __points.end())
//                {
//                    pointDistances[CantorFunction(point1->getid(), point2->getid())] = point1->distanceTo(*point2);
//                    point2++;
//                }
//                point1++;
//                if(point1 == __points.end())
//                {
//                    break;
//                }
//                point2 = point1;
//                point2++;
//            }
//
//        }
//
//    };
//
//
//
//}
//#endif //CLUSTERING_CLUSTER_H
//
