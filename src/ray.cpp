#include "ray.h"

Vector3<float> Ray::at(float scalar) const {
    return m_origin + scalar * (m_direction - m_origin);
}