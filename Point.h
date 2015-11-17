// An n-dimensional point class!
// Coordinates are double-precision floating point.

#ifndef __point_h
#define __point_h
#include <iostream>
#include <vector>



namespace Clustering {
    template<typename T, int dim>
    class Point {
        std::vector<T> coords;
        static constexpr char POINT_VALUE_DELIM = ',';
        unsigned int __id;

    public:
        // Constructors
        Point();                      // default constructor
        Point(int);    // constructor with a given number of dimensions
        Point(int, T *);
        Point(const Point<T, dim> &);

        // Destructor
        ~Point();

        // Overloaded assignment, comparison, and arithmetic operators
        Point<T, dim> &operator=(const Point &rhs);

//        friend bool operator==(const Point &, const Point &);
//
//        friend bool operator!=(const Point &, const Point &);
//
//        friend bool operator<(const Point &, const Point &);
//
//        friend bool operator>(const Point &, const Point &);
//
//        friend bool operator<=(const Point &, const Point &);
//
//        friend bool operator>=(const Point &, const Point &);
//
//        friend Point &operator+=(Point &, const Point &);
//
//        friend Point &operator-=(Point &, const Point &);
//
//        friend const Point operator+(const Point &, const Point &);
//
//        friend const Point operator-(const Point &, const Point &);
//
        T &operator[](int index) { return coords[index]; }
//
//        friend std::ostream &operator<<(std::ostream &output, const Point &point);
//
//        friend std::istream &operator>>(std::istream &, Point &);
//
//
//        //Member Variable overloaded arithemtic operators
        Point &operator*=(T);

        Point &operator/=(T);

        const Point operator*(T) const;

        const Point operator/(T) const;

        // Mutator methods
        T getValue(int) const;
        void setValue(int, T);

        // Accessor methods
        int getDims() const { return dim; }

        T distanceTo(Point &point1) const;

        static unsigned int generateid();

        void static rewindIdGen();

        unsigned int getid()const;





    };

}

#include "Point.cpp"


#endif // __point_h