#include "node.h"

Node::Node()
{
}

Node::Node(double x, double y, double z)
    : point(x, y, z) {

}

void Node::addTriangle(int triangle)
{
    if(!triangles.contains(triangle)){
        triangles.push_back(triangle);
    }
}

void Node::addNode(int node)
{
    if(!nodes.contains(node)){
        nodes.push_back(node);
    }
}

const Point3D &Node::getPoint() const
{
    return point;
}

void Node::setPoint(const Point3D &value)
{
    point = value;
}
QVector<int> Node::getTriangles() const
{
    return triangles;
}

QVector<int> Node::getNodes() const
{
    return nodes;
}

Node Node::translate(Point3D normal, double dPoint) const
{
    Node res;
    res.triangles = triangles;
    res.nodes = nodes;
    res.setPoint(point.translate(normal, dPoint));
    return res;
}



