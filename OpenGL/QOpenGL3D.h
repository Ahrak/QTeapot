#include "Class3D/CPoint3d.h"
#include "Class3D/CVector3d.h"
#include "OpenGL/QOpenGL.h"

class QOpenGL3D : public QOpenGL
{
public:
    QOpenGL3D(void);
    ~QOpenGL3D(void);
	
    void lookAt(const Point3D&, const Point3D&, const Vector3D&);
	void ortho(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void frustum(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void perspective(GLfloat, GLfloat, GLfloat, GLfloat);
	
protected:
	bool m_bOrtho, m_bFrustum, m_bPerspective;
	GLfloat m_fleft, m_fright, m_fbottom, m_ftop, m_fnear, m_ffar;
	GLfloat m_fangle, m_faspect;
    Point3D m_Pposition, m_Ptarget;
    Vector3D m_VviewingUp;
};
