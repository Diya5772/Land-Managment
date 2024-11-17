#include<bits/stdc++.h>
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
    void sell_prop(vector<int>);
    void rent_my_prop(void);
    void show_my_prop(vector<int>, int);
    void add_prop(vector<int>&);
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
    show_my_prop(user_prop_id, 0);

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
    show_my_prop(user_prop_id, 0);
    manage_property_menu();
    return;
}

void property::add_prop(vector<int>& user_prop_id) {
    int id, pincode_value;
    string name, owner_name, type_value;
    double price_value, area_value;
    char sale_status, rent_status;

    // Generate new property ID (this example uses the next available ID)
    if (!user_prop_id.empty()) {
        id = *max_element(user_prop_id.begin(), user_prop_id.end()) + 1;
    } else {
        id = 1;  // Start from ID 1 if there are no properties
    }

    // Collect property details from the user
    cout << "Enter the property details: " << endl;
    cout << "Name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);

    cout << "Owner: ";
    getline(cin, owner_name);

    cout << "Pincode: ";
    cin >> pincode_value;

    cout << "Price: ";
    cin >> price_value;

    cout << "Area: ";
    cin >> area_value;

    cout << "Is the property for sale? (y/n): ";
    cin >> sale_status;
    for_sale = (sale_status == 'y' || sale_status == 'Y');

    cout << "Is the property for rent? (y/n): ";
    cin >> rent_status;
    for_rent = (rent_status == 'y' || rent_status == 'Y');

    cout << "Type (Residential/Commercial/Luxury/etc.): ";
    cin.ignore(); // Clear the input buffer again
    getline(cin, type_value);

    // Add property ID to the user_prop_id vector
    user_prop_id.push_back(id);

    // Open the CSV file to append the new property
    ofstream file("property.csv", ios::app);
    if (file.is_open()) {
        // Write the new property to the file in CSV format
        file << id << "," << name << "," << owner_name << "," << pincode_value << ","
             << price_value << "," << area_value << ","
             << (for_sale ? "true" : "false") << ","
             << (for_rent ? "true" : "false") << ","
             << type_value << "\n";

        file.close();
        cout << "Property added successfully!" << endl;
        show_my_prop(user_prop_id, 0);
        manage_property_menu();
    } else {
        cerr << "Error opening file for writing." << endl;
    }
}

void property::show_my_prop(vector<int> user_prop_id, int x=1) {
    ifstream file("property.csv");
    string line;
    bool found = false;

    // Check if file is open
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    cout << "Here are your properties: " << endl;
    cout << "---------------------------------" << endl;

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int id, pincode_value;
        string name, owner_name, type_value;
        double price_value, area_value;
        string for_sale_str, for_rent_str;

        // Parse the CSV line
        getline(ss, temp, ',');
        id = stoi(temp); // Property ID

        // Check if the current property ID is in the user_prop_id vector
        if (find(user_prop_id.begin(), user_prop_id.end(), id) != user_prop_id.end()) {
            found = true;

            // Property details
            getline(ss, name, ',');       // Name
            getline(ss, owner_name, ','); // Owner
            getline(ss, temp, ',');       // Pincode
            pincode_value = stoi(temp);

            getline(ss, temp, ',');       // Price
            price_value = stod(temp);

            getline(ss, temp, ',');       // Area
            area_value = stod(temp);

            getline(ss, for_sale_str, ','); // For sale
            for_sale = (for_sale_str == "true");

            getline(ss, for_rent_str, ','); // For rent
            for_rent = (for_rent_str == "true");

            getline(ss, type_value, ','); // Type

            // Display property details
            cout << "Property ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Owner: " << owner_name << endl;
            cout << "Pincode: " << pincode_value << endl;
            cout << "Price: " << price_value << endl;
            cout << "Area: " << area_value << " sq.ft." << endl;
            cout << "For Sale: " << (for_sale ? "Yes" : "No") << endl;
            cout << "For Rent: " << (for_rent ? "Yes" : "No") << endl;
            cout << "Type: " << type_value << endl;
            cout << "---------------------------------" << endl;
        }
    }

    if (!found) {
        cout << "No properties found for the given IDs." << endl;
    }
    file.close();
    if(x==1)
    {
        manage_property_menu();
    }
    return;
}
void property::sell_prop(vector<int> user_prop_id)
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
    cout<<"hello";

}