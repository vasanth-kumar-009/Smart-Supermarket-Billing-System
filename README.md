# Supermarket Billing System — C++ OOP Project

A command-line supermarket inventory and billing system built using **C++ and Object-Oriented Programming (OOP)**.

## Features
- Add items with names, unit prices, and quantities.
- Persist inventory to `Bill.txt` using C++ file handling.
- Generate a shopping bill and calculate the total.
- Validate quantities and prevent purchases when stock is insufficient.
- Automatically deduct purchased quantities from available inventory.
- Run an **interactive browser demo** so recruiters can try the project without installing C++.

## OOP concepts demonstrated
- **Class and object:** `Bill` and its instances.
- **Encapsulation:** private item, rate and quantity members.
- **Constructor:** initializes the members of a `Bill` object.
- **Member methods:** getters and a setter for quantity.

Note: This project demonstrates core OOP concepts; it does **not** implement inheritance or polymorphism.

## Run the original C++ console project

The `main.cpp` is a portable C++17 revision of the Windows-only original. Run:

```bash
g++ -std=c++17 main.cpp -o supermarket
./supermarket
```

On Windows, run `supermarket.exe` after compilation. The app creates `Bill.txt` when you add an item.

## Browser demo

Open `index.html` locally to use the demo, or publish it through **GitHub Pages**:

1. Create a **public GitHub repository** named `supermarket-billing-system`.
2. Upload `index.html`, `main.cpp`, and `README.md` to the default branch's root.
3. Open **Settings → Pages**.
4. Under **Build and deployment**, choose **Deploy from a branch**, select your default branch and `/ (root)`, then **Save**.
5. Once GitHub Pages publishes, your URL is typically `https://YOUR_USERNAME.github.io/supermarket-billing-system/`.

The browser demo is an **HTML/CSS/JavaScript adaptation** of the C++ program, not a C++ binary compiled to WebAssembly. The web app uses browser `localStorage` for inventory, whereas `main.cpp` uses `Bill.txt`. The bill is kept in memory for the active browser session, so printing or completing it before closing the page is recommended.

## Resume entry

**Supermarket Billing System | C++, OOP, File Handling**

Built a console-based supermarket billing application using C++ classes, encapsulation, constructors, and file operations. Implemented inventory management, stock validation, automated bill totals, and stock updates. Created an interactive browser demo for easy project review.

[Source Code](YOUR_GITHUB_REPOSITORY_URL) · [Live Demo](YOUR_GITHUB_PAGES_URL)
