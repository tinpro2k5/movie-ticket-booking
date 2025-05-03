#ifndef _BASE_REPOSITORY_H_
#define _BASE_REPOSITORY_H_

#include "../utils/DatabaseManager.h"
#include "../utils/Logger.h"

// TODO sửa lại các hàm của class con dùng con trỏ dbManager và logger 

class BaseRepository {
protected:
    DatabaseManager* dbManager; // Pointer to the database manager    
    Logger* logger; // Pointer to the logger
public:
    // có thể thêm constructor với tham số
    BaseRepository(); 
    virtual ~BaseRepository();
    // Define common methods for all repositories here

};

#endif
