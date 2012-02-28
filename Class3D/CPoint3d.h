#ifndef POINT3D_H
#define POINT3D_H

class Point3D
{

public:
    Point3D(float x = 0, float y = 0, float z = 0);
    float x;
    float y;
    float z;

    void set(float x, float y, float z);
};

#endif // POINT3D_H
