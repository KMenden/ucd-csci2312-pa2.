#include "Point.h"
#include <cmath>
#include <cassert>
#include <iomanip>
#include "Exceptions.h"
#include <algorithm>
#include <sstream>

using namespace std;
using namespace Clustering;


// Default constructor
// Initializes the point to (0.0, 0.0, 0.0)
template<typename T, int dim>
Point<T, dim>::Point() {

}

// Constructor
template<typename T, int dim>
Point<T, dim>::Point(int numofdemensions)
{



    for (int i = 0; i < dim; i++)
    {
        coords.push_back(0);
    }

    __id = generateid();
}
template<typename T, int dim>
Point<T, dim>::Point(int numofdemensions, T *array)
{


    for (int i = 0; i < dim; i++)
    {
        coords.push_back(array[i]);
    }

    __id = generateid();

}

template<typename T, int dim>
Point<T, dim>::Point(const Point<T, dim> &temp)
    {


        vector<double>::iterator thisit = coords.begin();
        vector<double>::const_iterator tempit = temp.coords.begin();

        for (int i = 0; i < dim; i++)
        {
            coords.push_back(*tempit);
            tempit++;
        }

        __id = temp.getid();
    }

// Destructor
//Releases the memory occupied by the coords pointer
template<typename T, int dim>
Point<T, dim>::~Point()
{
  coords.clear();
}
template<typename T, int dim>
T Point<T, dim>::getValue(int index) const
{
    return coords[index];

}

template<typename T, int dim>
void Point<T, dim>::setValue(int index, T value)
{
    coords[index] = value;
}

template<typename T, int dim>
 Point<T, dim>& Point<T, dim>::operator=(const Point &rhs)
 {
     if(this == &rhs)
         return *this;

//     try {

//         if(dim != rhs.dim)
//             throw DimensionalityMismatchEx(dim, "DimensionalityMismatchEx");

        typename vector<T>::iterator thisit = coords.begin();
         typename vector<T>::const_iterator tempit = rhs.coords.begin();


         for (int i = 0; i < dim; i++) {

             *thisit = *tempit;
             thisit++;
             tempit++;
         }
//     }
//     catch(DimensionalityMismatchEx e)
//     {
//         cerr << "ERROR:Exception " << e.getName() << " detected with assignment operator = with point " << *this << "and " << rhs << endl;
//         cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//     }
     return *this;
 }

//namespace Clustering {
//
//
//    bool operator==(const Point &lhs, const Point &rhs) {
//        bool result;
//
//        if(lhs.__id != rhs.__id)
//        {
//            return false;
//        }
//
//        try {
//            if(lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            vector<double>::const_iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//            for (int i = 0; i < lhs.getDims(); i++) {
//                if (*thisit == *tempit )
//                    result = true;
//                else {
//                    result = false;
//                    return result;
//                }
//                thisit++;
//                tempit++;
//            }
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator == with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//        }
//        return result;
//    }
//
//
//    bool operator!=(const Point &lhs, const Point &rhs) {
//        bool result;
//
//        if(lhs.__id == rhs.__id)
//        {
//            return false;
//        }
//
//        try {
//            if(lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            vector<double>::const_iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//            for (int i = 0; i < lhs.getDims(); i++) {
//                if (*thisit == *tempit)
//                    result = false;
//                else {
//                    result = true;
//                    return result;
//                }
//                thisit++;
//                tempit++;
//            }
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator != with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//        }
//        return result;
//    }
//
//    bool operator<(const Point &lhs, const Point &rhs) {
//        int index = 0;
//        vector<double>::const_iterator thisit = lhs.coords.begin();
//        vector<double>::const_iterator tempit = rhs.coords.begin();
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//            for (int i = 0; i < lhs.getDims(); i++) {
//                if (*thisit == *tempit) {
//                    index++;
//                    thisit++;
//                    tempit++;
//                }
//                else
//                    break;
//            }
//
//            if (lhs.coords[index] < rhs.coords[index])
//                return true;
//            else
//                return false;
//
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator < with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//            return false;
//        }
//    }
//
//    bool operator>(const Point &lhs, const Point &rhs) {
//        int index = 0;
//        vector<double>::const_iterator thisit = lhs.coords.begin();
//        vector<double>::const_iterator tempit = rhs.coords.begin();
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            for (int i = 0; i < lhs.getDims(); i++) {
//                if (*thisit == *tempit) {
//                    tempit++;
//                    thisit++;
//                    index++;
//                }
//                else
//                    break;
//            }
//
//            if (*thisit > *tempit)
//                return true;
//            else
//                return false;
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator > with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//            return false;
//        }
//    }
//
//    bool operator<=(const Point &lhs, const Point &rhs) {
//        int index = 0;
//        bool same;
//
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            vector<double>::const_iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//            for (int i = 0; i < lhs.getDims(); i++) {
//                if (*thisit == *tempit) {
//                    index++;
//                    thisit++;
//                    tempit++;
//                    same = true;
//                }
//                else
//                    same = false;
//                break;
//            }
//            if (same == true)
//                return true;
//            else {
//                if (*thisit < *tempit)
//                    return true;
//                else
//                    return false;
//            }
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator <= with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//            return false;
//        }
//    }
//
//    bool operator>=(const Point &lhs, const Point &rhs) {
//        int index = 0;
//        bool same;
//
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            vector<double>::const_iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//
//            for (int i = 0; i < lhs.getDims(); i++) {
//                if (*thisit == *tempit) {
//                    thisit++;
//                    tempit++;
//                    index++;
//                    same = true;
//                }
//                else
//                    same = false;
//                break;
//            }
//            if (same == true)
//                return true;
//            else {
//                if (*thisit > *tempit)
//                    return true;
//                else
//                    return false;
//            }
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator >= with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//            return false;
//        }
//    }
//
//    Point &operator+=(Point &lhs, const Point &rhs)
//    {
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            vector<double>::iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//
//            for (int i = 0; i < lhs.dim; i++) {
//                *thisit += *tempit;
//                thisit++;
//                tempit++;
//            }
//
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator += with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//
//        }
//        return lhs;
//
//    }
//
//
//    Point &operator-=(Point &lhs, const Point &rhs)
//    {
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            vector<double>::iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//
//            for (int i = 0; i < lhs.dim; i++) {
//                lhs.coords[i] -= rhs.coords[i];
//                thisit++;
//                tempit++;
//            }
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator -= with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//        }
//        return lhs;
//
//    }
//
//
//    const Point operator+(const Point &lhs, const Point &rhs)
//    {
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            Point result(lhs.dim);
//
//            vector<double>::const_iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//            vector<double>::iterator resultit = result.coords.begin();
//
//
//            for (int i = 0; i < lhs.dim; i++) {
//                *resultit = *thisit + *tempit;
//                thisit++;
//                tempit++;
//                resultit++;
//            }
//
//            return result;
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator + with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//            Point result(lhs.dim);
//            return result;
//        }
//
//
//    }
//
//    const Point operator-(const Point &lhs, const Point &rhs)
//    {
//        try {
//            if (lhs.dim != rhs.dim)
//                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
//
//            Point result(lhs.dim);
//
//            vector<double>::const_iterator thisit = lhs.coords.begin();
//            vector<double>::const_iterator tempit = rhs.coords.begin();
//            vector<double>::iterator resultit = result.coords.begin();
//
//            for(int i = 0; i < lhs.dim; i++)
//            {
//                *resultit = *thisit - *tempit;
//                thisit++;
//                tempit++;
//                resultit++;
//            }
//
//            return result;
//
//
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator - with point " << lhs << "and " << rhs << endl;
//            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
//            Point result(lhs.dim);
//            return result;
//        }
//
//    }
//
    template<typename T, int dim>
    Point<T, dim> &Point<T, dim>::operator*=(T number)
    {
      typename vector<T>::iterator thisit = coords.begin();

        for(int i = 0; i < dim; i++)
        {
            *thisit *= number;
            thisit++;
        }

        return *this;
    }

    template<typename T, int dim>
    Point<T, dim> &Point<T, dim>::operator/=(T number)
    {
        assert( number != 0);

       typename vector<T>::iterator thisit = coords.begin();

        for(int i = 0; i < dim; i++)
        {
            *thisit /= number;
            thisit++;
        }

    }

    template<typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator*(T number) const
    {
        Point<T, dim> result(dim);

       typename vector<T>::const_iterator thisit = coords.begin();
       typename vector<T>::iterator resultit = result.coords.begin();

        for(int i = 0; i < dim; i++)
        {
            *resultit = *thisit * number;
            resultit++;
            thisit++;
        }

        return result;

    }

    template<typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator/(T number) const
    {
        Point<T, dim> result(dim);

       typename vector<T>::const_iterator thisit = coords.begin();
       typename vector<T>::iterator resultit = result.coords.begin();
        for(int i = 0; i < dim; i++)
        {
            *resultit = *thisit / number;
            resultit++;
            thisit++;
        }

        return result;

    }

//    template<typename T, int dim>
//    std::ostream &operator<<(std::ostream &output, const Point<T, dim> &point)
//    {
//
//        vector<double>::const_iterator thisit = point.coords.begin();
//        for (int i = 0; i < point.getDims(); i++) {
//
//            output << *thisit << ", ";
//            thisit++;
//
//        }
//
//        return output;
//
//    }
//
//    template<typename T, int dim>
//    std::istream &operator>>(std::istream &input, Point<T, dim> &point)
//    {
//
//        string value;
//        T d;
//        int i = 0;
//        long int countDelim;
//        string pointline;
//
//
//        getline(input, pointline);
//
//        stringstream valueline(pointline);
//
//
//        countDelim = count(pointline.begin(), pointline.end(), ',') + 1;
//
//        try
//        {
//            if (point.dim != countDelim)
//                throw DimensionalityMismatchEx(point.dim, "DimensionalityMismatchEx");
//
//            while (getline(valueline, value, ','))
//            {
//                d = stod(value);
//
//                cout << "Value: " << d << endl;
//
//                point.setValue(i++, d);
//            }
//        }
//        catch(DimensionalityMismatchEx e)
//        {
//            cerr << "ERROR:Exception " << e.getName() << " detected with extraction operator using point " << point << endl;
//            cerr << "Point dimensionality (" << point.dim << ") is mismatched with number of inputs (" << countDelim << ")" << endl;
//        }
//
//        return input;
//    }
//
//
//}
//
//// Mutator methods
//// Change the values of private member variables
//
//
//// Accessors
//// Return the current values of private member variables
//
//
template<typename T, int dim>
T Point<T, dim>::distanceTo(Point &point1) const
{
    typename vector<T>::const_iterator thisit = coords.begin();
    typename vector<T>::const_iterator pointit = point1.coords.begin();


    T sum = 0;
    T difference = 0;
    for(int i = 0; i < dim; i++)
    {
        difference = (pow(*thisit - *pointit, 2));
        sum += difference;
        thisit++;
        pointit++;
    }

    sqrt(sum);

  return sum;
}

template<typename T, int dim>
unsigned int Point<T, dim>::generateid()
{
    static unsigned int tempidpoint = 0;
    tempidpoint++;
    return tempidpoint;
}

template<typename T, int dim>
void Point<T, dim>::rewindIdGen()
{
    static unsigned int tempidpoint = 0;
    tempidpoint--;
    return;
}

template<typename T, int dim>
unsigned int Point<T, dim>::getid()const {
    return __id;
}
