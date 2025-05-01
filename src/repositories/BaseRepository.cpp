#include "../../include/repositories/BaseRepository.h"

BaseRepository::BaseRepository() {
    dbManager = DatabaseManager::getInstance();
    logger = Logger::getInstance();
}
BaseRepository::~BaseRepository() {
    // Destructor
    // Clean up resources if needed
}
