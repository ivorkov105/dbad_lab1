#include "Data/DataSources/Remote/Database.h"
#include "Domain/DI/DIFactory.h"
#include "Presentation/CLI/CLI.h"
#include <iostream>
#include <memory>
#include <locale>
#include <limits>

int main() {
    try {
        std::locale::global(std::locale(""));
        std::wcout.imbue(std::locale());
        std::wcin.imbue(std::locale());
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to set locale: " << e.what() << std::endl;
    }

    //auto db = std::make_shared<Database>("dbad_db");
    auto db = std::make_shared<Database>("bdvdv");
    bool isConnected = false;

    try {
        isConnected = db->connect();
    }
    catch (const std::exception& e) {
        std::cerr << "DB connection check failed: " << e.what() << std::endl;
    }

    if (!isConnected) {
        std::wcerr << L"\n!!!\nWarning: Database is not connected. Application will run in OFFLINE mode.\n!!!\n" << std::endl;
        std::wcout << L"Press Enter to continue...";
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
    }

    try {
        auto appCli = app::create_injectors(db);
        appCli.run();
    }
    catch (const std::exception& e) {
        std::cerr << "An unhandled error occurred in the application: " << e.what() << std::endl;
    }

    if (db && isConnected) {
        db->disconnect();
    }

    return 0;
}