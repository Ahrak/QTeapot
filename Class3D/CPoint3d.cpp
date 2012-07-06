#include "CPoint3d.h"

Point3D::Point3D(double x, double y, double z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{
    //
}


void Point3D::set(double x, double y, double z)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}
