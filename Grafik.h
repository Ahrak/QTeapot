#ifndef GRAFIK_H
#define GRAFIK_H

/**
 * Graphic that will be drawn on the openGL Widget
 * @author Tommy Hartmann
 */
class CGraphic
{
public:

    /**
     * Constructor
     */
    CGraphic();

    /**
     * Destructor
     */
    ~CGraphic();

    /**
     * Initializes OpenGL Elements
     */
    void Init();


    /**
     * Draws OpenGL Elements
     */
    void Draw();
};

#endif // GRAFIK_H
