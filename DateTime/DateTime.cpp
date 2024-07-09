#include <iostream>

class DateTime {
public:
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;

    DateTime() : DateTime(0, 1, 1, 0, 0, 0) {}
    DateTime(int y, int m, int d, int h, int min, int s)
        : year(y), month(m), day(d), hours(h), minutes(min), seconds(s) {}

    int getYear() { return year; }
    void setYear(int y) { year = y; }

    int getMonth()  { return month; }
    void setMonth(int m) { month = m; }

    int getDay()  { return day; }
    void setDay(int d) { day = d; }

    int getHours()  { return hours; }
    void setHours(int h) { hours = h; }

    int getMinutes()  { return minutes; }
    void setMinutes(int min) { minutes = min; }

    int getSeconds()  { return seconds; }
    void setSeconds(int sec) { seconds = sec; }

    DateTime operator+(const DateTime& d2) const {
        DateTime result = *this;

        long long this_seconds = this->toSeconds();
        long long d2_seconds = d2.toSeconds();

        long long diff_seconds = this_seconds + d2_seconds;


        result = result.fromSeconds(diff_seconds);

        return result;
    }
    DateTime operator-(const DateTime& d2) const {
        DateTime result = *this;

        long long this_seconds = this->toSeconds();
        long long d2_seconds = d2.toSeconds();

        long long diff_seconds = this_seconds - d2_seconds;


        result = result.fromSeconds(diff_seconds);

        return result;
    }
    bool operator<(const DateTime& d2) const {
        if (year < d2.year) return true;
        if (year > d2.year) return false;
        if (month < d2.month) return true;
        if (month > d2.month) return false;
        if (day < d2.day) return true;
        if (day > d2.day) return false;
        if (hours < d2.hours) return true;
        if (hours > d2.hours) return false;
        if (minutes < d2.minutes) return true;
        if (minutes > d2.minutes) return false;
        if (seconds < d2.seconds) return true;
        return false;
    }
private:
    long long toSeconds() const {
        long long total_seconds = 0;

        for (int i = 1970; i < year; ++i) {
            total_seconds += IsLeapYear(i) ? 366 * 24 * 60 * 60 : 365 * 24 * 60 * 60;
        }

        for (int i = 1; i < month; ++i) {
            total_seconds += DaysInMonth(i, year) * 24 * 60 * 60;
        }

        total_seconds += (day - 1) * 24 * 60 * 60;


        total_seconds += hours * 60 * 60 + minutes * 60 + seconds;

        return total_seconds;
    }
    DateTime fromSeconds(long long total_seconds) const {
        DateTime result;


        while (true) {
            int days_in_year = IsLeapYear(result.year) ? 366 : 365;
            if (total_seconds >= days_in_year * 24 * 60 * 60) {
                total_seconds -= days_in_year * 24 * 60 * 60;
                ++result.year;
            }
            else {
                break;
            }
        }


        result.month = 1;
        while (true) {
            int days_in_month = DaysInMonth(result.month, result.year);
            if (total_seconds >= days_in_month * 24 * 60 * 60) {
                total_seconds -= days_in_month * 24 * 60 * 60;
                ++result.month;
            }
            else {
                break;
            }
        }


        result.day = total_seconds / (24 * 60 * 60) + 1;
        total_seconds %= (24 * 60 * 60);


        result.hours = total_seconds / (60 * 60);
        total_seconds %= (60 * 60);
        result.minutes = total_seconds / 60;
        result.seconds = total_seconds % 60;

        return result;
    }

    bool IsLeapYear(int year) const {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }
    int DaysInMonth(int month, int year) const {
        static const int days_m[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && IsLeapYear(year)) {
            return 29;
        }
        return days_m[month - 1];
    }
};

int main() {
    DateTime date1(2024, 7, 9, 12, 30, 15);
    DateTime date2(2023, 5, 15, 10, 0, 0);

    DateTime date3 = date1 + date2;

    DateTime date4 = date1 - date2;
    return 0;
}
