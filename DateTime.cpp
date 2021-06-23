#include "DateTime.h"
#include <stdexcept>

uint64_t monthDays[] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

DateTime::DateTime(const uint64_t year, const uint64_t month, const uint64_t day, const uint64_t hour, const uint64_t minute, const uint64_t sec)
{
	if (year < 1970 || month > 12 || (day > monthDays[month + 1] - monthDays[month]) || hour > 23 || minute > 59 || sec > 59 || month == 0 || day == 0)
		throw std::invalid_argument("Invalid value entered");

	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = sec;
}
DateTime::DateTime(uint64_t time, bool isFileTime)
{
	time /= (isFileTime ? 10000000 : 1);
	second = time % 60;
	minute = (time / 60) % 60;
	hour = (time / 60 / 60) % 24;

	
	day = time / 86400;
	year = day / 365 + (isFileTime ? 1601 : 1970);
	while (year > 1970 && DateTime(year).GetUnixTime() > this->GetUnixTime()) year--;
	month = 1;
	day -= (year / 4) - (year / 100) + (year / 400) - (isFileTime ? 389 : 478) - (day % 365 < 60 && (year % 4) == 0 && (year % 100 != 0 || year % 400 == 0) ? 1 : 0);
	day = day % 365;
	(day == 0 ? day = 365 : 0);
	while (day > monthDays[month] + ((((year % 4) == 0 && (year % 400 == 0 || year % 100 != 0) && month > 2) ? 1 : 0))) month++;
	month--;
	if (((year % 4) == 0 && (year % 400 == 0 || year % 100 != 0) && day == 60)) month--;
	day -= monthDays[month];
}

DateTime& DateTime::SetYear(const uint64_t year)
{
	if (year < 1970)
		throw std::invalid_argument("Invalid value entered");

	this->year = year;

	return *this;
}
DateTime& DateTime::SetMonth(const uint64_t month)
{
	if (month > 12 || month == 0)
		throw std::invalid_argument("Invalid value entered");

	this->month = month;

	return *this;
}
DateTime& DateTime::SetDay(const uint64_t day)
{
	if(day > monthDays[month + 1] - monthDays[month] || day == 0)
		throw std::invalid_argument("Invalid value entered");

	this->day = day;

	return *this;
}
DateTime& DateTime::SetHour(const uint64_t hour)
{
	if(hour > 23)
		throw std::invalid_argument("Invalid value entered");

	this->hour = hour;

	return *this;
}
DateTime& DateTime::SetMinute(const uint64_t minute)
{
	if (minute > 23)
		throw std::invalid_argument("Invalid value entered");

	this->minute = minute;

	return *this;
}
DateTime& DateTime::SetSecond(const uint64_t second)
{
	if (second > 23)
		throw std::invalid_argument("Invalid value entered");

	this->second = second;

	return *this;
}
DateTime& DateTime::SetDataTime(const uint64_t year, const uint64_t month, const uint64_t day, const uint64_t hour, const uint64_t minute, const uint64_t sec)
{
	if (year < 1970 || month > 12 || (day > monthDays[month + 1] - monthDays[month]) || hour > 23 || minute > 59 || sec > 59 || month == 0 || day == 0)
		throw std::invalid_argument("Invalid value entered");

	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
    this->second = sec;

	return *this;
}
DateTime& DateTime::SetUnixFileTime(uint64_t time, bool isFileTime)
{
	time /= (isFileTime ? 10000000 : 1);
	second = time % 60;
	minute = (time / 60) % 60;
	hour = (time / 60 / 60) % 24;


	day = time / 86400;
	year = day / 365 + (isFileTime ? 1601 : 1970);
	while (year > 1970 && DateTime(year).GetUnixTime() > this->GetUnixTime()) year--;
	month = 1;
	day -= (year / 4) - (year / 100) + (year / 400) - (isFileTime ? 389 : 478) - (day % 365 < 60 && (year % 4) == 0 && (year % 100 != 0 || year % 400 == 0) ? 1 : 0);
	day = day % 365;
	(day == 0 ? day = 365 : 0);
	while (day > monthDays[month] + ((((year % 4) == 0 && (year % 400 == 0 || year % 100 != 0) && month > 2) ? 1 : 0))) month++;
	month--;
	if (((year % 4) == 0 && (year % 400 == 0 || year % 100 != 0) && day == 60)) month--;
	day -= monthDays[month];

	return *this;
}

uint64_t DateTime::GetFileTime() const
{
	return (((((year - 1601ull) * 365 + monthDays[month] + day + (year / 4) - (year / 100) + (year / 400) - 389 - ((monthDays[month] + day < 60 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0)) * 24 + hour) * 60 + minute) * 60 + second) * 10000000;
}
uint64_t DateTime::GetUnixTime() const
{
	return ((((year - 1970ull) * 365 + monthDays[month] + day + (year / 4) - (year / 100) + (year / 400) - 478 - ((monthDays[month] + day < 60 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0)) * 24 + hour) * 60 + minute) * 60 + second;
}

uint64_t DateTime::GetYear() const { return year; }
uint64_t DateTime::GetMonth() const { return month; }
uint64_t DateTime::GetDay() const { return day; }
uint64_t DateTime::GetHour() const { return hour; }
uint64_t DateTime::GetMinute() const { return minute; }
uint64_t DateTime::GetSecond() const { return second; }

void DateTime::PrintDateTime() const
{
	std::cout << *this;
}
void DateTime::ReadDateTime()
{
	std::cin >> *this;
}

DateTime& DateTime::operator=(const DateTime right)
{
	year = right.year;
	month = right.month;
	day = right.day;
	hour = right.day;
	minute = right.minute;
	second = right.second;

	return *this;
}
std::ostream& operator<<(std::ostream& left, const DateTime right)
{
	return left << "Date: " << right.year << "." << (right.month < 10 ? "0" : "") << right.month << "." << (right.day < 10 ? "0" : "") << right.day
		<< " Time: " << (right.hour < 10 ? "0" : "") << right.hour << ":" << (right.minute < 10 ? "0" : "") << right.minute << ":" << (right.second < 10 ? "0" : "") << right.second << '\n';;
}
std::istream& operator>>(std::istream& left, DateTime right)
{
	uint64_t year, month, day, hour, minute, second;
	while (left.peek() == ' ' || left.peek() == '\n') left.ignore(1);
	int count = 0;
	while ((left.peek() == 'D' || left.peek() == 'a' || left.peek() == 't' || left.peek() == 'e' || left.peek() == ':') && count < 5)
	{
		left.ignore(1);
		count++;
	}
	if (count != 5)
	{
		left.get();
		return left;
	}
	left >> year;
	left.ignore(1);
	left >> month;
	left.ignore(1);
	left >> day;

	while (left.peek() == ' ' || left.peek() == '\n') left.ignore(1);
	count = 0;
	while ((left.peek() == 'T' || left.peek() == 'i' || left.peek() == 'm' || left.peek() == 'e' || left.peek() == ':') && count < 5)
	{
		left.ignore(1);
		count++;
	}
	if (count != 5)
	{
		left.get();
		return left;
	}
	left >> hour;
	left.ignore(1);
	left >> minute;
	left.ignore(1);
	left >> second;

	right = DateTime(year, month, day, hour, minute, second);
	return left;
}
