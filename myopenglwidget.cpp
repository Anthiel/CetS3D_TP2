//R. Raffin, M1 Informatique, "Surfaces 3D"
//tiré de CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

#include <iostream>


static const QString vertexShaderFile   = ":/basic.vsh";
static const QString fragmentShaderFile = ":/basic.fsh";


myOpenGLWidget::myOpenGLWidget(QWidget *parent) :
	QOpenGLWidget(parent)
{
	qDebug() << "init myOpenGLWidget" ;

	QSurfaceFormat sf;
	sf.setDepthBufferSize(24);
	sf.setSamples(16);  // nb de sample par pixels : suréchantillonnage por l'antialiasing, en décalant à chaque fois le sommet
						// cf https://www.khronos.org/opengl/wiki/Multisampling et https://stackoverflow.com/a/14474260
	setFormat(sf);

	setEnabled(true);  // événements clavier et souris
	setFocusPolicy(Qt::StrongFocus); // accepte focus
	setFocus();                      // donne le focus


	m_timer = new QTimer(this);
	m_timer->setInterval(50);  // msec
	connect (m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

}

myOpenGLWidget::~myOpenGLWidget()
{
	qDebug() << "destroy GLArea";

	delete m_timer;

	// Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
	// dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
	makeCurrent();
	tearGLObjects();
	doneCurrent();
}


void myOpenGLWidget::initializeGL()
{
	qDebug() << __FUNCTION__ ;
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	makeGLObjects();

	//shaders
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);  // compile
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);

	if (! m_program->link()) {  // édition de lien des shaders dans le shader program
		qWarning("Failed to compile and link shader program:");
		qWarning() << m_program->log();
	}
}

void myOpenGLWidget::doProjection()
{
	//m_mod.setToIdentity();
	//modelMatrix.ortho( -aratio, aratio, -1.0f, 1.0f, -1.0f, 1.0f );
}


void myOpenGLWidget::makeGLObjects()
{
    if (firstDraw){
        controlPoints[0] =  *new Point(-1.0, -1.0, 0.5);
        controlPoints[1] =  *new Point(-1.0, 1.0, 0.5);
        controlPoints[2] =  *new Point(1.0, 1.0, 0.5);
        controlPoints[3] =  *new Point(1.0, -1.0, 0.5);
        controlPoints[4] =  *new Point(-1.0, -1.0, 0.0);
        controlPoints[5] =  *new Point(-1.0, 1.0, 0.0);
        controlPoints[6] =  *new Point(1.0, 1.0, 0.0);
        controlPoints[7] =  *new Point(1.0, -1.0, 0.0);
        controlPoints[8] =  *new Point(-1.0, -1.0, -0.5);
        controlPoints[9] =  *new Point(-1.0, 1.0, -0.5);
        controlPoints[10] = *new Point(1.0, 1.0, -0.5);
        controlPoints[11] = *new Point(1.0, -1.0, -0.5);
        controlPoints[12] = *new Point(-1.0, -1.0, -1.0);
        controlPoints[13] = *new Point(-1.0, 1.0, -1.0);
        controlPoints[14] = *new Point(1.0, 1.0, -1.0);
        controlPoints[15] = *new Point(1.0, -1.0, -1.0);
        E = new Point(0.0, 0.0, 0.0,0,1,1);
        F = new Point(0.0, 0.0, 0.0,0,1,1);
        C1 = new CourbeParametrique(controlPoints, 0.0, 1.0, 0.0);
        firstDraw=false;
    }
    else{
        if(editing){
            *E = C1->getPoint(numPoint);
            E->setColor(0,1.0,1.0);
            F->setX(E->getX()+dx);
            F->setY(E->getY()+dy);
            F->setZ(E->getZ()+dz);
        }
        else if(edited){
            controlPoints[numPoint]=*F;
            C1->update();
        }
    }
    int decal=0;
    QVector<GLfloat> vertData;
    C1->makeObject(&vertData);     C1->setStart(decal);    decal+=C1->getSize();


    if(editing){
        E->makeObject(&vertData);
        F->makeObject(&vertData);
        decal+=2;
    }
	m_vbo.create();
	m_vbo.bind();
	//qDebug() << "vertData " << vertData.count () << " " << vertData.data ();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}


void myOpenGLWidget::tearGLObjects()
{
	m_vbo.destroy();
}


void myOpenGLWidget::resizeGL(int w, int h)
{
	qDebug() << __FUNCTION__ << w << h;

	//C'est fait par défaut
	glViewport(0, 0, w, h);

	m_ratio = (double) w / h;
	//doProjection();
}

void myOpenGLWidget::paintGL()
{
	qDebug() << __FUNCTION__ ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_program->bind(); // active le shader program


	/// Ajout RR pour gérer les 3 matrices utiles
	/// à mettre dans doProjection() pour clarifier
	/// -----------------------------------------
		m_modelView.setToIdentity();
		m_modelView.lookAt(QVector3D(0.0f, 0.0f, 3.0f),    // Camera Position
						 QVector3D(0.0f, 0.0f, 0.0f),    // Point camera looks towards
						 QVector3D(0.0f, 1.0f, 0.0f));   // Up vector

        m_projection.setToIdentity ();
        m_projection.perspective(70.0, width() / height(), 0.1, 100.0); //ou m_ratio


		//m_model.translate(0, 0, -3.0);
        m_modelView.translate(m_x,m_y,m_z);
		// Rotation de la scène pour l'animation
        m_modelView.rotate(m_angleX, 1, 0, 0);
        m_modelView.rotate(m_angleY, 0, 1, 0);
        m_modelView.rotate(m_angleZ, 0, 0, 1);

		QMatrix4x4 m = m_projection * m_modelView * m_model;
	///----------------------------

	m_program->setUniformValue("matrix", m);

	m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
	m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
	m_program->enableAttributeArray("posAttr");
	m_program->enableAttributeArray("colAttr");

    if(editing){
        glPointSize (10.0f);
        glDrawArrays(GL_POINTS, C1->getSize(), 1);
        glDrawArrays(GL_POINTS, C1->getSize()+1, 1);
    }
    glPointSize (5.0f);
    glLineWidth(2.0f);

    glDrawArrays(GL_POINTS, C1->getStart(), C1->getSizeCourbeParam());
    glDrawArrays(GL_LINES, C1->getStart(), C1->getSize());




	m_program->disableAttributeArray("posAttr");
    m_program->disableAttributeArray("colAttr");

	m_program->release();
}

void myOpenGLWidget::keyPressEvent(QKeyEvent *ev)
{
    //qDebug() << __FUNCTION__ << ev->text();

	switch(ev->key()) {
        case Qt::Key_6 :
            m_angleY += 1;
            if (m_angleY >= 360) m_angleY -= 360;
            update();
            break;
        case Qt::Key_4 :
            m_angleY -= 1;
            if (m_angleY <= -1) m_angleY += 360;
            update();
            break;
        case Qt::Key_5 :
            m_angleX += 1;
            if (m_angleX >= 360) m_angleX -= 360;
            update();
            break;
        case Qt::Key_8 :
            m_angleX -= 1;
            if (m_angleX <= -1) m_angleX += 360;
            update();
            break;
        case Qt::Key_7 :
            m_angleZ += 1;
            if (m_angleZ >= 360) m_angleZ -= 360;
            update();
            break;
        case Qt::Key_9 :
            m_angleZ -= 1;
            if (m_angleZ <= -1) m_angleZ += 360;
            update();
            break;
        case Qt::Key_S :
            if(editing){
                dz+=0.1;
                makeGLObjects();
            }else{
                m_z-=0.1f;
            }
            update();
            break;
        case Qt::Key_Z :
            if(editing){
                dz-=0.1;
                makeGLObjects();
            }else{
                m_z+=0.1f;
            }
            update();
            break;
        case Qt::Key_Q :
            if(editing){
                dx-=0.1;
                makeGLObjects();
            }else{
                m_x+=0.1f;
            }
            update();
            break;
        case Qt::Key_D :
            if(editing){
                dx+=0.1;
                makeGLObjects();
            }else{
                m_x-=0.1f;
            }
            update();
            break;

        case Qt::Key_F:
            if(editing){
                dy-=0.1;
                makeGLObjects();
            }else{
                m_y+=0.1f;
            }
                update();
                break;
        case Qt::Key_R:
            if(editing){
                dy+=0.1;
                makeGLObjects();
            }else{
                m_y-=0.1f;
            }
                update();
                break;
        case Qt::Key_Space:
            dx=0;
            dy=0;
            dz=0;
            editing=!editing;
            edited=false;
            makeGLObjects();
            update();
            break;
        case Qt::Key_Plus :
            if (editing){
                dx=0;
                dy=0;
                dz=0;
                numPoint++;
                if(numPoint>15)
                    numPoint=0;
                makeGLObjects();
                update();
            }
            break;
        case Qt::Key_Minus :
            if (editing){
                dx=0;
                dy=0;
                dz=0;
                numPoint--;
                if(numPoint<0)
                    numPoint=15;
                makeGLObjects();
                update();
            }
            break;
        case Qt::Key_Return :
            if (editing){
                editing=false;
                edited=true;
                dx=0;
                dy=0;
                dz=0;
                makeGLObjects();
                update();
            }else{
                m_x=0;
                m_y=0;
                m_z=0;
                m_angleX=0;
                m_angleY=0;
                m_angleZ=0;
                update();
            }
            break;
	}
}

void myOpenGLWidget::keyReleaseEvent(QKeyEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->text();
}

void myOpenGLWidget::mousePressEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseReleaseEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseMoveEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y();
}

void myOpenGLWidget::onTimeout()
{
	qDebug() << __FUNCTION__ ;

	update();
}





