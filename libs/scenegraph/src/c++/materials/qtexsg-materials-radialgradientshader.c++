//
// Created by whs31 on 28.09.23.
//

#include "qtexsg-materials-radialgradientshader.h"

#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))

namespace QtEx
{
  QSGMaterialShader* RadialGradientShader::createShader() { return new RadialGradientShader; }
  QSGSimpleMaterialComparableMaterial<State>* RadialGradientShader::createMaterial() {
    return new QSGSimpleMaterialComparableMaterial<State>(RadialGradientShader::createShader);
  }

  const char* RadialGradientShader::vertexShader() const
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

  const char* RadialGradientShader::fragmentShader() const
  {
    return "uniform lowp float qt_Opacity;                  \n"
           "uniform lowp vec4 color;                        \n"
           "varying highp vec2 texCoord;                    \n"
           "void main () {                                  \n"
           "    vec4 col = color * qt_Opacity;              \n"
           "    col.w = 1.0;                                  \n"
           "    gl_FragColor = 2.0 * col * min(max(sqrt(pow(texCoord.x - .5, 2.0) + pow(texCoord.y - .5, 2.0)), .3), 1.0); \n"
           "}";
  }

  QList<QByteArray> RadialGradientShader::attributes() const { return QList<QByteArray>() << "aVertex" << "aTexCoord"; }
  void RadialGradientShader::updateState(const State* state, const State*) { program()->setUniformValue(id_color, state->color); }
  void RadialGradientShader::resolveUniforms() { id_color = program()->uniformLocation("color"); }
} // QtEx

#endif