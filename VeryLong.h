#ifndef VeryLong_h
#define VeryLong_h

#include <string>
#include "ADT.h"

class VeryLong : public ADT
{
private:
	std::string number;
public:
	VeryLong(const int64_t num = 0);
	explicit VeryLong(const std::string& num);
	VeryLong(const VeryLong& num);

	explicit operator int64_t();
	explicit operator std::string();

	VeryLong operator+(const VeryLong right) const;
	VeryLong operator-(const VeryLong right) const;
	VeryLong operator*(const VeryLong right) const;
	VeryLong operator/(const VeryLong right) const;

	VeryLong operator+=(const VeryLong right);
	VeryLong operator-=(const VeryLong right);
	VeryLong operator*=(const VeryLong right);
	VeryLong operator/=(const VeryLong right);

	VeryLong operator-() const;
	VeryLong operator=(const VeryLong right);

	friend bool operator<(const VeryLong left, const VeryLong right);
	friend bool operator>(const VeryLong left, const VeryLong right);
	friend bool operator==(const VeryLong left, const VeryLong right);
	friend bool operator!=(const VeryLong left, const VeryLong right);
	friend bool operator<=(const VeryLong left, const VeryLong right);
	friend bool operator>=(const VeryLong left, const VeryLong right);

	friend std::ostream& operator<<(std::ostream& left, const VeryLong right);
	friend std::istream& operator>>(std::istream& left, VeryLong right);
};

#endif //VeryLong_h