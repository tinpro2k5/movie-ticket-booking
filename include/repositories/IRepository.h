#ifndef _BASE_REPOSITORY_H_
#define _BASE_REPOSITORY_H_

#include "../repositories/Result.h"
#include "../utils/DatabaseManager.h"
#include "../utils/Logger.h"


template <typename T>
class IRepository {
public:
    // có thể thêm constructor với tham số
    IRepository() = default; 
    virtual ~IRepository() = default;
    virtual Result<int> create(const T& item) = 0;
    virtual Result<bool> update(const T& item) {
        return Result<bool>(false, "Not implemented");
    }
    virtual Result<bool> remove(int id)
    {
        return Result<bool>(false, "Not implemented");
    }
};


#endif
