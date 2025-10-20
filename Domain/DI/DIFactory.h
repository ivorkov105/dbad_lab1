#ifndef COMPOSITION_ROOT_H
#define COMPOSITION_ROOT_H

#include <memory>
#include "../../Presentation/CLI/CLI.h"
#include "../../Data/DataSources/DatabaseConnection.h"
#include "../../Domain/LocalStorage/DataContainer.h"
#include "../../Data/Repo/Repositories.h"
#include "../../Data/DAOs/DAOs.h"
#include "../../Data/DataMappers/DataMappers.h"

namespace app {

inline CLI create_injectors(std::shared_ptr<DatabaseConnection> dbConnection) {
    auto dataContainer = std::make_shared<DataContainer>();

    auto shopDao = std::make_shared<ShopDAO>(dbConnection);
    auto deptDao = std::make_shared<DepartmentDAO>(dbConnection);
    auto passDao = std::make_shared<PassportDAO>(dbConnection);
    auto prodDao = std::make_shared<ProductDAO>(dbConnection);
    auto empDao = std::make_shared<EmployeeDAO>(dbConnection);
    auto invDao = std::make_shared<InventoryItemDAO>(dbConnection);
    auto saleDao = std::make_shared<SaleDAO>(dbConnection);

    auto shopMapper = std::make_shared<ShopMapper>();
    auto deptMapper = std::make_shared<DepartmentMapper>();
    auto passMapper = std::make_shared<PassportMapper>();
    auto prodMapper = std::make_shared<ProductMapper>();
    auto empMapper = std::make_shared<EmployeeMapper>();
    auto invMapper = std::make_shared<InventoryItemMapper>();
    auto saleMapper = std::make_shared<SaleMapper>();
    
    auto shopRepo = std::make_shared<ShopRepository>(dataContainer, shopMapper, shopDao, invDao);
    auto deptRepo = std::make_shared<DepartmentRepository>(dataContainer, deptMapper, deptDao);
    auto passRepo = std::make_shared<PassportRepository>(dataContainer, passMapper, passDao);
    auto prodRepo = std::make_shared<ProductRepository>(dataContainer, prodMapper, prodDao, invDao);
    auto empRepo = std::make_shared<EmployeeRepository>(dataContainer, empMapper, empDao);
    auto invRepo = std::make_shared<InventoryItemRepository>(dataContainer, invMapper, invDao);
    auto saleRepo = std::make_shared<SaleRepository>(dataContainer, saleMapper, saleDao);

    CLI appCli(shopRepo, deptRepo, passRepo, prodRepo, empRepo, invRepo, saleRepo);
    
    return appCli;
}

}

#endif