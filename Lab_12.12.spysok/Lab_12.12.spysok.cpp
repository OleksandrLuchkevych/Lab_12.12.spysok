#include <iostream>

using namespace std;

struct Note {
    char surname[50];
    char name[50];
    char phoneNumber[20];
    int day;
    int month;
    int year;
    Note* next;
};

void addNote(Note*& head) {
    char surname[50], name[50], phoneNumber[20];
    int day, month, year;

    cout << "Enter surname: ";
    cin >> surname;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    cout << "Enter birthday (day month year): ";
    cin >> day >> month >> year;

    Note* newNote = new Note;

    int i;
    for (i = 0; surname[i] != '\0' && i < sizeof(newNote->surname) - 1; ++i) {
        newNote->surname[i] = surname[i];
    }
    newNote->surname[i] = '\0';

    for (i = 0; name[i] != '\0' && i < sizeof(newNote->name) - 1; ++i) {
        newNote->name[i] = name[i];
    }
    newNote->name[i] = '\0';

    for (i = 0; phoneNumber[i] != '\0' && i < sizeof(newNote->phoneNumber) - 1; ++i) {
        newNote->phoneNumber[i] = phoneNumber[i];
    }
    newNote->phoneNumber[i] = '\0';

    newNote->day = day;
    newNote->month = month;
    newNote->year = year;
    newNote->next = nullptr;

    if (head == nullptr) {
        head = newNote;
    }
    else {
        Note* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNote;
    }
}

int compareStrings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i]) {
        ++i;
    }
    return str1[i] - str2[i];
}

void printByMonth(Note* head, int month) {
    Note* current = head;
    bool found = false;

    cout << "Records for Month " << month << ":" << endl;

    while (current != nullptr) {
        if (current->month == month) {
            cout << "Surname: " << current->surname << endl;
            cout << "Name: " << current->name << endl;
            cout << "Phone Number: " << current->phoneNumber << endl;
            cout << "Birthday: " << current->day << "." << current->month << "." << current->year << endl;
            cout << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No records found for the specified month." << endl;
    }
}

void printAddressBook(Note* head) {
    Note* current = head;

    while (current != nullptr) {
        cout << "Surname: " << current->surname << endl;
        cout << "Name: " << current->name << endl;
        cout << "Phone Number: " << current->phoneNumber << endl;
        cout << "Birthday: " << current->day << "." << current->month << "." << current->year << endl;
        cout << endl;
        current = current->next;
    }
}

void sortAlphabetically(Note* head) {
    if (head == nullptr || head->next == nullptr) {
        return; // Немає потреби сортувати, якщо список порожній або містить лише один елемент
    }

    bool swapped;
    Note* current;
    Note* previous = nullptr;
    int iteration = 0;

    do {
        swapped = false;
        current = head;
        iteration++;

        while (current->next != nullptr) {
            Note* nextNode = current->next;

            if (compareStrings(current->surname, nextNode->surname) > 0) {
                if (previous != nullptr) {
                    previous->next = nextNode;
                }
                else {
                    head = nextNode;
                }

                current->next = nextNode->next;
                nextNode->next = current;
                swapped = true;
            }

            previous = current;
            current = nextNode;
        }
    } while (swapped);

    // Вивід після завершення сортування
    cout << "Printing the sorted address book:" << endl;
    printAddressBook(head);
}

int main() {
    Note* addressBook = nullptr;
    int numMonth;

    int choice;
    do {
        cout << "========== Menu ==========" << endl;
        cout << "1. Add Note" << endl;
        cout << "2. Sort Alphabetically" << endl;
        cout << "3. Search By Month" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            addNote(addressBook);
            break;
        }
        case 2:
        {
            sortAlphabetically(addressBook);
            break;
        }
        case 3: {
            cout << "Enter the month: ";
            cin >> numMonth;

            printByMonth(addressBook, numMonth);
            break;
        }
        case 4: {
            cout << "Exiting..." << endl;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    } while (choice != 4);

    return 0;
}
