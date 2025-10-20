#ifndef CLI_H
#define CLI_H

#include "../../Domain/Repo/IRepositories.h"
#include <memory>
#include <string>
#include <optional>
#include <vector>
#include <iostream>

class CLI {
public:
    CLI(
        std::shared_ptr<IShopRepository> shopRepo,
        std::shared_ptr<IDepartmentRepository> departmentRepo,
        std::shared_ptr<IPassportRepository> passportRepo,
        std::shared_ptr<IProductRepository> productRepo,
        std::shared_ptr<IEmployeeRepository> employeeRepo,
        std::shared_ptr<IInventoryItemRepository> inventoryItemRepo,
        std::shared_ptr<ISaleRepository> saleRepo
    );

    void run();

private:
    template<typename T>
    std::shared_ptr<T> selectItem(const std::vector<std::shared_ptr<T>>& items, void (*printFunc)(const T&));

    void runShopsMenu();
    void runDepartmentsMenu();
    void runPassportsMenu();
    void runProductsMenu();
    void runEmployeesMenu();
    void runInventoryMenu();
    void runSalesMenu();

    void listInventoryByShop();

    void clearScreen();
    void waitForEnter();

    long long getLongLongInput(const std::wstring& prompt);
    double getDoubleInput(const std::wstring& prompt);
    std::wstring getStringInput(const std::wstring& prompt);

    std::optional<long long> getOptionalLongLongInput(const std::wstring& prompt);
    std::optional<double> getOptionalDoubleInput(const std::wstring& prompt);
    std::optional<std::wstring> getOptionalStringInput(const std::wstring& prompt);

    std::shared_ptr<IShopRepository> shopRepo;
    std::shared_ptr<IDepartmentRepository> departmentRepo;
    std::shared_ptr<IPassportRepository> passportRepo;
    std::shared_ptr<IProductRepository> productRepo;
    std::shared_ptr<IEmployeeRepository> employeeRepo;
    std::shared_ptr<IInventoryItemRepository> inventoryItemRepo;
    std::shared_ptr<ISaleRepository> saleRepo;
};

template<typename T>
std::shared_ptr<T> CLI::selectItem(const std::vector<std::shared_ptr<T>>& items, void (*printFunc)(const T&)) {
    if (items.empty()) {
        std::wcout << L"No items available to select." << std::endl;
        return nullptr;
    }

    std::wcout << L"Please select an item from the list:" << std::endl;
    for (size_t i = 0; i < items.size(); ++i) {
        std::wcout << L"  " << (i + 1) << L". ";
        printFunc(*items[i]);
        std::wcout << std::endl;
    }

    long long choice = -1;
    while (true) {
        choice = getLongLongInput(L"Enter the number of your choice (or 0 to cancel): ");
        if (choice == 0) {
            return nullptr;
        }
        if (choice > 0 && choice <= static_cast<long long>(items.size())) {
            return items[choice - 1];
        }
        std::wcout << L"Invalid selection. Please try again." << std::endl;
    }
}

#endif