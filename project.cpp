#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;


class navigation
{
    public:
    void main_menu(void);
    void real_estate_menu(void);
    void manage_property_menu(void);
    void find_property_menu(void);
};
void navigation::main_menu(void)
{
    //code
}
void navigation::real_estate_menu(void)
{
    //code
}
void navigation::manage_property_menu(void)
{
    //code
}
void navigation::find_property_menu(void)
{
    //code
}


class pincode_search
{
    public:
    void search_landmark(void);
};
void pincode_search::search_landmark(void)
{
    //code
}


class property: navigation
{
    //data members
    int prop_id, pincode;
    string prop_name, owner, type;
    double price, area;
    bool for_sale, for_rent;

    public:
    //functions for manage property
    void edit_prop(vector<int>);
    void sell_prop(void);
    void rent_my_prop(void);
    void show_my_prop(vector<int>);
    void add_prop(void);
    //functions for find a property
    void buy_prop(void);
    void rent_a_prop(void);
    void show_prop(void);
};
void property::edit_prop(vector<int> user_prop_id)
{
    int id, value;
    string to_change, new_value;
    double new_double_value;
    bool property_found = false;

    cout << "These are your current properties:" << endl;
    cout << "------------------------------------------" << endl;
    show_my_prop(user_prop_id);

    cout << "Enter the property ID you want to edit: ";
    cin >> id;

    if (find(user_prop_id.begin(), user_prop_id.end(), id) == user_prop_id.end()) {
        cout << "You do not own this property or the property ID is invalid." << endl;
        manage_property_menu();
        return;//go back
    }

    cout << "What do you want to change?" << endl;
    cout << "1. Change Name" << endl;
    cout << "2. Change Price" << endl;
    cout << "3. Change Area" << endl;
    cout << "4. Change Type" << endl;
    cin >> value;

    switch (value) {
        case 1:
            to_change = "name";
            break;
        case 2:
            to_change = "price";
            break;
        case 3:
            to_change = "area";
            break;
        case 4:
            to_change = "type";
            break;
        default:
            cout << "Entered invalid input." << endl;
            manage_property_menu();
            return; //go back
    }

    cout << "Enter the new value: ";
    if (to_change == "price" || to_change == "area") {
        cin >> new_double_value;
    } else {
        cin.ignore(); // Clear buffer
        getline(cin, new_value);
    }

    // Read the CSV file, update the selected property, and rewrite the file
    ifstream inputFile("property.csv");
    ofstream tempFile("temp.csv");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string row_id, name, owner, pincode, price, area, for_sale, for_rent, type;

        // Parse the CSV row
        getline(ss, row_id, ',');
        getline(ss, name, ',');
        getline(ss, owner, ',');
        getline(ss, pincode, ',');
        getline(ss, price, ',');
        getline(ss, area, ',');
        getline(ss, for_sale, ',');
        getline(ss, for_rent, ',');
        getline(ss, type, ',');

        // Check if this is the property to be edited
        if (stoi(row_id) == id) {
            property_found = true;

            // Update the selected field
            if (to_change == "name") {
                name = new_value;
            } else if (to_change == "price") {
                price = to_string(new_double_value);
            } else if (to_change == "area") {
                area = to_string(new_double_value);
            } else if (to_change == "type") {
                type = new_value;
            }

            // Write the updated row to the temp file
            tempFile << row_id << "," << name << "," << owner << "," << pincode << ","
                     << price << "," << area << "," << for_sale << "," << for_rent << "," << type << "\n";
        } else {
            // Copy the original row for other properties
            tempFile << line << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    if (!property_found) {
        cout << "Property ID not found in the file." << endl;
        remove("temp.csv");
        return;
    }

    // Replace the original file with the updated file
    remove("property.csv");
    rename("temp.csv", "property.csv");

    cout << "Property updated successfully!" << endl;
    show_my_prop(user_prop_id);
    manage_property_menu();
    return;
}

void property::add_prop(void)
{
    //code
}
void property::show_my_prop(vector<int> user_prop_id)
{
    //code
}
void property::sell_prop(void)
{
    //code
}
void property::rent_my_prop(void)
{
    //code
}
void property::show_prop(void)
{
    //code
}
void property::buy_prop(void)
{
    //code
}
void property::rent_a_prop(void)
{
    //code
}


class user
{
    string user_id, name;
    int age;
    vector<int> user_prop; //this will be a vector of property ids that user has
    public:
    void user_register(void);
    void user_login(void);
};
void user::user_register(void)
{
    //code
}
void user::user_login(void)
{
    //code
}


int main()
{
    //code

}