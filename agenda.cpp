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

        void add_event(Date date, Heure heure, std::string description) {
            contenu[date][heure] = description;
        }

        /* std::map<Heure, std::string> get_day(Date date) { */
        /*     return contenu[date]; */
        /* } */

        /* void show_day(Date date) { */
        /*     std::map<Heure, std::string> day = contenu[date]; */
        /*     std::map<Heure, std::string>::iterator it; */
        /*     for(it=day.begin(); it!=day.end(); ++it) { */
        /*         /1* std::cout << it->first << " => " << it->second << std::endl; *1/ */
        /*         std::cout << "=>"; */
        /*     } */
        /* } */

};



int main() {
    Agenda a;
    Date d = Date(25, 5, 2005);
    Heure h = Heure(22, 3);
    a.add_event(d, h, "test");

    /* a.show_day(d); */
    return 0;
}


