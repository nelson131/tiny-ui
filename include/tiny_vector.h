#ifndef TINY_VECTOR_H
#define TINY_VECTOR_H

#include <iostream>
#include <cmath>

class Vector {
    public:
    Vector();
    Vector(float x, float y);
    
    float x, y;

    Vector& add(const Vector& v);
    Vector& add(float x, float y);
    Vector get_added(const Vector& v);

    Vector& subtract(const Vector& v);
    Vector& subtract(float x, float y);
    Vector get_subtracted(const Vector& v);

    Vector& multiply(const Vector& v);
    Vector& multiply(float x, float y);
    Vector get_multiplied(const Vector& v);

    Vector& divide(const Vector& v);
    Vector& divide(float x, float y);
    Vector get_divided(const Vector& v);

    friend Vector& operator + (Vector v1, const Vector& other);
    friend Vector& operator - (Vector v1, const Vector& other);
    friend Vector& operator * (Vector v1, const Vector& other);
    friend Vector& operator / (Vector v1, const Vector& other);
    friend bool operator > (Vector v1, const Vector& other);

    size_t len();

};

#endif