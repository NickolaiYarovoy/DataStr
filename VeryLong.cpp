#include "VeryLong.h"

#include <iostream>
#include <stdexcept>

VeryLong::VeryLong(const int64_t num)
{
	if (num == 0)
	{
		number = "+0";
		return;
	}

	if (num > 0) number = "+";
	else number = "-";

	long long now = (num > 0 ? num : -num);
	while (now > 0)
	{
		number += now % 10 + '0';
		now /= 10;
	}
}
VeryLong::VeryLong(const VeryLong& num)
{
	number = num.number;
}
VeryLong::VeryLong(const std::string& num)
{
	if (num[0] != 45 && (num[0] > 57 || num[0] < 48))
		throw std::invalid_argument("There is no number");

	for (int i = num.length() - 1; i > 0; i--)
		if (num[0] > 57 || num[0] < 48)
			throw std::invalid_argument("There is no number");

	this->number = "";
	for (int i = num.length() - 1; i > 0; i--)
		this->number += num[i];

	if (num[0] == '-') this->number = '-' + this->number;
	else if (num[0] == '+') this->number = '+' + this->number;
	else this->number = '+' + this->number + num[0];

	for (size_t i = this->number.length() - 1; i > 1 && this->number[i] == '0'; i--) this->number.erase(i, 1);
	if (this->number.length() == 1) this->number += '0';
}

VeryLong::operator int64_t()
{
	if (number == "+0") return 0;

	int64_t now = (number[1] - '0'), stepNow = 10;

	size_t length = number.length();

	for (size_t i = 2; i < length && ((number[0] == '+' && now < 223372036854775808) || (number[0] == '-' && now < 223372036854775809)); i++)
	{
		now += (number[i] - '0') * stepNow;
		stepNow *= 10;
	}

	now *= (number[0] == '+' ? 1 : -1);

	return now;
}
VeryLong::operator std::string()
{
	std::string result = "";
	if (number[0] == '-') result = "-";
	for (int i = number.length() - 1; i > 0; i--)
	{
		result += number[i];
	}
	return result;
}

VeryLong VeryLong::operator+(const VeryLong right) const
{
	if (this->number[0] != right.number[0]) return *this - (-right);

	VeryLong result = (this->number.length() > right.number.length() ? *this : right);

	size_t lenght = (this->number.length() > right.number.length() ? right.number.length() : this->number.length()), next;
	bool isNext = false;
	for (size_t i = 1; i < lenght; i++)
	{
		next = this->number[i] + right.number[i] + isNext - '0' - '0';
		result.number[i] = next % 10 + '0';
		isNext = next / 10;
	}
	size_t bigLenght = (this->number.length() < right.number.length() ? right.number.length() : this->number.length());
	while (isNext)
	{
		if (lenght != bigLenght) {
			next = result.number[lenght] + isNext - '0';
			result.number[lenght] = next % 10 + '0';
			isNext = next / 10;
			lenght++;
		}
		else
		{
			result.number += '1';
			isNext = false;
		}
	}

	for (size_t i = result.number.length() - 1; i > 1 && result.number[i] == '0'; i--) result.number.erase(i, 1);
	if (result.number.length() == 1) result.number += '0';

	return result;
}
VeryLong VeryLong::operator-(const VeryLong right) const
{
	if (this->number[0] != right.number[0]) return *this + (-right);
	if (right.number.length() > this->number.length()) return -(right - *this);

	VeryLong result = *this;
	size_t lenght = right.number.length(), next;
	bool isNext = false;

	for (size_t i = 1; i < lenght; i++)
	{
		next = this->number[i] - right.number[i] - isNext;
		result.number[i] = (next + 10) % 10 + '0';
		isNext = next < 0;
	}
	if (isNext && this->number.length() == lenght) return -(right - *this);
	else
	{
		while (isNext)
		{
			next = this->number[lenght] - isNext - '0';
			result.number[lenght] = (next + 10) % 10 + '0';
			isNext = next < 0;
			lenght++;
		}
	}

	for (size_t i = result.number.length() - 1; i > 1 && result.number[i] == '0'; i--) result.number.erase(i, 1);
	if (result.number.length() == 1) result.number += '0';

	return result;
}
VeryLong VeryLong::operator*(const VeryLong right) const
{
	VeryLong result = 0;
	VeryLong count1, count2;
	count1.number = count2.number = "";
	size_t length1 = this->number.length(), length2 = right.number.length();
	char nextChar = 0;
	VeryLong now;
	for (size_t i = 1; i < length1; i++)
	{
		nextChar = 0;
		count2.number = "";
		for (size_t j = 1; j < length2; j++)
		{
			now.number = '+' + count1.number + count2.number + (char)((nextChar + (this->number[i] - '0') * (right.number[j] - '0')) % 10 + '0');
			nextChar = (nextChar + (this->number[i] - '0') * (right.number[j] - '0')) / 10;
			result = result + now;
			count2.number += "0";
		}
		now.number = '+' + count1.number + count2.number + (char)(nextChar + '0');
		result = result + now;
		count1.number += "0";
	}
	if (this->number[0] != right.number[0]) result = -result;

	for (size_t i = result.number.length() - 1; i > 1 && result.number[i] == '0'; i--) result.number.erase(i, 1);
	if (result.number.length() == 1) result.number += '0';

	return result;
}
VeryLong VeryLong::operator/(const VeryLong right) const
{
	if (right == 0)
		throw std::invalid_argument("Divide by zero");

	VeryLong now = 1, bigNow = 1, del = (this->number[0] == '+' ? *this : -*this), result = 0;
	while (result * right < del && bigNow != 0)
	{
		now = 1;
		while ((result + now) * right < del)now = now * 10;
		(now.number.length() > 2 ? now.number.erase(1, 1) : now.number);
		bigNow = now;
		while ((result + bigNow) * right < del)	bigNow = bigNow + now;
		bigNow = bigNow - now;
		result = result + bigNow;
	}
	if (this->number[0] != right.number[0]) result = -result;

	for (size_t i = result.number.length() - 1; i > 1 && result.number[i] == '0'; i--) result.number.erase(i, 1);
	if (result.number.length() == 1) result.number += '0';

	return result;
}

VeryLong VeryLong::operator+=(const VeryLong right)
{
	*this = *this + right;
	return *this;
}
VeryLong VeryLong::operator-=(const VeryLong right)
{
	*this = *this - right;
	return *this;
}
VeryLong VeryLong::operator*=(const VeryLong right)
{
	*this = *this * right;
	return *this;
}
VeryLong VeryLong::operator/=(const VeryLong right)
{
	*this = *this / right;
	return *this;
}



VeryLong VeryLong::operator-() const
{
	VeryLong now = *this;
	now.number[0] = (number[0] == '+' ? '-' : '+');
	return now;
}
VeryLong VeryLong::operator=(const VeryLong right)
{
	this->number = right.number;
	return *this;
}

bool operator<(const VeryLong left, const VeryLong right)
{
	if (left.number.length() < right.number.length()) return true;
	else if (left.number.length() > right.number.length()) return false;

	for (size_t i = left.number.length() - 1; i > 0; i--)
	{
		if (left.number[i] > right.number[i]) return false;
		else if (left.number[i] < right.number[i]) return true;
	}
	return false;
}
bool operator>(const VeryLong left, const VeryLong right)
{
	if (left.number.length() > right.number.length()) return true;
	else if (left.number.length() < right.number.length()) return false;

	for (size_t i = left.number.length() - 1; i > 0; i--)
	{
		if (left.number[i] < right.number[i]) return false;
		else if (left.number[i] > right.number[i]) return true;
	}
	return false;
}
bool operator==(const VeryLong left, const VeryLong right)
{
	return left.number == right.number;
}
bool operator!=(const VeryLong left, const VeryLong right)
{
	return !(left.number == right.number);
}
bool operator<=(const VeryLong left, const VeryLong right)
{
	if (left.number.length() < right.number.length()) return true;
	else if (left.number.length() > right.number.length()) return false;

	for (size_t i = left.number.length() - 1; i > 0; i--)
	{
		if (left.number[i] > right.number[i]) return false;
		else if (left.number[i] < right.number[i]) return true;
	}
	return true;
}
bool operator>=(const VeryLong left, const VeryLong right)
{
	if (left.number.length() > right.number.length()) return true;
	else if (left.number.length() < right.number.length()) return false;

	for (size_t i = left.number.length() - 1; i > 0; i--)
	{
		if (left.number[i] > right.number[i]) return false;
		else if (left.number[i] < right.number[i]) return true;
	}
	return true;
}

std::ostream& operator<<(std::ostream& left, const VeryLong right)
{
	if (right.number[0] == '-') left << '-';
	for (size_t i = right.number.length() - 1; i >= 1; i--) left << right.number[i];
	return left;
}
std::istream& operator>>(std::istream& left, VeryLong right)
{
	while (left.peek() == ' ' || left.peek() == '\n') left.ignore(1);
	bool isNeg = false;
	while (left.peek() == '-' || left.peek() == '+')
	{
		isNeg = (left.peek() == '-' || !isNeg || isNeg);
		left.ignore(1);
	}
	right.number = "";
	while (left.peek() >= '0' && left.peek() <= '9')
		right.number = (char)left.peek() + right.number;

	right.number = (isNeg ? '+' : '-') + right.number;
	for (size_t i = right.number.length() - 1; i > 1 && right.number[i] == '0'; i--) right.number.erase(i, 1);
	if (right.number.length() == 1) right.number += '0';

	return left;
}