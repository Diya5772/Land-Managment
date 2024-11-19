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
     int selection;
    cout << "Choose an option:\n1. Manage Property\n2. Find Property\n";
    cin >> selection;

    switch (selection)
    {
    case 1:
        manage_property_menu();
        break;
    case 2:
        find_property_menu();
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}
void navigation::manage_property_menu(void)
{
     int selection;
    cout << "Choose an option:\n1. edit property \n2. sell property  \n3. rent my property  \n4. show my property  \n5. add property\n";
    cin >> selection;

    switch (selection)
    {
    case 1:
        void edit_prop(vector<int>);
        break;
    case 2:
        void sell_prop(vector<int>);
        break;
    case 3:
        void rent_my_prop(void);
        break;
    case 4:
        void show_my_prop(vector<int>, int);
        break;
    case 5:
        void add_prop(vector<int> &);
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    cout << "Manage Property Menu" << endl;
}
void navigation::find_property_menu(void)
{
   int selection;
    cout << "Choose an option:\n1. buy property \n2. rent property  \n3. show property \n";
    cin >> selection;

    switch (selection)
    {
    case 1:
 void buy_prop(void);
         break;
    case 2:
        void rent_a_prop(void);
        break;
    case 3:
         void show_prop(void);
        break;
   
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    cout << "Find Property Menu" << endl;
}



class pincode_search
{
    public:
    void search_landmark(void);
};
void pincode_search::search_landmark(void)
{
    cout<<"Welcome to pincode search!"<<endl;
    cout<<"Here you can find and know all the landmarks of any city or area. "<<endl;
    vector<long int> available_pincodes {456368,685894,578493,589385,587959};
    for (long int i: available_pincodes) 
        cout<< i<<endl;
    long int input_pincode;
    cout<< "Enter the pincode you want to search from the above available pincodes: ";
    cin>> input_pincode;
    if (find(available_pincodes.begin(), available_pincodes.end(), input_pincode) == available_pincodes.end()) 
        cout << "Sorry, the entered pincode " << input_pincode << " is not available." << endl;
    else{
        cout<<"The landmarks and their details in the area is as follows: ";
    ifstream file("pincode.csv");
        if (!file.is_open()) {
            cerr << "Error displaying property!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.find(to_string(input_pincode)) != string::npos) {
                cout << line << endl;             }
        }

        file.close(); 
        }
    cout << "---------------------------------" << endl;

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
    cout << "Enter the property ID of the property you want to put for sale: ";
    int prop_id;
    cin >> prop_id;

    // Check if the property ID belongs to the user
    if (find(user_prop_id.begin(), user_prop_id.end(), prop_id) == user_prop_id.end()) {
        cout << "You do not own this property or the property ID is invalid." << endl;
        manage_property_menu();
        return;
    }

    bool property_found = false;

    // Open the input file and a temporary output file
    ifstream inputFile("properties.csv");
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

        // Check if the current row matches the property ID
        if (stoi(row_id) == prop_id) {
            property_found = true;

            // Update the "for_sale" column to "Y"
            for_sale = "Y";
        }

        // Write the row to the temp file (updated or unchanged)
        tempFile << row_id << "," << name << "," << owner << "," << pincode << ","
                 << price << "," << area << "," << for_sale << "," << for_rent << "," << type << "\n";
    }

    inputFile.close();
    tempFile.close();

    if (!property_found) {
        cout << "Property ID not found in the file." << endl;
        remove("temp.csv");
        return;
    }

    // Replace the original file with the updated file
    remove("properties.csv");
    rename("temp.csv", "properties.csv");

    cout << "Property with ID " << prop_id << " has been successfully marked for sale!" << endl;
    manage_property_menu();
    return;


}
void property::rent_my_prop(void)
{
    //code
}
void property::show_prop(void)
{
    cout<< "Properties of the following pincodes are available: "<<endl;
    vector<long int> available_pincodes {456368,685894,578493,589385,587959};
    for (long int i: available_pincodes) 
        cout<< i<<endl;
    long int input_pincode;
    cout<< "Enter the pincode you want to search from the above available pincodes: ";
    cin>> input_pincode;
    if (find(available_pincodes.begin(), available_pincodes.end(), input_pincode) == available_pincodes.end()) 
        cout << "Sorry, the entered pincode " << input_pincode << " is not available." << endl;
    else{
        cout<<"The data of properties of this area is as follows: ";
    ifstream file("properties.csv");
        if (!file.is_open()) {
            cerr << "Error displaying property!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.find(to_string(input_pincode)) != string::npos) {
                cout << line << endl;             }
        }

        file.close(); 

    }
    cout << "---------------------------------" << endl;

}



void property::buy_prop(void)
{
    //code
}
void property::rent_a_prop(void)
{
    //code
}


class User {
    static int nextID;  
    static unordered_map<int, string> userDirectory; 
    string name;
    int age, user_id;
    vector<int> user_prop; 

public:
    void user_register();
    static string getUserNameByID(int id);

    int getUserID() const {
        return user_id;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    vector<int> getUserProp() const {
        return user_prop;
    }
};


int User::nextID = 1;
unordered_map<int, string> User::userDirectory;

void User::user_register() {
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your age: ";
    cin >> age;
    user_id = nextID++;
    userDirectory[user_id] = name;  
    cout << "Registration successful. Your user ID is " << user_id << endl;
}

string User::getUserNameByID(int id) {
    if (userDirectory.find(id) != userDirectory.end()) {
        return userDirectory[id];
    } else {
        return "User ID not found.";
    }
}


   int main()
{
    vector<User> users;
    navigation nav;
    char choice;

    do
    {
        cout << "Choose an option:\n1. Register User\n2. Look up User by ID\n3. Exit\n";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            User newUser;
            newUser.user_register();
            users.push_back(newUser);
            break;
        }
        case '2':
        {
            int lookupID;
            cout << "Enter user ID to lookup: ";
            cin >> lookupID;
            cout << "User Name: " << User::getUserNameByID(lookupID) << endl;
            nav.real_estate_menu();
            break;
        }
        case '3':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != '3');

    return 0;
}
