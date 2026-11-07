<div align="center">

# 🛒 Smart Supermarket Billing System

**A C++ inventory and billing project with an interactive WebAssembly terminal demo.**

[![C++](https://img.shields.io/badge/C%2B%2B-OOP%20%26%20File%20Handling-00599C?logo=cplusplus&logoColor=white)](main.cpp)
[![WebAssembly](https://img.shields.io/badge/WebAssembly-Browser%20Demo-654FF0?logo=webassembly&logoColor=white)](source/main-web.cpp)
[![GitHub Pages](https://img.shields.io/badge/GitHub%20Pages-Live%20Demo-222222?logo=github&logoColor=white)](https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/)

[**Try the Live Demo**](https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/) · [Windows C++ Source](main.cpp) · [Browser C++ Source](source/main-web.cpp)

</div>

## Overview

Smart Supermarket Billing System is a menu-driven C++ application for adding products, recording available stock, and calculating customer bills. Inventory records are read from and written to `Bill.txt` using C++ file streams.

The repository contains two ways to run the project:

- **Windows console application:** compile and run the original [`main.cpp`](main.cpp).
- **Browser terminal demo:** run the adapted [`source/main-web.cpp`](source/main-web.cpp), compiled to WebAssembly with Emscripten.

**The browser demo executes compiled C++ billing logic.** Its HTML and JavaScript provide terminal output, an input field, and runtime loading. Visitors do not need a compiler, installation, account, or backend server to use the published demo.

## Contents

- [Features](#features)
- [Technology Stack](#technology-stack)
- [Project Structure](#project-structure)
- [Try the Browser Demo](#try-the-browser-demo)
- [Run the Browser Demo Locally](#run-the-browser-demo-locally)
- [Run the Windows Console Application](#run-the-windows-console-application)
- [Rebuild the Browser Demo](#rebuild-the-browser-demo)
- [GitHub Pages Deployment](#github-pages-deployment)
- [C++ Design and Browser Integration](#c-design-and-browser-integration)
- [Storage and Version Differences](#storage-and-version-differences)
- [Current Limitations](#current-limitations)
- [Troubleshooting](#troubleshooting)

## Features

### Inventory and billing

- Add products with a name, whole-number unit rate, and stock quantity.
- Append inventory records to `Bill.txt`.
- Find products by name when creating a bill.
- Calculate each purchase amount as **unit rate × quantity**.
- Deduct purchased quantities from available stock.
- Accumulate the total across a billing session.
- Report unavailable items or insufficient stock.
- Return to the main menu or exit the program.

### Browser terminal

- Type answers into an input field and submit with **Enter** or **Send**.
- See C++ prompts and output in a scrollable terminal.
- Clear displayed output without clearing inventory.
- Restart the demo with a fresh inventory.
- Follow the expandable example included on the page.
- Use a layout that adapts to desktop and mobile screens.

The browser source also retries failed numeric extraction, preserves stock records after an insufficient-stock request, and skips unparseable inventory lines during billing.

## Technology Stack

| Component | Technology |
| --- | --- |
| Product model and billing logic | C++ |
| Inventory storage | C++ file streams and text records |
| Record parsing | `std::stringstream` |
| Original console interface | Windows console, `windows.h`, `Sleep()`, `system("cls")` |
| Browser compilation | Emscripten and WebAssembly |
| Asynchronous browser input | Asyncify and `EM_ASYNC_JS` |
| Terminal bridge | Custom `std::streambuf` classes |
| Browser interface | HTML, inline CSS, and JavaScript |
| Static hosting | GitHub Pages and GitHub Actions |

## Project Structure

| Path | Purpose |
| --- | --- |
| [`main.cpp`](main.cpp) | Original Windows console application |
| [`main.exe`](main.exe) | Windows executable included in the repository |
| [`source/main-web.cpp`](source/main-web.cpp) | C++ application adapted for browser execution |
| [`source/browser_terminal.h`](source/browser_terminal.h) | Browser input/output bridge, yielding delays, and input helper |
| [`public/index.html`](public/index.html) | Terminal page with embedded styling and UI logic |
| [`public/supermarket.js`](public/supermarket.js) | Generated Emscripten JavaScript runtime |
| [`public/supermarket.wasm`](public/supermarket.wasm) | Compiled WebAssembly module |
| [`build.bat`](build.bat) | Windows command script for rebuilding the browser runtime |
| [`.github/workflows/static.yml`](.github/workflows/static.yml) | GitHub Pages deployment workflow |
| [`.gitignore`](.gitignore) | Ignore rules for local inventory and selected build outputs |

`Bill.txt` and the temporary `Bill Temp.txt` are runtime inventory files. They are not required in the repository for the demo to start.

## Try the Browser Demo

**[Open the interactive demo](https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/)**

1. Wait for the main menu to appear.
2. Enter one answer at a time in the input field.
3. Press **Enter** or click **Send** after each answer.
4. Use single-word product names and match their capitalization when billing.

### Main menu

| Choice | Action |
| --- | --- |
| `1` | Open the Add Item menu |
| `2` | Open the Print Bill menu |
| `3` | Exit the program |

Inside **Add Item**, choose `1` to add a product or `2` to return to the main menu. Inside **Print Bill**, choose `1` to add a purchase or `2` to close the session and display the total.

### Example: a bill totaling 295

Enter the following answers **individually**, not as a single pasted line:

| Step | Answers to enter in order |
| --- | --- |
| Add Rice: rate 80, stock 10 | `1` → `1` → `Rice` → `80` → `10` |
| Add Sugar: rate 45, stock 8 | `1` → `Sugar` → `45` → `8` |
| Return to the main menu | `2` |
| Open billing | `2` |
| Buy 2 Rice | `1` → `Rice` → `2` |
| Buy 3 Sugar | `1` → `Sugar` → `3` |
| Close the billing session | `2` |

| Item | Rate | Purchased quantity | Amount | Remaining stock |
| --- | ---: | ---: | ---: | ---: |
| Rice | 80 | 2 | 160 | 8 |
| Sugar | 45 | 3 | 135 | 5 |
| **Total** | | | **295** | |

Prices are integer values; the C++ terminal does not enforce a currency.

**Clear screen** only removes displayed text. **Restart demo** reloads the page and resets the browser inventory. After choosing Exit, use Restart demo to begin again.

## Run the Browser Demo Locally

The compiled `.js` and `.wasm` files are committed, so rebuilding is unnecessary just to try the demo.

### 1. Clone the repository

```bash
git clone https://github.com/vasanth-kumar-009/Smart-Supermarket-Billing-System.git
cd Smart-Supermarket-Billing-System
```

Alternatively, download and extract the repository ZIP.

### 2. Start a local web server

**Option A — VS Code Live Server**

1. Open the repository folder in VS Code.
2. Install the Live Server extension.
3. Right-click `public/index.html` and select **Open with Live Server**.

**Option B — Python static server**

If Python is installed, run this from the repository root:

```bash
python -m http.server 8000 --bind 127.0.0.1 --directory public
```

Open **http://localhost:8000**. On systems where needed, use `py` or `python3` instead of `python`.

Python only serves the static files in this optional method; the billing program executes in the browser. Stop the server with `Ctrl+C`.

Do not open the page using `file://`. The runtime needs to load `supermarket.wasm` through a web server.

## Run the Windows Console Application

### Requirements

- Windows.
- A compatible C++ compiler, such as MinGW-w64 `g++`, available in your terminal.

From the repository root, compile:

```powershell
g++ main.cpp -std=c++17 -o supermarket.exe
```

Then run:

```powershell
.\supermarket.exe
```

The program creates `Bill.txt` in the current working directory when products are added. Run it from the same folder each time to reuse that inventory.

The repository also includes `main.exe`; compiling from source is the clearest way to ensure the executable matches the source you are reviewing.

`main.cpp` uses Windows-specific APIs and does not compile unchanged with a standard Linux or macOS toolchain.

## Rebuild the Browser Demo

Rebuild when you change `source/main-web.cpp` or `source/browser_terminal.h`. Editing the original `main.cpp` alone does **not** update the browser version.

### 1. Install and activate Emscripten

Use **Windows Command Prompt (`cmd.exe`)** for these batch commands. Git and Python must be available for SDK installation.

```bat
cd /d "%USERPROFILE%"
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
emsdk.bat install latest
emsdk.bat activate latest
emsdk_env.bat
em++ --version
```

If `emsdk` is already installed, reuse that installation instead of cloning into the same folder again.

Official instructions: [Emscripten download and installation](https://emscripten.org/docs/getting_started/downloads.html).

### 2. Build from the project folder

In the **same Command Prompt**, change to your repository. Replace this example path with your actual location:

```bat
cd /d "D:\projects\Smart-Supermarket-Billing-System"
build.bat
```

The script runs:

```bat
em++ source\main-web.cpp -std=c++17 -O2 -sASYNCIFY -sEXIT_RUNTIME=1 -sENVIRONMENT=web -sEXPORTED_RUNTIME_METHODS=stringToUTF8,lengthBytesUTF8,UTF8ToString -o public\supermarket.js
```

It generates or replaces:

- `public/supermarket.js`
- `public/supermarket.wasm`

Refresh the local demo to test the new build. Commit **both generated files and your source changes** before publishing.

When opening a new Command Prompt later, activate the SDK again before building:

```bat
call "%USERPROFILE%\emsdk\emsdk_env.bat"
```

## GitHub Pages Deployment

The workflow in [`.github/workflows/static.yml`](.github/workflows/static.yml):

1. Runs on pushes to `main` or a manual workflow dispatch.
2. Checks out the repository and configures GitHub Pages.
3. Uploads the contents of `public/`.
4. Deploys that artifact to GitHub Pages.

In the repository's **Settings → Pages**, select **GitHub Actions** as the deployment source. After pushing changes, check the **Actions** tab for the deployment result.

The workflow publishes the checked-in files; **it does not compile C++**. Run `build.bat` locally after changing the browser C++ source, then commit the updated `.js` and `.wasm` files.

Published address:

**https://vasanth-kumar-009.github.io/Smart-Supermarket-Billing-System/**

## C++ Design and Browser Integration

### Product model

The `Bill` class stores three private fields:

- `Item`: product name.
- `Rate`: unit price.
- `Quantity`: stock quantity.

Its constructor initializes these fields, while getters and setters provide access. `addItem()` appends inventory records; `printBill()` scans those records, calculates purchase amounts, and writes updated stock through a temporary file.

### Concepts demonstrated

| Concept | Where it appears |
| --- | --- |
| Classes and objects | `Bill` and the object created in `main()` |
| Encapsulation | Private product fields with public getters/setters |
| Constructors | Initial values set by `Bill()` |
| File handling | `ifstream`, `ofstream`, append mode, file replacement |
| String parsing | `stringstream` reads product records |
| Control flow | Menu loops and conditional billing operations |
| Inheritance and virtual overrides | Browser input/output adapters derive from `std::streambuf` |
| Templates | `readValue<T>()` in the browser helper |

### How browser input reaches C++

Emscripten compiles `source/main-web.cpp` to WebAssembly. The terminal page loads the generated runtime and module. `BrowserInput` requests a line through JavaScript; Asyncify pauses C++ execution while the visitor types. Submitting the line resumes the C++ program. `BrowserOutput` forwards C++ output back to the page.

See [Emscripten asynchronous code documentation](https://emscripten.org/docs/porting/asyncify.html) for the mechanism used by the input bridge.

## Storage and Version Differences

| Aspect | Windows application | Browser terminal |
| --- | --- | --- |
| Entry source | `main.cpp` | `source/main-web.cpp` |
| Execution | Native Windows executable | Compiled WebAssembly in the browser |
| Inventory | `Bill.txt` on the local disk | `Bill.txt` in a temporary in-memory filesystem |
| Persistence | Remains on disk between runs | Reset on page refresh or Restart demo |
| Interface | Windows terminal | Webpage terminal and input field |
| Delays | Original three-second pauses | Pauses capped at 150 milliseconds |
| Screen clearing | `system("cls")` calls | Output history retained; manual Clear screen button |
| Failed numeric extraction | No recovery helper | `readValue()` clears the failure and retries |
| Insufficient stock | Original branch omits the matching record from the replacement file | Matching record is preserved |
| Unparseable inventory lines | No extraction-result check | Line is retained and skipped for billing |

Each browser visitor has an independent temporary inventory. There is no shared database, server-side inventory, or synchronization with the Windows application's local file.

## Current Limitations

This is an educational project demonstrating C++ and file handling.

- Product names are single-word, case-sensitive tokens. Avoid spaces and the record delimiter `:`.
- Rates, quantities, and totals use `int`; decimal prices and overflow checks are not implemented.
- Numeric parsing recovery in the browser does not enforce business rules. Use nonnegative rates/stock and positive purchase quantities.
- Duplicate names are appended as separate records. Billing processes every matching record, so use unique names for predictable results.
- The browser inventory is not persisted across refreshes.
- Stock is deducted as purchases are added, rather than after a separate checkout confirmation.
- There is no authentication, tax/discount calculation, sales history, database, or receipt PDF export.
- Browser fixes are in `source/main-web.cpp`; they have not automatically been applied to the original Windows `main.cpp`.

## Troubleshooting

| Problem | What to check |
| --- | --- |
| Demo does not load when opened directly | Use Live Server or another HTTP server instead of `file://`. |
| Page reports missing build files | Keep `index.html`, `supermarket.js`, and `supermarket.wasm` together in `public/`. |
| Old demo or build still appears | Use `Ctrl+F5` and confirm the latest Pages deployment succeeded. |
| Cannot type immediately | Wait until the program requests input and enables the field. |
| Program has exited | Click Restart demo to start a new session. |
| Inventory disappeared | Refresh and Restart deliberately reset the browser filesystem. |
| `em++` is not recognized | Run `emsdk_env.bat` in the same Command Prompt before building. |
| `windows.h` is missing during compilation | Build `main.cpp` with a Windows toolchain; use `build.bat` for the browser source. |
| C++ changes are absent from the live demo | Edit the correct source, rebuild, and commit both generated runtime files. |
| An item is not found | Match its single-word name and capitalization exactly. |

---

Repository maintained by [**vasanth-kumar-009**](https://github.com/vasanth-kumar-009).
