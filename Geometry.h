#pragma once

class Vector2 
{
    public:
    	double x;
        double y;

        Vector2();
        Vector2(double x, double y);
        double pythagoreanDistance(Vector2 podouble);
		double manhattenDistance(Vector2 podouble);

        friend bool operator==(const Vector2& lhs, const Vector2& rhs);
        friend bool operator!=(const Vector2& lhs, const Vector2& rhs);
        friend bool operator<(const Vector2& lhs, const Vector2& rhs);
        friend bool operator>(const Vector2& lhs, const Vector2& rhs);
}; 

class Vector3
{
    public:
    	double x;
        double y;
        double z;

        Vector3();
        Vector3(double x, double y, double z);
        double pythagoreanDistance(Vector3 podouble);
		double manhattenDistance(Vector3 podouble);

        friend bool operator==(const Vector3& lhs, const Vector3& rhs);
        friend bool operator!=(const Vector3& lhs, const Vector3& rhs);
        friend bool operator<(const Vector3& lhs, const Vector3& rhs);
        friend bool operator>(const Vector3& lhs, const Vector3& rhs);
}; 




