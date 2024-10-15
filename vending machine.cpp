#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <ctime> // For scheduling

using namespace std;

// Data structures to store user details and inventory
unordered_map<string, string> users; // username -> password
unordered_map<string, int> inventory = {
    {"Paracetamol", 10},
    {"Ibuprofen", 15},
    {"Antacid", 8},
    {"Cough Syrup", 5},
    {"Antihistamine", 12}
};

// Threshold for low stock alerts
const int lowStockThreshold = 3;

// Function to clear the input buffer
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display the main menu
void displayMainMenu() {
    cout << "\nWelcome to the Med ATM (Medicine Vending Machine)\n";
    cout << "Please choose an option:\n";
    cout << "1. Enter medicines required\n";
    cout << "2. Upload a prescription\n";
    cout << "3. Consult a doctor\n";
    cout << "4. View Profile\n";
    cout << "5. Exit\n";
}

// Function to display delivery options
void displayDeliveryOptions() {
    cout << "\nChoose a delivery option:\n";
    cout << "1. Takeaway\n";
    cout << "2. Schedule online delivery\n";
}

// Function to display medicine categories
void displayMedicinesInventory() {
    cout << "\nAvailable medicines and stock:\n";
    int i = 1;
    for (const auto& item : inventory) {
        cout << i++ << ". " << item.first << " (Stock: " << item.second << ")\n";
    }
}

// Function to display payment options
void displayPaymentOptions() {
    cout << "\nSelect payment method:\n";
    cout << "1. Credit/Debit Card\n";
    cout << "2. UPI\n";
    cout << "3. QR Code Payment\n";
}

// Function to handle the payment process
void processPayment(int paymentChoice) {
    switch (paymentChoice) {
        case 1:
            cout << "Processing Credit/Debit Card payment...\n";
            cout << "Payment successful!\n";
            break;
        case 2:
            cout << "Processing UPI payment...\n";
            cout << "Payment successful!\n";
            break;
        case 3:
            cout << "Displaying QR code for payment...\n";
            cout << "Please scan the QR code to complete your payment.\n";
            cout << "Payment successful!\n";
            break;
        default:
            cout << "Invalid payment option.\n";
    }
}

// Function to ask if the user wants to continue
bool askToContinue() {
    char continueChoice;
    cout << "\nDo you want to return to the main menu? (y/n): ";
    cin >> continueChoice;
    return (continueChoice == 'y' || continueChoice == 'Y');
}

// Function to check if the selected medicine is in stock
bool processMedicineSelection(const string& medicineName) {
    if (inventory[medicineName] > 0) {
        inventory[medicineName]--;
        cout << medicineName << " is available. Dispensing...\n";
        
        // Check if the medicine needs restocking
        if (inventory[medicineName] <= lowStockThreshold) {
            cout << "Warning: " << medicineName << " is running low on stock.\n";
        }
        return true;
    } else {
        cout << medicineName << " is out of stock!\n";
        return false;
    }
}

// Function to schedule takeaway
void scheduleTakeaway() {
    int hour, minute;
    cout << "Enter the hour (24-hour format) for takeaway pickup: ";
    cin >> hour;
    cout << "Enter the minute: ";
    cin >> minute;
    cout << "Your takeaway has been scheduled for " << hour << ":" << (minute < 10 ? "0" : "") << minute << ".\n";
}

// User Authentication System
bool signup() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Please try logging in.\n";
        return false;
    }
    cout << "Enter a password: ";
    cin >> password;
    users[username] = password;
    cout << "Signup successful! You can now log in.\n";
    return true;
}

bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username] == password) {
        cout << "Login successful! Welcome " << username << ".\n";
        return true;
    } else {
        cout << "Invalid username or password.\n";
        return false;
    }
}

int main() {
    int choice;
    bool running = true, loggedIn = false;

    signup();
    cout << "Please log in to continue.\n";
    while (!loggedIn) {
        loggedIn = login();
    }

    while (running) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nEnter the medicines you need (choose from available inventory): ";
                displayMedicinesInventory();
                string medicine;
                cin >> medicine;
                if (processMedicineSelection(medicine)) {
                    displayDeliveryOptions();
                    int deliveryChoice;
                    cin >> deliveryChoice;
                    if (deliveryChoice == 1) {
                        cout << "You selected Takeaway.\n";
                        scheduleTakeaway();
                    } else if (deliveryChoice == 2) {
                        cout << "You selected Schedule online delivery.\n";
                    } else {
                        cout << "Invalid option.\n";
                    }

                    displayPaymentOptions();
                    int paymentChoice;
                    cin >> paymentChoice;
                    processPayment(paymentChoice);
                }
                break;
            }
            case 2: {
                cout << "\nUploading prescription...\n";
                cout << "Prescription uploaded successfully!\n";

                displayDeliveryOptions();
                int deliveryChoice;
                cin >> deliveryChoice;
                if (deliveryChoice == 1) {
                    cout << "You selected Takeaway.\n";
                    scheduleTakeaway();
                } else if (deliveryChoice == 2) {
                    cout << "You selected Schedule online delivery.\n";
                } else {
                    cout << "Invalid option.\n";
                }

                displayPaymentOptions();
                int paymentChoice;
                cin >> paymentChoice;
                processPayment(paymentChoice);
                break;
            }
            case 3: {
                cout << "\nConnecting to a doctor...\n";
                cout << "You are now in consultation with a doctor.\n";
                break;
            }
            case 4: {
                cout << "\nDisplaying your profile...\n";
                break;
            }
            case 5: {
                cout << "Exiting the system...\n";
                running = false;
                break;
            }
            default: {
                cout << "Invalid option. Please try again.\n";
            }
        }

        if (running && !askToContinue()) {
            running = false;
        }
    }

    return 0;
}
