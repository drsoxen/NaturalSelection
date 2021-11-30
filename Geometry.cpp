#include "Geometry.h"
#include <cstdlib>
#include <cmath>

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Vector2::pythagoreanDistance(Vector2 point)
{
    return sqrt((this->x - point.x)*(this->x - point.x) + (this->y - point.y)*(this->y - point.y));
}

double Vector2::manhattenDistance(Vector2 point)
{
    return abs(this->x - point.x) + abs(this->y - point.y);
}

bool operator==(const Vector2& lhs, const Vector2& rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Vector2& lhs, const Vector2& rhs) {
            return lhs.x != rhs.x && lhs.y != rhs.y;
}

bool operator<(const Vector2& lhs, const Vector2& rhs) {
            return lhs.x < rhs.x && lhs.y < rhs.y;
}

bool operator>(const Vector2& lhs, const Vector2& rhs) {
            return lhs.x > rhs.x && lhs.y > rhs.y;
}

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vector3::pythagoreanDistance(Vector3 point)
{
    return sqrt((this->x - point.x)*(this->x - point.x) + (this->y - point.y)*(this->y - point.y) + (this->z - point.z)*(this->z - point.z));
}

double Vector3::manhattenDistance(Vector3 point)
{
    return abs(this->x - point.x) + abs(this->y - point.y) + abs(this->z - point.z);
}

bool operator==(const Vector3& lhs, const Vector3& rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vector3& lhs, const Vector3& rhs) {
            return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z;
}

bool operator<(const Vector3& lhs, const Vector3& rhs) {
            return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z;
}

bool operator>(const Vector3& lhs, const Vector3& rhs) {
            return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z;
}








