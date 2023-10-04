//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <queue>
#include <QtCore/QObject>
#include <QtExCore/Global>

using std::queue;

class QGeoPolygon;
class QNetworkAccessManager;
class QNetworkReply;

namespace QtEx
{
  class TileLoader : public Object
  {
    Q_OBJECT
    Q_PROPERTY(QString serverUrl READ serverUrl WRITE setServerUrl NOTIFY serverUrlChanged FINAL)
    Q_PROPERTY(QString storageUrl READ storageUrl WRITE setStorageUrl NOTIFY storageUrlChanged FINAL)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged STORED false FINAL);

    constexpr static const uint8_t MAX_ALLOWED_PARALLEL = 4;

    public:
      explicit TileLoader(String storageUrl, Object* parent = nullptr);

      [[nodiscard]] String serverUrl() const;    void setServerUrl(const String&);
      [[nodiscard]] String storageUrl() const;   void setStorageUrl(const String&);
      [[nodiscard]] int progress() const;

      void download(int zoom, int x, int y);
      void download(const QGeoPolygon&, int zoom = 18);
      invokable void download(const QList<QVariant>&, int zoom = 18);
      ByteArray tileAt(int zoom, int x, int y) const;

      [[nodiscard]] invokable static int estimate(const QList<QVariant>&, int zoom = 18);

    signals:
      void serverUrlChanged();
      void storageUrlChanged();
      void progressChanged();

    private:
      Q_SLOT void onFinished(QNetworkReply* reply);
      void process();

      static uint32_t longitudeToTileX(double longitude, uint8_t zoom);
      static uint32_t latitudeToTileY(double latitude, uint8_t zoom);
      static double tileXToLongitude(uint32_t x, uint8_t zoom);
      static double tileYToLatitude(uint32_t y, uint8_t zoom);

    private:
      struct Tile
      {
        Tile(int zoom, int x, int y);

        int zoom;
        int x;
        int y;
      };

      QNetworkAccessManager* m_nam;
      long m_total_tiles;
      long m_loaded_tiles;
      queue<Tile> m_queue;
      int m_parallel_loaded_count;
      String m_server_url;
      String m_storage_url;
  };
} // QtEx
