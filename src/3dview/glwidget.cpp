#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) { initSettings(); }

GLWidget::~GLWidget() { cleanup(); }

void GLWidget::initSettings() {
  projectionMode = 0;
  backgroundColor.setRgb(0, 0, 0);
  lineColor.setRgb(0, 127, 51);
  lineSize = 1;
  lineMode = 0;
  pointColor.setRgb(0, 214, 120);
  pointSize = 1;
  pointMode = 0;
}

void GLWidget::clearBuffers() {
  if (VertexArrObj.isCreated()) {
    VertexArrObj.destroy();
  }
  if (VertexBuff.isCreated()) {
    VertexBuff.destroy();
  }
  if (ElemBuff.isCreated()) {
    ElemBuff.destroy();
  }
}

void GLWidget::cleanup() {
  makeCurrent();
  clearBuffers();
  remove_obj(&objData);
  doneCurrent();
}

void GLWidget::initBuffers() {
  clearBuffers();
  VertexArrObj.create();
  VertexArrObj.bind();
  VertexBuff = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  VertexBuff.create();
  VertexBuff.bind();
  VertexBuff.setUsagePattern(QOpenGLBuffer::StaticDraw);
  VertexBuff.allocate(objData.vertexs.matrix[0],
                      4 * objData.vertexs_count * sizeof(GLfloat));

  ElemBuff = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  ElemBuff.create();
  ElemBuff.bind();
  ElemBuff.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ElemBuff.allocate(objData.faces, 2 * objData.faces_lenght * sizeof(GLint));

  VertexArrObj.release();
}

// Код веришнного шейдера на GLSL
static const char *vertexShaderSourceCore =
    "attribute vec4 vertex;\n"
    "uniform mat4 coeffMatrix;\n"
    "void main() {\n"
    "   gl_Position = coeffMatrix * vertex;\n"
    "}\n";

// Код фрагментного шейдера на GLSL
static const char *fragmentShaderSourceCore =
    "uniform vec4 color;\n"
    "void main() {\n"
    "   gl_FragColor = color;\n"
    "}\n";

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  m_program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                    vertexShaderSourceCore);
  m_program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                    fragmentShaderSourceCore);
  m_program.bindAttributeLocation("vertex", 0);
  m_program.link();
  m_program.bind();
  m_coeffMatrixLoc = m_program.uniformLocation("coeffMatrix");
  m_colorLoc = m_program.uniformLocation("color");

  moveMatrix.setToIdentity();
  moveMatrix.lookAt(QVector3D(0, 0, 2.), QVector3D(0, 0, 0),
                    QVector3D(0, 0.1, 0));
}

void GLWidget::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), backgroundColor.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (VertexArrObj.isCreated()) {
    projectionMatrix.setToIdentity();

    if (projectionMode == 0) {
      projectionMatrix.perspective(45, (float)width() / height(), 0.01, 100);
    } else if (projectionMode == 1) {
      projectionMatrix.ortho(-(float)width() / height(),
                             (float)width() / height(), -1, 1, -10, 10);
    }

    VertexBuff.bind();
    VertexArrObj.bind();
    m_program.bind();
    ElemBuff.bind();
    VertexBuff.write(0, objData.vertexs.matrix[0],
                     4 * objData.vertexs_count * sizeof(GLfloat));
    m_program.enableAttributeArray(0);
    m_program.setAttributeBuffer(0, GL_FLOAT, 0, 4);
    m_program.setUniformValue(m_coeffMatrixLoc, projectionMatrix * moveMatrix);

    if (pointMode != 0) {
      m_program.setUniformValue(m_colorLoc, pointColor);
      glPointSize(pointSize);
      if (pointMode == 1) {
        glEnable(GL_POINT_SMOOTH);
      }
      glDrawArrays(GL_POINTS, 0, objData.vertexs_count);
      if (pointMode == 1) {
        glDisable(GL_POINT_SMOOTH);
      }
    }

    m_program.setUniformValue(m_colorLoc, lineColor);

    glLineWidth(lineSize);
    if (lineMode == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(2, 0x00F0);
    }

    glDrawElements(GL_LINES, objData.faces_lenght * 2, GL_UNSIGNED_INT, 0);
    if (lineMode == 1) {
      glDisable(GL_LINE_STIPPLE);
    }
    VertexArrObj.release();
    ElemBuff.release();
    m_program.release();
  }
}

int NormalizeAngle(int angle) {
  while (angle < -180) angle += 360;
  while (angle > 180) angle -= 360;
  return angle;
}

void GLWidget::setXMove(int step) {
  m_xMove = step - prev_xMove;
  prev_xMove = step;
  move_xyz(&objData, 0.05 * (m_xMove), 0, 0);
  emit xMoveChanged(step);
  update();
}

void GLWidget::setYMove(int step) {
  m_yMove = step - prev_yMove;
  prev_yMove = step;
  move_xyz(&objData, 0, 0.05 * (m_yMove), 0);
  emit yMoveChanged(step);
  update();
}

void GLWidget::setZMove(int step) {
  m_zMove = step - prev_zMove;
  prev_zMove = step;
  move_xyz(&objData, 0, 0, 0.05 * (m_zMove));
  update();
}

void GLWidget::setXRotation(int angle) {
  angle = NormalizeAngle(angle);
  m_xRot = angle - prev_xRot;
  prev_xRot = angle;
  rotate_xyz(&objData, m_xRot, 0, 0);
  emit xRotationChanged(angle);
  update();
}

void GLWidget::setYRotation(int angle) {
  angle = NormalizeAngle(angle);
  m_yRot = angle - prev_yRot;
  prev_yRot = angle;
  rotate_xyz(&objData, 0, m_yRot, 0);
  emit yRotationChanged(angle);
  update();
}

void GLWidget::setZRotation(int angle) {
  angle = NormalizeAngle(angle);
  m_zRot = angle - prev_zRot;
  prev_zRot = angle;
  rotate_xyz(&objData, 0, 0, m_zRot);
  emit zRotationChanged(angle);
  update();
}

void GLWidget::setZoom(int zoom) {
  zoomVal = fabs(zoom / prev_zoomVal);
  prev_zoomVal = zoom;
  scale_xyz(&objData, zoomVal, zoomVal, zoomVal);
  update();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  m_lastPos = event->position().toPoint();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->position().toPoint().x() - m_lastPos.x();
  int dy = event->position().toPoint().y() - m_lastPos.y();
  if (event->buttons() & Qt::LeftButton) {
    setXRotation(prev_xRot + dy);
    setYRotation(prev_yRot + dx);
  } else if (event->buttons() & Qt::RightButton) {
    setZRotation(prev_zRot - dx);
  } else if (event->buttons() & Qt::MiddleButton) {
    setXMove(prev_xMove - dx);
    setYMove(prev_yMove + dy);
  }
  m_lastPos = event->position().toPoint();
}
