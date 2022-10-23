#include "ray.h"

Vector3<double> Ray::at(double scalar) const {
    return m_origin + scalar * (m_direction - m_origin);
}