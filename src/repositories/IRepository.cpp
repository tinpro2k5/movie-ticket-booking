#include "../../include/repositories/IRepository.h"

template <typename T>
IRepository<T>::IRepository() {
    dbManager = DatabaseManager::getInstance();
    logger = Logger::getInstance();
}
template <typename T>
IRepository<T>::~IRepository() {
    // Destructor
    // Clean up resources if needed
}

template <typename T>
Result<bool> IRepository<T>::update(const T& item) {
    return Result<bool>(false, "Not implemented");
}

template <typename T>
Result<bool> IRepository<T>::remove(int id) {
    return Result<bool>(false, "Not implemented");
}