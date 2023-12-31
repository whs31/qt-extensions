//
// Created by whs31 on 28.09.23.
//

#pragma once

#include <QtCore/QtGlobal>
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))

#include <QtQuick/QSGSimpleMaterial>
#include <QtExtensionsScenegraph/Materials/State>

namespace QtEx
{
  class FadingGradientShader : public QSGSimpleMaterialShader<State>
  {
    public:
      static QSGMaterialShader* createShader();
      static QSGSimpleMaterialComparableMaterial<State>* createMaterial();

      const char* vertexShader() const override;
      const char* fragmentShader() const override;
      QList<QByteArray> attributes() const override;
      void updateState(const State* state, const State*) override;
      void resolveUniforms() override;

    private:
      int id_color;
  };
} // QtEx

#endif