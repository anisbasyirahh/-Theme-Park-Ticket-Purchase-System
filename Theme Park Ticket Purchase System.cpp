#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

// Visitor structure
struct Visitor {
    string name;
    int age;
    string contactInfo;
    int ticketsPurchased;
    string citizenship;
    double totalCost;
};

// Function 
void addVisitor(vector<Visitor>& visitors);
int countVisitors(const vector<Visitor>& visitors);
void displayPurchaseSummary(const vector<Visitor>& visitors);
void saveVisitors(const vector<Visitor>& visitors, const string& filename);
void displayMenu();
double calculateTicketCost(int age, const string& citizenship, int ticketsPurchased);

int main() {
    vector<Visitor> visitors;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addVisitor(visitors);
                break;
            case 2: {
                int visitorCount = countVisitors(visitors);
                cout << "Total number of visitors: " << visitorCount << "\n\n";
                break;
            }
            case 3:
                displayPurchaseSummary(visitors);
                break;
            case 4:
                saveVisitors(visitors, "visitors.txt");
                cout << "Visitors saved to file.\n\n";
                break;
            case 0:
                cout << "Exiting program.\n\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n\n";
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function to display the menu
void displayMenu() {
    cout << "Theme Park Ticket Purchase System Menu:\n";
    cout << "1. Add Visitor\n";
    cout << "2. Count Visitors\n";
    cout << "3. Purchase Summary\n";
    cout << "4. Save Visitors to File\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

// Function to add a new visitor purchase
void addVisitor(vector<Visitor>& visitors) {
    Visitor visitor;
    cout << "Enter visitor name: ";
    getline(cin, visitor.name);
    cout << "Enter visitor age: ";
    cin >> visitor.age;
    cin.ignore();
    cout << "Enter visitor contact info: ";
    getline(cin, visitor.contactInfo);
    cout << "Is the visitor a local citizen? (Y/N): ";
    char citizenshipOption;
    cin >> citizenshipOption;
    cin.ignore();
    if (citizenshipOption == 'Y' || citizenshipOption == 'y') {
        visitor.citizenship = "local";
    } else if (citizenshipOption == 'N' || citizenshipOption == 'n') {
        visitor.citizenship = "non-local";
    } else {
        cout << "Invalid option. Assuming non-local citizenship.\n";
        visitor.citizenship = "non-local";
    }
    cout << "Enter number of tickets to purchase: ";
    cin >> visitor.ticketsPurchased;
    cin.ignore();

    visitor.totalCost = calculateTicketCost(visitor.age, visitor.citizenship, visitor.ticketsPurchased);
    visitors.push_back(visitor);
    cout << "Details added successfully. Total cost: RM" << visitor.totalCost << "\n\n";
}

// Function to count the number of visitors
int countVisitors(const vector<Visitor>& visitors) {
    return visitors.size();
}

// Function to display the purchase summary
void displayPurchaseSummary(const vector<Visitor>& visitors) {
    for (const auto& visitor : visitors) {
        cout << "Name: " << visitor.name << "\n";
        cout << "Age: " << visitor.age << "\n";
        cout << "Contact Info: " << visitor.contactInfo << "\n";
        cout << "Citizenship: " << visitor.citizenship << "\n";
        cout << "Tickets Purchased: " << visitor.ticketsPurchased << "\n";
        cout << "Total Cost: RM" << visitor.totalCost << "\n";
        cout << "------------------------------\n\n";
    }
}

// Function to save visitors to a text file
void saveVisitors(const vector<Visitor>& visitors, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& visitor : visitors) {
            file << visitor.name << " " << visitor.age << " " << visitor.contactInfo << " "
                 << visitor.citizenship << " " << visitor.ticketsPurchased << " " << visitor.totalCost << "\n";
        }
        file.close();
    } else {
        cerr << "Unable to open file " << filename << "\n";
    }
}

// Function to calculate ticket cost based on age and citizenship
double calculateTicketCost(int age, const string& citizenship, int ticketsPurchased) {
    double ticketPrice;
    if (citizenship == "local") {
        if (age <= 12) {
            ticketPrice = 125.0;
        } else {
            ticketPrice = 150.0;
        }
    } else { // assuming non-local or foreign
        if (age <= 12) {
            ticketPrice = 150.0;
        } else {
            ticketPrice = 200.0;
        }
    }
    return ticketPrice * ticketsPurchased;
}

