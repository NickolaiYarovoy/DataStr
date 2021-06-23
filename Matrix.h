#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include "ADT.h"

struct Element
{
	size_t row;
	size_t column;
	double value;
};

class Matrix : public ADT
{
private:
	Element* matrix;
	size_t size;
	size_t rows;
	size_t cols;
public:
	Matrix();
	Matrix(const size_t rows, const size_t cols, const size_t size = 0, const Element* elements = nullptr);
	Matrix(const Matrix& matrix);

	~Matrix();

	Matrix Transpose() const;

	Matrix Add(const Element add);
	Matrix Add(const size_t row, const size_t column, const double value);
	Matrix Remove(const Element remove);
	Matrix Remove(const size_t row, const size_t column);

	Matrix operator+(const Matrix right) const;
	Matrix operator-(const Matrix right) const;
	Matrix operator*(const Matrix right) const;

	friend std::ostream& operator<<(std::ostream& left, const Matrix right);
	friend std::istream& operator>>(std::istream& left, const Matrix right);
};

#endif // Matrix_h
