#include <iostream>
#include <string>
#include "heure.cpp"
#include "date.cpp"

class Agenda {
    private:
        std::map<Date, std::map<Heure, std::string>> contenu;

    public:
        Agenda() {
        }

        void add_event(Date date, Heure heure, string description) {
            contenu[date][heure] = description;
        }


}

int main() {
    Agenda a;
    a.add_event(Date(25, 05), Heure(22, 3), "test");
    a.show_events();

    return 0;
}


