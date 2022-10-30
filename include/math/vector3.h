#ifndef RAYTRACER_MATH_VEC3_H
#define RAYTRACER_MATH_VEC3_H

#include <cmath>
#include <iostream>

#include "utility.h"

#define EPSILON 10e-8       // A small value that for practical considerations
                            // can be assumed to be "0"

// Vector class representing a quantity in 3D space. Depending on context, can
// either be used for color (RGB), points or directions.
class Vector3 {
    public:
        Vector3() : e{0, 0, 0} {}
        Vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vector3& operator+=(const Vector3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vector3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vector3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        bool is_zero() const {
            return std::fabs(e[0]) < EPSILON
                && std::fabs(e[1]) < EPSILON
                && std::fabs(e[2]) < EPSILON;
        }

        static Vector3 random_vector(double min, double max) {
            return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

    public:
        double e[3];
};

// Vector3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const Vector3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3 operator+(const Vector3 &u, const Vector3 &v) {
    return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v) {
    return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3 operator*(const Vector3 &u, const Vector3 &v) {
    return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3 operator*(double t, const Vector3 &v) {
    return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator*(const Vector3 &v, double t) {
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector3 &u, const Vector3 &v) {
    return u.e[0] * v.e[0]
           + u.e[1] * v.e[1]
           + u.e[2] * v.e[2];
}

inline Vector3 cross(const Vector3 &u, const Vector3 &v) {
    return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vector3 unit_vector(Vector3 v) {
    return v / v.length();
}

inline Vector3 random_in_unit_disk() {
    while (true) {
        auto p = Vector3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vector3 random_in_unit_sphere() {
    while (true) {
        auto p = Vector3::random_vector(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vector3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline Vector3 reflect(const Vector3& v, const Vector3& n) {
    return v - 2*dot(v,n)*n;
}

inline Vector3 refract(const Vector3& uv, const Vector3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}


#endif
