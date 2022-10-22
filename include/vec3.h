#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

template<typename T>
class Vector3 {
    public:
        Vector3();
        Vector3(T x, T y, T z);

        T& operator[](int index);

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
Vector3<T>::Vector3() {
    m_elements[0] = m_elements[1] = m_elements[2] = 0;
}

#endif