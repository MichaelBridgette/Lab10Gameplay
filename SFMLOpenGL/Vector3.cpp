#include"Vector3.h"
#include<math.h>
//Vector3();
//Vector3(double x1, double y1, double z1);
//double Length();
//double LengthSquared();
//void Normalise();
//Vector3 operator+(Vector3 V2);
//Vector3 operator-(Vector3 V2);
//Vector3 operator*(Vector3 V2);
//Vector3 operator*(double k);
//double Negate();

MyVector3::MyVector3() {
	m_x = 0;
	m_y = 0;
	m_z = 0;
}
MyVector3::MyVector3(double x1, double y1, double z1)
{
	m_x = x1;
	m_y = y1;
	m_z = z1;
}
MyVector3::MyVector3(float x1, float y1, float z1)
{
	m_x = x1;
	m_y = y1;
	m_z = z1;
}

double MyVector3::Length()
{
	return (double) sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

double MyVector3::LengthSquared()
{
	return (m_x*m_x + m_y*m_y + m_z*m_z);
}

const double MyVector3::GetX()
{
	return m_x;
}

const double MyVector3::GetY()
{
	return m_y;
}

const double MyVector3::GetZ()
{
	return m_z;
}

 float MyVector3::GetXf()
{
	return (float)m_x;
}

 float MyVector3::GetYf()
{
	return (float)m_y;
}

 float MyVector3::GetZf()
{
	return (float)m_z;
}

void MyVector3::Normalise()
{
	if (MyVector3::Length() > 0)
	{
		double magnit = MyVector3::Length();
		m_x /= magnit;
		m_y /= magnit;
		m_z /= magnit;
	}
}
MyVector3 MyVector3::operator+(MyVector3 V2)
{
	return MyVector3(m_x+V2.m_x , m_y+V2.m_y, m_z+ V2.m_z);
}

MyVector3 MyVector3::operator-(MyVector3 V2)
{
	return MyVector3(m_x - V2.m_x, m_y - V2.m_y, m_z - V2.m_z);
}

MyVector3 MyVector3::operator*(MyVector3 V2)
{
	return MyVector3(m_x* V2.m_x, m_y*V2.m_y, m_z*V2.m_z);
}

MyVector3  MyVector3::operator*(double k)
{
	return MyVector3(m_x*k, m_y*k, m_z*k);
}

MyVector3 MyVector3::Negate()
{
	return MyVector3(-m_x, -m_y, -m_z);
}

std::string MyVector3::ToString()
{
	return "(" + std::to_string(m_x) + " , " + std::to_string(m_y) + " , " + std::to_string(m_z)+")";

}

double MyVector3::ConvertToDouble()
{
	return (m_x + m_y + m_z);
}