#include "Cluster.h"


using namespace Clustering;

namespace Clustering {

    Cluster::Cluster(const Cluster &other)
    {
        size = other.size;
        points = new LNode;
        points->p = other.points->p;
        points->next = nullptr;
        LNodePtr cursor = points;
        LNodePtr othercursor = other.points;
        for(int i = 1; i < size; i++)
        {
            cursor->next = othercursor->next;
            cursor = cursor->next;
            othercursor = othercursor->next;
        }
    }

    Cluster& Cluster::operator=(const Cluster &other)
    {
        size = other.size;
        points = other.points;
        return *this;
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

    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        bool result;
        LNodePtr lhcursor = lhs.points;
        LNodePtr rhcursor = rhs.points;

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

    }


    Cluster& Cluster::operator+=(const Point &rhs)
    {

        PointPtr temp = new Point(rhs);
        if (points == nullptr)
        {
            points = new LNode;
            *(points->p) = rhs;
            points->next = nullptr;
            size++;
        }
        else
        {
            LNodePtr cursor;
            cursor = points;
            for(int i = 1; i < size; i++)
            {
                cursor = cursor->next;
            }
            cursor->next = new LNode;
            cursor->next->next = nullptr;
            cursor->next->p = temp;
            size++;
        }

        return *this;
    }

    Cluster& Cluster::operator-=(const Point &rhs)
    {
        if(points->p == &rhs)
        {
            if (points->next == nullptr)
            {
                delete points;
                --size;
                return *this;
            }
            else
            {
                LNodePtr tempoint;
                tempoint = points->next;
                delete points;
                points = tempoint;
                --size;
                return *this;
            }
        }
        LNodePtr cursor;
        cursor = points;
        int index;
        for(int i = 1; i < size; i++)
        {
            cursor = cursor->next;
            if(cursor->p == &rhs)
            {
                LNodePtr tempoint;
                tempoint = cursor->next;
                delete cursor;
                --size;
                index = i;
                cursor = points;
                for(int i = 1; i < index; i++)
                {
                    cursor = cursor->next;
                }
                cursor->next = tempoint;
                return *this;

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

        result -= *rhs;

        return result;
    }


    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {

        Cluster result(lhs);
        LNodePtr lhcursor;
        LNodePtr rhcursor;

        lhcursor = result.points;
        rhcursor = rhs.points;

        if(lhcursor == nullptr)
        {
            lhcursor = new LNode;
            lhcursor->p = rhcursor->p;
            lhcursor->next = nullptr;
            result.size++;
            rhcursor = rhcursor->next;
        }


        for(int i = 0; i < rhs.size; i++)
        {
            for(int i = 0; i < result.size; i++)
            {
                if(lhcursor->next == nullptr && rhcursor != nullptr)
                {
                    lhcursor->next = new LNode;
                    lhcursor->next->p = rhcursor->p;
                    lhcursor->next->next = nullptr;
                    result.size++;
                    break;
                }
                else
                {
                    lhcursor = lhcursor->next;
                }
            }
            if(rhcursor == nullptr)
            {
                return result;
            }
            else
            {
                rhcursor = rhcursor->next;
            }
        }
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster result(lhs);
        LNodePtr lhcursor;
        LNodePtr rhcursor;

        lhcursor = result.points;
        rhcursor = rhs.points;

        for(int i = 0; i < rhs.size; i++)
        {
            if(lhcursor->p == rhcursor->p)
            {
                if (lhcursor->next == nullptr)
                {
                    delete lhcursor;
                    --result.size;
                    lhcursor = result.points;
                }
                else
                {
                    LNodePtr tempoint;
                    tempoint = lhcursor->next;
                    delete lhcursor;
                    lhcursor = tempoint;


                }
            }
        }

    }

}