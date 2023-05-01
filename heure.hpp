#include <iostream>
#include <string>
#define Heure_delimiter ((std::string) ":")

class Heure {
    private:
        int hh;
        int mm;

    public:
        Heure(int h, int m) {
            set_hour(h, m);
        }

        Heure() { Heure(3, 45); }

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

        /* convert a time into a string representation of itself
         * Important : the strings are flushed right, so times before 12 are
         * preceded by a space to align the "h" in every time.
         * Examples:
         *     Heure(13, 7) gives "13h07"
         *     Heure(9, 0) gives " 9h00" */
        std::string to_string() const {
            std::string mm_str = std::to_string(mm);
            if (mm < 10) {
                mm_str = "0" + mm_str;
            }
            std::string hh_str = std::to_string(hh);
            if (hh < 10) {
                hh_str = " " + hh_str;
            }
            return hh_str + Heure_delimiter + mm_str;
        }

        std::string serialize() const {
            return std::to_string(hh) + Heure_delimiter + std::to_string(hh);
        }


    bool operator== (const Heure& other) const {
        return (hh == other.hh) && (mm == other.mm);
    }

    bool operator!= (const Heure& other) const {
        return (hh != other.hh) || (mm != other.mm);
    }

    bool operator< (const Heure& other) const {
        return (hh < other.hh) || (mm < other.mm);
    }

    bool operator> (const Heure& other) const {
        return (hh > other.hh) || (mm > other.hh);
    }

};


Heure deserialize_Heure(std::string repr) {
    std::string left, right;
    left = repr.substr(0, repr.find(Heure_delimiter));
    right = repr.substr(repr.find(Heure_delimiter)+Heure_delimiter.length(), repr.length());
    int hh = std::stoi(left);
    int mm = std::stoi(right);
    return Heure(hh, mm);
}



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


