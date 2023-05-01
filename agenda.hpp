#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "heure.hpp"
#include "date.hpp"
#define serial_separator ((std::string) " ")

Date get_Date_from_serial_event(std::string repr) {
    std::string serial_date;
    serial_date = repr.substr(0, repr.find(serial_separator));
    return deserialize_Date(serial_date);
}

Heure get_Heure_from_serial_event(std::string repr) {
    std::string serial_hour;
    repr.erase(0, repr.find(serial_separator) + serial_separator.length());
    serial_hour = repr.substr(0, repr.find(serial_separator));
    return deserialize_Heure(serial_hour);
}

std::string get_description_from_serial_event(std::string repr) {
    repr.erase(0, repr.find(serial_separator) + serial_separator.length());
    repr.erase(0, repr.find(serial_separator) + serial_separator.length());
    return repr;
}


class Agenda {
    private:
        std::map<Date, std::map<Heure, std::string> > contenu;

    public:
        Agenda() { }

        /* Get a day's events */
        std::map<Heure, std::string> get_day(Date date) { return contenu[date]; }

        /* Add an event into the angenda
         * Args:
         *     Date date: The date of the event.
         *     Heure hour: The time of the event.
         *     string description: The description (contents) of the event. */
        void add_event(Date date, Heure hour, std::string description) {
            contenu[date][hour] = description;
            std::cout << "adding : "<< date.to_string() << hour.to_string() << description << std::endl;
            std::cout << "i have : "<< contenu[date][hour] << std::endl;
            show(); // XXX
        }


        bool has_day(Date day) {
            return contenu.count(day) > 0;
        }

        bool has_event(Date day, Heure hour) {
            if ( !has_day(day) ) {
                return false;
            }
            return contenu[day].count(hour) > 0;
        }

        /* Show every event of a day
         * Args:
         *     Date date: the date to list events of
         *     int count_IO: the Index Origin of the events counter. Defaults to 1.*/
        int show_day(Date date, int count_IO) {
            int counter = count_IO;
            std::cout << "┏━ " << date.to_string() << "\n"; // show the day

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
            int tortus_counter = 1; // XXX
            std::map<Date, std::map<Heure, std::string> >::iterator it;
            // for every day of the agenda
            for (it=contenu.begin(); it!=contenu.end(); ++it) {
                std::cout << "counter : " << tortus_counter << std::endl;
                tortus_counter++;
                counter = show_day(it->first, counter); // show every event of the day
            }
        }

        /* Test if a day has no events (also true if the day is not at all in
         * the agenda's map) */
        bool day_is_empty(Date date) {
            return contenu.count(date) == 0 || contenu[date].empty();
        }

        /* Delete a day if and only if it contains no events 
         * return 0 if the day is still here (it wasn't empty), 1 if the day
         * has been removed or wasn't in the agenda */
        int delete_day_if_empty(Date date) {
            if ( day_is_empty(date) ) {
                contenu.erase(date);
                return 1;
            }
            return 0;
        }

        /* Delete a whole day from the agenda.
         * 1 if the day is found, 0 if not */
        int delete_day(Date date) {
            return contenu.erase(date);
        }

        /* Delete an event from the agend.
         * 1 if the event is found, 0 if not */
        int delete_event(Date date, Heure hour) {
            if ( !has_day(date) ) {
                return 0;
            }
            return contenu[date].erase(hour);
        }

        /* 1 if the event is found, 0 if not */
        int change_event_hour(Date date, Heure hour, Heure new_hour) {
            if ( !has_event(date, hour) ) {
                return 0;
            }
            std::string description = contenu[date][hour];
            delete_event(date, hour);
            add_event(date, new_hour, description);
            delete_day_if_empty(date);
            return 1;
        }

        int change_event_day(Date date, Heure hour, Date new_date) {
            if ( !has_event(date, hour) ) {
                return 0;
            }
            std::string description = contenu[date][hour];
            delete_event(date, hour);
            add_event(new_date, hour, description);
            delete_day_if_empty(date);
            return 1;
        }

        int shift_event_day(Date date, Heure hour, int day_shift) {
            Date new_date = date.day_shift(day_shift);
            return change_event_day(date, hour, new_date);
        }

        int show_event_at_index(int index) {
            int current_index = 0;
            // initialize iterator for the current day
            std::map<Date, std::map<Heure, std::string> > day = contenu;
            std::map<Date, std::map<Heure, std::string> >::iterator it;
            // go through the days with the iterator
            for(it=day.begin(); it!=day.end(); ++it) {
                // iterator for the current hour
                std::map<Heure, std::string> hour = contenu[it->first];
                std::map<Heure, std::string>::iterator sub_it;
                // go through hours
                for (sub_it=hour.begin(); sub_it!=hour.end(); ++sub_it) {
                    current_index++;
                    // when the iteration counter matches the index
                    if (current_index == index) {
                        std::cout << "n°" << index << " "
                                  << it->first.to_string()
                                  << " " << sub_it->first.to_string()
                                  << " => " << sub_it->second
                                  << std::endl;
                        return 1;
                    }
                }
            }
            std::cout << "n°" << index << " not found" << std::endl;
            return 0;
        }

        /* write the current agenda serialized into a file */
        void serialize_to_file(std::ofstream *file) {
            // initialize iterator for the current day
            std::map<Date, std::map<Heure, std::string> > day = contenu;
            std::map<Date, std::map<Heure, std::string> >::iterator it;
            // go through the days with the iterator
            for(it=day.begin(); it!=day.end(); ++it) {
                // iterator for the current hour
                std::map<Heure, std::string> hour = contenu[it->first];
                std::map<Heure, std::string>::iterator sub_it;
                // go through hours
                for (sub_it=hour.begin(); sub_it!=hour.end(); ++sub_it) {
                    *file << it->first.serialize() << serial_separator
                        << sub_it->first.serialize() << serial_separator
                        << sub_it->second << "\n";
                }
            }
        }

        /* serialize into a string
         * Can be a bit memory-hungry for big angendas
         * Anyways less optimized than the version that writes into a file
         * (because that version uses a stream). */
        std::string serialize() {
            std::string result = "";
            // initialize iterator for the current day
            std::map<Date, std::map<Heure, std::string> > day = contenu;
            std::map<Date, std::map<Heure, std::string> >::iterator it;
            // go through the days with the iterator
            for(it=day.begin(); it!=day.end(); ++it) {
                // iterator for the current hour
                std::map<Heure, std::string> hour = contenu[it->first];
                std::map<Heure, std::string>::iterator sub_it;
                // go through hours
                for (sub_it=hour.begin(); sub_it!=hour.end(); ++sub_it) {
                    result += it->first.serialize() + serial_separator
                            + sub_it->first.serialize() + serial_separator
                            + sub_it->second + "\n";
                }
            }
            return result;
        }


        /* deserialize the representation of an event, and insert it into the calendar */
        void add_serialized_event(std::string repr) {
            Date date = get_Date_from_serial_event(repr);
            Heure heure = get_Heure_from_serial_event(repr);
            std::string description = get_description_from_serial_event(repr);
            add_event(date, heure, description);
        }

        /* deserialize the representation of an event, and insert it into the calendar */
        void delete_serialized_event(std::string repr) {
            Date date = get_Date_from_serial_event(repr);
            Heure heure = get_Heure_from_serial_event(repr);
            delete_event(date, heure);
        }

};



void save_to_file(Agenda agenda, std::string filename) {
    std::ofstream file(filename);

    /* file << agenda.serialize(); */
    agenda.serialize_to_file(&file);

    file.close();
}

Agenda recover_from_file(std::string filename) {
    Agenda agenda;
    std::string line;
    std::ifstream file(filename);

    while (std::getline(file, line)) {
        agenda.add_serialized_event(line);
    }
    return agenda;
}


void sep() {
    std::cout << "\n━━━━━━━━━━━━━━━━━━━━\n";
}





/* int main() { */
/*     /1* Agenda a; *1/ */
/*     /1* Date d1 = Date(25, 5, 2005); *1/ */
/*     /1* Date d2 = Date(26, 5, 2005); *1/ */
/*     /1* Date d3 = Date(27, 5, 2005); *1/ */
/*     /1* Heure h1 = Heure(9, 0); *1/ */
/*     /1* Heure h2 = Heure(13, 7); *1/ */
/*     /1* Heure h3 = Heure(22, 45); *1/ */

/*     /1* a.add_event(d1, h1, "truc"); *1/ */
/*     /1* a.add_event(d2, h1, "réveil"); *1/ */
/*     /1* a.add_event(d2, h2, "organisation"); *1/ */
/*     /1* a.add_event(d2, h3, "fête"); *1/ */
/*     /1* a.add_event(d3, h2, "fatigue"); *1/ */
/*     /1* a.add_event(d3, h3, "rangement"); *1/ */

/*     /1* a.change_event_hour(d1, h1, h2); *1/ */

/*     /1* a.show(); *1/ */
/*     /1* sep(); *1/ */
/*     /1* save_to_file(a, "agenda.tsv"); *1/ */
/*     /1* Agenda b = recover_from_file("agenda.tsv"); *1/ */
/*     /1* b.show(); *1/ */

/*     return 0; */
/* } */






