#ifndef POINT3D_H
#define POINT3D_H

/**
 * Represents a point in 3D
 * @author Tommy Hartmann
 */
class Point3D
{

public:

    /**
     * Constructor
     * @param x initial x coordinate
     * @param y initial y coordinate
     * @param z initial z coordinate
     */
    Point3D(double x = 0, double y = 0, double z = 0);

    /**
     * set new coordinates
     */
    void set(double x, double y, double z);

    /**
     * getter for x
     * @return x value
     */
    double x() { return m_x; };


    /**
     * getter for y
     * @return y value
     */
    double y() { return m_y; };


    /**
     * getter for z
     * @return z value
     */
    double z() { return m_z; };

private:

    /** x value */
    double m_x;
    /** y value */
    double m_y;
    /** z value */
    double m_z;

};

#endif // POINT3D_H
