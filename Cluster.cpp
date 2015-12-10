#include "Cluster.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace Clustering;
using namespace std;

namespace Clustering {

    Cluster::Cluster(const Cluster &other)
    {
        if(other.points == nullptr)
        {
            return;
        }
        size = other.size;
        points = new LNode;
        LNodePtr current = points;
        LNodePtr othercurrent = other.points;

        for( ; othercurrent != nullptr; current = current->next)
        {
            current->p = othercurrent->p;
            othercurrent = othercurrent->next;
            if(othercurrent != nullptr)
            {
                current->next = new LNode;
            }
            else
            {
                current->next = nullptr;
                return;
            }
        }
        __id = 1;
    }

    Cluster& Cluster::operator=(const Cluster &other)
    {
        if(points == nullptr)
        {
            if(other.points == nullptr)
            {
                return *this;
            }
            size = other.size;
            points = new LNode;
            LNodePtr current = points;
            LNodePtr othercurrent = other.points;

            for( ; othercurrent != nullptr; current = current->next)
            {
                current->p = othercurrent->p;
                othercurrent = othercurrent->next;
                if(othercurrent != nullptr)
                {
                    current->next = new LNode;
                }
                else
                {
                    current->next = nullptr;
                    return *this;
                }
            }
        }
        else
        {
          LNodePtr current = points;
            LNodePtr prev = points;
            for( ; current != nullptr; current = current->next)
            {
                if(current->next == nullptr)
                {
                    if(current == prev)
                    {
                        delete points;
                        size--;
                        points = nullptr;
                        current = points;
                        break;
                    }
                    else
                    {
                        delete current;
                        prev->next = nullptr;
                        size--;
                        prev = points;
                        current = points;
                    }
                }
                else
                {
                    if(current != prev)
                    {
                        prev = prev->next;
                    }
                }

            }
            delete prev;
            points = nullptr;
            size--;
            if(points == nullptr)
            {
                if (other.points == nullptr)
                {
                    return *this;
                }
                size = other.size;
                points = new LNode;
                LNodePtr current = points;
                LNodePtr othercurrent = other.points;

                for (; othercurrent != nullptr; current = current->next)
                {
                    current->p = othercurrent->p;
                    othercurrent = othercurrent->next;
                    if (othercurrent != nullptr)
                    {
                        current->next = new LNode;
                    }
                    else
                    {
                        current->next = nullptr;
                        return *this;
                    }
                }
            }
        }
    }

    Cluster::~Cluster()
    {
        for(int i = 0; i < size; i++)
        {
            if(points == nullptr)
            {
                return;
            }
            else
            {
                LNodePtr cursor2 = points;
                LNodePtr temp = points;
                for(int i2 = 0; i2 < size; i++)
                {
                    if(cursor2->next == nullptr)
                    {

                        delete cursor2;
                        --size;
                        cursor2 = points;
                        for(int i3 = 0; i3 < size - 1; i3++)
                        {
                            cursor2 = cursor2->next;
                        }
                        cursor2->next = nullptr;

                    }
                    else
                    {
                        cursor2 = cursor2 -> next;
                    }
                }
            }
        }
    }


    Cluster::Move::Move(const PointPtr &point, Cluster *cfrom, Cluster *cto)
    {
        ptr = point;
        from = cfrom;
        to = cto;
    }


    void Cluster::Move::perform()
    {
        to->add(from->remove(ptr));
    }

    void Cluster::add(const PointPtr &point) {
        if (points == nullptr)
        {
            points = new LNode;
            points->p = point;
            points->next = nullptr;
            size++;
            return;
        }

        LNodePtr current = points;
        LNodePtr prev = points;
        for( ; current != nullptr; current = current->next)
        {
            if((*current->p) > *point)
            {
                if(current == prev)
                {
                    points = new LNode;
                    points->p = point;
                    points->next = current;
                    size++;
                    return;
                }
                else
                {
                    prev->next = new LNode;
                    prev->next->p = point;
                    prev->next->next = current;
                    size++;
                    return;
                }
            }
            else
            {
                if(current != prev)
                {
                    prev = prev->next;
                }
            }
        }
        if(current == nullptr)
        {
            prev->next = new LNode;
            prev->next->p = point;
            prev->next->next = nullptr;
            size++;
            return;
        }

    }

    const PointPtr& Cluster::remove(const PointPtr &point)
    {
        if(points == nullptr)
        {
            return point;
        }

        LNodePtr current = points;
        LNodePtr prev = points;
        for( ; current != nullptr; current = current->next)
        {
            if(current->p == point)
            {
                if(current == prev)
                {
                    points = prev->next;
                    size--;
                    delete current;
                    return point;
                }
                else
                {
                    prev->next = current->next;
                    delete current;
                    size--;
                    return point;
                }
            }
            else
            {
                if(current != prev)
                {
                    prev = prev->next;
                }
            }
        }
    }

    std::ostream &operator<<(std::ostream &os, const Cluster &ctemp) {

        if (ctemp.size == 0) {
            os << "The list is empty" << std::endl;
        }
        else {
            os << *(ctemp.points->p) << std::endl;
            if (ctemp.points->next == nullptr)
            {
                return os;
            }
            else
            {
                LNodePtr cursor;
                cursor = ctemp.points;
                do
                {
                    os << *(cursor->next->p) << std::endl;
                    cursor = cursor->next;

                }while(cursor->next != nullptr);
                return os;
            }
        }
    }

    std::istream &operator>>(std::istream &is, Cluster &ctemp)
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

//            while(getline(pointdim, temp, ','))
//            {
//                pointdims++;
//            }
//            pointdims++;

            PointPtr p = new Point(5);

            linestream >> *p;

            ctemp.add(p);
        }

    }

    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        bool result;
        LNodePtr lhcursor = lhs.points;
        LNodePtr rhcursor = rhs.points;

        if(lhcursor == nullptr && rhcursor == nullptr)
        {
            return true;
        }
        else if(lhcursor == nullptr || rhcursor == nullptr)
        {
            return false;
        }

        if(lhcursor->p == rhcursor->p)
        {
            lhcursor = lhcursor->next;
            rhcursor = rhcursor->next;
            for(int i = 1; i < lhs.size; i++)
            {
                if(lhcursor->p == rhcursor->p)
                {
                    if(lhcursor->next == nullptr)
                    {
                        result = true;
                        return result;
                    }
                    lhcursor = lhcursor->next;
                    rhcursor = rhcursor->next;
                }
            }
        }
        else
        {
            result = false;
            return result;
        }

        return result;
    }

    Cluster& Cluster::operator+=(const Cluster &rhs)
    {
        if(rhs.points == nullptr)
        {
            return *this;
        }

        LNodePtr current = points;
        LNodePtr rhscurrent = rhs.points;

        for( ; rhscurrent != nullptr; rhscurrent = rhscurrent->next)
        {
            bool result = false;
            for( ; current !=nullptr; current = current->next)
            {

                if(current == nullptr)
                {
                    break;
                }
                if(current->p == rhscurrent->p)
                {
                    result = true;
                    break;
                }

            }
            if(result == false)
            {
                add(rhscurrent->p);
            }
            current = points;
        }

        return *this;
    }

    Cluster& Cluster::operator-=(const Cluster &rhs)
    {
        if(rhs.points == nullptr)
        {
            return *this;
        }

        LNodePtr current = points;
        LNodePtr rhscurrent = rhs.points;

        for( ; rhscurrent != nullptr; rhscurrent = rhscurrent->next)
        {

            for( ; current !=nullptr; current = current->next)
            {

                if(current == nullptr)
                {
                    break;
                }
                if(current->p == rhscurrent->p)
                {
                    remove(rhscurrent->p);
                    break;
                }

            }
            current = points;
        }

        return *this;
    }


    Cluster& Cluster::operator+=(const Point &rhs)
    {

        PointPtr temp = new Point(rhs);
        add(temp);

        return *this;
    }

    Cluster& Cluster::operator-=(const Point &rhs)
    {
        if(points == nullptr)
        {
            return *this;
        }

        LNodePtr current = points;
        LNodePtr prev = points;
        for( ; current != nullptr; current = current->next)
        {
            if(current->p == &rhs)
            {
                if(current == prev)
                {
                    points = prev->next;
                    size--;
                    delete current;
                    return *this;
                }
                else
                {
                    prev->next = current->next;
                    delete current;
                    size--;
                    return *this;
                }
            }
            else
            {
                if(current != prev)
                {
                    prev = prev->next;
                }
            }
        }
    }

    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster result(lhs);

        result.add(rhs);

        return result;

    }
    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster result(lhs);

        result.remove(rhs);

        return result;
    }


    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster result(lhs);

        result += rhs;

        return result;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster result(lhs);
        result -= rhs;

        return result;
    }

   unsigned int Cluster::getid()const {
        return __id;
    }

    int Cluster::getSize()
    {
        return size;
    }


    void Cluster::pickPoints(int k, Point pointarray[])
    {
        LNodePtr current = points;
        int index = 0;

        while(current != nullptr)
        {
            pointarray[index] = *(current->p);
            current = current->next;
            index++;
        }
    }

}