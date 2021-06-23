#include "Matrix.h"

#include <iostream>
#include <stdexcept>

Matrix::Matrix() : matrix(nullptr), size(0), rows(0), cols(0) { }
Matrix::Matrix(const size_t row, const size_t col, const size_t size, const Element* elements)
{
	this->rows = row;
	this->cols = col;
	this->size = size;

	if (size == 0)
	{
		matrix = nullptr;
		return;
	}
	matrix = new Element[size];

	Element* sortElements = new Element[size];

	size_t minRow = rows + 1, minCol = cols + 1;
	double minValue = 0;
	for (size_t j = 0; j < size; j++)
	{
		if (minRow > elements[j].row || (minRow == elements[j].row && minCol > elements[j].column))
		{
			minRow = elements[j].row;
			minCol = elements[j].column;
			minValue = elements[j].value;
		}
	}

	sortElements[0] = { minRow, minCol, minValue };

	for (size_t i = 1; i < size; i++)
	{
		minRow = rows + 1, minCol = cols + 1;
		for (size_t j = 0; j < size; j++)
		{
			minRow = rows + 1, minCol = cols + 1;
			if ((minRow > elements[j].row || (minRow == elements[j].row && minCol > elements[j].column)) &&
				(elements[j].row > sortElements[i - 1].row || (elements[j].row == sortElements[i - 1].row && elements[j].column > sortElements[i - 1].column)))
			{
				minRow = elements[j].row;
				minCol = elements[j].column;
				minValue = elements[j].value;
			}
		}
		sortElements[i] = { minRow, minCol, minValue };
	}

	for (size_t i = 0; i < size; i++)
	{
		matrix[i].column = sortElements[i].column;
		matrix[i].row = sortElements[i].row;
		matrix[i].value = sortElements[i].value;
	}
}
Matrix::Matrix(const Matrix& matrix)
{
	rows = matrix.rows;
	cols = matrix.cols;
	size = matrix.size;
	this->matrix = new Element[size];

	for (size_t i = 0; i < size; i++)
	{
		this->matrix[i].column = matrix.matrix[i].column;
		this->matrix[i].row = matrix.matrix[i].row;
		this->matrix[i].value = matrix.matrix[i].value;
	}
}

Matrix Matrix::Transpose() const
{
	Matrix result = Matrix(cols, rows);
	result.size = size;
	result.matrix = new Element[size];

	size_t minRow = rows + 1, minCol = cols + 1;
	double minValue = 0;
	for (size_t j = 0; j < size; j++)
	{
		if (minCol > matrix[j].column || (minCol == matrix[j].column && minRow > matrix[j].row))
		{
			minRow = matrix[j].row;
			minCol = matrix[j].column;
			minValue = matrix[j].value;
		}
	}

	result.matrix[0] = { minCol, minRow, minValue };

	for (size_t i = 1; i < size; i++)
	{
		minRow = rows + 1, minCol = cols + 1;
		for (size_t j = 0; j < size; j++)
		{
			if (minCol > matrix[j].column || (minCol == matrix[j].column && minRow > matrix[j].row))
				if (matrix[j].column > result.matrix[i - 1].row || (matrix[j].column == result.matrix[i - 1].row && matrix[j].row > result.matrix[i - 1].column))
				{
					minRow = matrix[j].row;
					minCol = matrix[j].column;
					minValue = matrix[j].value;
				}

		}
		result.matrix[i] = { minCol, minRow, minValue };
	}

	return result;
}

Matrix Matrix::Add(const Element add)
{
	if (add.row > rows - 1 || add.column > cols - 1)
		throw std::invalid_argument("Index out of range");

	if (size == 0)
	{
		this->matrix = new Element[1];
		this->matrix[0] = add;
		size = 1;
		return *this;
	}

	size_t row = add.row, col = add.column;
	bool isAdd = false;
	Element* temp = new Element[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		if ((row < this->matrix[i].row || (row == this->matrix[i].row && col < this->matrix[i].column)) && !isAdd)
		{
			isAdd = true;
			temp[i] = add;
		}
		else temp[i] = this->matrix[i - isAdd];
	}
	if (isAdd) temp[size] = this->matrix[size - 1];
	else temp[size] = add;

	delete this->matrix;
	this->matrix = new Element[size + 1];
	size++;
	for (size_t i = 0; i < size; i++)
		this->matrix[i] = temp[i];
	delete[] temp;
	return *this;
}
Matrix Matrix::Add(const size_t row, const size_t column, const double value)
{
	return this->Add({ row, column, value });
}

Matrix Matrix::Remove(const Element remove)
{
	if (remove.row > rows || remove.column > cols)
		throw std::invalid_argument("Index out of range");

	bool valid = false;
	for (size_t i = 0; i < size; i++)
	{
		if (matrix[i].column == remove.column && matrix[i].row == remove.row) valid = true;
	}

	if (!valid)
		throw std::invalid_argument("Element doesn't exist");

	if (size == 1)
	{
		delete this->matrix;
		this->matrix = nullptr;
		size = 0;
		return *this;
	}

	Element* temp = new Element[size - 1];
	bool isRemove = false;
	for (size_t i = 0; i < size; i++)
	{
		if (matrix[i].column == remove.column && matrix[i].row == remove.row) isRemove = true;
		else temp[i - isRemove] = this->matrix[i];
	}

	delete this->matrix;
	this->matrix = new Element[size - 1];
	size--;
	for (size_t i = 0; i < size; i++) this->matrix[i] = temp[i];
	delete[] temp;
	return *this;
}
Matrix Matrix::Remove(const size_t row, size_t column)
{
	return this->Remove({ row, column, 0 });
}

Matrix Matrix::operator+(const Matrix right) const
{
	if (this->cols != right.cols || this->rows != right.rows)
		throw std::invalid_argument("Different sizes of matrices");

	Matrix result = Matrix(rows, cols, 0, nullptr);

	size_t i = 0, j = 0;
	while (i < this->size && j < right.size)
	{
		if (this->matrix[i].column == right.matrix[j].column && this->matrix[i].row == right.matrix[j].row)
		{
			result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value + right.matrix[j].value });
			i++;
			j++;
		}
		else if (this->matrix[i].row < right.matrix[j].row)
		{
			result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value });
			i++;
		}
		else if (this->matrix[i].row > right.matrix[j].row)
		{
			result.Add({ right.matrix[j].row, right.matrix[j].column, right.matrix[j].value });
			j++;
		}
		else if (this->matrix[i].column < right.matrix[j].column)
		{
			result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value });
			i++;
		}
		else
		{
			result.Add({ right.matrix[j].row, right.matrix[j].column, right.matrix[j].value });
			j++;
		}
	}

	while (i < this->size)
	{
		result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value });
		i++;
	}

	while (j < right.size)
	{
		result.Add({ right.matrix[j].row, right.matrix[j].column, right.matrix[j].value });
		j++;
	}

	return result;
}
Matrix Matrix::operator-(const Matrix right) const
{
	if (this->cols != right.cols || this->rows != right.rows)
		throw std::invalid_argument("Different sizes of matrices");

	Matrix result = Matrix(rows, cols, 0, nullptr);

	size_t i = 0, j = 0;
	while (i < this->size && j < right.size)
	{
		if (this->matrix[i].column == right.matrix[j].column && this->matrix[i].row == right.matrix[j].row)
		{
			result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value - right.matrix[j].value });
			i++;
			j++;
		}
		else if (this->matrix[i].row < right.matrix[j].row)
		{
			result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value });
			i++;
		}
		else if (this->matrix[i].row > right.matrix[j].row)
		{
			result.Add({ right.matrix[j].row, right.matrix[j].column, -right.matrix[j].value });
			j++;
		}
		else if (this->matrix[i].column < right.matrix[j].column)
		{
			result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value });
			i++;
		}
		else
		{
			result.Add({ right.matrix[j].row, right.matrix[j].column, -right.matrix[j].value });
			j++;
		}
	}

	while (i < this->size)
	{
		result.Add({ this->matrix[i].row, this->matrix[i].column, this->matrix[i].value });
		i++;
	}

	while (j < right.size)
	{
		result.Add({ right.matrix[j].row, right.matrix[j].column, right.matrix[j].value });
		j++;
	}

	return result;
}
Matrix Matrix::operator*(const Matrix right) const
{
	if (this->cols != right.rows)
		throw std::invalid_argument("The number of rows is not equal to the number of columns");

	Matrix result = Matrix(this->rows, right.cols, 0, nullptr);
	Matrix temp = right.Transpose();
	double now;
	size_t num1 = 0, num2 = 0, num = 0;
	for (size_t i = 0; i < this->rows; i++)
	{
		num2 = 0;
		num = num1;
		if (this->matrix[num1].row == i) {
			for (size_t j = 0; j < temp.rows; j++)
			{
				num1 = num;
				if (temp.matrix[num2].row == j)
				{
					now = 0;
					for (size_t t = 0; t < this->cols; t++)
					{
						if (this->matrix[num1].column == t && temp.matrix[num2].column == t)
						{
							now += this->matrix[num1].value * temp.matrix[num2].value;
							num1++;
							num2++;
						}
						else if (this->matrix[num1].column == t) num1++;
						else if (temp.matrix[num2].column == t) num2++;
					}
					if (now != 0) result.Add({ i, j, now });
				}
			}
		}
	}
	return result;
}

Matrix::~Matrix()
{
	delete matrix;
}

std::ostream& operator<<(std::ostream& left, const Matrix right)
{
	left << right.rows << " " << right.cols << "\n";

	size_t now = 0;
	if (right.size == 0)
	{
		for (size_t i = 0; i < right.rows; i++)
		{
			for (size_t j = 0; j < right.cols; j++)
			{
				std::cout << "0 ";
			}
			left << "\n";
		}
	}
	for (size_t i = 0; i < right.rows; i++)
	{
		for (size_t j = 0; j < right.cols; j++)
		{
			if (i == right.matrix[now].row && j == right.matrix[now].column)
			{
				left << right.matrix[now].value << " ";
				now++;
			}
			else left << "0 ";
		}
		left << "\n";
	}
	return left;
}
std::istream& operator>>(std::istream& left, Matrix right)
{
	std::cin >> right.rows >> right.cols >> right.size;
	if (right.size == 0)
	{
		right.matrix = nullptr;
		return left;
	}

	right.matrix = new Element[right.size];
	for (size_t i = 0; i < right.size; i++)
	{
		std::cin >> right.matrix[i].row >> right.matrix[i].column >> right.matrix[i].value;
	}

	return left;
}
