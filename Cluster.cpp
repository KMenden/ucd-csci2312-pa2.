#include "Cluster.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Exceptions.h"
#include <unordered_map>

using namespace Clustering;
using namespace std;



namespace Clustering {


    template<typename T, int dim>
    Cluster<T, dim>::Cluster(const Cluster<T, dim> &other)
    {
        size = other.size;
        pointdimensions = other.pointdimensions;
        __centroid = other.__centroid;
        __points = other.__points;
        __id = generateid();

    }

    template<typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator=(const Cluster &other)
    {
        size = other.size;
        __points = other.__points;
        return *this;
    }

    template<typename T, int dim>
    Cluster<T, dim>::~Cluster()
    {
       __points.clear();
    }

    template<typename T, int dim>
    void Cluster<T, dim>::Move::perform()
    {
        to->add(from->remove(ptr));
        to->__centroidvalidity = false;
        from->__centroidvalidity = false;
    }

    template<typename T, int dim>
    void Cluster<T, dim>::add(const T &point) {
        if (__points.empty())
        {
           __points.push_front(point);
            size++;
            return;
        }
        else
        {
            typename std::forward_list<T>::iterator currentit = __points.begin();
            typename std::forward_list<T>::iterator previt = __points.begin();
            while(currentit != __points.end())
            {
                if(*currentit < point)
                {
                    if(previt != currentit)
                    {
                        previt++;
                    }
                    currentit++;

                }
                else
                {
                    if(*__points.begin() > point)
                    {
                        __points.push_front(point);
                        ++size;
                        return;
                    }
                    else
                    {
                        __points.insert_after(currentit, point);
                        ++size;
                        return;
                    }
                }
            }

                __points.insert_after(previt, point);
                ++size;
                return;

        }


    }

    template<typename T, int dim>
    const T& Cluster<T, dim>::remove(const T &point)
    {
//        try
//        {
//            if (__points.empty()) {
//                throw RemoveFromEmptyEx(point, "RemoveFromEmptyEx");
//            }
//        }
//        catch(RemoveFromEmptyEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with cluster remove function" << endl;
//            cerr << "Cluster #" << __id << " is already empty" << endl;
//            return point;
//        }

       typename std::forward_list<T>::iterator currentit = __points.begin();
       typename std::forward_list<T>::iterator previt = __points.begin();

        while(currentit != __points.end())
        {
            if(*currentit == point )
            {
                if(previt != currentit)
                {
                    __points.erase_after(previt);
                    --size;
                    return point;
                }
                else
                {
                  __points.pop_front();
                    --size;
                    return point;
                }

            }
            else
            {
              if(previt != currentit)
              {
                  previt++;
              }
                currentit++;
            }
        }

        return point;
    }

    template<typename T, int dim>
    std::ostream &operator<<(std::ostream &os, const Cluster<T, dim> &ctemp) {

        if (ctemp.size == 0) {
            os << "The list is empty" << std::endl;
        }
        else
        {
            typename std::forward_list<T>::const_iterator currentit = ctemp.__points.begin();

            while(currentit != ctemp.__points.end())
            {
                os << *currentit << ": " << ctemp.getid() << endl;
                currentit++;

            }
        }

        return os;
    }

    template<typename T, int dim>
    std::istream &operator>>(std::istream &is, Cluster<T, dim> &ctemp)
    {
        string line;
        while(getline(is, line))
        {
            cout << "Line: " << line << endl;

            int pointdims = 0;
            stringstream pointdim(line);
            double temp;
            stringstream linestream(line);
            string value;
            double d;
            long int countDelim;

            countDelim = count(line.begin(), line.end(), ',') + 1;

            if(countDelim == ctemp.pointdimensions)
            {
                T* p = new T(ctemp.pointdimensions);

                linestream >> *p;

                ctemp.add(*p);
            }
            else
            {
                cerr << "ERROR: Point " << line << " does not contain the number of dimensions as specified at KMeans object creation!" << endl;
                cerr << "Point " << line << " was skipped and not added to the clustering algorithm" << endl;
            }
        }

    }

    template<typename T, int dim>
    bool operator==(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs)
    {
        bool result;
        if(lhs.pointdimensions != rhs.pointdimensions)
        {
            result = false;
            return result;
        }
       typename std::forward_list<T>::const_iterator lhsit = lhs.__points.begin();
        typename std::forward_list<T>::const_iterator rhsit = rhs.__points.begin();

        while(lhsit != lhs.__points.end() && rhsit != rhs.__points.end())
        {
            if(*lhsit == *rhsit)
            {
                lhsit++;
                rhsit++;
            }
            else
            {
                result = false;
                return result;
            }
        }
        result = true;
        return result;

    }

    template<typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator+=(const Cluster<T, dim> &rhs)
    {
        if(rhs.__points.empty())
        {
            return *this;
        }

       typename std::forward_list<T>::const_iterator rhsit = rhs.__points.begin();

        while(rhsit != rhs.__points.end())
        {
            add(*rhsit);
            rhsit++;
        }

        return *this;

    }

    template<typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator-=(const Cluster<T, dim> &rhs)
    {
        if(rhs.__points.empty())
        {
            return *this;
        }

       typename std::forward_list<T>::const_iterator rhsit = rhs.__points.begin();

        while(rhsit != rhs.__points.end())
        {
            remove(*rhsit);
            rhsit++;
        }

        return *this;

    }

    template<typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator+=(const T &rhs)
    {

        add(rhs);
        return *this;
    }

    template<typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator-=(const T &rhs)
    {
        remove(rhs);
        return *this;
    }

    template<typename T,int dim>
    const Cluster<T, dim> operator+(const Cluster<T, dim> &lhs, const T &rhs)
    {
        Cluster<T, dim> result(lhs);

        result.add(rhs);

        return result;

    }

    template<typename T,int dim>
    const Cluster<T, dim> operator-(const Cluster<T, dim> &lhs, const T &rhs)
    {
        Cluster<T, dim> result (lhs);

        result.remove(rhs);

        return result;
    }

    template<typename T,int dim>
    const Cluster<T, dim> operator+(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs)
    {
        Cluster<T, dim> result(lhs);

        result += rhs;

        return result;
    }

    template<typename T,int dim>
    const Cluster<T, dim> operator-(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs)
    {
        Cluster<T, dim> result(lhs);
        result -= rhs;

        return result;
    }

    template<typename T, int dim>
    unsigned int Cluster<T, dim>::generateid()
    {
        static unsigned int tempid = 0;
        tempid++;
        return tempid;
    }

    template<typename T, int dim>
   unsigned int Cluster<T, dim>::getid()const {
        return __id;
    }

    template<typename T, int dim>
    int Cluster<T, dim>::getsize()
    {
        return size;
    }

    template<typename T, int dim>
    void Cluster<T, dim>::setcentroid(const T &point)
    {
            __centroid = point;
        return;
    }

    template<typename T, int dim>
    const T Cluster<T, dim>::getcentroid()
    {
        return __centroid;
    }

    template<typename T, int dim>
    void Cluster<T, dim>::computecentroid()
    {
//        try{
//
//            if(__points.empty())
//            {
//                throw RemoveFromEmptyEx(__centroid,"RemoveFromEmptyEx");
//            }
//
//        }
//        catch(RemoveFromEmptyEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with cluster computecentroid function" << endl;
//            cerr << "Cluster #" << __id << " is already empty" << endl;
//            return;
//        }
       typename std::forward_list<T>::iterator currentit = __points.begin();
        T p(pointdimensions);
        while(currentit != __points.end())
        {
            p += *currentit / pointdimensions;
            currentit++;
        }
        __centroid = p;
        __centroidvalidity = true;
    }

    template<typename T, int dim>
    void Cluster<T, dim>::pickPoints(int k, vector<T> &pointarray)
    {

        int index = 0;

       typename std::forward_list<T>::iterator currentit = __points.begin();

        while(currentit != __points.end() && index < k)
        {

            pointarray[index] = *currentit;
            currentit++;
            index++;
        }
    }


    template<typename T, int dim>
    double Cluster<T, dim>::intraClusterDistance()
    {
        if(pointDistances.empty()) {
           typename std::forward_list<T>::iterator firstit = __points.begin();
           typename std::forward_list<T>::iterator secondit = __points.begin();

            double distance = 0;
            double sum = 0;

            while (firstit != __points.end()) {
                while (secondit != __points.end()) {
                    distance = firstit->distanceTo(*secondit);
                    sum += distance;
                    secondit++;
                }
                secondit = __points.begin();
                firstit++;
            }
            sum /= 2;
            return sum;
        }
        else
        {
            double distance = 0;
            double sum = 0;
           typename std::forward_list<T>::iterator firstit = __points.begin();
           typename std::forward_list<T>::iterator secondit = __points.begin();

            secondit++;
            while(firstit != __points.end())
            {
                while(secondit != __points.end())
                {
                    distance = pointDistances[CantorFunction(firstit->getid(), secondit->getid())];
                    sum += distance;
                    secondit++;
                }
                firstit++;
                secondit = firstit;
                if(secondit == __points.end())
                {
                    break;
                }
                secondit++;
            }

            return sum;
        }

    }

    template<typename T, int dim>
    double interClusterDistance(Cluster<T, dim> &c1, Cluster<T, dim> &c2)
    {
        if(c1.pointDistances.empty())
        {
           typename std::forward_list<T>::iterator firstit = c1.__points.begin();
           typename std::forward_list<T>::iterator secondit = c2.__points.begin();
            double distance = 0;
            double sum = 0;

            while (firstit != c1.__points.end())
            {
                while (secondit != c2.__points.end())
                {
                    double const distance = firstit->distanceTo(*secondit);
                    sum += distance;
                    secondit++;
                }
                secondit = c2.__points.begin();
                firstit++;
            }
            return sum;
        }
        else
        {
           typename std::forward_list<T>::iterator firstit = c1.__points.begin();
           typename std::forward_list<T>::iterator secondit = c2.__points.begin();
            double distance = 0;
            double sum = 0;

            while (firstit != c1.__points.end())
            {
                while (secondit != c2.__points.end())
                {
                    distance = c1.pointDistances[c1.CantorFunction(firstit->getid(), secondit->getid())];
                    sum += distance;
                    secondit++;
                }
                firstit++;
                secondit = firstit;
                if(secondit == c1.__points.end())
                {
                    break;
                }
                secondit++;
            }
            return sum;
        }
    }

    template<typename T, int dim>
    int Cluster<T, dim>::getClusterEdges()
    {
        int edges = 0;

        edges = (size *(size - 1)) / 2;

        return edges;
    }

    template<typename T, int dim>
    double interClusterEdges(const Cluster<T, dim> &c1, const Cluster<T, dim> &c2)
    {
        int edges = 0;

        edges = c1.size * c2.size;

        return edges;
    }

    template<typename T, int dim>
    void Cluster<T, dim>::setPointDemensions(unsigned int value)
    {
        pointdimensions = value;
    }

    template<typename T, int dim>
    bool Cluster<T, dim>::contains(const T &point)
    {
       typename std::forward_list<T>::iterator currentit = __points.begin();

        while(currentit != __points.end())
        {
            if(*currentit == point)
            {
                return true;
            }
            else
            {
                currentit++;
            }
        }
        return false;
    }

    template<typename T, int dim>
    void Cluster<T, dim>::computeMap()
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

    template<typename T, int dim>
    std::unordered_map<unsigned int, double> Cluster<T, dim>::pointDistances;
}