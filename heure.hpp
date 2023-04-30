#include <iostream>
#include <string>

class Heure {
    private:
        int hh;
        int mm;
    public:
        Heure(int h, int m) {
            set_hour(h, m);
        }

        ~Heure() {}

        /* Getter for hh (hours) */
        int get_hh() {return hh;}

        /* Setter for hh (hours)
         * Args:
         *     int h : The hour to set
         * Returns:
         *     int : 0 if everything went well, 1 if the given hour is invalid */
        int set_hh(int h) {
            if (0 <= h && h <= 24) {
                hh = h;
                return 0;
            } else {
                return 1;
            }
        }

        /* Getter for mm (minutes) */
        int get_mm() {return mm;}

        /* Setter for mm (minutes)
         * Args:
         *     int m : The minutes to set
         * Returns:
         *     int : 0 if everything went well, 1 if the given minute is invalid */
        int set_mm(int m) {
            if (0 <= m && m <= 60) {
                mm = m;
                return 0;
            } else {
                return 1;
            }
        }

        /* Setter for both attributes (hours and minutes)
         * Args:
         *     int h : The hours to set (new value for hh).
         *     int m : The minutes to set (new value for mm).
         * Returns:
         *     int : 0 if everything went well, 1 if the given hour is invalid.
         *           Note that, if 1 is returned, none of the attributes will be changed. */
        int set_hour(int h, int m) {
            int status, prev_hh;
            prev_hh = hh;
            status = set_hh(h);
            if (status != 0) {
                return 1;
            }
            status = set_mm(m);
            if (status != 0) {
                hh = prev_hh;  // make sure nothing has been modified
                return 1;
            }
            return 0;
        }

        std::string to_string() {
            return std::to_string(hh) + ":" + std::to_string(mm);
        }

    bool const operator== (const Heure& other) {
        return (hh == other.hh) && (mm == other.mm);
    }

    bool const operator!= (const Heure& other) {
        return (hh != other.hh) || (mm != other.mm);
    }

    bool const operator< (const Heure& other) {
        return (hh < other.hh) || (mm < other.mm);
    }

    bool const operator> (const Heure& other) {
        return (hh > other.hh) || (mm > other.hh);
    }

};





/* int main() { */
/*     /1* TESTS *1/ */
/*     /1* Heure matin = Heure(8, 30); *1/ */
/*     /1* std::cout << matin.to_string() << std::endl; *1/ */
/*     /1* matin.set_mm(70); *1/ */
/*     /1* matin.set_mm(-10); *1/ */
/*     /1* matin.set_hh(30); *1/ */
/*     /1* matin.set_hh(-10); *1/ */
/*     /1* std::cout << matin.to_string() << std::endl; *1/ */
/*     return 0; */
/* } */


