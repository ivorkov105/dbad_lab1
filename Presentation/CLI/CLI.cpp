#include "CLI.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <vector>

namespace {
    void printShop(const Shop& s) { std::wcout << L"Name: " << s.getName() << L", Address: " << s.getAddress(); }
    void printDepartment(const Department& d) { std::wcout << L"Name: " << d.getName(); }
    void printPassport(const Passport& p) { std::wcout << L"Number: " << p.getNum() << L", Issued: " << p.getIssueDate() << L", Authority: " << p.getAuthority(); }
    void printProduct(const Product& p) { std::wcout << L"Name: " << p.getName() << L", Unit: " << p.getUnit(); }
    void printEmployee(const Employee& e) { std::wcout << L"Name: " << e.getFullName() << L", Shop ID: " << e.getShopId(); }

    void printInventoryItem(const InventoryItem& i, const Shop& shop, const Product& product) {
        std::wcout << L"Shop: " << shop.getName()
                   << L", Product: " << product.getName()
                   << L", Quantity: " << i.getQuantity()
                   << L", Price: " << i.getPrice();
    }

    void printSale(const Sale& s, const Shop& shop, const Product& product) {
        std::wcout << L"Shop: " << shop.getName()
                   << L", Product: " << product.getName()
                   << L", Qty: " << s.getQuantitySold()
                   << L", Date: " << s.getSaleDate();
    }
}

CLI::CLI(
    std::shared_ptr<IShopRepository> shopRepo, std::shared_ptr<IDepartmentRepository> departmentRepo,
    std::shared_ptr<IPassportRepository> passportRepo, std::shared_ptr<IProductRepository> productRepo,
    std::shared_ptr<IEmployeeRepository> employeeRepo, std::shared_ptr<IInventoryItemRepository> inventoryItemRepo,
    std::shared_ptr<ISaleRepository> saleRepo)
    : shopRepo(shopRepo), departmentRepo(departmentRepo), passportRepo(passportRepo),
    productRepo(productRepo), employeeRepo(employeeRepo), inventoryItemRepo(inventoryItemRepo), saleRepo(saleRepo) {
}

void CLI::run() {
    bool running = true;
    while (running) {
        clearScreen();
        std::wcout << L"====== MAIN MENU ======\n"
            << L"  1. Shops\n"
            << L"  2. Departments\n"
            << L"  3. Passports\n"
            << L"  4. Products\n"
            << L"  5. Employees\n"
            << L"  6. Inventory\n"
            << L"  7. Sales\n"
            << L"  0. Exit\n"
            << L"=======================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: runShopsMenu(); break;
        case 2: runDepartmentsMenu(); break;
        case 3: runPassportsMenu(); break;
        case 4: runProductsMenu(); break;
        case 5: runEmployeesMenu(); break;
        case 6: runInventoryMenu(); break;
        case 7: runSalesMenu(); break;
        case 0: running = false; break;
        default: std::wcout << L"\nInvalid choice."; waitForEnter(); break;
        }
    }
}

void CLI::runShopsMenu() {
    bool inMenu = true;
    while (inMenu) {
        clearScreen();
        std::wcout << L"====== Shops Management ======\n"
            << L"  1. List all\n"
            << L"  2. Add new\n"
            << L"  3. Update existing\n"
            << L"  4. Delete existing\n"
            << L"  5. List inventory by shop\n"
            << L"  0. Back to Main Menu\n"
            << L"============================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: {
            clearScreen();
            auto items = shopRepo->findAll();
            for (const auto& item : items) { printShop(*item); std::wcout << std::endl; }
            waitForEnter();
            break;
        }
        case 2: {
            clearScreen();
            Shop model;
            model.setName(getStringInput(L"Enter name: "));
            model.setAddress(getStringInput(L"Enter address: "));
            shopRepo->add(model);
            waitForEnter();
            break;
        }
        case 3: {
            clearScreen();
            auto items = shopRepo->findAll();
            auto selectedShop = selectItem(items, printShop);
            if (selectedShop) {
                Shop model = *selectedShop;
                if (auto val = getOptionalStringInput(L"Name [" + model.getName() + L"]: ")) model.setName(*val);
                if (auto val = getOptionalStringInput(L"Address [" + model.getAddress() + L"]: ")) model.setAddress(*val);
                shopRepo->update(model);
                 std::wcout << L"Shop updated successfully.\n";
            } else { std::wcout << L"Update cancelled or no shops available.\n"; }
            waitForEnter();
            break;
        }
        case 4: {
            clearScreen();
            auto items = shopRepo->findAll();
            auto selectedShop = selectItem(items, printShop);
            if (selectedShop) {
                shopRepo->remove(*selectedShop);
                std::wcout << L"Shop removed successfully.\n";
            } else { std::wcout << L"Deletion cancelled or no shops available.\n"; }
            waitForEnter();
            break;
        }
        case 5: {
            listInventoryByShop();
            break;
        }
        case 0: inMenu = false; break;
        default: std::wcout << L"Invalid choice.\n"; waitForEnter(); break;
        }
    }
}

void CLI::runDepartmentsMenu() {
    bool inMenu = true;
    while (inMenu) {
        clearScreen();
        std::wcout << L"====== Departments Management ======\n"
            << L"  1. List all\n"
            << L"  2. Add new\n"
            << L"  3. Update existing\n"
            << L"  4. Delete existing\n"
            << L"  0. Back to Main Menu\n"
            << L"==================================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: {
            clearScreen();
            auto items = departmentRepo->findAll();
            for (const auto& item : items) { printDepartment(*item); std::wcout << std::endl; }
            waitForEnter();
            break;
        }
        case 2: {
            clearScreen();
            Department model;
            model.setName(getStringInput(L"Enter name: "));
            departmentRepo->add(model);
            waitForEnter();
            break;
        }
        case 3: {
            clearScreen();
            auto items = departmentRepo->findAll();
            auto selectedDept = selectItem(items, printDepartment);
            if (selectedDept) {
                Department model = *selectedDept;
                if (auto val = getOptionalStringInput(L"Name [" + model.getName() + L"]: ")) model.setName(*val);
                departmentRepo->update(model);
                std::wcout << L"Department updated successfully.\n";
            } else { std::wcout << L"Update cancelled or no departments available.\n"; }
            waitForEnter();
            break;
        }
        case 4: {
            clearScreen();
            auto items = departmentRepo->findAll();
            auto selectedDept = selectItem(items, printDepartment);
            if (selectedDept) {
                departmentRepo->remove(*selectedDept);
                std::wcout << L"Department removed successfully.\n";
            } else { std::wcout << L"Deletion cancelled or no departments available.\n"; }
            waitForEnter();
            break;
        }
        case 0: inMenu = false; break;
        default: std::wcout << L"Invalid choice.\n"; waitForEnter(); break;
        }
    }
}

void CLI::runPassportsMenu() {
    bool inMenu = true;
    while (inMenu) {
        clearScreen();
        std::wcout << L"====== Passports Management ======\n"
            << L"  1. List all\n"
            << L"  2. Add new\n"
            << L"  3. Update existing\n"
            << L"  4. Delete existing\n"
            << L"  0. Back to Main Menu\n"
            << L"================================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: {
            clearScreen();
            auto items = passportRepo->findAll();
            for (const auto& item : items) { printPassport(*item); std::wcout << std::endl; }
            waitForEnter();
            break;
        }
        case 2: {
            clearScreen();
            Passport model;
            model.setNum(getStringInput(L"Enter number: "));
            model.setIssueDate(getStringInput(L"Enter issue date (YYYY-MM-DD): "));
            model.setAuthority(getStringInput(L"Enter issuing authority: "));
            passportRepo->add(model);
            waitForEnter();
            break;
        }
        case 3: {
            clearScreen();
            auto items = passportRepo->findAll();
            auto selectedPassport = selectItem(items, printPassport);
            if (selectedPassport) {
                Passport model = *selectedPassport;
                if (auto val = getOptionalStringInput(L"Number [" + model.getNum() + L"]: ")) model.setNum(*val);
                if (auto val = getOptionalStringInput(L"Issue Date [" + model.getIssueDate() + L"]: ")) model.setIssueDate(*val);
                if (auto val = getOptionalStringInput(L"Authority [" + model.getAuthority() + L"]: ")) model.setAuthority(*val);
                passportRepo->update(model);
                std::wcout << L"Passport updated successfully.\n";
            } else { std::wcout << L"Update cancelled or no passports available.\n"; }
            waitForEnter();
            break;
        }
        case 4: {
            clearScreen();
            auto items = passportRepo->findAll();
            auto selectedPassport = selectItem(items, printPassport);
            if (selectedPassport) {
                passportRepo->remove(*selectedPassport);
                 std::wcout << L"Passport removed successfully.\n";
            } else { std::wcout << L"Deletion cancelled or no passports available.\n"; }
            waitForEnter();
            break;
        }
        case 0: inMenu = false; break;
        default: std::wcout << L"Invalid choice.\n"; waitForEnter(); break;
        }
    }
}

void CLI::runProductsMenu() {
    bool inMenu = true;
    while (inMenu) {
        clearScreen();
        std::wcout << L"====== Products Management ======\n"
            << L"  1. List all\n"
            << L"  2. Add new\n"
            << L"  3. Update existing\n"
            << L"  4. Delete existing\n"
            << L"  0. Back to Main Menu\n"
            << L"===============================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: {
            clearScreen();
            auto items = productRepo->findAll();
            for (const auto& item : items) { printProduct(*item); std::wcout << std::endl; }
            waitForEnter();
            break;
        }
        case 2: {
            clearScreen();
            Product model;
            model.setName(getStringInput(L"Enter name: "));
            model.setUnit(getStringInput(L"Enter unit: "));
            productRepo->add(model);
            waitForEnter();
            break;
        }
        case 3: {
            clearScreen();
            auto items = productRepo->findAll();
            auto selectedProduct = selectItem(items, printProduct);
            if (selectedProduct) {
                Product model = *selectedProduct;
                if (auto val = getOptionalStringInput(L"Name [" + model.getName() + L"]: ")) model.setName(*val);
                if (auto val = getOptionalStringInput(L"Unit [" + model.getUnit() + L"]: ")) model.setUnit(*val);
                productRepo->update(model);
                std::wcout << L"Product updated successfully.\n";
            } else { std::wcout << L"Update cancelled or no products available.\n"; }
            waitForEnter();
            break;
        }
        case 4: {
            clearScreen();
            auto items = productRepo->findAll();
            auto selectedProduct = selectItem(items, printProduct);
            if (selectedProduct) {
                productRepo->remove(*selectedProduct);
                std::wcout << L"Product removed successfully.\n";
            } else { std::wcout << L"Deletion cancelled or no products available.\n"; }
            waitForEnter();
            break;
        }
        case 0: inMenu = false; break;
        default: std::wcout << L"Invalid choice.\n"; waitForEnter(); break;
        }
    }
}

void CLI::runEmployeesMenu() {
    bool inMenu = true;
    while (inMenu) {
        clearScreen();
        std::wcout << L"====== Employees Management ======\n"
            << L"  1. List all\n"
            << L"  2. Add new\n"
            << L"  3. Update existing\n"
            << L"  4. Delete existing\n"
            << L"  0. Back to Main Menu\n"
            << L"================================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: {
            clearScreen();
            auto items = employeeRepo->findAll();
            for (const auto& item : items) { printEmployee(*item); std::wcout << std::endl; }
            waitForEnter();
            break;
        }
        case 2: {
            clearScreen();
            Employee model;
            model.setLastName(getStringInput(L"Enter last name: "));
            model.setFirstName(getStringInput(L"Enter first name: "));
            model.setMiddleName(getStringInput(L"Enter middle name: "));
            model.setAddress(getStringInput(L"Enter address: "));
            model.setBirthDate(getStringInput(L"Enter birth date (YYYY-MM-DD): "));

            auto passports = passportRepo->findAll();
            auto selectedPassport = selectItem(passports, printPassport);
            if (!selectedPassport) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setPassportId(selectedPassport->getId());

            auto shops = shopRepo->findAll();
            auto selectedShop = selectItem(shops, printShop);
            if (!selectedShop) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setShopId(selectedShop->getId());

            auto departments = departmentRepo->findAll();
            auto selectedDepartment = selectItem(departments, printDepartment);
            if (!selectedDepartment) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setDepartmentId(selectedDepartment->getId());

            employeeRepo->add(model);
            std::wcout << L"Employee added successfully.\n";
            waitForEnter();
            break;
        }
        case 3: {
            clearScreen();
            auto items = employeeRepo->findAll();
            auto selectedEmployee = selectItem(items, printEmployee);
            if (selectedEmployee) {
                Employee model = *selectedEmployee;
                if (auto val = getOptionalStringInput(L"Last Name [" + model.getLastName() + L"]: ")) model.setLastName(*val);
                if (auto val = getOptionalStringInput(L"First Name [" + model.getFirstName() + L"]: ")) model.setFirstName(*val);
                if (auto val = getOptionalStringInput(L"Middle Name [" + model.getMiddleName() + L"]: ")) model.setMiddleName(*val);
                if (auto val = getOptionalStringInput(L"Address [" + model.getAddress() + L"]: ")) model.setAddress(*val);
                if (auto val = getOptionalStringInput(L"Birth Date [" + model.getBirthDate() + L"]: ")) model.setBirthDate(*val);
                
                std::wcout << L"Select a new passport (or press 0 to keep current): \n";
                auto passports = passportRepo->findAll();
                auto selectedPassport = selectItem(passports, printPassport);
                if(selectedPassport) model.setPassportId(selectedPassport->getId());

                std::wcout << L"Select a new shop (or press 0 to keep current): \n";
                auto shops = shopRepo->findAll();
                auto selectedShop = selectItem(shops, printShop);
                if(selectedShop) model.setShopId(selectedShop->getId());

                std::wcout << L"Select a new department (or press 0 to keep current): \n";
                auto departments = departmentRepo->findAll();
                auto selectedDepartment = selectItem(departments, printDepartment);
                if(selectedDepartment) model.setDepartmentId(selectedDepartment->getId());

                employeeRepo->update(model);
                std::wcout << L"Employee updated successfully.\n";
            } else { std::wcout << L"Update cancelled or no employees available.\n"; }
            waitForEnter();
            break;
        }
        case 4: {
            clearScreen();
            auto items = employeeRepo->findAll();
            auto selectedEmployee = selectItem(items, printEmployee);
            if (selectedEmployee) {
                employeeRepo->remove(*selectedEmployee);
                std::wcout << L"Employee removed successfully.\n";
            } else { std::wcout << L"Deletion cancelled or no employees available.\n"; }
            waitForEnter();
            break;
        }
        case 0: inMenu = false; break;
        default: std::wcout << L"Invalid choice.\n"; waitForEnter(); break;
        }
    }
}

void CLI::runInventoryMenu() {
    bool inMenu = true;
    while (inMenu) {
        clearScreen();
        std::wcout << L"====== Inventory Management ======\n"
            << L"  1. List all\n"
            << L"  2. Add new item\n"
            << L"  3. Update existing item\n"
            << L"  4. Delete existing item\n"
            << L"  0. Back to Main Menu\n"
            << L"================================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: {
            clearScreen();
            auto items = inventoryItemRepo->findAll();
            for (const auto& item : items) {
                Shop tempShop; tempShop.setId(item->getShopId());
                auto shop = shopRepo->find(tempShop);
                Product tempProd; tempProd.setId(item->getProductId());
                auto product = productRepo->find(tempProd);
                if (shop && product) {
                    printInventoryItem(*item, *shop, *product);
                    std::wcout << std::endl;
                }
            }
            waitForEnter();
            break;
        }
        case 2: {
            clearScreen();
            InventoryItem model;
            
            auto shops = shopRepo->findAll();
            auto selectedShop = selectItem(shops, printShop);
            if (!selectedShop) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setShopId(selectedShop->getId());

            auto products = productRepo->findAll();
            auto selectedProduct = selectItem(products, printProduct);
            if (!selectedProduct) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setProductId(selectedProduct->getId());
            
            model.setQuantity(getDoubleInput(L"Enter quantity: "));
            model.setPrice(getDoubleInput(L"Enter price: "));
            inventoryItemRepo->add(model);
            std::wcout << L"Inventory item added successfully.\n";
            waitForEnter();
            break;
        }
        case 3: {
            clearScreen();
            auto items = inventoryItemRepo->findAll();
            if (items.empty()) {
                std::wcout << L"No items to update.\n";
                waitForEnter();
                break;
            }
            std::wcout << L"Please select an item to update:\n";
            for (size_t i = 0; i < items.size(); ++i) {
                Shop tempShop; tempShop.setId(items[i]->getShopId());
                auto shop = shopRepo->find(tempShop);
                Product tempProd; tempProd.setId(items[i]->getProductId());
                auto product = productRepo->find(tempProd);
                std::wcout << L"  " << (i + 1) << L". ";
                if (shop && product) printInventoryItem(*items[i], *shop, *product);
                std::wcout << std::endl;
            }
            long long choice = getLongLongInput(L"Enter your choice (0 to cancel): ");
            if (choice > 0 && choice <= static_cast<long long>(items.size())) {
                auto selectedItem = items[choice - 1];
                InventoryItem model = *selectedItem;
                if (auto val = getOptionalDoubleInput(L"Quantity [" + std::to_wstring(model.getQuantity()) + L"]: ")) model.setQuantity(*val);
                if (auto val = getOptionalDoubleInput(L"Price [" + std::to_wstring(model.getPrice()) + L"]: ")) model.setPrice(*val);
                inventoryItemRepo->update(model);
                std::wcout << L"Inventory item updated successfully.\n";
            } else { std::wcout << L"Update cancelled.\n"; }
            waitForEnter();
            break;
        }
        case 4: {
            clearScreen();
            auto items = inventoryItemRepo->findAll();
             if (items.empty()) {
                std::wcout << L"No items to delete.\n";
                waitForEnter();
                break;
            }
            std::wcout << L"Please select an item to delete:\n";
            for (size_t i = 0; i < items.size(); ++i) {
                Shop tempShop; tempShop.setId(items[i]->getShopId());
                auto shop = shopRepo->find(tempShop);
                Product tempProd; tempProd.setId(items[i]->getProductId());
                auto product = productRepo->find(tempProd);
                std::wcout << L"  " << (i + 1) << L". ";
                if (shop && product) printInventoryItem(*items[i], *shop, *product);
                std::wcout << std::endl;
            }
            long long choice = getLongLongInput(L"Enter your choice (0 to cancel): ");
            if (choice > 0 && choice <= static_cast<long long>(items.size())) {
                inventoryItemRepo->remove(*items[choice - 1]);
                std::wcout << L"Inventory item removed successfully.\n";
            } else { std::wcout << L"Deletion cancelled.\n"; }
            waitForEnter();
            break;
        }
        case 0: inMenu = false; break;
        default: std::wcout << L"Invalid choice.\n"; waitForEnter(); break;
        }
    }
}

void CLI::runSalesMenu() {
    bool inMenu = true;
    while (inMenu) {
        clearScreen();
        std::wcout << L"====== Sales Management ======\n"
            << L"  1. List all\n"
            << L"  2. Add new\n"
            << L"  3. Update existing\n"
            << L"  4. Delete existing\n"
            << L"  0. Back to Main Menu\n"
            << L"============================\n";
        int choice = getLongLongInput(L"Enter your choice: ");
        switch (choice) {
        case 1: {
            clearScreen();
            auto items = saleRepo->findAll();
            for (const auto& item : items) {
                Shop tempShop; tempShop.setId(item->getShopId());
                auto shop = shopRepo->find(tempShop);
                Product tempProd; tempProd.setId(item->getProductId());
                auto product = productRepo->find(tempProd);
                if (shop && product) {
                    printSale(*item, *shop, *product);
                    std::wcout << std::endl;
                }
            }
            waitForEnter();
            break;
        }
        case 2: {
            clearScreen();
            Sale model;

            auto shops = shopRepo->findAll();
            auto selectedShop = selectItem(shops, printShop);
            if (!selectedShop) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setShopId(selectedShop->getId());

            auto products = productRepo->findAll();
            auto selectedProduct = selectItem(products, printProduct);
            if (!selectedProduct) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setProductId(selectedProduct->getId());

            auto employees = employeeRepo->findAll();
            auto selectedEmployee = selectItem(employees, printEmployee);
            if (!selectedEmployee) { std::wcout << L"Cancelled.\n"; waitForEnter(); break; }
            model.setEmployeeId(selectedEmployee->getId());

            model.setQuantitySold(getDoubleInput(L"Enter quantity sold: "));
            saleRepo->add(model);
            std::wcout << L"Sale recorded successfully.\n";
            waitForEnter();
            break;
        }
        case 3: {
            clearScreen();
            auto items = saleRepo->findAll();
            if (items.empty()) {
                std::wcout << L"No sales to update.\n";
                waitForEnter();
                break;
            }
            std::wcout << L"Please select a sale to update:\n";
            for (size_t i = 0; i < items.size(); ++i) {
                Shop tempShop; tempShop.setId(items[i]->getShopId());
                auto shop = shopRepo->find(tempShop);
                Product tempProd; tempProd.setId(items[i]->getProductId());
                auto product = productRepo->find(tempProd);
                std::wcout << L"  " << (i + 1) << L". ";
                if (shop && product) printSale(*items[i], *shop, *product);
                std::wcout << std::endl;
            }
            long long choice = getLongLongInput(L"Enter your choice (0 to cancel): ");
            if (choice > 0 && choice <= static_cast<long long>(items.size())) {
                auto selectedSale = items[choice - 1];
                Sale model = *selectedSale;
                if (auto val = getOptionalDoubleInput(L"Quantity Sold [" + std::to_wstring(model.getQuantitySold()) + L"]: ")) model.setQuantitySold(*val);
                saleRepo->update(model);
                std::wcout << L"Sale updated successfully.\n";
            } else { std::wcout << L"Update cancelled.\n"; }
            waitForEnter();
            break;
        }
        case 4: {
            clearScreen();
            auto items = saleRepo->findAll();
             if (items.empty()) {
                std::wcout << L"No sales to delete.\n";
                waitForEnter();
                break;
            }
            std::wcout << L"Please select a sale to delete:\n";
            for (size_t i = 0; i < items.size(); ++i) {
                Shop tempShop; tempShop.setId(items[i]->getShopId());
                auto shop = shopRepo->find(tempShop);
                Product tempProd; tempProd.setId(items[i]->getProductId());
                auto product = productRepo->find(tempProd);
                std::wcout << L"  " << (i + 1) << L". ";
                if (shop && product) printSale(*items[i], *shop, *product);
                std::wcout << std::endl;
            }
            long long choice = getLongLongInput(L"Enter your choice (0 to cancel): ");
            if (choice > 0 && choice <= static_cast<long long>(items.size())) {
                saleRepo->remove(*items[choice - 1]);
                std::wcout << L"Sale removed successfully.\n";
            } else { std::wcout << L"Deletion cancelled.\n"; }
            waitForEnter();
            break;
        }
        case 0: inMenu = false; break;
        default: std::wcout << L"Invalid choice.\n"; waitForEnter(); break;
        }
    }
}

void CLI::listInventoryByShop() {
    clearScreen();
    auto shops = shopRepo->findAll();
    auto shop = selectItem(shops, printShop);
    if (!shop) {
        std::wcout << L"Action cancelled or no shops available.\n";
        waitForEnter();
        return;
    }

    std::wcout << L"\n--- Inventory for shop: " << shop->getName() << L" ---\n";
    auto items = inventoryItemRepo->findAllByShop(*shop);
    if (items.empty()) {
        std::wcout << L"(No inventory items found for this shop)\n";
    } else {
        for (const auto& item : items) {
            Product tempProduct;
            tempProduct.setId(item->getProductId());
            auto product = productRepo->find(tempProduct);
            std::wcout << L"  Product: " << (product ? product->getName() : L"Unknown")
                << L", Quantity: " << item->getQuantity()
                << L", Price: " << item->getPrice() << std::endl;
        }
    }
    waitForEnter();
}

void CLI::clearScreen() {
    system("cls");
}

void CLI::waitForEnter() {
    std::wcout << L"\nPress Enter to continue...";
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
    if(std::wcin.rdbuf()->in_avail() > 0)
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
}

std::wstring CLI::getStringInput(const std::wstring& prompt) {
    std::wcout << prompt;
    std::wstring input;
    std::getline(std::wcin, input);
    return input;
}

long long CLI::getLongLongInput(const std::wstring& prompt) {
    long long value;
    std::wstring line;
    while (true) {
        std::wcout << prompt;
        std::getline(std::wcin, line);
        if (line.empty() && prompt.find(L"choice") != std::wstring::npos) {
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            continue;
        }
        std::wstringstream ss(line);
        if (ss >> value && ss.eof()) {
            return value;
        }
        std::wcout << L"Invalid input. Please enter an integer.\n";
    }
}

double CLI::getDoubleInput(const std::wstring& prompt) {
    double value;
    std::wstring line;
    while (true) {
        std::wcout << prompt;
        std::getline(std::wcin, line);
        std::wstringstream ss(line);
        if (ss >> value && ss.eof()) {
            return value;
        }
        std::wcout << L"Invalid input. Please enter a number (e.g., 123.45).\n";
    }
}

std::optional<std::wstring> CLI::getOptionalStringInput(const std::wstring& prompt) {
    std::wcout << prompt;
    std::wstring line;
    std::getline(std::wcin, line);
    if (line.empty()) {
        return std::nullopt;
    }
    return line;
}

std::optional<long long> CLI::getOptionalLongLongInput(const std::wstring& prompt) {
    std::wcout << prompt;
    std::wstring line;
    std::getline(std::wcin, line);
    if (line.empty()) {
        return std::nullopt;
    }
    std::wstringstream ss(line);
    long long value;
    if (ss >> value && ss.eof()) {
        return value;
    }
    return std::nullopt;
}

std::optional<double> CLI::getOptionalDoubleInput(const std::wstring& prompt) {
    std::wcout << prompt;
    std::wstring line;
    std::getline(std::wcin, line);
    if (line.empty()) {
        return std::nullopt;
    }
    std::wstringstream ss(line);
    double value;
    if (ss >> value && ss.eof()) {
        return value;
    }
    return std::nullopt;
}