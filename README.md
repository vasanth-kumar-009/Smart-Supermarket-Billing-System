<div align="center">

# 🛒 Smart Supermarket Billing System

### C++ Object-Oriented Programming Project with an Interactive Web Demo

A menu-driven supermarket inventory and billing application developed in **C++**, with a separate **HTML, CSS, and JavaScript** browser demo to showcase its functionality.

[![C++](https://img.shields.io/badge/C%2B%2B-Console%20Application-00599C?logo=cplusplus&logoColor=white)](main.cpp)
[![OOP](https://img.shields.io/badge/Concepts-OOP%20%26%20File%20Handling-blue)](main.cpp)
[![Live Demo](https://img.shields.io/badge/Live%20Demo-GitHub%20Pages-success)](https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/)

**[🌐 Try Browser Demo](https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/)** · **[💻 View C++ Source](main.cpp)**

</div>

---

## 📌 Overview

**Smart Supermarket Billing System** is a console-based application built to practice fundamental **Object-Oriented Programming (OOP)** and **file handling in C++**. It allows a supermarket operator to add products, generate bills for customers, calculate purchase totals, and update available stock as items are sold.

The original C++ program stores inventory records in a local `Bill.txt` file. A separate browser-based demonstration is provided so visitors can explore a similar workflow without installing a compiler.

> **Note:** The browser demo is a JavaScript recreation of the C++ application's behavior. GitHub Pages hosts the web files; it does **not** compile or execute `main.cpp`.

## ✨ Features

### Original C++ application

- **Add products:** Enter an item name, unit rate, and available quantity.
- **Store inventory:** Append product records to `Bill.txt` using C++ file streams.
- **Create customer bills:** Select products and quantities to purchase.
- **Calculate totals:** Compute each purchased item's amount (`rate × quantity`) and accumulate the bill total.
- **Update stock:** Reduce stored quantities after a valid purchase.
- **Check availability:** Display a message when an item does not exist or sufficient stock is unavailable.
- **Menu-driven interaction:** Navigate between adding products, billing, and exiting the program.

### Interactive browser demo

- Add products using a form.
- View available inventory in a table.
- Add products to a customer bill and see the running total.
- Update stock quantities when products are billed.
- Print a receipt or save it as a PDF using the browser's print dialog.
- Clear a billing session or reset inventory.
- Retain inventory in the current browser using `localStorage` (no server or database required).

## 🧰 Tech Stack

| Component | Technology | Purpose |
| --- | --- | --- |
| Core application | C++ | Console-based billing and inventory logic |
| Programming concepts | OOP | Classes, objects, encapsulation, constructors, getters, and setters |
| Inventory persistence (C++) | `<fstream>` / text file | Read and update stock in `Bill.txt` |
| Record parsing (C++) | `<sstream>` | Parse stored product details |
| Web demo UI | HTML5 and CSS3 | Browser interface and responsive layout |
| Web demo behavior | JavaScript | Recreate inventory and billing interactions |
| Web demo persistence | Browser `localStorage` | Store inventory on the visitor's device |
| Web hosting | GitHub Pages and GitHub Actions | Publish the static demo |

## 🧠 OOP Concepts Demonstrated

The original program defines a `Bill` class to represent product details.

| OOP concept | Implementation |
| --- | --- |
| **Class and object** | `Bill` defines product data and methods; `main()` creates a `Bill` object. |
| **Encapsulation** | `Item`, `Rate`, and `Quantity` are private data members. |
| **Constructor** | `Bill()` initializes the product name, rate, and quantity. |
| **Setters** | `setItem()`, `setRate()`, and `setQuant()` assign product details. |
| **Getters** | `getItem()`, `getRate()`, and `getQuant()` read product details. |

The project focuses on these core OOP fundamentals. **Inheritance and polymorphism are not implemented** in the current C++ code.

## 📁 Project Structure

```text
Smart-Supermarket-Billing-System/
├── .github/
│   └── workflows/       # GitHub Pages deployment workflow
├── public/
│   ├── index.html       # Browser demo page
│   ├── style.css        # Demo styling
│   └── function.js      # Browser inventory and billing logic
├── .gitignore
├── main.cpp             # Original C++ console application
├── main.exe             # Windows executable (included in repository)
└── README.md            # Project documentation
```

When the C++ application is run and an item is added, it creates or updates a local `Bill.txt` inventory file in its working directory.

## ⚙️ Run the Original C++ Project

### Prerequisites

- **Windows** (the original source uses `windows.h`, `Sleep()`, and `system("cls")`).
- A C++ compiler such as **MinGW-w64 g++**, or a compatible C++ IDE/toolchain.

### Steps

1. Clone the repository:

   ```bash
   git clone https://github.com/vasanth-kumar-009/Smart-Supermarket-Billing-System.git
   ```

2. Open the project directory:

   ```bash
   cd Smart-Supermarket-Billing-System
   ```

3. Compile the program in a Windows terminal with `g++` available:

   ```bash
   g++ main.cpp -o supermarket.exe
   ```

4. Run the executable:

   ```powershell
   .\supermarket.exe
   ```

The program displays a menu with options to **Add Item**, **Print Bill**, or **Exit**.

> The original C++ source is Windows-specific and is not directly runnable on GitHub Pages or a typical Linux-based online compiler without adjustments.

## 🖥️ How to Use the Application

1. Select **Add Item** from the main menu.
2. Enter the product name, price per unit, and stock quantity. Repeat for more products.
3. Return to the main menu and choose **Print Bill**.
4. Enter a product name and the quantity the customer wants to purchase.
5. For available stock, the program calculates the amount and deducts the purchased quantity.
6. Continue adding items, then select **Close Session** to view the final bill total.

### Example

Suppose the inventory contains:

| Item | Unit rate | Initial stock |
| --- | ---: | ---: |
| Rice | ₹80 | 10 |
| Sugar | ₹45 | 8 |

A customer purchases **2 Rice** and **3 Sugar**:

| Item | Rate | Quantity | Amount |
| --- | ---: | ---: | ---: |
| Rice | ₹80 | 2 | ₹160 |
| Sugar | ₹45 | 3 | ₹135 |
| **Total** | | | **₹295** |

After the purchase, the stock becomes **8 Rice** and **5 Sugar**.

*This is an illustrative example of the billing workflow, not a screenshot of program output.*

## 🌐 Interactive Browser Demo

**[Open the Live Demo](https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/)**

The demo is served from the [`public/`](public/) folder and provides a convenient interface for exploring the project's features.

**Try it:** Add a product → Open **Print Bill** → Select an item and quantity → Add it to the bill → Print/save the receipt.

### Differences Between the C++ Program and the Browser Demo

| Aspect | Original C++ program | Browser demo |
| --- | --- | --- |
| Interface | Windows console | Web browser |
| Application logic | C++ | JavaScript adaptation |
| Inventory storage | Local `Bill.txt` | Browser `localStorage` |
| Billing | Console output | On-page receipt with print/PDF option |
| Installation | Windows C++ compiler/executable | None; open in a browser |

**Privacy/storage note:** Browser inventory data stays in the visitor's own browser and is not shared with other users or synchronized with the C++ application's `Bill.txt` file. The current bill is held in page memory, so closing or refreshing the page can clear the active receipt.

## 🚀 GitHub Pages Deployment

The repository includes a GitHub Actions workflow for static-site deployment. For the workflow to publish the web demo correctly, its Pages artifact must point to the `public/` directory:

```yaml
- name: Upload artifact
  uses: actions/upload-pages-artifact@v3
  with:
    path: './public'
```

In **Repository Settings → Pages**, select **GitHub Actions** as the deployment source. A successful deployment publishes the contents of `public/` at the live-demo URL above.

## 🎯 Learning Outcomes

This project provides practical experience with:

- Designing a simple application using C++ classes and encapsulation.
- Organizing data through constructors, getters, and setters.
- Reading, writing, and updating records with file streams.
- Parsing text records using string streams.
- Implementing a menu-driven program and transaction-based billing logic.
- Presenting a console project through a separate static browser demonstration.

## 🔍 Current Scope and Limitations

This is an educational project rather than a production-ready point-of-sale system. The current implementation has some constraints:

- The C++ program is Windows-specific.
- Product input in the console uses single-word names (`cin >> item`).
- Inventory is stored in a plain text file, not a database.
- Repeated product names are not consolidated automatically.
- The C++ program does not include a dedicated stock-management screen or printable receipt export.
- The browser demo is a separate implementation and does not run or modify the C++ source.

Potential future improvements include improved input validation, unique product IDs, database support, sales-history reports, and broader platform compatibility.

## 👨‍💻 Source Code & Demo

- **GitHub Repository:** https://github.com/vasanth-kumar-009/Smart-Supermarket-Billing-System
- **Original C++ Code:** [main.cpp](main.cpp)
- **Web Demo Source:** [public/](public/)
- **Live Browser Demo:** https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/

---

<div align="center">

**Built as a hands-on C++ OOP and file-handling project.**

</div>
