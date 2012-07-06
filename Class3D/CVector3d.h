#ifndef VECTOR3D_H
#define VECTOR3D_H

/**
 * Represents an 3D-Vector
 */
class Vector3D
{
public:

    /**
     * Construtor
     * @param a intial first value
     * @param b initial second value
     * @param c initial third value
     */
    Vector3D(double a = 0, double b = 0, double c = 0);

    /**
     * Setter for all values
     */
    void set(double a, double b, double c);

    /**
     * Getter for a value
     * @return a value
     */
    double a() { return m_a;};

    /**
     * Getter for b value
     * @return b value
     */
    double b() { return m_b;};

    /**
     * Getter for c value
     * @return c value
     */
    double c() { return m_c;};

private:

    /** first value */
    double m_a;
    /** first value */
    double m_b;
    /** first value */
    double m_c;
};

#endif // VECTOR3D_H
