/*
 * matrix.hpp
 *
 *  Created on: May 5, 2017
 *      Author: Mohammad Reza Mozaffari
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <iostream>
#include <stdio.h>
#include <cmath>

class Matrix
{
public:
	Matrix ();
	Matrix (int, int);
	Matrix (int, int, double**);
	Matrix (const Matrix&);
	~Matrix ();

	int get_rows ();
	int get_cols ();
	double member (const int, const int);

	double& operator()(const int, const int);
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const double);
	Matrix& operator/=(const double);

	friend Matrix operator+(const Matrix&, const Matrix&);
	friend Matrix operator-(const Matrix&, const Matrix&);
	friend Matrix operator*(const double, const Matrix&);
	friend Matrix operator*(const Matrix&, const double);
	friend Matrix operator*(const Matrix&, const Matrix&);

	void print ();
	double trace ();
	double trace (const Matrix&);
	Matrix transpose ();
	Matrix transpose (const Matrix&);

private:
	int rows, cols;
	double** element;
};

Matrix::Matrix ()
{
	rows = cols = 0;
	element = NULL;
}

Matrix::Matrix (int _rows, int _cols)
{
	rows =_rows; cols =_cols;
	element = new double * [rows];
	for(int i=0; i<rows; i++)
		element[i] = new double [cols];

	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			element[i][j] = 0.0;
}

Matrix::Matrix (int _rows, int _cols, double** _element)
{
	rows =_rows; cols =_cols;
	element = new double * [rows];
	for(int i=0; i<rows; i++)
		element[i] = new double [cols];

	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			element[i][j] = _element[i][j];
}

Matrix::Matrix (const Matrix& other)
{
	rows = other.rows;
	cols = other.cols;	
	element = new double * [rows];
	for(int i=0; i<rows; i++)
		element[i] = new double [cols];

	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			element[i][j] = other.element[i][j];
}

Matrix::~Matrix()
{
	for(int i=0; i<rows; i++)
		delete [] element[i];
	delete [] element;
}

int Matrix::get_rows ()
{
	return rows;
}

int Matrix::get_cols ()
{
	return cols;
}

double Matrix::member (const int i, const int j)
{
	return element[i][j];
}

double& Matrix::operator()(const int i, const int j)
{
	return element[i][j];
}

Matrix& Matrix::operator=(const Matrix& other)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<rows; j++)
			element[i][j] = other.element[i][j];

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<rows; j++)
			element[i][j] = element[i][j] + other.element[i][j];

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<rows; j++)
			element[i][j] = element[i][j] - other.element[i][j];

	return *this;
}

Matrix& Matrix::operator*=(const double scale)
{

	for(int i=0; i<rows; i++)
		for(int j=0; j<rows; j++)
			element[i][j] = element[i][j]*scale;

	return *this;
}

Matrix& Matrix::operator/=(const double scale)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<rows; j++)
			element[i][j] = element[i][j]/scale;

	return *this;
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
	Matrix C(A);
	return C+=B;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
	Matrix C(A);
	return C-=B;
}

Matrix operator*(const double scale, const Matrix& A)
{
	Matrix C(A);
	return C*=scale;
}

Matrix operator*(const Matrix& A, const double scale)
{
	Matrix C(A);
	return C*=scale;
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
	Matrix C(A.rows, B.cols);
	for(int i=0; i<C.rows; i++)
	{
		for(int j=0; j<C.cols; j++)
		{
			C.element[i][j] = 0.0;
			for(int k=0; k<A.cols; k++)
				C.element[i][j] = C.element[i][j] + A.element[i][k]*B.element[k][j];
		}
	}

	return C;
}

void Matrix::print ()
{
	for(int i=0; i<rows; i++)
	{
		printf("(");
		for(int j=0; j<(cols-1); j++)
			printf("%.8f, ", element[i][j]);
		printf("%.8f)\n", element[i][cols-1]);
	}
}

double Matrix::trace ()
{
	double _trace_ = 0.0;
	for(int i=0; i<rows; i++)
		_trace_ = _trace_ + element[i][i];

	return _trace_;
}

double Matrix::trace (const Matrix& A)
{
	double _trace_ = 0.0;
	for(int i=0; i<A.rows; i++)
		_trace_ = _trace_ + A.element[i][i];

	return _trace_;
}

Matrix Matrix::transpose ()
{
	Matrix C(rows, cols);
	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			C.element[i][j] = element[j][i];

	return C;
}

Matrix Matrix::transpose (const Matrix& A)
{
	Matrix C(A.rows, A.cols);
	for(int i=0; i<A.rows; i++)
		for(int j=0; j<A.cols; j++)
			C.element[i][j] = A.element[j][i];

	return C;
}

#endif /* Martix_HPP_ */

