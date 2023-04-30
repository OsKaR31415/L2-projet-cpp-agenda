#include <iostream>
#include <string>
#include <map>
#include "heure.hpp"
#include "date.hpp"

class Agenda {
    private:
        std::map<Date, std::map<Heure, std::string> > contenu;

    public:
        Agenda() {
        }

        /* Add an event into the angenda
         * Args:
         *     Date date: The date of the event.
         *     Heure heure: The time of the event.
         *     string description: The description (contents) of the event. */
        void add_event(Date date, Heure heure, std::string description) {
            contenu[date][heure] = description;
        }

        std::map<Heure, std::string> get_day(Date date) { return contenu[date]; }

        /* Show every event for a day 
         * Args:
         *     Date date: the date to list events of
         *     int count_IO: the Index Origin of the events counter. Defaults to 1.*/
        int show_day(Date date, int count_IO) {
            int counter = count_IO;
            std::cout << "┏━ " << date.to_string(); // show the day

            // initialize iterator for the current day
            std::map<Heure, std::string> day = contenu[date];
            std::map<Heure, std::string>::iterator it;
            // go through the days with the iterator
            for(it=day.begin(); it!=day.end(); ++it) {
                std::cout << "┃" << (it->first).to_string() << " => " << it->second << "  n°" << counter << std::endl;
                counter++;
            }
            return counter;
        }
        int show_day(Date date) {
            return show_day(date, 1);
        }


        void show() {
            int counter = 1;
            std::map<Date, std::map<Heure, std::string> >::iterator it;
            for (it=contenu.begin(); it!=contenu.end(); ++it) { // for every day of the agenda
                counter = show_day(it->first, counter); // show every event of the day
            }
        }


};



int main() {
    Agenda a;
    Date d1 = Date(25, 5, 2005);
    Date d2 = Date(26, 5, 2005);
    Date d3 = Date(27, 5, 2005);
    Heure h1 = Heure(9, 0);
    Heure h2 = Heure(13, 7);
    Heure h3 = Heure(22, 45);

    a.add_event(d2, h2, "organisation");
    a.add_event(d3, h2, "fatigue");
    a.add_event(d3, h3, "rangement");
    a.add_event(d2, h1, "réveil");
    a.add_event(d1, h1, "idée");
    a.add_event(d2, h3, "fête");

    a.show();
    return 0;
}


