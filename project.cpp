// #include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include <cstdio>
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
    cout << "Choose an option:\n1. Register User\n2. Login\n3. Pincode search\n4. Tax Calculator\n5. Exit"<<endl;
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
            // Delete original files
            std::remove("property.csv");
            std::remove("pincode.csv");
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
    cout << "Choose an option:\n1. Manage Property\n2. Find Property\n3. Go back"<<endl;
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
    cout << "Choose an option:\n1. edit property \n2. sell property  \n3. rent my property  \n4. show my property  \n5. My Applications\n6. add property\n7. Go back"<<endl;
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
    cout << "Choose an option:\n1. buy property \n2. rent property  \n3. show property\n4. go back"<<endl;
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
                    edit_prop(id);
                    return;
            }

            cout << "Enter the new value: ";
            cin.ignore(); // Clear buffer
            getline(cin, new_value);
            

            // Update the selected field
            if (to_change == "name") {
                name = new_value;
            } else if (to_change == "price") {
                price = new_value;
            } else if (to_change == "area") {
                area = new_value;
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

    // Determine the next available property ID
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
    cout << "Enter the property details:\n";
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
    ofstream file("property.csv", ios::out | ios::app);
    if (file.is_open()) {
        // Write the new property to the file in CSV format
        file << property_id << "," << name << "," << owner_name << "," << pincode_value << ","
             << price_value << "," << area_value << ","
             << 0 << "," // for_sale
             << 0 << "," // for_rent
             << type_value << "," << id <<"\n"; // Add user ID to the end
        file.close();
        cout << "Property added successfully!\n";
    } else {
        cerr << "Error opening property.csv for writing.\n";
    }

    // Check and update pincode.csv
    ifstream pincodeFile("pincode.csv");
    bool pincodeExists = false;
    if (pincodeFile.is_open()) {
        string line;
        while (getline(pincodeFile, line)) {
            stringstream ss(line);
            string existing_pincode;
            getline(ss, existing_pincode, ',');
            if (stoi(existing_pincode) == pincode_value) {
                pincodeExists = true;
                break;
            }
        }
        pincodeFile.close();
    }

    if (!pincodeExists) {
        ofstream pincodeFileOut("pincode.csv", ios::app);
        if (pincodeFileOut.is_open()) {
            pincodeFileOut << pincode_value;
            for (int i = 0; i < 11; ++i) { // Append 11 zeros
                pincodeFileOut << ",0";
            }
            pincodeFileOut << "\n";
            pincodeFileOut.close();
            cout << "Pincode added successfully!\n";
        } else {
            cerr << "Error opening pincode.csv for writing.\n";
        }
    } else {
        cout << "Pincode already exists in pincode.csv.\n";
    }

    // Optionally show updated list of properties
    show_my_prop(id, 0);
    nav.manage_property_menu(id);
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
        nav.manage_property_menu(id);
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
    int selected_pincode;

    // Step 1: Display available pincodes
    ifstream pincode_file("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error: Unable to open pincode.csv!" << endl;
        return;
    }

    vector<int> pincodes;
    string line;

    while (getline(pincode_file, line)) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); // Extract pincode
        pincodes.push_back(stoi(temp));
    }
    pincode_file.close();

    if (pincodes.empty()) {
        cout << "No pincodes available!" << endl;
        return;
    }

    cout << "Available Pincodes:\n";
    for (size_t i = 0; i < pincodes.size(); ++i) {
        cout << i + 1 << ". " << pincodes[i] << endl;
    }

    cout << "Enter the pincode to view properties: ";
    cin >> selected_pincode;

    if (find(pincodes.begin(), pincodes.end(), selected_pincode) == pincodes.end()) {
        cout << "Invalid pincode selected!" << endl;
        return;
    }

    // Step 2: Display properties in the selected pincode
    ifstream property_file("property.csv");
    if (!property_file.is_open()) {
        cerr << "Error: Unable to open property.csv!" << endl;
        return;
    }

    string property_line;
    bool properties_found = false;

    cout << "\nProperties in Pincode " << selected_pincode << ":\n";
    cout << "----------------------------------------------------------\n";

    while (getline(property_file, property_line)) {
        stringstream ss(property_line);
        string temp;
        int pincode;
        string name, owner, type_value;
        double price_value, area_value;
        int for_sale, for_rent, user_id;

        getline(ss, temp, ','); // Skip Property ID
        getline(ss, name, ','); // Name
        getline(ss, owner, ','); // Owner
        getline(ss, temp, ','); // Pincode
        pincode = stoi(temp);

        if (pincode == selected_pincode) {
            properties_found = true;

            getline(ss, temp, ',');       // Price
            price_value = stod(temp);

            getline(ss, temp, ',');       // Area
            area_value = stod(temp);

            getline(ss, temp, ',');       // For Sale
            for_sale = stoi(temp);

            getline(ss, temp, ',');       // For Rent
            for_rent = stoi(temp);

            getline(ss, type_value, ','); // Type
            getline(ss, temp, ',');       // User ID
            user_id = stoi(temp);

            cout << "Property Name: " << name << "\n";
            cout << "Owner: " << owner << "\n";
            cout << "Price: " << price_value << "\n";
            cout << "Area: " << area_value << " sq.ft.\n";
            cout << "Type: " << type_value << "\n";
            cout << "For Sale: " << (for_sale > 0 ? "Yes, Price: " + to_string(for_sale) : "No") << "\n";
            cout << "For Rent: " << (for_rent > 0 ? "Yes, Rent: " + to_string(for_rent) : "No") << "\n";
            cout << "----------------------------------------------------------\n";
        }
    }
    property_file.close();

    if (!properties_found) {
        cout << "No properties available in the selected pincode.\n";
    }
    nav.find_property_menu(id);
}

void property::buy_prop(int id) {
    int selected_pincode;

    // Step 1: Display available pincodes
    ifstream pincode_file("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error: Unable to open pincode.csv!" << endl;
        return;
    }

    vector<int> pincodes;
    string line;
    while (getline(pincode_file, line)) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); // Extract pincode
        pincodes.push_back(stoi(temp));
    }
    pincode_file.close();

    if (pincodes.empty()) {
        cout << "No pincodes available!" << endl;
        return;
    }

    cout << "Available Pincodes:\n";
    for (size_t i = 0; i < pincodes.size(); ++i) {
        cout << i + 1 << ". " << pincodes[i] << endl;
    }

    cout << "Enter the pincode where you want to search for properties: ";
    cin >> selected_pincode;

    if (find(pincodes.begin(), pincodes.end(), selected_pincode) == pincodes.end()) {
        cout << "Invalid pincode selected!" << endl;
        return;
    }

    // Step 2: Display properties for sale in the selected pincode
    ifstream property_file("property.csv");
    if (!property_file.is_open()) {
        cerr << "Error: Unable to open property.csv!" << endl;
        return;
    }

    vector<string> file_lines;
    vector<int> sale_properties;
    string property_line;
    bool properties_found = false;

    while (getline(property_file, property_line)) {
        file_lines.push_back(property_line); // Store lines for potential updates

        stringstream ss(property_line);
        string temp;
        int prop_id, pincode, for_sale;
        string name, owner;

        getline(ss, temp, ','); // Property ID
        prop_id = stoi(temp);

        getline(ss, name, ',');          // Name
        getline(ss, owner, ',');         // Owner
        getline(ss, temp, ',');          // Pincode
        pincode = stoi(temp);
        getline(ss, temp, ',');          // Skip Price
        getline(ss, temp, ',');          // Skip Area
        getline(ss, temp, ',');          // For Sale
        for_sale = stoi(temp);

        if (pincode == selected_pincode && for_sale > 0) {
            sale_properties.push_back(prop_id);
            properties_found = true;
            cout << "Property ID: " << prop_id << "\n"
                 << "Name: " << name << "\n"
                 << "Owner: " << owner << "\n"
                 << "Price: " << for_sale << "\n"
                 << "-----------------------------------\n";
        }
    }
    property_file.close();

    if (!properties_found) {
        cout << "No properties available for sale in the selected pincode.\n";
        return;
    }

    // Step 3: Ask the user to select a property to buy
    int selected_property;
    cout << "Enter the Property ID you want to buy: ";
    cin >> selected_property;

    if (find(sale_properties.begin(), sale_properties.end(), selected_property) == sale_properties.end()) {
        cout << "Invalid Property ID!" << endl;
        return;
    }

    // Step 4: Update the selected property in the CSV file
    ofstream temp_file("temp_property.csv");
    if (!temp_file.is_open()) {
        cerr << "Error: Unable to create temp_property.csv!" << endl;
        return;
    }

    for (const auto& line : file_lines) {
        stringstream ss(line);
        string temp;
        int prop_id;

        getline(ss, temp, ','); // Property ID
        prop_id = stoi(temp);

        if (prop_id == selected_property) {
            string updated_line;
            stringstream update_ss(line);
            vector<string> columns;

            // Parse columns into a vector
            while (getline(update_ss, temp, ',')) {
                columns.push_back(temp);
            }

            // Update sale column to 0 and set user ID to current user
            columns[6] = "0";          // For Sale column
            columns.back() = to_string(id); // User ID column

            // Reconstruct updated line
            for (size_t i = 0; i < columns.size(); ++i) {
                updated_line += columns[i];
                if (i != columns.size() - 1)
                    updated_line += ",";
            }

            temp_file << updated_line << "\n";
        } else {
            temp_file << line << "\n";
        }
    }

    temp_file.close();

    // Replace original file with updated file
    if (remove("property.csv") != 0 || rename("temp_property.csv", "property.csv") != 0) {
        cerr << "Error updating the property.csv file!" << endl;
    } else {
        cout << "Property purchased successfully!" << endl;
    }
    nav.find_property_menu(id);
}

void property::rent_a_prop(int id) {
    int selected_pincode;

    // Step 1: Display available pincodes
    ifstream pincode_file("pincode.csv");
    if (!pincode_file.is_open()) {
        cerr << "Error: Unable to open pincode.csv!" << endl;
        return;
    }

    vector<int> pincodes;
    string line;
    while (getline(pincode_file, line)) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); // Extract pincode
        pincodes.push_back(stoi(temp));
    }
    pincode_file.close();

    if (pincodes.empty()) {
        cout << "No pincodes available!" << endl;
        return;
    }

    cout << "Available Pincodes:\n";
    for (size_t i = 0; i < pincodes.size(); ++i) {
        cout << i + 1 << ". " << pincodes[i] << endl;
    }

    cout << "Enter the pincode where you want to search for properties: ";
    cin >> selected_pincode;

    if (find(pincodes.begin(), pincodes.end(), selected_pincode) == pincodes.end()) {
        cout << "Invalid pincode selected!" << endl;
        return;
    }

    // Step 2: Display properties for rent in the selected pincode
    ifstream property_file("property.csv");
    if (!property_file.is_open()) {
        cerr << "Error: Unable to open property.csv!" << endl;
        return;
    }

    vector<string> file_lines;
    vector<int> rent_properties;
    string property_line;
    bool properties_found = false;

    while (getline(property_file, property_line)) {
        file_lines.push_back(property_line); // Store lines for potential updates

        stringstream ss(property_line);
        string temp;
        int prop_id, pincode, for_rent;
        string name, owner;

        getline(ss, temp, ','); // Property ID
        prop_id = stoi(temp);

        getline(ss, name, ',');          // Name
        getline(ss, owner, ',');         // Owner
        getline(ss, temp, ',');          // Pincode
        pincode = stoi(temp);
        getline(ss, temp, ',');          // Skip Price
        getline(ss, temp, ',');          // Skip Area
        getline(ss, temp, ',');          // Skip For Sale
        getline(ss, temp, ',');          // For Rent
        for_rent = stoi(temp);

        if (pincode == selected_pincode && for_rent > 0) {
            rent_properties.push_back(prop_id);
            properties_found = true;
            cout << "Property ID: " << prop_id << "\n"
                 << "Name: " << name << "\n"
                 << "Owner: " << owner << "\n"
                 << "Rent Price: " << for_rent << "\n"
                 << "-----------------------------------\n";
        }
    }
    property_file.close();

    if (!properties_found) {
        cout << "No properties available for rent in the selected pincode.\n";
        return;
    }

    // Step 3: Ask the user to select a property to rent
    int selected_property;
    cout << "Enter the Property ID you want to rent: ";
    cin >> selected_property;

    if (find(rent_properties.begin(), rent_properties.end(), selected_property) == rent_properties.end()) {
        cout << "Invalid Property ID!" << endl;
        return;
    }

    // Step 4: Update the selected property in the CSV file
    ofstream temp_file("temp_property.csv");
    if (!temp_file.is_open()) {
        cerr << "Error: Unable to create temp_property.csv!" << endl;
        return;
    }

    for (const auto& line : file_lines) {
        stringstream ss(line);
        string temp;
        int prop_id;

        getline(ss, temp, ','); // Property ID
        prop_id = stoi(temp);

        if (prop_id == selected_property) {
            string updated_line;
            stringstream update_ss(line);
            vector<string> columns;

            // Parse columns into a vector
            while (getline(update_ss, temp, ',')) {
                columns.push_back(temp);
            }

            // Update rent column to 0 and set user ID to current user
            columns[7] = "0";          // For Rent column
            columns.back() = to_string(id); // User ID column

            // Reconstruct updated line
            for (size_t i = 0; i < columns.size(); ++i) {
                updated_line += columns[i];
                if (i != columns.size() - 1)
                    updated_line += ",";
            }

            temp_file << updated_line << "\n";
        } else {
            // Write the original line
            temp_file << line << "\n";
        }
    }

    temp_file.close();

    // Replace original file with updated file
    if (remove("property.csv") != 0 || rename("temp_property.csv", "property.csv") != 0) {
        cerr << "Error updating the property.csv file!" << endl;
    } else {
        cout << "Property rented successfully!" << endl;
    }
    nav.find_property_menu(id);
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
    cout<<"Welcome "<<users[id-1].name<<endl;
    nav.real_estate_menu(id);  
}


int main()
{


    // Copy properties.csv to property.csv
    std::ifstream src1("main_properties.csv", std::ios::binary);
    std::ofstream dest1("property.csv", std::ios::binary);
    dest1 << src1.rdbuf();
    src1.close();
    dest1.close();

    // Copy pincodes.csv to pincode.csv
    std::ifstream src2("main_pincodes.csv", std::ios::binary);
    std::ofstream dest2("pincode.csv", std::ios::binary);
    dest2 << src2.rdbuf();
    src2.close();
    dest2.close();


    // std::cout << "Files copied and originals deleted.\n";
    // return 0;


    nav.main_menu();
    return 0;
}
