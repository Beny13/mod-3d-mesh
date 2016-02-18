#include "triangle.h"


Triangle::Triangle()
{
}

Triangle::Triangle(int index1, int index2, int index3)
 : index1(index1), index2(index2), index3(index3)
{
}
int Triangle::getIndex1() const
{
    return index1;
}

void Triangle::setIndex1(int value)
{
    index1 = value;
}
int Triangle::getIndex2() const
{
    return index2;
}

void Triangle::setIndex2(int value)
{
    index2 = value;
}
int Triangle::getIndex3() const
{
    return index3;
}

void Triangle::setIndex3(int value)
{
    index3 = value;
}

bool Triangle::hasIndex(int index)
{
    return index == index1 || index == index2 || index == index3;
}

QString Triangle::format() const
{
    QString res;
    QTextStream stream(&res);
    stream << index1 + 1 << " "
           << index2 + 1 << " "
           << index3 + 1 << " 508";
    return res;
}



