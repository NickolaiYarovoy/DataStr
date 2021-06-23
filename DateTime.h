#ifndef DateTime_h
#define DateTime_h

#include <iostream>
#include <stdint.h>
#include "ADT.h"

class DateTime : public ADT
{
private:
	uint64_t year;
	uint64_t month;
	uint64_t day;
	uint16_t hour;
	uint16_t minute;
	uint16_t second;
public:
	DateTime(const uint64_t year = 1970, const uint64_t month = 1, const uint64_t day = 1, const uint64_t hour = 0, const uint64_t minute = 0, const uint64_t sec = 0);
	DateTime(uint64_t time, bool isFile);

	DateTime& SetYear(const uint64_t year);
	DateTime& SetMonth(const uint64_t month);
	DateTime& SetDay(const uint64_t day);
	DateTime& SetHour(const uint64_t hour);
	DateTime& SetMinute(const uint64_t minute);
	DateTime& SetSecond(const uint64_t second);
	DateTime& SetDataTime(const uint64_t year = 1970, const uint64_t month = 1, const uint64_t day = 1, const uint64_t hour = 0, const uint64_t minute = 0, const uint64_t sec = 0);
	DateTime& SetUnixFileTime(uint64_t time, bool isFileTime);

	uint64_t GetFileTime() const;
	uint64_t GetUnixTime() const;

	uint64_t GetYear() const;
	uint64_t GetMonth() const;
	uint64_t GetDay() const;
	uint64_t GetHour() const;
	uint64_t GetMinute() const;
	uint64_t GetSecond() const;

	void PrintDateTime() const;
	void ReadDateTime();

	DateTime& operator=(const DateTime right);
	friend std::ostream& operator<<(std::ostream& left, const DateTime right);
	friend std::istream& operator>>(std::istream& left, DateTime right);
};

#endif // DateTime_h
