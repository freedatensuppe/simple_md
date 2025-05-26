#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3D
{
   public:
    float x, y, z;

    Vector3D();
    Vector3D(float x_, float y_, float z_);

    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(float scalar) const;

    float    dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;

    float    magnitude() const;
    Vector3D normalized() const;

    void print() const;
};

#endif   // VECTOR3D_HPP
