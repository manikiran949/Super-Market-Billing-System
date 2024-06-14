# 🛒 Supermarket Billing System

A console-based application written in C++ for managing a supermarket's inventory and billing process. This project provides features such as inventory management, cart management, GST calculations, and more.

## 🚀 Features

- 📦 **Inventory Management**: Add, update, and view stock items.
- 🛒 **Cart Management**: Add items to the cart, view the cart, and proceed to checkout.
- 🧾 **Billing**: Calculate the total bill with GST and optional discounts.
- 📁 **File I/O Operations**: Store and retrieve item details using file operations.

## 🛠️ Project Structure

- `ItemDetails`: A class to store details of individual items.
- `Bill`: A class derived from `ItemDetails` to handle billing details including quantity.
- `BillingSystem`: A class to manage the overall billing process, including receipt generation and stock management.

## 📋 Usage

### Adding Items to Stock

To add items to the stock, run the program and select the option to add items. Enter the item name, price, and quantity as prompted.

### Adding Items to Cart

To add items to the cart, run the program and select the option to add items to the cart. Enter the item name and quantity as prompted. You can view the cart and proceed to checkout from the menu options.

### Viewing Stock

To view the available stock, select the option to view stock. The stock details will be displayed on the console.

### Checkout Process

During the checkout process, you can choose to apply a festival discount and add a carry bag. The final bill will be calculated with GST and displayed.

## 📄 Code Example

Here's a snippet of the main function demonstrating how the application runs:

```cpp
int main() {
    srand(time(0));
    bool exit = false;
    BillingSystem billingSystem;
    while (!exit) {
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

        if (val == "1") {
            system("cls");
            addItem();
            Sleep(3000);
        }
        else if (val == "2") {
            Add_to_cart(billingSystem);
        }
        else if (val == "3") {
            system("cls");
            cout << endl << endl;
            cout << "\tName  Price  Quantity";
            cout << endl << endl;
            billingSystem.ViewStock();
            cout << "\tEnter 1 to leave stock : ";
            string str; 
            cin >> str;
        }
        else if (val == "4") {
            system("cls");
            exit = true;
            cout << endl << endl;
            cout << "\t\t  Thank you for Visiting ! Please visit us again !" << endl;
            Sleep(7000);
        }
        else {
            cout << endl;
            cout << "\t\tINVALID Option ! Please Enter a Valid Choice !" << endl;
            Sleep(4000);
        }
    }
}
```

## 📦 Dependencies

- C++ Standard Library
- Windows.h (for Sleep function)
- I/O Streams for file operations

## ⚙️ Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/supermarket-billing-system.git
   ```
2. **Navigate to the project directory**:
   ```bash
   cd supermarket-billing-system
   ```
3. **Compile the project**:
   ```bash
   g++ -o SupermarketBillingSystem main.cpp
   ```
4. **Run the executable**:
   ```bash
   ./SupermarketBillingSystem
   ```

## 👨‍💻 Authors

- **Mani Kiran** - [GitHub](https://github.com/manikiran949)
- **Sathish** - [GitHub](https://github.com/Satjaxxs)

