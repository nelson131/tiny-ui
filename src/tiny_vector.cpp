#include "../include/tiny_vector.h"
#include <iostream>

Vector::Vector()
    : x(0), y(0) 
{
    
}

Vector::Vector(float x, float y)
    : x(x), y(y)
{

}

Vector& Vector::add(const Vector& v){
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector& Vector::add(float x, float y){
    this->x += x;
    this->x += y;
    return *this;
}

Vector Vector::get_added(const Vector& v){
    return Vector{this->x + v.x, this->y + v.y};
}


Vector& Vector::subtract(const Vector& v){
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector& Vector::subtract(float x, float y){
    this->x -= x;
    this->y -= y;
    return *this;
}

Vector Vector::get_subtracted(const Vector& v){
    return Vector{this->x - v.x, this->y - v.y};
}


Vector& Vector::multiply(const Vector& v){
    this->x *= v.x;
    this->y *= v.y;
    return *this;
}

Vector& Vector::multiply(float x, float y){
    this->x *= x;
    this->y *= y;
    return *this;
}

Vector Vector::get_multiplied(const Vector& v){
    return Vector{this->x *= v.x, this->y *= y};
}

Vector& Vector::divide(const Vector& v){
    if(v.x != 0 && v.y != 0){
        this->x /= v.x;
        this->y /= v.y;
    }

    return *this;
}

Vector& Vector::divide(float x, float y){
    if(x != 0 && y != 0){
        this->x /= x;
        this->y /= y;
    }

    return *this;
}

Vector Vector::get_divided(const Vector& v){
    if(v.x == 0 || v.y == 0){
        return *this;
    }
    return Vector{this->x / v.x, this->y / v.y};
}

Vector& operator + (Vector v1, const Vector& other){
    return v1.add(other);
}

Vector& operator - (Vector v1, const Vector& other){
    return v1.subtract(other);
}

Vector& operator * (Vector v1, const Vector& other){
    return v1.multiply(other);
}

Vector& operator / (Vector v1, const Vector& other){
    return v1.divide(other);
}

size_t Vector::len(){
    return sqrt(x * x + y * y);
}
