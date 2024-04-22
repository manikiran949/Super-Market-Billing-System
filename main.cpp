#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <unistd.h>
#include <ctime>
#include <vector> 
#include <map>
#include <utility> 

using namespace std;

class ItemDetails{
    protected: // taken protected, so that we can inherit.
    string Item;
    double Price;
    friend class BillingSystem;
};

class Bill : private ItemDetails{

private:
    int Quantity;
    friend class BillingSystem;
public:

    // constructor
    Bill(string Item,double Price,int Quantity){
        this -> Item = Item;
        this -> Price = Price;
        this -> Quantity = Quantity;
    }

     // Overloaded constructor without Quantity parameter
    Bill(string Item, double Price) {
        this->Item = Item;
        this->Price = Price;
        this->Quantity = 1; // Default quantity is 1
    }

    // setter functions.
    void setItem(string Item){
        this -> Item = Item;
    }

    void setPrice(double Price){
        this -> Price = Price;
    }

    void setQuantity(int Quantity){
        this -> Quantity = Quantity;
    }
    
    // getter functions
    string getItem(){
        return Item;
    }

    double getPrice(){
        return Price;
    }

    int getQuantity(){
        return Quantity;
    }

    // destructor.
    ~Bill(){
        // no cleanup required.
    }
};


class BillingSystem{

    public:
    
    void print_receipt(double x,double fd,double gst,bool carrybag){
        // to print the final receipt.

        cout << "\t\t\t\t\t\t SubTotal    :  " << x << "/-" << endl;
        cout << "\t\t\t\t\t\t Discounts   : -" << fd << "/-" << endl;
        cout << "\t\t\t\t\t\t CGST 2.5%   :  " << gst << "/-" << endl;
        cout << "\t\t\t\t\t\t SGST 2.5%   :  " << gst << "/-" << endl;

        double mk = 0;
        if(carrybag) mk = 5.0;
        cout << "\t\t\t\t\t\t Carry Bag   :  " << mk << "/-" << endl;
        // cout << endl;
        cout << "\t\t\t\t\t\t------------------------" << endl;
        cout << "\t\t\t\t\t\t Grand Total : " << "Rs " << x + 2 * gst + mk - fd << "/-" << endl; 
        cout << "\t\t\t\t\t\t------------------------" << endl;
        cout << endl << endl;
        cout << "\t\t\t   Thank you For Shopping with us ! Please visit us again !" << endl;

        cout << endl << endl;
    }

    void show_cart(map<string, int> &cur_cart, map<string,double> &vp){
        cout << "\t\tCurrent Cart :- " << endl << endl;
        if((int)cur_cart.size() == 0){
            // nothing in the cart.
            cout << "\t\tYour Cart is Empty :(" << endl;
        }
        // print the cart.
        for(auto it : cur_cart){
            cout << "\t\t" << it.first << " : " << it.second << endl;
        }
        double total_price = 0.0;
        for(auto it : vp){
            total_price += it.second;
        }
        cout << endl;
        cout << "\t\tCurrent Total : " << total_price << endl;
    }
    
    double calculate_gst(double x,double fd){
        // calculating gst : 2.5% of the subtotal.
        double gst = (2.5 * 1.0/100) * (x - fd)*1.0;
        return gst;
    }

    void ViewStock(){
        // view all the available items in the stock through reading the file.
        ifstream file("C:/Users/MANIKIRAN/Desktop/OOPS Project/shop.txt");
        if (!file.is_open()) {
            cerr << "Error ! , Unable to open the file" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
        return;
    } 

    void updateItem(ItemDetails &item, const string& newItem, double newPrice){
        item.Item = newItem;
        item.Price = newPrice;
    }

    void updateBill(Bill &bill, const string& newItem, double newPrice, int newQuantity){
        bill.Item = newItem;
        bill.Price = newPrice;
        bill.Quantity = newQuantity;
    }

};


void print_date_time(){
    // to print the current date and time.
    time_t now = time(0); 
    tm* ltm = localtime(&now);
    // generate random numbers using rand().
    cout << "\t\t\tCashier ID : " << 1000 + rand()%1000 << "\t\t\t Date : " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
    cout << "\t\t\tBill No    : " << 1 + rand()%10 << "\t\t\t\t Time : " << ltm->tm_hour <<":"<< ltm->tm_min << ":" << ltm->tm_sec << endl;
    cout << endl;
    cout << "\t\t\t**********************************************************";
    cout << endl;
    return;
}

// to add items into stock.
int addItem(){
    bool close = false;
    
    while (!close){
        string choice;
        cout << endl;
        system("cls");
        cout << "\tYou are Adding item(s) to the stock : ";
        cout << endl << endl;
        cout << "\t1) Add an item " << endl;
        cout << "\t2) Exit stock " << endl;
        cout << endl;
        cout << "\tPlease Enter Choice : ";
        cin >> choice;

        if (choice == "1"){
            system("cls");
            string item;
            int Quant;
            cout << endl;
            cout << "\tItem Details : " << endl << endl;
            cout << "\tName of the item you wish to add : ";
            cin >> item;
            double rate;
            cout << "\tEnter Price Of the Item : "; 
            cin >> rate;

            cout << "\tEnter Quantity Of the Item : ";
            cin >> Quant;
            Bill b(item,rate,Quant);

            // append the item details into the file.
            ofstream out("C:/Users/MANIKIRAN/Desktop/OOPS Project/shop.txt", ios::app);
            if (!out){
                cout << "\tError: File Can't Open !" << endl;
            }

            else{
                out << "\t " << b.getItem() << " :  " << b.getPrice() << " :  " << b.getQuantity() << endl << endl;
            }
            out.close();
            cout << endl;
            cout << "\tItem Added Successfully !" << endl;
            Sleep(3000);
        }

        else if (choice == "2"){
            system("cls");
            close = true;
            cout << "\tReturning To Main Menu !" << endl;
            Sleep(1);
            // Sleep(4000);
        }
        else{
            cout << endl;
            cout << "\tINVALID Option ! Please Enter a Valid Choice !" << endl;
            Sleep(4000);
        }
    }
}
 


// to add items into cart and then print the bill.
int Add_to_cart(BillingSystem billingSystem){

    map<string,double> vp;
    system("cls");
    double count = 0;
    bool close = false;
    // bool to check if user wants carrybag or festival discount.
    bool carrybag = false;
    bool festive_discount = false;
    // map to store the items and their quantities in the cart.
    map<string, int> cur_cart;
    while (!close){
        system("cls");
        string choice;

        cout << "\t1) Add Items(s) to Cart " << endl;
        cout << "\t2) View Cart " << endl;
        cout << "\t3) Proceed to check out " << endl;
        cout << endl;
        cout << "\tPlease Enter your choice : ";
        cin >> choice;

        if (choice == "1"){
            string item;
            int Quant;
            cout << "\tEnter Item : ";
            cin >> item;
            cout << "\tEnter Quantity : ";
            cin >> Quant;
            cout << endl;
            ifstream in("C:/Users/MANIKIRAN/Desktop/OOPS Project/shop.txt");
            ofstream out("C:/Users/MANIKIRAN/Desktop/OOPS Project/shop tmp.txt");
            string line;
            bool found = false;

            while (getline(in, line)){
                stringstream ss;
                ss << line;
                string itemName;
                double itemPrice;
                int itemQuant;
                char tempchar;
                ss >> itemName >> tempchar >> itemPrice >> tempchar >> itemQuant;
                if (item == itemName){
                    found = true;
                    if (Quant <= itemQuant){
                        double amount = itemPrice * Quant;
                        cout << "\t Item | Price | Quantity | Amount" << endl << endl;
                        cur_cart[item] += Quant;
                        vp[itemName] += amount;
                        cout << "\t " << itemName << "\t " << itemPrice << "\t " << Quant << "\t " << amount;
                        cout << endl;
                        int cur_Quantity = itemQuant - Quant;
                        itemQuant = cur_Quantity;
                        count += amount;
                        out << "\t" << itemName << " : " << itemPrice << " : " << itemQuant << endl;
                    }
                    else{
                        // when requested quantity is greater than available quantity.
                        // so we should write back into the file the original quantity of the stock.
                        out << "\t" << itemName << " : " << itemPrice << " : " << itemQuant << endl;
                        cout << "\tSorry, " << item << " is out of stock !" << endl;
                    }
                }
                else{
                    out << line << endl;
                }
            }
            if (!found){
                // if the item was never available.
                cout << "\tItem is currently Unavailable !" << endl;
            }
            out.close();
            in.close();
            remove("C:/Users/MANIKIRAN/Desktop/OOPS Project/shop.txt");
            rename("C:/Users/MANIKIRAN/Desktop/OOPS Project/shop tmp.txt", "C:/Users/MANIKIRAN/Desktop/OOPS Project/shop.txt");
        }

        else if(choice == "2"){
            system("cls");
            // print the cart.
            billingSystem.show_cart(cur_cart,vp);
            Sleep(5000);
        }

        else if (choice == "3"){
            close = true;
            cout << endl << endl;
            system("cls");
            // add festival discount.
            cout << endl << endl;
            cout << "\t\tAdd Festival Discount ? " << endl;
            cout << endl;
            cout << "\t\t1) Yes" << endl;
            cout << "\t\t2) No" << endl;
            cout << endl;
            cout << "\t\tPlease Enter your choice : ";
            string cur_choice;
            cin >> cur_choice;

            if(cur_choice == "1"){
                festive_discount = 1;
                cout << endl;
                cout << "\t\tFestival discount of 10% applied :) ";
                cout << endl;
                Sleep(3000);
            }

            system("cls");
            cout << endl << endl;
            cout << "\t\tDo you need carry bag ? " << endl;
            cout << endl;
            string ch;
            cout << "\t\t1) Yes" << endl;
            cout << "\t\t2) No" << endl;
            cout << endl;
            cout << "\t\tPlease Enter your choice : ";
            cin >> ch;
            if(ch == "1"){
                carrybag = 1;
            }
            cout << endl;
            cout << endl;
            cout << "\t\tCalculating Total Bill ......" << endl;
        }

        else {
            cout << endl;
            cout << "\tINVALID Option ! Please Enter a Valid Choice !" << endl;
        }

        Sleep(4000);
    }

    system("cls");
    cout << endl << endl;
    cout << "\t\t\t\t\t\tSMK SHOPPING MALL" << endl;
    cout << "\t\t\t\t\t     GSTIN : 38AANCA1901C1Z6" << endl;
    cout << endl;
    cout << "\t\t\t**********************************************************";
    cout << endl;
    print_date_time();
    double x = count * 1.0;
    cout << endl;
    int sz = vp.size();
    int max_width = 0;
    vector<pair<string,double>> all;
    for(auto it : vp){
        all.push_back({it.first, it.second});
    }
    for (int i = 0; i < sz; i++) {
       int width = all[i].first.size();
       if (width > max_width)
           max_width = width;
    }

    for (int i = 0; i < sz; i++) {
       cout << "\t\t\t                         " << all[i].first; 
       for (int j = 0; j < max_width - all[i].first.size(); j++) {
          cout << " ";
       }
       cout << "\t     :  ";
       cout << all[i].second << "/-" << endl;
    }

    cout << endl;
    double fd = 0.0;
    if(festive_discount) fd = 0.1 * x; 
    
    // calculate the bill after removing discount.
    double gst = billingSystem.calculate_gst(x, fd);
    billingSystem.print_receipt(x,fd,gst,carrybag);
    
    Sleep(300000);
}


int main(){
    srand(time(0));
    bool exit = false;
    BillingSystem billingSystem;
    while (!exit){
        system("cls");
        string val;
        cout << "\t\t\t\t\t\tCS 212 OOPs PROJECT" << endl;
        cout << endl;
        cout << "\t\tWelcome To Super Market Billing System by Mani Kiran (2212056) and Sathish (2212055) ! " << endl;
        cout << endl;
        cout << "\t\t1) Add Item(s) to stock" << endl;
        cout << "\t\t2) Add Item(s) to cart" << endl;
        cout << "\t\t3) View stock" << endl;
        cout << "\t\t4) Exit" << endl;
        cout << endl;
        cout << "\t\tPlease Enter your choice : ";
        cin >> val;

        if (val == "1"){
            system("cls");
            // add items into stock.
            addItem();
            Sleep(3000);
        }

        else if (val == "2"){
            // go to cart.
            Add_to_cart(billingSystem);
        }

        else if(val == "3") {
            system("cls");
            cout << endl << endl;
            // print the items in the stock.
            cout << "\tName  Price  Quantity";
            cout << endl << endl;
            billingSystem.ViewStock();
            cout << "\tEnter 1 to leave stock : ";
            string str; 
            cin >> str;
            //Sleep(9000);
        }

        else if(val == "4"){
            system("cls");
            exit = true;
            cout << endl << endl;
            cout << "\t\t  Thank you for Visiting ! Please visit us again !" << endl;
            Sleep(7000);
        }

        else{
            cout << endl;
            cout << "\t\tINVALID Option ! Please Enter a Valid Choice !" << endl;
            Sleep(4000);
        }
    }
}
