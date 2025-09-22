#include <bits/stdc++.h>
#include "admin.h"
#include "user.h"
#include "driver.h"
using namespace std;

int main() {
    admin Admin;
    Admin.loadData();

    // Add a sample user/driver only once (for testing)

        Admin.users[2] = user("Alige", "alice@mail.com", "123456", "pass123");

        Admin.drivers[2] = driver("kitty", "bob@mail.com", "987654", "driverpass");

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Add location\n";
        cout << "2. Add road\n";
        cout << "3. Display graph data\n";
        cout << "4. Add user & request ride\n";
        cout << "5. Add driver\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1:
                Admin.add_location();
                break;
            case 2:
                Admin.add_road();
                break;
            case 3:
                Admin.displayData();
                break;
            case 4: {
                string name, email, phone, pass;
                cout << "Enter user name email phone password: ";
                cin >> name >> email >> phone >> pass;

                int nextUserId = Admin.users.empty() ? 1 : Admin.users.begin()->first + 1;
                Admin.users[nextUserId] = user(name, email, phone, pass);

                Admin.users[nextUserId].requestRide(Admin);
                break;
            }
            case 5: {
                string name, email, phone, pass;
                cout << "Enter driver name email phone password: ";
                cin >> name >> email >> phone >> pass;

                int nextDriverId = Admin.drivers.empty() ? 1 : Admin.drivers.begin()->first + 1;
                Admin.drivers[nextDriverId] = driver(name, email, phone, pass);

                cout << "Driver added!\n";
                break;
            }
            default:
                cout << "Invalid choice!\n";
        }
    }

    cout << "\nSaving " << Admin.users.size() << " users and "
         << Admin.drivers.size() << " drivers...\n";

    Admin.saveData();

    cout << "Goodbye!\n";
    return 0;
}
