#include "glwidget.h"
#include <QOpenGLTexture>
#include <QFile>
#include <ogrsf_frmts.h>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_program(nullptr)
{
}

GLWidget::~GLWidget()
{
    makeCurrent();
    m_vbo.destroy();
    m_vao.destroy();
    delete m_program;
    doneCurrent();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    setupShaders();
    setupBuffers();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    m_vao.bind();

    updateMatrices();
    m_program->setUniformValue("mvp", m_projection * m_view);

    glDrawArrays(GL_POINTS, 0, m_features.size());

    m_vao.release();
    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::setupShaders()
{
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment.frag");
    m_program->link();
}

void GLWidget::setupBuffers()
{
    m_vao.create();
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(m_features.data(), m_features.size() * sizeof(MapFeature));

    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3, sizeof(MapFeature));

    m_program->enableAttributeArray("texCoord");
    m_program->setAttributeBuffer("texCoord", GL_FLOAT, sizeof(QVector3D), 2, sizeof(MapFeature));

    m_vao.release();
}

void GLWidget::updateMatrices()
{
    m_view.setToIdentity();
    m_view.translate(0, 0, -5);
}

void GLWidget::loadShapefile(const QString& filename)
{
    GDALAllRegister();
    GDALDataset *poDS = (GDALDataset*) GDALOpenEx(filename.toStdString().c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (poDS == NULL) {
        qDebug() << "Failed to open shapefile.";
        return;
    }

    OGRLayer *poLayer = poDS->GetLayer(0);
    OGRFeature *poFeature;

    m_features.clear();
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != NULL) {
        OGRGeometry *poGeometry = poFeature->GetGeometryRef();
        if (poGeometry != NULL && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint) {
            OGRPoint *poPoint = (OGRPoint *) poGeometry;
            MapFeature feature;
            feature.position = QVector3D(poPoint->getX(), poPoint->getY(), 0);
            feature.texCoord = QVector2D(0, 0);  // You'll need to calculate proper texture coordinates
            m_features.push_back(feature);
        }
        OGRFeature::DestroyFeature(poFeature);
    }

    GDALClose(poDS);

    setupBuffers();  // Rebuild the VBO with new data
    update();  // Request a repaint
}
