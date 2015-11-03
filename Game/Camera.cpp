//#include "Camera.h"
//
//double Camera::getCameraZoom() const {
//  return zoom;
//}
//
//Physics::Geometry::Point Camera::getCameraPosition() const {
//  return cameraPosition;
//}
//
//Camera & Camera::updateViewPortParams(uint16_t newWidth, uint16_t newHeight) {
//  halfScreen.x = newWidth / 2;
//  halfScreen.y = newHeight / 2;
//  return *this;
//}
//
//Camera & Camera::setZoom(double newZoom) {
//  zoom = newZoom;
//  invZoom = 1 / zoom;
//  return *this;
//}
//
//Physics::Geometry::Point Camera::translateToScreenCoord(Physics::Geometry::Point p) {
//  return halfScreen + (p - cameraPosition) * zoom;
//}
