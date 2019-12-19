#pragma once
#include <random>
#include <string>
#include <iostream>
#include <assert.h>

class Matrix
{
public:
	Matrix()= default;
	Matrix(int row, int column, bool randomize);
	double randomize();
	Matrix operator*(Matrix& rhs)const;
	Matrix operator*(double& rhs)const;
	static Matrix Hadamard(Matrix& m1, Matrix& m2);
	Matrix operator-(double value)const;
	Matrix operator-(Matrix& rhs)const;
	Matrix& operator-=(double value);
	Matrix& operator-=(Matrix& rhs);
	Matrix transpose();
	std::vector<double> Vectorize();
	void SetValue(int row, int column, double value);
	double GetValue(int row, int column);
	int GetRow();
	int GetColumn();
	void Print();
private:
	int row;
	int column;
	std::vector<std::vector<double>> values;
};