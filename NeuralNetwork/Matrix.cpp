#include "Matrix.h"
#include <assert.h>

Matrix::Matrix(int row, int column, bool randomize)
	:
	row(row),
	column(column)
{
	for (int i = 0; i < row; i++)
	{
		std::vector<double> r;
		for (int j = 0; j < column; j++)
		{
			double val = 0.00;
			if (randomize)
			{
				val = this->randomize();
			}
			r.emplace_back(val);
		}
		values.emplace_back(r);
	}
}

double Matrix::randomize()
{
	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_real_distribution<> Dist(0, 1);

	return Dist(rng);
}

Matrix Matrix::operator*(Matrix& rhs) const
{
	assert(column == rhs.row);
	Matrix c = Matrix(row, rhs.column, false);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < rhs.column; j++)
		{ 
			double sum = 0.00;
			for (int k = 0; k < rhs.row; k++)
			{
				sum += values.at(i).at(k) * rhs.values.at(k).at(j);
			}
			c.SetValue(i, j, sum);
			sum = 0.00;
		}
	}
	return c;
}

Matrix Matrix::Hadamard(Matrix& m1, Matrix& m2)
{
	assert(m1.row == m2.row && m1.column == m2.column);
	Matrix c = Matrix(m1.row, m1.column, false);
	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m1.column; j++)
		{
			c.SetValue(i, j, m1.GetValue(i, j) * m2.GetValue(i, j));
		}
	}

	return c;
}

Matrix Matrix::operator-(double value) const
{
	Matrix c = Matrix(row, column, false);
	for (int i = 0; i < row; i++)
	{
		double difference = 0.00;
		for (int j = 0; j < column; j++)
		{
			difference = values.at(i).at(j) - value;
			c.SetValue(i, j, difference);
		}
	}
	return c;
}

Matrix Matrix::operator-(Matrix& rhs) const
{
	assert(row == rhs.row && 
		column == rhs.column);
	Matrix c = Matrix(row, column, false);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			double d = values.at(i).at(j) - rhs.values.at(i).at(j);
			c.SetValue(i, j, d);
		}
	}
	return c;
}

Matrix& Matrix::operator-=(double value)
{
	return *this = *this - value;
}

Matrix& Matrix::operator-=(Matrix& rhs)
{
	assert(row == rhs.row && column == rhs.column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			double d = this->values.at(i).at(j) - rhs.values.at(i).at(j);
			this->SetValue(i, j, d);
		}
	}
	return *this;
}

Matrix Matrix::transpose()
{
	Matrix c = Matrix(column, row, false);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			c.SetValue(j, i, values.at(i).at(j));
		}
	}
	return c;
}

std::vector<double> Matrix::Vectorize()
{
	std::vector<double> c;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			c.emplace_back(values.at(i).at(j));
		}
	}
	return c;
}

void Matrix::SetValue(int row, int column, double value)
{
	values.at(row).at(column) = value;
}

double Matrix::GetValue(int row, int column)
{
	return values.at(row).at(column);
}

int Matrix::GetRow()
{
	return row;
}

int Matrix::GetColumn()
{
	return column;
}

void Matrix::Print()
{
	std::cout << "Matrix :" << std::endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			std::cout << values.at(i).at(j) << "\t \t";
		}
		std::cout << std::endl;
	}
}
