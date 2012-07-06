#include "CVector3d.h"

Vector3D::Vector3D(double a, double b, double c)
    : m_a(a)
    , m_b(b)
    , m_c(c)
{
   //
}

void Vector3D::set(double a, double b, double c)
{
    this->m_a = a;
    this->m_b = b;
    this->m_c = c;
}

