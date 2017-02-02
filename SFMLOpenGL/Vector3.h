#pragma once
#include<iostream>
#include<string>

class MyVector3 {

private:
	double m_x;
	double m_y;
	double m_z;

public:
	MyVector3();
	MyVector3(double x1, double y1, double z1);
	MyVector3(float x1, float y1, float z1);
    const double GetX();
	const double GetY();
	const double GetZ();
	float GetXf();
	float GetYf();
	float GetZf();
	double Length();
	double LengthSquared();
	void Normalise();
	MyVector3 operator+(MyVector3 V2);
	MyVector3 operator-(MyVector3 V2);
	MyVector3 operator*(MyVector3 V2);
	double ConvertToDouble();
	MyVector3 operator*(double k);
	MyVector3 Negate();
	std::string ToString();


};