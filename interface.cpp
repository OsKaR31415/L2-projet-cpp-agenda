#include <iostream>
#include <string>
#include "agenda.hpp"

void title() {
    std::cout << "\n"
        << "┏━┓┏━╸┏━┓                  \n"
        << "┗━┓┃  ┣━┛                  \n"
        << "┗━┛┗━╸╹                    \n"
        << "Super Calendar Productivity\n";
}


void actions_box() {
    std::cout << "\n\n"
        << "┏━━━━━━━━━━━━━━━━━━┓\n"
        << "┃ Choose action :  ┃\n"
        << "┃ 1 - add event    ┃\n"
        << "┃ 2 - remove event ┃\n"
        << "┃ 3 - modify event ┃\n"
        << "┃ 4 - show events  ┃\n"
        << "┃ 5 - save agenda  ┃\n"
        << "┃ 6 - load agenda  ┃\n"
        << "┗━━━━━━━━━━━━━━━━━━┛\n";
}

int input_action_num() {
    int action = -1;
    std::cout << "[enter action number] --> ";
    std::cin.clear();
    std::cin >> action;
    return action;
}


void modify_event(Agenda agenda, Date date, Heure heure) {
    std::cout << "\n\n"
        << "┓━━━━━━━━━━━━━━━━━━┏\n"
        << "┃ Choose action :  ┃\n"
        << "┃ 1 - change day   ┃\n"
        << "┃ 2 - shift day    ┃\n"
        << "┃ 3 - change time  ┃\n"
        << "┗━━━━━━━━━━━━━━━━━━┛\n";

    int action = input_action_num();

    Date new_date;
    Heure new_hour;
    int shift;
    std::string serial;

    switch (action) {

        case (1):
            std::cout << "Please type in the new day in the dd/MM/yyyy format :\n"
                << "[new day]> ";
            std::cin >> serial;
            new_date = deserialize_Date(serial);
            agenda.change_event_day(date, heure, new_date);
            break;

        case (2):
            std::cout << "Please enter how many days you want to shift the event.\n"
                << "Note : negative amounts mean a shift in the past.\n"
                << "[number of days of shift]> ";
            std::cin >> shift;
            agenda.shift_event_day(date, heure, shift);
            break;

        case (3):
            std::cout << "Please type in the new hour of the event (hh:mm format) :\n";
            std::cin >> serial;
            new_hour = deserialize_Heure(serial);
            agenda.change_event_hour(date, heure, new_hour);
            break;
    }

}

void do_action(Agenda &agenda, int action) {
    std::string serial_event;
    Date date = Date();
    Heure heure = Heure();
    switch (action) {

        case (1):
            std::cout << "ADDING EVENT\n"
                << "Please type in the event in the following format :\n"
                << "dd/MM/yyyy hh:mm description of the event\n"
                << "[new event]> " << std::flush;
            std::getline(std::cin, serial_event);
            std::getline(std::cin, serial_event);
            agenda.add_serialized_event(serial_event);
            break;

        case (2):
            std::cout << "REMOVING EVENT\n"
                << "Please type in the event's date and time in the following format :\n"
                << "dd/MM/yyyy hh:mm\n"
                << "[remove event]> ";
            std::cin >> serial_event;
            agenda.delete_serialized_event(serial_event);
            break;

        case (3):
            std::cout << "MODIFYING EVENT\n"
                << "Please type int the date and time of the event you want to modify int the following format :\n"
                << "dd/MM/yyyy hh:mm\n"
                << "[modify event]> ";
            std::cin >> serial_event;
            date = get_Date_from_serial_event(serial_event);
            heure = get_Heure_from_serial_event(serial_event);
            modify_event(agenda, date, heure);
            break;

        case (4):
            agenda.show();
            break;
        case (5):
            break;
        case (6):
            break;
    }
}

int main() {
    Agenda agenda = Agenda();

    title();

    actions_box();
    do_action(agenda, input_action_num());
    agenda.add_serialized_event("25/05/2005 13:45 anniv2");
    agenda.show();
    actions_box();
    do_action(agenda, input_action_num());
}



