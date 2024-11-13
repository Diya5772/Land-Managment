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


class property
{
    //data members
    int prop_id, pincode;
    string prop_name, owner, type;
    double price, area;
    bool for_sale, for_rent;

    public:
    //functions for manage property
    void edit_prop(void);
    void sell_prop(void);
    void rent_my_prop(void);
    void show_my_prop(void);
    void add_prop(void);
    //functions for find a property
    void buy_prop(void);
    void rent_a_prop(void);
    void show_prop(void);
};
void property::edit_prop(void)
{
    //code
}
void property::add_prop(void)
{
    //code
}
void property::show_my_prop(void)
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