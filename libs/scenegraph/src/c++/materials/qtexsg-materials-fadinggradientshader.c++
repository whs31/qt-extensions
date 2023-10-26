//
// Created by whs31 on 28.09.23.
//

#include "qtexsg-materials-fadinggradientshader.h"

#if(QT_VERSION_MAJOR == 5)

namespace QtEx
{
  QSGMaterialShader* FadingGradientShader::createShader() { return new FadingGradientShader; }
  QSGSimpleMaterialComparableMaterial<State>* FadingGradientShader::createMaterial() {
    return new QSGSimpleMaterialComparableMaterial<State>(FadingGradientShader::createShader);
  }

  const char* FadingGradientShader::vertexShader() const
  {
    return "attribute highp vec4 aVertex;           \n"
           "attribute highp vec2 aTexCoord;         \n"
           "uniform highp mat4 qt_Matrix;           \n"
           "varying highp vec2 texCoord;            \n"
           "void main() {                           \n"
           "    gl_Position = qt_Matrix * aVertex;  \n"
           "    texCoord = aTexCoord;               \n"
           "}";
  }

  const char* FadingGradientShader::fragmentShader() const
  {
    return "uniform lowp float qt_Opacity;                  \n"
           "uniform lowp vec4 color;                        \n"
           "varying highp vec2 texCoord;                    \n"
           "void main () {                                  \n"
           "    gl_FragColor = qt_Opacity * min(1.3 -         "
           "    texCoord.y, 1.0) * color;                   \n"
           "}";
  }

  QList<QByteArray> FadingGradientShader::attributes() const { return QList<QByteArray>() << "aVertex" << "aTexCoord"; }
  void FadingGradientShader::updateState(const State* state, const State*) { program()->setUniformValue(id_color, state->color); }
  void FadingGradientShader::resolveUniforms() { id_color = program()->uniformLocation("color"); }
} // QtEx

#endif