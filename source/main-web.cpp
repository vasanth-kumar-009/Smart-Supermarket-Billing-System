#include <iostream>
#include <fstream>
#include <sstream>
#include "browser_terminal.h"
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) {
        Item = item;
    }

    void setRate(int rate) {
        Rate = rate;
    }

    void setQuant(int quant) {
        Quantity = quant;
    }

    string getItem() {
        return Item;
    }

    int getRate() {
        return Rate;
    }

    int getQuant() {
        return Quantity;
    }
};

void addItem(Bill b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1.Add." << endl;
        cout << "\t2.close." << endl;
        cout << "\tEnter Choice: ";
        readValue(choice);

        if (choice == 1) {
            // Browser terminal keeps the output history visible.
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            readValue(item);
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            readValue(rate);
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            readValue(quant);
            b.setQuant(quant);

            ofstream out("Bill.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            }
            else {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl
                    << endl;
            }
            out.close();
            cout << "\tItem Added Successfuly" << endl;
            Sleep(3000);
        }

        else if (choice == 2) {
            // Browser terminal keeps the output history visible.
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(3000);
        }
    }
}

void printBill() {
    // Browser terminal keeps the output history visible.
    int count = 0;
    bool close = false;
    while (!close) {
        // Browser terminal keeps the output history visible.
        int choice;
        cout << "\t1.Add Bill." << endl;
        cout << "\t2.Close Session." << endl;
        cout << "\tEnter Choice: ";
        readValue(choice);

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            readValue(item);
            cout << "\tEnter Quantity: ";
            readValue(quant);

            ifstream in("Bill.txt");
            ofstream out("Bill Temp.txt");

            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss;
                ss << line;
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                if (!(ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant)) {
                    out << line << endl;
                    continue;
                }

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << "\t " << itemRate << "\t " << quant << "\t " << amount << endl;
                        int newQuant = itemQuant - quant;
                        itemQuant = newQuant;
                        count += amount;

                        out << "\t" << itemName << " : " << itemRate << " : " << itemQuant << endl;
                    }
                    else {
                        cout << "\tSorry, " << item << " Ended!" << endl;
                        out << line << endl; // Keep stock when a purchase cannot be fulfilled.
                    }
                }
                else {
                    out << line << endl;
                }
            }
            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }
            out.close();
            in.close();
            remove("Bill.txt");
            rename("Bill Temp.txt", "Bill.txt");
        }
        else if (choice == 2) {
            close = true;
            cout << "\tCounting Total Bill" << endl;
        }
        Sleep(3000);
    }
    // Browser terminal keeps the output history visible.
    cout << endl
         << endl;
    cout << "\t Total Bill ----------------- : " << count << endl
         << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(3000);
}

int main() {
    setupBrowserTerminal();
    Bill b;

    bool exit = false;
    while (!exit) {
        // Browser terminal keeps the output history visible.
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1.Add Item." << endl;
        cout << "\t\t2.Print Bill." << endl;
        cout << "\t\t3.Exit." << endl;
        cout << "\t\tEnter Choice: ";
        readValue(val);

        if (val == 1) {
            // Browser terminal keeps the output history visible.
            addItem(b);
            Sleep(3000);
        }

        else if (val == 2) {
            printBill();
        }

        else if (val == 3) {
            // Browser terminal keeps the output history visible.
            exit = true;
            cout << "\tThank You for Shopping! See you again" << endl;
            Sleep(3000);
        }
    }
}
