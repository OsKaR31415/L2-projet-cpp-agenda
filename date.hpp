#include <iostream>
#include <string>
#define Date_delimiter ((std::string) "/")

class Date {
    private :
        int day;
        int month;
        int year;

        int months_length[12];

    public :

        Date(int i_day, int i_month, int i_year)
        {
            day = i_day;
            month = i_month;
            year = i_year;

            for (int i = 0; i < 12; i++) {
                months_length[i] = 30;
            }
            months_length[1] = get_february_length();
            months_length[3] = 30;
            months_length[5] = 30;
            months_length[8] = 30;
            months_length[10] = 30;

        }

        Date() { Date(25, 05, 2005); }

        ~Date() {}

        int get_day() {return day;}
        int get_month() {return month;}
        int get_year() {return year;}

        int set_day(int i_day) {
            if (i_day < 1 | i_day > 31) {return 0;}
            else
            {
                day = i_day;
                return 1;
            }
        }

        int set_month(int i_month) {
            if(i_month < 1 | i_month > 12) {return 0;}
            else
            {
                month = i_month;
                return 1;
            }
        }

        int set_year(int i_year) {
            if(i_year < 2000) {return 0;}
            else
            {
                year = i_year;
                return 1;
            }
        }

        std::string to_string() const {
            return std::to_string(day) + Date_delimiter + std::to_string(month) + Date_delimiter + std::to_string(year);
        }

        // test if the current year is leap
        bool leap_year() {
            if ( 0 == year % 400 ) {
                return false;
            } else if ( 0 == year % 100 ) {
                return true;
            } else {
                return 0 == year % 4;
            }
        }

        int get_february_length() {
            if ( leap_year() ) {
                return 29;
            } else {
                return 28;
            }
        }

        int get_month_length() {
            // `month-1` because arrays are 0-indexed while months are 1-indexed.
            return months_length[month-1];
        }

        /* Create a new Date, the next day of the current Date */
        Date next_day() {
            if (day >= get_month_length()) {
                if (month >= 12) {
                    return Date(1, 1, year+1);
                } else {
                    return Date(1, month+1, year);
                }
            } else {
                return Date(day+1, month, year);
            }
        }

        /* Create a new Date, the previous of the current Date */
        Date previous_day() {
            if (day <= 1) {
                if ( month <= 1 ) {
                    return Date(31, 12, year-1);
                } else {
                    return Date(months_length[month-1], month-1, year);
                }
            } else {
                return Date(day-1, month, year);
            }
        }

        /* Create a new Date, the current one shifted of `day_shift` days */
        Date day_shift(int day_shift) {
            Date final_date = *this;
            if ( day_shift > 0 ) {
                for (int i = day_shift; i > 0; i--) {
                    final_date = final_date.next_day();
                }
            } else if ( day_shift < 0 ) {
                for (int i = day_shift; i < 0; i++) {
                    final_date = final_date.previous_day();
                }
            } else { // day_shift == 0
                return *this;
            }
            return final_date;
        }


        /* serialize the object. Representation with the format dd/MM/yyyy */
        std::string serialize() const { return to_string(); }


        bool operator== (const Date& other) const {
            return (day   == other.day   &&
                    month == other.month &&
                    year  == other.year  );
        }

        bool operator!= (const Date& other) const {
            return (day   != other.day   ||
                    month != other.month ||
                    year  != other.year  );
        }

        bool operator< (const Date& other) const {
            if (year < other.year) {
                return true;
            }
            if (month < other.month) {
                return true;
            }
            return day < other.day;
        }

        bool operator> (const Date& other) const {
            if (year > other.year) {
                return true;
            }
            if (month > other.month) {
                return true;
            }
            return day > other.day;
        }

};

Date deserialize_Date(std::string repr) {
    std::string left, mid, right;
    left = repr.substr(0, repr.find(Date_delimiter));
    repr.erase(0, repr.find(Date_delimiter) + Date_delimiter.length());
    mid = repr.substr(0, repr.find(Date_delimiter));
    repr.erase(0, repr.find(Date_delimiter) + Date_delimiter.length());
    right = repr;
    int day = std::stoi(left);
    int month = std::stoi(mid);
    int year = std::stoi(right);
    return Date(day, month, year);
}


/* int main() { */
/*     return 0; */
/* } */
