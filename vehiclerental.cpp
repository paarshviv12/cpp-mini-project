#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Vehicle {
public:
    string model;
    float rentPerDay;
    bool available;

    Vehicle() {
        available = true;
    }

    void input() {
        cout << "Enter Model Name: ";
        getline(cin, model);

        cout << "Enter Rent per Day: ";
        cin >> rentPerDay;
    }

    void display(int index) {
        cout << index << ". " << model
             << " | Rs." << rentPerDay
             << " | " << (available ? "Available" : "Rented") << endl;
    }
};

class Car : public Vehicle {
public:
    float calculateRent(int days) {
        return rentPerDay * days;
    }
};

class Bike : public Vehicle {
public:
    float calculateRent(int days) {
        return rentPerDay * days;
    }
};

class UserAuth
{
public:
    void registerUser()
    {
        string username, password;
        ofstream file("users.txt");

        cout << "Create Username: ";
        cin >> username;
        cout << "Create Password: ";
        cin >> password;

        file << username << " " << password;
        file.close();

        cout << "\nRegistration Successful!\n";
    }

    bool loginUser()
    {
        string u, p;
        string fileUser, filePass;
        ifstream file("users.txt");

        if (!file)
        {
            cout << "No user registered.\n";
            return false;
        }

        file >> fileUser >> filePass;
        file.close();

        cout << "\nLogin\n";
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        if (u == fileUser && p == filePass)
        {
            cout << "\nLogin Successful!\n";
            return true;
        }
        else
        {
            cout << "\nInvalid Username or Password!\n";
            return false;
        }
    }
};

class RentalSystem {
public:
    Car cars[10];
    Bike bikes[10];
    int carCount = 0;
    int bikeCount = 0;

    void loadFromFile() {
        ifstream file("vehicles.txt");
        string type, status;

        while (file >> type >> ws) {
            if (type == "Car" && carCount < 10) {
                getline(file, cars[carCount].model);
                file >> cars[carCount].rentPerDay >> status;
                cars[carCount].available = (status == "Available");
                carCount++;
            }
            else if (type == "Bike" && bikeCount < 10) {
                getline(file, bikes[bikeCount].model);
                file >> bikes[bikeCount].rentPerDay >> status;
                bikes[bikeCount].available = (status == "Available");
                bikeCount++;
            }
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("vehicles.txt");

        for (int i = 0; i < carCount; i++) {
            file << "Car " << cars[i].model << endl
                 << cars[i].rentPerDay << " "
                 << (cars[i].available ? "Available" : "Rented") << endl;
        }

        for (int i = 0; i < bikeCount; i++) {
            file << "Bike " << bikes[i].model << endl
                 << bikes[i].rentPerDay << " "
                 << (bikes[i].available ? "Available" : "Rented") << endl;
        }

        file.close();
    }

    void addVehicle() {
        int choice;
        cout << "\n1. Add Car\n2. Add Bike\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 && carCount < 10) {
            cars[carCount++].input();
            cout << "Car added successfully.\n";
        }
        else if (choice == 2 && bikeCount < 10) {
            bikes[bikeCount++].input();
            cout << "Bike added successfully.\n";
        }
        else {
            cout << "Invalid choice or storage full.\n";
        }

        saveToFile();
    }

    void viewAllVehicles() {
        cout << "\n======= VEHICLE COLLECTION =======\n";

        if (carCount == 0 && bikeCount == 0) {
            cout << "No vehicles available.\n";
            return;
        }

        if (carCount > 0) {
            cout << "\n--- Cars ---\n";
            for (int i = 0; i < carCount; i++)
                cars[i].display(i + 1);
        }

        if (bikeCount > 0) {
            cout << "\n--- Bikes ---\n";
            for (int i = 0; i < bikeCount; i++)
                bikes[i].display(i + 1);
        }
    }

    void rentVehicle() {
        int type;
        cout << "\n1. Car\n2. Bike\nChoice: ";
        cin >> type;

        int choice, days;
        float total = 0;

        if (type == 1) {
            int count = 0;
            cout << "\nAvailable Cars:\n";
            for (int i = 0; i < carCount; i++)
                if (cars[i].available)
                    cars[i].display(++count);

            if (count == 0) {
                cout << "No cars available.\n";
                return;
            }

            cout << "Enter choice number: ";
            cin >> choice;
            cout << "Enter days to rent: ";
            cin >> days;

            count = 0;
            for (int i = 0; i < carCount; i++) {
                if (cars[i].available && ++count == choice) {
                    total = cars[i].calculateRent(days);
                    cars[i].available = false;
                    break;
                }
            }
        }
        else if (type == 2) {
            int count = 0;
            cout << "\nAvailable Bikes:\n";
            for (int i = 0; i < bikeCount; i++)
                if (bikes[i].available)
                    bikes[i].display(++count);

            if (count == 0) {
                cout << "No bikes available.\n";
                return;
            }

            cout << "Enter choice number: ";
            cin >> choice;
            cout << "Enter days to rent: ";
            cin >> days;

            count = 0;
            for (int i = 0; i < bikeCount; i++) {
                if (bikes[i].available && ++count == choice) {
                    total = bikes[i].calculateRent(days);
                    bikes[i].available = false;
                    break;
                }
            }
        }
        else {
            cout << "Invalid selection.\n";
            return;
        }

        cout << "\nFinal Cost: Rs. " << total << endl;

        int payment;
        cout << "\nPayment Method:\n1. UPI\n2. Credit/Debit Card\nChoice: ";
        cin >> payment;

        cout << "\nPayment Successful.\n";
        cout << "Thank You For Choosing our service. Have safe Travels\n";

        saveToFile();
        exit(0);
    }
};

int main()
{
    UserAuth auth;
    int choice;

    cout << "1. Register\n2. Login\nChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        auth.registerUser();
    }

    if (!auth.loginUser())
    {
        cout << "Access Denied.\n";
        return 0;
    }

    RentalSystem rs;
    rs.loadFromFile();

    int menu;
    do
    {
        cout << "\n1. Add Vehicle";
        cout << "\n2. Rent Vehicle";
        cout << "\n3. View All Vehicles";
        cout << "\n4. Exit";
        cout << "\nChoice: ";
        cin >> menu;

        switch (menu)
        {
        case 1:
            rs.addVehicle();
            break;
        case 2:
            rs.rentVehicle();
            break;
        case 3:
            rs.viewAllVehicles();
            break;
        case 4:
            cout << "Thank You for choosing our Service! Goodbye!\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (menu != 4);

    return 0;
}