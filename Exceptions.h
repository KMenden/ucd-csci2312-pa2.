#ifndef KELLEN_CSCI2312_PA2_EXCEPTIONS_H
#define KELLEN_CSCI2312_PA2_EXCEPTIONS_H
#include <string>
#include "Cluster.h"

namespace Clustering {

    class DimensionalityMismatchEx
    {
        std::string exname;
        int exdata;
        public:
            DimensionalityMismatchEx(int data,std::string name) : exdata(data), exname(name) {};
            std::string getName();
            int getData();
    };


    class OutOfBoundsEx{

    public:
        OutOfBoundsEx(int data, std::string name) : exdata(data), exname(name) {};
        std::string exname;
        int exdata;

        std::string getName();
        int getData();
    };

    class RemoveFromEmptyEx{

    public:
        RemoveFromEmptyEx(PointPtr data, std::string name) : exdata(data), exname(name) {};
        std::string exname;
        PointPtr exdata;

        std::string getName();
        PointPtr getData();
    };

}


#endif //KELLEN_CSCI2312_PA2_EXCEPTIONS_H
