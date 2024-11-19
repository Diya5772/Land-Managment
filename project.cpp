// #include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;


class navigation;
class User;

vector<User> users;


class User
{
    string name;
    int age, user_id;

    public:
    void user_register(void);
    void user_login(void);
    
};

class property
{
    //data members
    int prop_id, pincode, for_sale, for_rent;
    string prop_name, owner, type;
    double price, area;

    public:
    //functions for manage property
    void edit_prop(int);
    void sell_prop(int);
    void rent_my_prop(int);
    void show_my_prop(int, int);
    void add_prop(int);
    void see_and_edit_application(int);
    //functions for find a property
    void buy_prop(int);
    void rent_a_prop(int);
    void show_prop(int);
};

class pincode_tax
{
    public:
    void search_landmark(void);
    void tax_calculator(void);
};

//navigation functions
class navigation:User,property,pincode_tax
{
    public:
    void main_menu(void);
    void real_estate_menu(int);
    void manage_property_menu(int);
    void find_property_menu(int);
    
};
navigation nav;
void navigation::main_menu(void)
{
    int choice;
    cout << "Choose an option:\n1. Register User\n2. Login\n3. Pincode search/n4. Tax Calculator\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            user_register();
            break; 
        }
        case 2:
        {
            user_login();
            break;
        }
        case 3:
        {
            search_landmark();
            break;
        }
        case 4:
        {
            tax_calculator();
            break;
        }
        case 5:
            cout << "Exiting program." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            main_menu();
            break;
    }
}

void navigation::real_estate_menu(int id)
{
    int selection;
    cout << "Choose an option:\n1. Manage Property\n2. Find Property\n3. Go back";
    cin >> selection;

    switch (selection)
    {
    case 1:
        manage_property_menu(id);
        break;
    case 2:
        find_property_menu(id);
        break;
    case 3:
        main_menu();
    default:
        cout << "Invalid choice. Please try again." << endl;
        real_estate_menu(id);
        break;
    }
}

void navigation::manage_property_menu(int id)
{
     int selection;
    cout << "Choose an option:\n1. edit property \n2. sell property  \n3. rent my property  \n4. show my property  \n5. My Applications\n6. add property\n7. Go back";
    cin >> selection;

    switch (selection)
    {
        case 1:
            edit_prop(id);
            break;
        case 2:
            sell_prop(id);
            break;
        case 3:
            rent_my_prop(id);
            break;
        case 4:
            show_my_prop(id,1);
            break;
        case 5:
            see_and_edit_application(id);
            break;
        case 6:
            add_prop(id);
            break;        
        case 7:
            real_estate_menu(id);
        default:
            cout << "Invalid choice. Please try again." << endl;
            manage_property_menu(id);
            break;
    }
}

void navigation::find_property_menu(int id)
{
   int selection;
    cout << "Choose an option:\n1. buy property \n2. rent property  \n3. show property\n4. go back";
    cin >> selection;

    switch (selection)
    {
    case 1:
        buy_prop(id);
         break;
    case 2:
        rent_a_prop(id);
        break;
    case 3:
        show_prop(id);
        break;
    case 4:
        real_estate_menu(id);
    default:
        cout << "Invalid choice. Please try again." << endl;
        find_property_menu(id);
        break;
    }
}



void pincode_tax::search_landmark(void) {
    ifstream pincode_file("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error opening pincode.csv file!" << endl;
        return;
    }

    string line;
    vector<int> pincodes; // To store pincodes

    // Read and display all the pincodes from the pincode.csv file
    cout << "Available Pincodes: " << endl;
    cout << "--------------------" << endl;

    // Skip the header row
    getline(pincode_file, line);
    string header_line = line;

    // Read each line to extract pincodes
    while (getline(pincode_file, line)) {
        stringstream ss(line);
        string temp;
        int pincode;

        // Extract the pincode (first column)
        getline(ss, temp, ',');
        pincode = stoi(temp);

        // Store pincode in the vector
        pincodes.push_back(pincode);
    }

    pincode_file.close();

    // Display pincodes to the user
    for (size_t i = 0; i < pincodes.size(); ++i) {
        cout << i + 1 << ". Pincode: " << pincodes[i] << endl;
    }

    int selected_pincode;
    cout << "Enter the Pincode you want to search for: ";
    cin >> selected_pincode;

    // Reopen the file to find the details of the selected pincode
    pincode_file.open("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error reopening pincode.csv file!" << endl;
        return;
    }

    getline(pincode_file, header_line); // Skip the header row

    bool found = false;
    cout << "\nDetails for Pincode " << selected_pincode << ":" << endl;
    cout << "--------------------------------------------------------" << endl;

    while (getline(pincode_file, line)) {
        stringstream ss(line);
        string temp;
        int pincode;

        // Extract the pincode (first column)
        getline(ss, temp, ',');
        pincode = stoi(temp);

        if (pincode == selected_pincode) {
            found = true;

            // Extract and display remaining columns
            vector<string> landmarks;
            while (getline(ss, temp, ',')) {
                landmarks.push_back(temp);
            }

            cout << "School: " << landmarks[0] << endl;
            cout << "Temple: " << landmarks[1] << endl;
            cout << "Hotel: " << landmarks[2] << endl;
            cout << "Restaurant: " << landmarks[3] << endl;
            cout << "Police Station: " << landmarks[4] << endl;
            cout << "Hospital: " << landmarks[5] << endl;
            cout << "Mall: " << landmarks[6] << endl;
            cout << "Medical Store: " << landmarks[7] << endl;
            cout << "Petrol Pump: " << landmarks[8] << endl;
            cout << "Saloon: " << landmarks[9] << endl;
            cout << "Park: " << landmarks[10] << endl;
            break;
        }
    }

    pincode_file.close();

    if (!found) {
        cout << "No details found for the entered Pincode!" << endl;
    }
    nav.main_menu();
}

void pincode_tax::tax_calculator(void) {
    int selected_pincode, property_id;
    double property_price, property_area, tax_rate, total_tax;

    // Open the property.csv file to display properties
    ifstream property_file("property.csv");
    if (!property_file.is_open()) {
        cerr << "Error opening property.csv file!" << endl;
        return;
    }

    cout << "Enter the pincode to search for properties: ";
    cin >> selected_pincode;

    cout << "\nProperties in Pincode " << selected_pincode << ":" << endl;
    cout << "----------------------------------------------------------" << endl;

    string line;
    bool property_found = false;
    vector<int> available_properties; // Store IDs of properties in the selected pincode

    // Skip the header row
    getline(property_file, line);

    // Display properties in the selected pincode
    while (getline(property_file, line)) {
        stringstream ss(line);
        string temp;
        int prop_id, pincode_value, for_sale, for_rent, user_id;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        prop_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        user_id = stoi(temp);

        // Display properties in the selected pincode
        if (pincode_value == selected_pincode) {
            property_found = true;
            available_properties.push_back(prop_id);

            cout << "Property ID: " << prop_id << endl;
            cout << "Name: " << name << endl;
            cout << "Owner: " << owner_name << endl;
            cout << "Price: " << price_value << endl;
            cout << "Area: " << area_value << " sq.ft." << endl;
            cout << "Type: " << type_value << endl;
            cout << "---------------------------------" << endl;
        }
    }

    property_file.close();

    // If no properties are found
    if (!property_found) {
        cout << "No properties found in the selected pincode." << endl;
        nav.main_menu();
        return;
    }

    // Ask the user to select a property by ID
    cout << "Enter the Property ID for which you want to calculate tax: ";
    cin >> property_id;

    // Validate the selected property ID
    if (find(available_properties.begin(), available_properties.end(), property_id) == available_properties.end()) {
        cout << "Invalid Property ID!" << endl;
        return;
    }

    // Open the property.csv file again to find the selected property
    ifstream property_file_reopen("property.csv");
    if (!property_file_reopen.is_open()) {
        cerr << "Error reopening property.csv file!" << endl;
        return;
    }

    // Skip the header row
    getline(property_file_reopen, line);

    while (getline(property_file_reopen, line)) {
        stringstream ss(line);
        string temp;
        int prop_id, pincode_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        prop_id = stoi(temp); // Property ID

        if (prop_id == property_id) {
            // Parse relevant details for the selected property
            getline(ss, temp, ','); // Name (skip)
            getline(ss, temp, ','); // Owner (skip)
            getline(ss, temp, ','); // Pincode (skip)
            getline(ss, temp, ','); // Price
            price_value = stod(temp);
            getline(ss, temp, ','); // Area
            area_value = stod(temp);

            property_price = price_value;
            property_area = area_value;

            break;
        }
    }

    property_file_reopen.close();

    // Calculate the tax based on a formula
    cout << "\nEnter the tax rate (as a percentage): ";
    cin >> tax_rate;

    // Example tax formula: Total Tax = (Property Price * Tax Rate) + (Area * 10)
    total_tax = (property_price * (tax_rate / 100)) + (property_area * 10);

    // Display the calculated tax
    cout << "Total Tax for Property ID " << property_id << " is: " << total_tax << endl;
    nav.main_menu();
}


//class property functions
void property::edit_prop(int id)
{
    int prop_id_tochange, value;
    string to_change, new_value;
    double new_double_value;
    bool property_found = false;

    cout << "These are your current properties:" << endl;
    cout << "------------------------------------------" << endl;

    // Display the user's properties
    show_my_prop(id, 0);

    cout << "Enter the property ID you want to edit: ";
    cin >> prop_id_tochange;

    // Open the CSV file to verify ownership and process updates
    ifstream inputFile("property.csv");
    ofstream tempFile("temp.csv");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    string line;
    bool ownership_verified = false;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string row_id, name, owner, pincode, price, area, for_sale, for_rent, type, csv_user_id;

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
        getline(ss, csv_user_id, ',');

        // Check if the property belongs to the user and matches the ID
        if (stoi(row_id) == prop_id_tochange && stoi(csv_user_id) == id) {
            ownership_verified = true;

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
                    nav.manage_property_menu(id);
                    return;
            }

            cout << "Enter the new value: ";
            if (to_change == "price" || to_change == "area") {
                cin >> new_double_value;
            } else {
                cin.ignore(); // Clear buffer
                getline(cin, new_value);
            }

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

            property_found = true;
        }

        // Write the updated or original row to the temp file
        tempFile << row_id << "," << name << "," << owner << "," << pincode << "," << price
                 << "," << area << "," << for_sale << "," << for_rent << "," << type << "," << csv_user_id << "\n";
    }

    inputFile.close();
    tempFile.close();

    if (!ownership_verified) {
        cout << "You do not own this property or the property ID is invalid." << endl;
        remove("temp.csv");
        nav.manage_property_menu(id);
        return;
    }

    if (!property_found) {
        cout << "Property ID not found in the file." << endl;
        remove("temp.csv");
        nav.manage_property_menu(id);
        return;
    }

    // Replace the original file with the updated file
    remove("property.csv");
    rename("temp.csv", "property.csv");

    cout << "Property updated successfully!" << endl;

    // Show updated properties
    show_my_prop(id, 0);
    nav.manage_property_menu(id);
    return;
}

void property::add_prop(int id) {
    int property_id, pincode_value;
    string name, owner_name, type_value;
    double price_value, area_value;
    bool for_sale, for_rent;

    // Open the CSV file to determine the next available property ID
    ifstream inputFile("property.csv");
    property_id = 1; // Start property ID from 1 if no properties exist

    if (inputFile.is_open()) {
        string line, last_line;
        while (getline(inputFile, line)) {
            last_line = line; // Keep the last line
        }

        if (!last_line.empty()) {
            stringstream ss(last_line);
            string last_id;
            getline(ss, last_id, ','); // Get the property ID of the last entry
            property_id = stoi(last_id) + 1; // Increment for the new property
        }
        inputFile.close();
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

    cout << "Type (Residential/Commercial/Luxury/etc.): ";
    cin.ignore(); // Clear the input buffer again
    getline(cin, type_value);

    // Append the new property to the CSV file
    ofstream file("property.csv", ios::app);
    if (file.is_open()) {
        // Write the new property to the file in CSV format
        file << property_id << "," << name << "," << owner_name << "," << pincode_value << ","
             << price_value << "," << area_value << ","
             << 0 << ","
             << 0 << ","
             << type_value << "," << id << "\n";

        file.close();
        cout << "Property added successfully!" << endl;

        // Show the updated list of properties for the user
        show_my_prop(id, 0);
        nav.manage_property_menu(id);
    } else {
        cerr << "Error opening file for writing." << endl;
        nav.manage_property_menu(id);
    }
}

void property::show_my_prop(int id, int x = 1) {
    ifstream file("property.csv");
    string line;
    bool found = false;

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    cout << "Here are your properties: " << endl;
    cout << "---------------------------------" << endl;

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int property_id, pincode_value, user_id;
        string name, owner_name, type_value;
        double price_value, area_value;
        int for_sale_value, for_rent_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        property_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale_value = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent_value = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        user_id = stoi(temp);

        // Check if the property belongs to the user
        if (user_id == id) {
            found = true;

            // Display property details
            cout << "Property ID: " << property_id << endl;
            cout << "Name: " << name << endl;
            cout << "Owner: " << owner_name << endl;
            cout << "Pincode: " << pincode_value << endl;
            cout << "Price: " << price_value << endl;
            cout << "Area: " << area_value << " sq.ft." << endl;
            cout << "For Sale: " << (for_sale_value > 0 ? "Yes, Price: " + to_string(for_sale_value) : "No") << endl;
            cout << "For Rent: " << (for_rent_value > 0 ? "Yes, Rent: " + to_string(for_rent_value) : "No") << endl;
            cout << "Type: " << type_value << endl;
            cout << "---------------------------------" << endl;
        }
    }

    if (!found) {
        cout << "No properties found for the given user ID." << endl;
    }

    file.close();

    if (x == 1) {
        nav.manage_property_menu(id);
    }
    return;
}

void property::sell_prop(int id) {
    // Display the user's properties
    show_my_prop(id, 0);

    int property_id;
    double sale_price;
    bool property_found = false;

    // Ask the user to select a property to sell
    cout << "Enter the Property ID you want to sell: ";
    cin >> property_id;

    cout << "Enter the price you want to quote for selling: ";
    cin >> sale_price;

    // Open the CSV file for reading
    ifstream file("property.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Create a temporary file to write updated data
    ofstream temp_file("temp.csv");
    if (!temp_file.is_open()) {
        cerr << "Error creating temporary file!" << endl;
        file.close();
        nav.manage_property_menu(id);
        return;
    }

    string line;

    // Read and process the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int csv_property_id, csv_user_id, pincode_value, for_sale, for_rent;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        csv_property_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        csv_user_id = stoi(temp);

        // Check if this is the property to be sold
        if (csv_property_id == property_id && csv_user_id == id) {
            property_found = true;
            for_sale = static_cast<int>(sale_price); // Update the for_sale value
            cout << "Property ID " << property_id << " is now listed for sale at " << sale_price << "!" << endl;
        }

        // Write the updated or original line to the temp file
        temp_file << csv_property_id << "," << name << "," << owner_name << "," << pincode_value << ","
                  << price_value << "," << area_value << "," << for_sale << "," << for_rent << "," 
                  << type_value << "," << csv_user_id << "\n";
    }

    file.close();
    temp_file.close();

    if (!property_found) {
        cout << "No property found with ID " << property_id << " belonging to you." << endl;
        remove("temp.csv"); // Cleanup the temporary file
        nav.manage_property_menu(id);
        return;
    }

    // Replace the original file with the updated file
    remove("property.csv");
    rename("temp.csv", "property.csv");
    nav.manage_property_menu(id);
}

void property::rent_my_prop(int id) {
    // Display the user's properties
    show_my_prop(id, 0);

    int property_id;
    double rent_price;
    bool property_found = false;

    // Ask the user to select a property to rent out
    cout << "Enter the Property ID you want to rent out: ";
    cin >> property_id;

    cout << "Enter the price you want to quote for rent: ";
    cin >> rent_price;

    // Open the CSV file for reading
    ifstream file("property.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Create a temporary file to write updated data
    ofstream temp_file("temp.csv");
    if (!temp_file.is_open()) {
        cerr << "Error creating temporary file!" << endl;
        file.close();
        nav.manage_property_menu(id);
        return;
    }

    string line;

    // Read and process the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int csv_property_id, csv_user_id, pincode_value, for_sale, for_rent;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        csv_property_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID (now replaced by id)
        csv_user_id = stoi(temp);

        // Check if this is the property to be rented out
        if (csv_property_id == property_id && csv_user_id == id) {
            property_found = true;
            for_rent = static_cast<int>(rent_price); // Update the for_rent value
            cout << "Property ID " << property_id << " is now listed for rent at " << rent_price << "!" << endl;
        }

        // Write the updated or original line to the temp file
        temp_file << csv_property_id << "," << name << "," << owner_name << "," << pincode_value << ","
                  << price_value << "," << area_value << "," << for_sale << "," << for_rent << "," 
                  << type_value << "," << csv_user_id << "\n";
    }

    file.close();
    temp_file.close();

    if (!property_found) {
        cout << "No property found with ID " << property_id << " belonging to you." << endl;
        remove("temp.csv"); // Cleanup the temporary file
        nav.manage_property_menu(id);
        return;
    }

    // Replace the original file with the updated file
    remove("property.csv");
    rename("temp.csv", "property.csv");
    nav.manage_property_menu(id);
}

void property::see_and_edit_application(int id) {
    ifstream file("property.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    string line;
    bool found = false;
    vector<int> properties_to_edit;

    cout << "Here are all the properties you have listed for sale or rent:" << endl;
    cout << "------------------------------------------------------------" << endl;

    // Read and display the properties for sale or rent
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int property_id, user_id, for_sale, for_rent;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        property_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        int pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        user_id = stoi(temp);

        // Check if the property is for sale or rent and belongs to the current user
        if ((for_sale > 0 || for_rent > 0) && user_id == id) {
            found = true;

            // Display the property details
            cout << "Property ID: " << property_id << endl;
            cout << "Name: " << name << endl;
            cout << "Owner: " << owner_name << endl;
            cout << "For Sale: " << (for_sale > 0 ? "Yes, Price: " + to_string(for_sale) : "No") << endl;
            cout << "For Rent: " << (for_rent > 0 ? "Yes, Price: " + to_string(for_rent) : "No") << endl;
            cout << "---------------------------------" << endl;

            // Add the property ID to the list of properties that can be edited
            properties_to_edit.push_back(property_id);
        }
    }

    file.close();

    if (!found) {
        cout << "You have no properties listed for sale or rent." << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Ask the user what action they want to take
    cout << "Enter the Property ID to edit or 0 to exit: ";
    int edit_property_id;
    cin >> edit_property_id;

    if (edit_property_id == 0) {
        return;
    }

    // Check if the property ID is valid
    if (find(properties_to_edit.begin(), properties_to_edit.end(), edit_property_id) == properties_to_edit.end()) {
        cout << "Invalid Property ID!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Ask the user what they want to do (edit or remove)
    cout << "What do you want to do with Property ID " << edit_property_id << "?" << endl;
    cout << "1. Edit sale/rent price" << endl;
    cout << "2. Remove from sale/rent" << endl;
    cout << "Enter your choice (1 or 2): ";
    int choice;
    cin >> choice;

    // Open the file again to edit the properties
    ifstream file_read("property.csv");
    ofstream file_write("temp.csv");

    if (!file_read.is_open() || !file_write.is_open()) {
        cerr << "Error opening file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    bool property_edited = false;
    
    // Read and process the file line by line
    while (getline(file_read, line)) {
        stringstream ss(line);
        string temp;
        int property_id, user_id, for_sale, for_rent;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        property_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        int pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        user_id = stoi(temp);

        // Check if the property is the one the user wants to edit
        if (property_id == edit_property_id && user_id == id) {
            property_edited = true;

            if (choice == 1) {
                // Edit sale/rent price
                cout << "Enter the new sale price (0 if not for sale): ";
                cin >> for_sale;
                cout << "Enter the new rent price (0 if not for rent): ";
                cin >> for_rent;
            } else if (choice == 2) {
                // Remove from sale/rent
                for_sale = 0;
                for_rent = 0;
            }

            cout << "Property updated successfully!" << endl;
        }

        // Write the updated or original line to the temp file
        file_write << property_id << "," << name << "," << owner_name << "," << pincode_value << ","
                   << price_value << "," << area_value << "," << for_sale << "," << for_rent << "," 
                   << type_value << "," << user_id << "\n";
    }

    file_read.close();
    file_write.close();

    if (!property_edited) {
        cout << "No such property found with ID " << edit_property_id << "!" << endl;
        remove("temp.csv");
        return;
    }

    // Replace the original file with the updated file
    remove("property.csv");
    rename("temp.csv", "property.csv");
    nav.manage_property_menu(id);
}

void property::show_prop(int id) {
    ifstream pincode_file("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error opening pincode.csv file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    string line;
    vector<int> pincodes; // To store pincodes

    // Read and display all the pincodes from the pincode.csv file
    cout << "Available Pincodes: " << endl;
    cout << "--------------------" << endl;
    
    // Skip the header row
    getline(pincode_file, line);

    // Read each line to extract pincodes
    while (getline(pincode_file, line)) {
        stringstream ss(line);
        string temp;
        int pincode;

        // Extract the pincode (first column)
        getline(ss, temp, ',');
        pincode = stoi(temp);

        // Store pincode in the vector
        pincodes.push_back(pincode);
    }
    pincode_file.close();

    // Display pincodes to the user
    for (size_t i = 0; i < pincodes.size(); ++i) {
        cout << i + 1 << ". Pincode: " << pincodes[i] << endl;
    }

    cout << "Enter the pincode you're interested in: ";
    int selected_pincode;
    cin >> selected_pincode;

    // Check if the selected pincode is valid
    if (find(pincodes.begin(), pincodes.end(), selected_pincode) == pincodes.end()) {
        cout << "Invalid pincode!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Now, display properties with the selected pincode from property.csv
    ifstream property_file("property.csv");
    if (!property_file.is_open()) {
        cerr << "Error opening property.csv file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    bool found_property = false;
    cout << "\nProperties available at Pincode " << selected_pincode << ":" << endl;
    cout << "----------------------------------------------------------" << endl;

    // Read and display properties from the property.csv file
    while (getline(property_file, line)) {
        stringstream ss(line);
        string temp;
        int prop_id, pincode_value, for_sale, for_rent, user_id;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        prop_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        user_id = stoi(temp);

        // Display the property if the pincode matches
        if (pincode_value == selected_pincode) {
            found_property = true;

            cout << "Property ID: " << prop_id << endl;
            cout << "Name: " << name << endl;
            cout << "Owner: " << owner_name << endl;
            cout << "Price: " << price_value << endl;
            cout << "Area: " << area_value << " sq.ft." << endl;
            cout << "For Sale: " << (for_sale > 0 ? "Yes, Price: " + to_string(for_sale) : "No") << endl;
            cout << "For Rent: " << (for_rent > 0 ? "Yes, Price: " + to_string(for_rent) : "No") << endl;
            cout << "Type: " << type_value << endl;
            cout << "---------------------------------" << endl;
        }
    }

    property_file.close();

    if (!found_property) {
        cout << "No properties found for the selected pincode." << endl;
    }
    nav.manage_property_menu(id);
}

void property::buy_prop(int id) {
    int selected_pincode;
    cout << "Enter the pincode where you want to search for properties: ";
    ifstream pincode_file("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error opening pincode.csv file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    string pincode_line; // Renamed variable for clarity
    vector<int> pincodes; // To store pincodes

    // Read and display all the pincodes from the pincode.csv file
    cout << "Available Pincodes: " << endl;
    cout << "--------------------" << endl;

    // Skip the header row
    getline(pincode_file, pincode_line);

    // Read each line to extract pincodes
    while (getline(pincode_file, pincode_line)) {
        stringstream ss(pincode_line);
        string temp;
        int pincode;

        // Extract the pincode (first column)
        getline(ss, temp, ',');
        pincode = stoi(temp);

        // Store pincode in the vector
        pincodes.push_back(pincode);
    }
    pincode_file.close();

    // Display pincodes to the user
    for (size_t i = 0; i < pincodes.size(); ++i) {
        cout << i + 1 << ". Pincode: " << pincodes[i] << endl;
    }
    cin >> selected_pincode;

    ifstream property_file("property.csv");
    if (!property_file.is_open()) {
        cerr << "Error opening property.csv file!" << endl;
        return;
    }

    vector<string> file_lines; // Store all lines to rewrite the file later
    string property_line;      // Renamed this line variable for clarity
    vector<int> available_properties; // Store property IDs for sale in the selected pincode

    // Header to preserve CSV structure
    bool header_parsed = false;
    string header_line;

    cout << "\nProperties available for sale in Pincode " << selected_pincode << ":" << endl;
    cout << "----------------------------------------------------------" << endl;

    while (getline(property_file, property_line)) {
        if (!header_parsed) {
            header_line = property_line;
            file_lines.push_back(property_line); // Store the header
            header_parsed = true;
            continue;
        }

        stringstream ss(property_line);
        string temp;
        int prop_id, pincode_value, for_sale, for_rent, user_id;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        prop_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        user_id = stoi(temp);

        file_lines.push_back(property_line); // Store the line for later modification

        // Check if the property matches the pincode and is for sale
        if (pincode_value == selected_pincode && for_sale > 0) {
            available_properties.push_back(prop_id);
            cout << "Property ID: " << prop_id << endl;
            cout << "Name: " << name << endl;
            cout << "Owner: " << owner_name << endl;
            cout << "Price: " << for_sale << endl;
            cout << "Area: " << area_value << " sq.ft." << endl;
            cout << "Type: " << type_value << endl;
            cout << "---------------------------------" << endl;
        }
    }

    property_file.close();

    // If no properties found
    if (available_properties.empty()) {
        cout << "No properties available for sale in the selected pincode." << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Ask user to select a property to buy
    int selected_property;
    cout << "Enter the Property ID you want to buy: ";
    cin >> selected_property;

    // Check if the selected property is valid
    if (find(available_properties.begin(), available_properties.end(), selected_property) == available_properties.end()) {
        cout << "Invalid Property ID!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Update the CSV file with the new owner (user_id updated to `id`)
    ofstream temp_file("temp_property.csv");
    if (!temp_file.is_open()) {
        cerr << "Error opening temp_property.csv file!" << endl;
        return;
    }

    for (const string& file_line : file_lines) {
        stringstream ss(file_line);
        string temp;
        int prop_id;

        // Parse property ID
        getline(ss, temp, ',');
        prop_id = stoi(temp);

        if (prop_id == selected_property) {
            // Update the user_id and set for_sale to 0
            string updated_line = file_line;
            size_t last_comma = updated_line.find_last_of(',');
            size_t second_last_comma = updated_line.find_last_of(',', last_comma - 1);

            // Modify user_id and for_sale fields
            updated_line.replace(second_last_comma + 1, last_comma - second_last_comma - 1, "0"); // for_sale
            updated_line.replace(last_comma + 1, string::npos, to_string(id)); // user_id

            temp_file << updated_line << "\n";
        } else {
            // Write the original line
            temp_file << file_line << "\n";
        }
    }

    temp_file.close();

    // Replace the original property file with the updated file
    if (remove("property.csv") != 0 || rename("temp_property.csv", "property.csv") != 0) {
        cerr << "Error updating the property file!" << endl;
    } else {
        cout << "Property purchased successfully!" << endl;
    }
    nav.manage_property_menu(id);
}

void property::rent_a_prop(int id) {
    int selected_pincode;
    cout << "Enter the pincode where you want to search for rental properties: ";

    ifstream pincode_file("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error opening pincode.csv file!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    string line;
    vector<int> pincodes; // To store pincodes

    // Read and display all the pincodes from the pincode.csv file
    cout << "Available Pincodes: " << endl;
    cout << "--------------------" << endl;
    
    // Skip the header row
    getline(pincode_file, line);

    // Read each line to extract pincodes
    while (getline(pincode_file, line)) {
        stringstream ss(line);
        string temp;
        int pincode;

        // Extract the pincode (first column)
        getline(ss, temp, ',');
        pincode = stoi(temp);

        // Store pincode in the vector
        pincodes.push_back(pincode);
    }
    pincode_file.close();

    // Display pincodes to the user
    for (size_t i = 0; i < pincodes.size(); ++i) {
        cout << i + 1 << ". Pincode: " << pincodes[i] << endl;
    }
    cin >> selected_pincode;

    ifstream property_file("property.csv");
    if (!property_file.is_open()) {
        cerr << "Error opening property.csv file!" << endl;
        return;
    }

    vector<string> file_lines; // Store all lines to rewrite the file later
    vector<int> available_properties; // Store property IDs for rent in the selected pincode

    // Header to preserve CSV structure
    bool header_parsed = false;
    string header_line;

    cout << "\nProperties available for rent in Pincode " << selected_pincode << ":" << endl;
    cout << "----------------------------------------------------------" << endl;

    while (getline(property_file, line)) {
        if (!header_parsed) {
            header_line = line;
            file_lines.push_back(line); // Store the header
            header_parsed = true;
            continue;
        }

        stringstream ss(line);
        string temp;
        int prop_id, pincode_value, for_sale, for_rent, user_id;
        string name, owner_name, type_value;
        double price_value, area_value;

        // Parse the CSV line
        getline(ss, temp, ',');
        prop_id = stoi(temp); // Property ID

        getline(ss, name, ',');       // Name
        getline(ss, owner_name, ','); // Owner
        getline(ss, temp, ',');       // Pincode
        pincode_value = stoi(temp);

        getline(ss, temp, ',');       // Price
        price_value = stod(temp);

        getline(ss, temp, ',');       // Area
        area_value = stod(temp);

        getline(ss, temp, ',');       // For sale
        for_sale = stoi(temp);

        getline(ss, temp, ',');       // For rent
        for_rent = stoi(temp);

        getline(ss, type_value, ','); // Type

        getline(ss, temp, ',');       // User ID
        user_id = stoi(temp);

        file_lines.push_back(line); // Store the line for later modification

        // Check if the property matches the pincode and is for rent
        if (pincode_value == selected_pincode && for_rent > 0) {
            available_properties.push_back(prop_id);
            cout << "Property ID: " << prop_id << endl;
            cout << "Name: " << name << endl;
            cout << "Owner: " << owner_name << endl;
            cout << "Rent Price: " << for_rent << endl;
            cout << "Area: " << area_value << " sq.ft." << endl;
            cout << "Type: " << type_value << endl;
            cout << "---------------------------------" << endl;
        }
    }

    property_file.close();

    // If no properties found
    if (available_properties.empty()) {
        cout << "No properties available for rent in the selected pincode." << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Ask user to select a property to rent
    int selected_property;
    cout << "Enter the Property ID you want to rent: ";
    cin >> selected_property;

    // Check if the selected property is valid
    if (find(available_properties.begin(), available_properties.end(), selected_property) == available_properties.end()) {
        cout << "Invalid Property ID!" << endl;
        nav.manage_property_menu(id);
        return;
    }

    // Update the CSV file to set for_rent to 0 (indicating it is now rented)
    ofstream temp_file("temp_property.csv");
    if (!temp_file.is_open()) {
        cerr << "Error opening temp_property.csv file!" << endl;
        return;
    }

    for (const string& file_line : file_lines) {
        stringstream ss(file_line);
        string temp;
        int prop_id;

        // Parse property ID
        getline(ss, temp, ',');
        prop_id = stoi(temp);

        if (prop_id == selected_property) {
            // Update for_rent to 0
            string updated_line = file_line;
            size_t rent_index = updated_line.find_last_of(',', updated_line.find_last_of(',') - 1);
            size_t sale_index = updated_line.find_last_of(',', rent_index - 1);

            // Modify for_rent field
            updated_line.replace(rent_index + 1, sale_index - rent_index - 1, "0"); 

            temp_file << updated_line << "\n";
        } else {
            // Write the original line
            temp_file << file_line << "\n";
        }
    }

    temp_file.close();

    // Replace the original property file with the updated file
    if (remove("property.csv") != 0 || rename("temp_property.csv", "property.csv") != 0) {
        cerr << "Error updating the property file!" << endl;
    } else {
        cout << "Property rented successfully!" << endl;
    }
    nav.manage_property_menu(id);
}


//user functions
void User::user_register(void) {
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your age: ";
    cin >> age;
    user_id=users.size()+1;
    User temp;
    temp.age=age;
    temp.name=name;
    temp.user_id=user_id;
    users.push_back(temp);
    cout << "Registration successful. Your user_name is " << temp.user_id << endl;
    nav.main_menu();
}
void User::user_login(void)
{
    int id;
    cout<<"Enter username"<<endl;
    cin>>id;
    cout<<"Seccesfully Logged in"<<endl;
    cout<<"Welcome "<<users[id-1].name;
    nav.real_estate_menu(id);  
}


int main()
{
    nav.main_menu();
    return 0;
}
