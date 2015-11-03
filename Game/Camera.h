//#pragma once
//#include <cstdint>
//#include "../PhysLib/Geometry.h"
//
//class Camera {
//public:
//  double getCameraZoom() const;
//  Physics::Geometry::Point getCameraPosition() const;
//  virtual Camera& update(const Physics::Geometry::Point& pivot, const Physics::Geometry::Point& target) = 0;
//  Camera& updateViewPortParams(uint16_t width, uint16_t height);
//  Camera& setZoom(double zoom);
//
//  Physics::Geometry::Point translateToScreenCoord(Physics::Geometry::Point p);
//  virtual ~Camera() { };
//
//protected:
//  double zoom;
//  double invZoom;
//  Physics::Geometry::Point halfScreen;
//  Physics::Geometry::Point cameraPosition;
//};
