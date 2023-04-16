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

        void show_events() {
            std::map<Date, std::map<Heure, std::string>>::iterator it;
            for (it = contenu.begin(); it != contenu.end(); ++it) {
                std::map<Heure,std::string>::iterator subit;
                for(subit = contenu.begin(); it != contenu.end; ++subit) {
                    cout << it->first << "->" << it->second << "->" << subit->first << "->" << subit->second << std::endl;
                }
            }
        }
}

int main() {
    Agenda a;
    a.add_event(Date(25, 05), Heure(22, 3), "test");
    a.show_events();

    return 0;
}


