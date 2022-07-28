#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::string;

class shopping
{
private:
    int prodCode;
    float price;
    float discount;
    string prodName;

public:
    void menu();
    void admin();
    void customer();
    void add();
    void edit();
    void remove();
    void list();
    void receipt();
};

void shopping::menu()
{
m:
    int option;
    string email;
    string password;

    // Menu display
    cout << "\t\t\t\t*************\n";
    cout << "\t\t\t\t  Main Menu\n";
    cout << "\t\t\t\t*************\n";
    cout << "\t\t1) Administrator\n";
    cout << "\t\t2) Customer\n";
    cout << "\t\t3) Exit\n";
    cout << "\nPlease select.\n";

    // User input
    cin >> option;
    switch (option)
    {
    case 1:
        cout << "\nPlease log in.\n";
        cout << "Enter Email.\n";
        cin >> email;
        cout << "Enter Password.\n";
        cin >> password;

        if (email == "admin" && password == "pass")
        {
            admin();
        }
        else
        {
            cout << "Invalid email/password.\n";
        }
        break;

    case 2:
        customer();
        break;

    case 3:
        exit(0);
        break;

    default:
        cout << "Invalid choice. Please select one of the given options.\n";
        break;
    }
    goto m;
}

void shopping::admin()
{
a:
    int option;
    cout << "\t\t\t\t**************\n";
    cout << "\t\t\t\t  Admin Menu\n";
    cout << "\t\t\t\t**************\n";
    cout << "\t\t1) Add product\n";
    cout << "\t\t2) Edit product\n";
    cout << "\t\t3) Delete product\n";
    cout << "\t\t4) Return to main menu\n";
    cout << "\nPlease select.\n";

    // User input
    cin >> option;
    switch (option)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        remove();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Invalid choice. Please select one of the given options.\n";
        break;
    }
    goto a;
}

void shopping::customer()
{
c:
    int option;
    cout << "\t\t\t\t*****************\n";
    cout << "\t\t\t\t  Customer Menu\n";
    cout << "\t\t\t\t*****************\n";
    cout << "\t\t1) Order products\n";
    cout << "\t\t2) Return to main menu\n";
    cout << "\nPlease select.\n";

    // User input
    cin >> option;
    switch (option)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "Invalid choice. Please select one of the given options.\n";
        break;
    }
    goto c;
}

void shopping::add()
/* 
Bug:
Adds the first item twice when creating the db
*/ 
{
m:
    std::fstream data;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\t\tAdd a new product\n";
    cout << "\t\tEnter the product's product code:\n";
    cin >> prodCode;
    cout << "\t\tEnter the product's name:\n";
    cin >> prodName;
    cout << "\t\tEnter the product's price:\n";
    cin >> price;
    cout << "\t\tEnter any applicable discounts on the product:\n";
    cin >> discount;

    data.open("database.txt", std::ios::in);

    if (!data)
    {
        data.open("database.txt", std::ios::app | std::ios::out);
        data << " " << prodCode << " " << prodName << " " << price << " " << discount << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (c == prodCode)
            {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
    }

    if (token == 1)
    {
        goto m;
    }
    else
    {
        data.open("database.txt", std::ios::app | std::ios::out);
        data << " " << prodCode << " " << prodName << " " << price << " " << discount << "\n";
        data.close();
    }
    cout << "\t\tProduct successfully entered.\n";
}

void shopping::edit()
{
    std::fstream data, data1;
    int token = 0;
    int key;
    int c;
    float p;
    float d;
    string n;

    cout << "\t\tEdit an existing product\n";
    cout << "\t\tEnter the product's product code:\n";
    cin >> key;

    data.open("database.txt", std::ios::in);

    if (!data)
    {
        cout << "\t\tFile doesn't exist.\n";
    }
    else
    {
        data1.open("database1.txt", std::ios::app | std::ios::out);
        data >> prodCode >> prodName >> price >> discount;
        while (!data.eof())
        {
            if (key == prodCode)
            {
                cout << "\t\tEditing product:" << prodCode;
                cout << "\n\t\tEnter the product's product code:\n";
                cin >> c;
                cout << "\t\tEnter the product's name:\n";
                cin >> n;
                cout << "\t\tEnter the product's price:\n";
                cin >> p;
                cout << "\t\tEnter any applicable discounts on the product:\n";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\t\tProduct successfully edited.\n";
                token++;
            }
            else
            {
                data1 << " " << prodCode << " " << prodName << " " << price << " " << discount << "\n";
            }
            data >> prodCode >> prodName >> price >> discount;
        }
        data.close();
        data1.close();

        std::remove("database.txt");
        std::rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\t\tProduct not found.\n";
        }
    }
}

void shopping::remove()
{
    std::fstream data, data1;
    int token = 0;
    int key;

    cout << "\t\tDelete a product\n";
    cout << "\t\tEnter the product's product code:\n";
    cin >> key;

    data.open("database.txt", std::ios::in);

    if (!data)
    {
        cout << "\t\tFile doesn't exist.\n";
    }
    else
    {
        data1.open("database1.txt", std::ios::app | std::ios::out);
        data >> prodCode >> prodName >> price >> discount;
        while (!data.eof())
        {
            if (key == prodCode)
            {
                cout << "\t\tProduct " << prodCode << " deleted.";
                token++;
            }
            else
            {
                data1 << " " << prodCode << " " << prodName << " " << price << " " << discount << "\n";
            }
            data >> prodCode >> prodName >> price >> discount;
        }
        data.close();
        data1.close();

        std::remove("database.txt");
        std::rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\t\tProduct not found.\n";
        }
    }
}

void shopping::list()
{
    std::fstream data;
    data.open("database.txt", std::ios::in);

    cout << "\t****************************************************\n";
    cout << "\t\tCode\t\tName\t\tPrice\n";
    cout << "\t****************************************************\n";

    data >> prodCode >> prodName >> price >> discount;
    while (!data.eof())
    {
        cout << "\t\t" << prodCode << "\t\t" << prodName << "\t\t" << price << "\n";
        data >> prodCode >> prodName >> price >> discount;
    }

    data.close();
}

void shopping::receipt()
{
    std::fstream data;
    int arrayC[100];
    int arrayQ[100];
    char options;
    int count = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

    cout << "\t\t\t\t**************\n";
    cout << "\t\t\t\t  Order Form\n";
    cout << "\t\t\t\t**************\n";

    data.open("database.txt", std::ios::in);

    if (!data)
    {
        cout << "\t\tFile doesn't exist.\n";
    }
    else
    {
        data.close();

        list();

        cout << "\t\tPlace an order...\n\n";
        cout << "\t\t\n";

        do
        {
        m:
            cout << "\nEnter the product code: ";
            cin >> arrayC[count];
            cout << "\nHow many of the product are you ordering? ";
            cin >> arrayQ[count];

            for (int i = 0; i < count; i++)
            {
                if (arrayC[i] == arrayC[count])
                {
                    cout << "\nThis product has already been added to the order. Please try again.";
                    goto m;
                }
            }
            count++;

            cout << "\nDo you have more to add to the order? (y/n) ";
            cin >> options;
        } while (options == 'y');

        cout << "\t**********************************************************************************************************\n";
        cout << "\t\tCode\t\tName\t\tQuantity\tPrice\t\tTotal\t\tDiscounted\n";
        cout << "\t**********************************************************************************************************\n";

        for (int i = 0; i < count; i++)
        {
            data.open("database.txt", std::ios::in);
            data >> prodCode >> prodName >> price >> discount;
            while (!data.eof())
            {
                if (arrayC[i] == prodCode)
                {
                    amount = price * arrayQ[i];
                    discount = amount - (amount*discount/100);
                    discount = std::round(discount * 100.0) / 100.0;
                    total = total + discount;
                    cout << "\t\t" << prodCode << "\t\t" << prodName << "\t\t" << arrayQ[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << discount << "\n";
                }
                data >> prodCode >> prodName >> price >> discount;
            }

            data.close();
        }
        
        cout << "\t**********************************************************************************************************\n";
        cout << "\n\tTotal: " << total << "\n\n";
    }
}

int main(){
    shopping s;
    s.menu();
    return 0;
}
