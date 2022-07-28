#include <iostream>
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
