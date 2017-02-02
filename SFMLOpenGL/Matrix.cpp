#include"Matrix3.h"



Matrix3::Matrix3()
{
	m_A11 = 0.0f;
	m_A12 = 0.0f;
	m_A13 = 0.0f;
	m_A21 = 0.0f;
	m_A22 = 0.0f;
	m_A23 = 0.0f;
	m_A31 = 0.0f;
	m_A32 = 0.0f;
	m_A33 = 0.0f;
}

Matrix3::Matrix3(MyVector3 Row1, MyVector3 Row2, MyVector3 Row3)
{
	m_A11 = Row1.GetX();
	m_A12 = Row1.GetY();
	m_A13 = Row1.GetZ();
	m_A21 = Row2.GetX();
	m_A22 = Row2.GetY();
	m_A23 = Row2.GetZ();
	m_A31 = Row3.GetX();
	m_A32 = Row3.GetY();
	m_A33 = Row3.GetZ();
}
Matrix3::Matrix3(double A11, double A12, double A13, double A21, double A22, double A23, double A31, double A32, double A33)
{
	m_A11 = A11;
	m_A12 = A12;
	m_A13 = A13;
	m_A21 = A21;
	m_A22 = A22;
	m_A23 = A23;
	m_A31 = A31;
	m_A32 = A32;
	m_A33 = A33;

}
MyVector3 Matrix3::operator*(MyVector3 V1)
{
	float x = (m_A11* V1.GetXf() + m_A12*V1.GetYf() + m_A13*V1.GetZf()); 
	float y = (m_A21* V1.GetXf() + m_A22*V1.GetYf() + m_A23*V1.GetZf());
	float z = (m_A31* V1.GetXf() + m_A32*V1.GetYf() + m_A33*V1.GetZf());
	return MyVector3(x, y, z);
}
Matrix3 Matrix3::operator+(Matrix3 M2)
{
	return Matrix3(m_A11+M2.m_A11,
		m_A12+M2.m_A12,
		m_A13+M2.m_A13,
		m_A21+M2.m_A21,
		m_A22+M2.m_A22,
		m_A23+M2.m_A23,
		m_A31+M2.m_A31,
		m_A32+M2.m_A32,
		m_A33+M2.m_A33);
}
Matrix3 Matrix3::operator-(Matrix3 M2)
{
	return Matrix3(m_A11 - M2.m_A11,
		m_A12 - M2.m_A12,
		m_A13 - M2.m_A13,
		m_A21 - M2.m_A21,
		m_A22 - M2.m_A22,
		m_A23 - M2.m_A23,
		m_A31 - M2.m_A31,
		m_A32 - M2.m_A32,
		m_A33 - M2.m_A33);
}
Matrix3 Matrix3::operator*(double x)
{
	return Matrix3(m_A11 *x,
		m_A12 *x,
		m_A13 *x,
		m_A21 *x,
		m_A22 *x,
		m_A23 *x,
		m_A31 *x,
		m_A32 *x,
		m_A33 *x);
}
Matrix3 Matrix3::operator*(Matrix3 M2)
{
	Matrix3 answer =  Matrix3();
	
	answer.m_A11 = Matrix3::Row(0).ConvertToDouble()* M2.Column(0).ConvertToDouble();
	answer.m_A11 = Matrix3::Row(0).ConvertToDouble() * M2.Column(0).ConvertToDouble();
	answer.m_A12 = Matrix3::Row(0).ConvertToDouble() * M2.Column(1).ConvertToDouble();
	answer.m_A13 = Matrix3::Row(0).ConvertToDouble() * M2.Column(2).ConvertToDouble();

	answer.m_A21 = Matrix3::Row(1).ConvertToDouble() * M2.Column(0).ConvertToDouble();
	answer.m_A22 = Matrix3::Row(1).ConvertToDouble() * M2.Column(1).ConvertToDouble();
	answer.m_A23 = Matrix3::Row(1).ConvertToDouble() * M2.Column(2).ConvertToDouble();

	answer.m_A31 = Matrix3::Row(2).ConvertToDouble() * M2.Column(0).ConvertToDouble();
	answer.m_A32 = Matrix3::Row(2).ConvertToDouble() * M2.Column(1).ConvertToDouble();
	answer.m_A33 = Matrix3::Row(2).ConvertToDouble() * M2.Column(2).ConvertToDouble();


	return answer;
}

Matrix3 Matrix3::Transpose(Matrix3 M2)
{
	return Matrix3( M2.m_A11,
	    M2.m_A12,
		M2.m_A13,
		M2.m_A21,
		M2.m_A22,
		M2.m_A23,
		M2.m_A31,
		M2.m_A32,
		M2.m_A33);

}
double Matrix3::Determinant()
{
	 return m_A11 * m_A22 *m_A33 - m_A11 * m_A32 * m_A23 + m_A21 * m_A32 * m_A13 - m_A31 * m_A22 * m_A13 + m_A31 * m_A12 * m_A23 - m_A21 * m_A12 * m_A33;
}

MyVector3 Matrix3::Row(int i)
{
	switch (i)
	{
	case 0:
		return  MyVector3(m_A11, m_A12, m_A13);
	case 1:
		return  MyVector3(m_A21, m_A22, m_A23);
	case 2:
	default:
		return MyVector3(m_A31, m_A32, m_A33);
	}
}

MyVector3 Matrix3::Column(int i)
{
	switch (i)
	{
	case 0:
		return MyVector3(m_A11, m_A21, m_A31);
	case 1:
		return MyVector3(m_A12, m_A22, m_A32);
	case 2:
	default:
		return MyVector3(m_A13, m_A23, m_A33);
	}
}

Matrix3 Matrix3::Inverse()
{
	double det = Matrix3::Determinant();
	if (det == 0)
		return Matrix3();
	else
	{
		double scale = 1 / det;
		Matrix3 answer = Matrix3();
		answer.m_A11 = scale * (m_A22 * m_A33 - m_A23 * m_A32); // ei-fh
		answer.m_A12 = scale * (m_A13 * m_A32 - m_A12 * m_A33); // ch-bi
		answer.m_A13 = scale * (m_A12 * m_A23 - m_A13 * m_A22); // ch-bi

		answer.m_A21 = scale * (m_A23 * m_A31 - m_A21 * m_A33); // fg-di
		answer.m_A22 = scale * (m_A11 * m_A33 - m_A13 * m_A31); // ai-cg
		answer.m_A23 = scale * (m_A13 * m_A21 - m_A11 * m_A23); // cd-af


		answer.m_A31 = scale * (m_A21 * m_A32 - m_A22 * m_A31); // dh-eg
		answer.m_A32 = scale * (m_A12 * m_A31 - m_A11 * m_A32); // bg-ah
		answer.m_A33 = scale * (m_A11 * m_A22 - m_A12 * m_A21); // ae-bd

		return answer;
	}
}

Matrix3 Matrix3::Rotation(int angle)
{
	double radians = M_PI / 180 * angle;
	Matrix3 answer = Matrix3();
	answer.m_A11 = cos(radians);
	answer.m_A12 = sin(radians);
	answer.m_A13 = 0;
	answer.m_A21 = -sin(radians);
	answer.m_A22 = cos(radians);
	answer.m_A23 = 0;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = 1;

	return answer;
}

Matrix3 Matrix3::Translate(int dx, int dy)
{
	Matrix3 answer = Matrix3();
	answer.m_A11 = 1;
	answer.m_A12 = 0;
	answer.m_A13 = 0;
	answer.m_A21 = 0;
	answer.m_A22 = 1;
	answer.m_A23 = 0;
	answer.m_A31 = dx;
	answer.m_A32 = dy;
	answer.m_A33 = 1;

	return answer;
}

Matrix3 Matrix3::Scale(float dx, float dy)
{
	Matrix3 answer =  Matrix3();
	answer.m_A11 = dx / 100;
	answer.m_A12 = 0;
	answer.m_A13 = 0;
	answer.m_A21 = 0;
	answer.m_A22 = dy / 100;
	answer.m_A23 = 0;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = 1;

	return answer;
}


Matrix3 Matrix3::RotationX(float angle)
{
	double radians = M_PI / 180 * angle;
	Matrix3 answer = Matrix3();
	answer.m_A11 = 1;
	answer.m_A12 = 0;
	answer.m_A13 = 0;
	answer.m_A21 = 0;
	answer.m_A22 = cos(radians);
	answer.m_A23 = -sin(radians);
	answer.m_A31 = 0;
	answer.m_A32 = sin(radians);
	answer.m_A33 = cos(radians);

	return answer;
}
Matrix3 Matrix3::RotationY(float angle)
{

	double radians = (M_PI / 180) * angle;
	Matrix3 answer = Matrix3();

	answer.m_A11 = cos(radians);
	answer.m_A12 = 0;
	answer.m_A13 = sin(radians);
	answer.m_A21 = 0;
	answer.m_A22 = 1;
	answer.m_A23 = 0;
	answer.m_A31 = -sin(radians);
	answer.m_A32 = 0;
	answer.m_A33 = cos(radians);

	return answer;
}
Matrix3 Matrix3::RotationZ(float angle)
{
	double radians = (angle / 180) * M_PI;
	Matrix3 answer = Matrix3();
	answer.m_A11 = cos(radians);
	answer.m_A12 = -sin(radians);
	answer.m_A13 = 0;
	answer.m_A21 = sin(radians);
	answer.m_A22 = cos(radians);
	answer.m_A23 = 0;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = 1;

	return answer;
}

Matrix3 Matrix3::Scale3D(float dx)
{
	
	Matrix3 answer = Matrix3();
	answer.m_A11 = dx / 100;
	answer.m_A12 = 0;
	answer.m_A13 = 0;
	answer.m_A21 = 0;
	answer.m_A22 = dx / 100;
	answer.m_A23 = 0;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = dx / 100;

	return answer;
}