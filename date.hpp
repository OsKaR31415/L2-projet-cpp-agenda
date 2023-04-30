#include <iostream>
#include <string>

class Date {
    private :
        int day;
        int month;
        int year;

    public :

        Date(int i_day, int i_month, int i_year) 
        {
            day = i_day;
            month = i_month;
            year = i_year;
        }

        ~Date() {}

        int get_day() {return day;}
        int get_month() {return month;}
        int get_year() {return year;}

        int set_day(int i_day) 
        {
            if (i_day < 1 | i_day > 31) {return 0;} 
            else 
            {
                day = i_day;
                return 1;
            }
        }

        int set_month(int i_month) 
        {
            if(i_month < 1 | i_month > 12) {return 0;}
            else 
            {
                month = i_month;
                return 1;
            }
        }

        int set_year(int i_year) 
        {
            if(i_year < 2000) {return 0;}  // TODO : ajouter un moyen de bloquer sur les 2 années précédentes dans l'agenda.
            else
            {
                year = i_year;
                return 1;
            }
        }

        std::string toString() 
        {
            return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year) + "\n";
        }



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



/* int main() { */
/*     return 0; */
/* } */
