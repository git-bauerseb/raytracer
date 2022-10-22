#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <cmath>
#include <ostream>

template<typename T>
class Vector3 {
    public:
        Vector3();
        Vector3(T x, T y, T z);

        Vector3<T> normalized() const;

        T operator[](int index) const;
        T& operator[](int index);

        T dot(Vector3<T> other) const;

        template<typename G>
        friend Vector3<G> operator-(const Vector3<G>& vec);

        template<typename G>
        friend Vector3<G> operator-(const Vector3<G>& first, const Vector3<G>& second);

        template<typename G>
        friend Vector3<G> operator*(float scalar, const Vector3<G>& vector);

        template<typename G>
        friend Vector3<G> operator/(float scalar, const Vector3<G>& vector);

        template<typename G>
        friend Vector3<G> operator+(const Vector3<G>& vec1, const Vector3<G>& vec2);

        template<typename G>
        friend std::ostream& operator<<(std::ostream& out, const Vector3<G>& vec);

    private:
        T m_elements[3];

};

template<typename T>
Vector3<T>::Vector3(T x, T y, T z) {
    m_elements[0] = x;
    m_elements[1] = y;
    m_elements[2] = z;
}

template<typename T>
T& Vector3<T>::operator[](int index) {
    return m_elements[index];
}

template<typename T>
T Vector3<T>::operator[](int index) const {
    return m_elements[index];
}

template<typename T>
Vector3<T>::Vector3() {
    m_elements[0] = m_elements[1] = m_elements[2] = 0;
}

template<typename T>
Vector3<T> Vector3<T>::normalized() const {
    float magnitude = std::sqrt(m_elements[0] * m_elements[0]
                    + m_elements[1] * m_elements[1]
                    + m_elements[2] * m_elements[2]);

    return Vector3<T>(m_elements[0] / magnitude,
                      m_elements[1] / magnitude,
                      m_elements[2] / magnitude);
}

// Overloaded operators
// Output vector to stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vector3<T> &vec) {
    return stream << vec[0] << " " << vec[1] << " " << vec[2];
}

template<typename T>
Vector3<T> operator-(const Vector3<T>& first, const Vector3<T>& second) {
    return Vector3<T>(first[0] - second[0], first[1] - second[1], first[2] - second[2]);
}

template<typename T>
Vector3<T> operator/(float scalar, const Vector3<T>& vector) {
    return Vector3<T>(vector[0] / scalar, vector[1] / scalar, vector[2] / scalar);
}

template<typename T>
Vector3<T> operator*(float scalar, const Vector3<T>& vector) {
    return Vector3<T>(scalar * vector[0], scalar * vector[1], scalar * vector[2]);
}

template<typename T>
Vector3<T> operator+(const Vector3<T>& vec1, const Vector3<T>& vec2) {
    return Vector3<T>(vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]);
}


template<typename T>
Vector3<T> operator-(const Vector3<T>& vec) {
    return Vector3<T>(-vec[0], -vec[1], -vec[2]);
}

template<typename T>
T Vector3<T>::dot(Vector3<T> other) const {
    return this->m_elements[0] * other.m_elements[0]
        + this->m_elements[1] * other.m_elements[1]
        + this->m_elements[2] * other.m_elements[2];
}

#endif