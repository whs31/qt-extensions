//
// Created by whs31 on 29.09.23.
//

#include "qtexelevation-algorithms.h"
#include <QtCore/QPointF>
#include <QtPositioning/QGeoPath>
#include <QtExCore/Math>
#include <QtExCore/Logging>
#include "QtExElevation/TileStorage"

namespace QtEx
{
  bool loadTile(const int8_t latitude, const int16_t longitude) { return TileStorage::get()->load(latitude, longitude); }
  bool loadTiles(const int8_t minLatitude, const int16_t minLongitude, const int8_t maxLatitude, const int16_t maxLongitude)
  {
    bool ret = true;
    for(int8_t lat = minLatitude; lat <= maxLatitude; ++lat)
      for(int16_t lon = minLongitude; lon <= maxLongitude; ++lon)
        ret &= loadTile(lat, lon);
    return ret;
  }

  int16_t elevation(const double latitude, const double longitude, PreLoad mode)
  {
    double lat = latitude;
    double lon = longitude;
    if (latitude - std::floor(latitude) < 0.00001)
      lat = std::floor(latitude);
    if(std::ceil(latitude) - latitude < 0.00001)
      lat = std::ceil(latitude);
    if(longitude - std::floor(longitude) < 0.00001)
      lon = std::floor(longitude);
    if(std::ceil(longitude) - longitude < 0.00001)
      lon = std::ceil(longitude);

    if(mode == PreLoad::True) {
      loadTile(lat, lon);
    }
    try { return TileStorage::get()->elevation(lat, lon); }
    catch(std::runtime_error& x) { throw x; }
  }

  vector<pair<uint32_t, int16_t>> buildProfile(const QGeoPath& path, uint8_t discrete)
  {
    loadTiles(path);
    vector<pair<uint32_t, int16_t>> groundProfile;

    if(path.size())
    {
      double distanceFromStart = 0;
      QGeoCoordinate prevBasePointGeo = path.coordinateAt(0);

      for(QGeoCoordinate point : path.path())
      {

        if(not groundProfile.empty())
        {
          double azimuth = prevBasePointGeo.azimuthTo(point);
          double distanceFromPrevBasePoint = prevBasePointGeo.distanceTo(point);

          double distance = discrete;
          QGeoCoordinate prevDeltaPointGeo = prevBasePointGeo;
          while(distance < distanceFromPrevBasePoint)
          {
            QGeoCoordinate deltaPointGeo = prevBasePointGeo.atDistanceAndAzimuth(distance, azimuth);
            auto a = deltaPointGeo.latitude();
            auto b = deltaPointGeo.longitude();
            auto c = prevDeltaPointGeo.latitude();
            auto d = prevDeltaPointGeo.longitude();
            auto e = point.latitude();
            auto f = point.longitude();


            try
            {
              deltaPointGeo.setAltitude(elevation(deltaPointGeo.latitude(), deltaPointGeo.longitude()));
            }
            catch(std::runtime_error& x)
            {
              Log::panic() << x.what();
              return {};
            }
            if(prevDeltaPointGeo.altitude() != deltaPointGeo.altitude())
            {
              if(prevDeltaPointGeo.altitude() > deltaPointGeo.altitude())
                groundProfile.emplace_back(distance - discrete + distanceFromStart, prevDeltaPointGeo.altitude());
              else
                groundProfile.emplace_back(distance + distanceFromStart, deltaPointGeo.altitude());
            }

            prevDeltaPointGeo = deltaPointGeo;
            distance += discrete;
          }

          distanceFromStart += distanceFromPrevBasePoint;
        }

        try
        {
          point.setAltitude(elevation(point.latitude(), point.longitude()));
        }
        catch(std::runtime_error& x)
        {
          Log::panic() << x.what();
          return {};
        }

        groundProfile.emplace_back(distanceFromStart, point.altitude());
        prevBasePointGeo = point;
      }
    }
    return groundProfile;
  }

  bool loadTiles(const QGeoPath& path)
  {
    if(path.isEmpty())
      return false;

    if(path.size() == 1)
      return loadTile(std::floor(path.coordinateAt(0).latitude()), std::floor(path.coordinateAt(0).longitude()));

    int8_t minLatitude{};
    int8_t maxLatitude{};
    int16_t minLongitude{};
    int16_t maxLongitude{};

    bool ret = true;
    for(int i = 1; i < path.size(); ++i)
    {
      QGeoCoordinate coord1 = path.coordinateAt(i - 1);
      QGeoCoordinate coord2 = path.coordinateAt(i);

      minLatitude = coord1.latitude() < coord2.latitude() ? static_cast<int8_t>(coord1.latitude()) : static_cast<int8_t>(coord2.latitude());
      maxLatitude = coord1.latitude() < coord2.latitude() ? static_cast<int8_t>(coord2.latitude()) : static_cast<int8_t>(coord1.latitude());
      minLongitude = coord1.longitude() < coord2.longitude() ? static_cast<int16_t>(coord1.longitude()) : static_cast<int16_t>(coord2.longitude());
      maxLongitude = coord1.longitude() < coord2.longitude() ? static_cast<int16_t>(coord2.longitude()) : static_cast<int16_t>(coord1.longitude());

      ret &= loadTiles(minLatitude, minLongitude, maxLatitude, maxLongitude);
    }
    return ret;
  }

  QGeoPath buildProfileAsGeoPath(const QGeoPath& path, float step)
  {
    if(not loadTiles(path))
      return {};

    QGeoPath ret;
    for(auto point : path.path())
    {
      if(ret.size())
      {
        auto previous = ret.coordinateAt(ret.size() - 1);
        auto azimuth = previous.azimuthTo(point);
        auto Δ = previous.distanceTo(point);
        float δ = step;
        auto t = previous;
        while(δ < Δ)
        {
          auto u = previous.atDistanceAndAzimuth(δ, azimuth);
          try { u.setAltitude(elevation(u.latitude(), u.longitude())); }
          catch(...) { return ret; }
          if(t.altitude() != u.altitude())
          {
            if(t.altitude() > u.altitude()) ret.addCoordinate(t);
            else ret.addCoordinate(u);
          }
          t = u;
          δ += step;
        }
      }
      try { point.setAltitude(elevation(point.latitude(), point.longitude())); }
      catch(...) { return ret; }
      ret.addCoordinate(point);
    }
    return ret;
  }
} // QtEx
