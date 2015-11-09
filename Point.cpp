#include "Point.h"
#include <cmath>
#include <cassert>
#include <iomanip>
#include "Exceptions.h"
#include <algorithm>

using namespace std;
using namespace Clustering;


// Default constructor
// Initializes the point to (0.0, 0.0, 0.0)
Point::Point() {

}

// Constructor

Point::Point(int numofdemensions)
{

       dim = numofdemensions;

    for (int i = 0; i < dim; i++)
    {
        coords.push_back(0);
    }
}

Point::Point(int numofdemensions, double *array)
{
    dim = numofdemensions;


    for (int i = 0; i < dim; i++)
    {
        coords.push_back(array[i]);
    }

}

Point::Point(const Point &temp)
    {
        dim = temp.dim;

        vector<double>::iterator thisit = coords.begin();
        vector<double>::const_iterator tempit = temp.coords.begin();

        for (int i = 0; i < dim; i++)
        {
            coords.push_back(*tempit);
            tempit++;
        }
    }

// Destructor
//Releases the memory occupied by the coords pointer
Point::~Point()
{
  coords.clear();
}

double Point::getValue(int index) const
{
    return coords[index];

}


void Point::setValue(int index, double value)
{
    coords[index] = value;
}

 Point& Point::operator=(const Point &rhs)
 {
     if(this == &rhs)
         return *this;

     try {

         if(dim != rhs.dim)
             throw DimensionalityMismatchEx(dim, "DimensionalityMismatchEx");

         vector<double>::iterator thisit = coords.begin();
         vector<double>::const_iterator tempit = rhs.coords.begin();
         dim = rhs.dim;

         for (int i = 0; i < dim; i++) {

             *thisit = *tempit;
             thisit++;
             tempit++;
         }
     }
     catch(DimensionalityMismatchEx e)
     {
         cerr << "ERROR:Exception " << e.getName() << " detected with assignment operator = with point " << *this << "and " << rhs << endl;
         cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
     }
     return *this;
 }

namespace Clustering {

    bool operator==(const Point &lhs, const Point &rhs) {
        bool result;

//        if(lhs.__id != rhs.__id)
//        {
//            return false;
//        }

        try {
            if(lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            vector<double>::const_iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();
            for (int i = 0; i < lhs.getDims(); i++) {
                if (*thisit == *tempit )
                    result = true;
                else {
                    result = false;
                    return result;
                }
                thisit++;
                tempit++;
            }
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator == with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
        }
        return result;
    }


    bool operator!=(const Point &lhs, const Point &rhs) {
        bool result;

        try {
            if(lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            vector<double>::const_iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();
            for (int i = 0; i < lhs.getDims(); i++) {
                if (*thisit == *tempit)
                    result = false;
                else {
                    result = true;
                    return result;
                }
                thisit++;
                tempit++;
            }
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator != with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
        }
        return result;
    }

    bool operator<(const Point &lhs, const Point &rhs) {
        int index = 0;
        vector<double>::const_iterator thisit = lhs.coords.begin();
        vector<double>::const_iterator tempit = rhs.coords.begin();
        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");
            for (int i = 0; i < lhs.getDims(); i++) {
                if (*thisit == *tempit) {
                    index++;
                    thisit++;
                    tempit++;
                }
                else
                    break;
            }

            if (lhs.coords[index] < rhs.coords[index])
                return true;
            else
                return false;

        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator < with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
            return false;
        }
    }

    bool operator>(const Point &lhs, const Point &rhs) {
        int index = 0;
        vector<double>::const_iterator thisit = lhs.coords.begin();
        vector<double>::const_iterator tempit = rhs.coords.begin();
        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            for (int i = 0; i < lhs.getDims(); i++) {
                if (*thisit == *tempit) {
                    tempit++;
                    thisit++;
                    index++;
                }
                else
                    break;
            }

            if (*thisit > *tempit)
                return true;
            else
                return false;
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator > with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
            return false;
        }
    }

    bool operator<=(const Point &lhs, const Point &rhs) {
        int index = 0;
        bool same;

        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            vector<double>::const_iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();
            for (int i = 0; i < lhs.getDims(); i++) {
                if (*thisit == *tempit) {
                    index++;
                    thisit++;
                    tempit++;
                    same = true;
                }
                else
                    same = false;
                break;
            }
            if (same == true)
                return true;
            else {
                if (*thisit < *tempit)
                    return true;
                else
                    return false;
            }
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator <= with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
            return false;
        }
    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        int index = 0;
        bool same;

        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            vector<double>::const_iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();

            for (int i = 0; i < lhs.getDims(); i++) {
                if (*thisit == *tempit) {
                    thisit++;
                    tempit++;
                    index++;
                    same = true;
                }
                else
                    same = false;
                break;
            }
            if (same == true)
                return true;
            else {
                if (*thisit > *tempit)
                    return true;
                else
                    return false;
            }
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with comparison operator >= with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
            return false;
        }
    }

    Point &operator+=(Point &lhs, const Point &rhs)
    {
        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            vector<double>::iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();

            for (int i = 0; i < lhs.dim; i++) {
                *thisit += *tempit;
                thisit++;
                tempit++;
            }

        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator += with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;

        }
        return lhs;

    }


    Point &operator-=(Point &lhs, const Point &rhs)
    {
        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            vector<double>::iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();

            for (int i = 0; i < lhs.dim; i++) {
                lhs.coords[i] -= rhs.coords[i];
                thisit++;
                tempit++;
            }
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator -= with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
        }
        return lhs;

    }


    const Point operator+(const Point &lhs, const Point &rhs)
    {
        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            Point result(lhs.dim);

            vector<double>::const_iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();
            vector<double>::iterator resultit = result.coords.begin();


            for (int i = 0; i < lhs.dim; i++) {
                *resultit = *thisit + *tempit;
                thisit++;
                tempit++;
                resultit++;
            }

            return result;
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator + with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
            Point result(lhs.dim);
            return result;
        }


    }

    const Point operator-(const Point &lhs, const Point &rhs)
    {
        try {
            if (lhs.dim != rhs.dim)
                throw DimensionalityMismatchEx(lhs.dim, "DimensionalityMismatchEx");

            Point result(lhs.dim);

            vector<double>::const_iterator thisit = lhs.coords.begin();
            vector<double>::const_iterator tempit = rhs.coords.begin();
            vector<double>::iterator resultit = result.coords.begin();

            for(int i = 0; i < lhs.dim; i++)
            {
                *resultit = *thisit - *tempit;
                thisit++;
                tempit++;
                resultit++;
            }

            return result;


        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with arithmetic operator - with point " << lhs << "and " << rhs << endl;
            cerr << "Dimensionality for point " << rhs << "must be " << e.getData() << endl;
            Point result(lhs.dim);
            return result;
        }

    }

    Point &Point::operator*=(double number)
    {
        vector<double>::iterator thisit = coords.begin();

        for(int i = 0; i < dim; i++)
        {
            *thisit *= number;
            thisit++;
        }

        return *this;
    }

    Point &Point::operator/=(double number)
    {
        assert( number != 0);

        vector<double>::iterator thisit = coords.begin();

        for(int i = 0; i < dim; i++)
        {
            *thisit /= number;
            thisit++;
        }

    }

    const Point Point::operator*(double number) const
    {
        Point result(dim);

        vector<double>::const_iterator thisit = coords.begin();
        vector<double>::iterator resultit = result.coords.begin();

        for(int i = 0; i < dim; i++)
        {
            *resultit = *thisit * number;
            resultit++;
            thisit++;
        }

        return result;

    }

    const Point Point::operator/(double number) const
    {
        Point result(dim);

        vector<double>::const_iterator thisit = coords.begin();
        vector<double>::iterator resultit = result.coords.begin();
        for(int i = 0; i < dim; i++)
        {
            *resultit = *thisit / number;
            resultit++;
            thisit++;
        }

        return result;

    }

    std::ostream &operator<<(std::ostream &output, const Point &point)
    {

        vector<double>::const_iterator thisit = point.coords.begin();
        for (int i = 0; i < point.getDims(); i++) {

            output << *thisit << ", ";
            thisit++;

        }

        return output;

    }

    std::istream &operator>>(std::istream &input, Point &point)
    {

        string value;
        double d;
        int i = 0;
        int countDelim;
        string pointline;

        getline(input,pointline);

        countDelim = count(pointline.begin(), pointline.end(), ',') + 1;

        try {
            if (point.dim != countDelim)
                throw DimensionalityMismatchEx(point.dim, "DimensionalityMismatchEx");

            while (getline(input, value, point.POINT_VALUE_DELIM)) {
                d = stod(value);

                cout << "Value: " << d << endl;

                point.setValue(i++, d);
            }
        }
        catch(DimensionalityMismatchEx e)
        {
            cerr << "ERROR:Exception " << e.getName() << " detected with extraction operator using point " << point << endl;
            cerr << "Point dimensionality (" << point.dim << ") is mismatched with number of inputs (" << countDelim << ")" << endl;
        }

        return input;
    }


}

// Mutator methods
// Change the values of private member variables


// Accessors
// Return the current values of private member variables



double Point::distanceTo(Point &point1)
{
    vector<double>::const_iterator thisit = coords.begin();
    vector<double>::const_iterator pointit = point1.coords.begin();

    assert(dim == point1.dim);
    double sum = 0;
    double difference = 0;
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