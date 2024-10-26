#include <QtWidgets>
#include <QOpenGLFunctions>

#include <math.h>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->xRot = 0.0f;
    this->yRot = 0.0f;
    this->zRot = 0.0f;
    this->zoom = 1.0f;

    this->qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    this->qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    this->marching = new Marching();
    this->fertilizer = new PotatoFertilizer();
    this->gardener = new Gardener(10.0f, 10.0f, 10.0f);
    this->fertilizer->setup(this->gardener);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000.0f/30.0f);
}

GLWidget::~GLWidget()
{
    delete this->marching;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::updateGL()
{
    update();
    this->fertilizer->update();
}

// ... (restul funcțiilor rămân neschimbate)

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    GLfloat afPropertiesAmbient [] = {0.50, 0.50, 0.50, 1.00};
    GLfloat afPropertiesDiffuse [] = {0.75, 0.75, 0.75, 1.00};
    GLfloat afPropertiesSpecular[] = {1.00, 1.00, 1.00, 1.00};

    qglClearColor(qtPurple.dark());
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_MULTISAMPLE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    static GLfloat lightPosition[4] = { 0, 0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glLightfv(GL_LIGHT0, GL_AMBIENT, afPropertiesAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, afPropertiesDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, afPropertiesSpecular);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

    glEnable(GL_LIGHT0);

    glMaterialfv(GL_BACK, GL_AMBIENT, afAmbientGreen);
    glMaterialfv(GL_BACK, GL_DIFFUSE, afDiffuseGreen);
    glMaterialfv(GL_FRONT, GL_AMBIENT, afAmbientBlue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, afDiffuseBlue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, afSpecularWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
}
