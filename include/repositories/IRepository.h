/**
 * @file IRepository.h
 * @brief Declares the IRepository interface for generic repository operations in the movie ticket booking system.
 *
 * This file defines the IRepository template interface, which provides a contract for
 * basic CRUD operations (create, update, remove) on data models in the application.
 *
 * Architecture overview:
 * - IRepository<T> is a generic interface for repository classes that manage persistence of entities of type T.
 * - Concrete repository classes should inherit from this interface and implement the required methods.
 * - The interface uses Result<T> to encapsulate operation results and error messages.
 * - This abstraction allows services to interact with data storage in a decoupled and testable manner.
 * - Repositories are used by service classes to perform business logic without depending on specific database code.
 */

#ifndef _BASE_REPOSITORY_H_
#define _BASE_REPOSITORY_H_

#include "../repositories/Result.h"
#include "../utils/DatabaseManager.h"
#include "../utils/Logger.h"

/**
 * @class IRepository
 * @brief Interface for generic repository pattern.
 *
 * This template interface defines the contract for repository classes that manage
 * persistence and CRUD operations for entities of type T.
 *
 * @tparam T The type of entity managed by the repository.
 */
template <typename T>
class IRepository {
public:
    /**
     * @brief Default constructor.
     */
    IRepository() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~IRepository() = default;

    /**
     * @brief Create a new entity in the repository.
     * @param item The entity to create.
     * @return Result containing the ID of the created entity or error information.
     */
    virtual Result<int> create(const T& item) = 0;

    /**
     * @brief Update an existing entity in the repository.
     * @param item The entity with updated data.
     * @return Result indicating success or failure.
     * @note Default implementation returns "Not implemented".
     */
    virtual Result<bool> update(const T& item) {
        return Result<bool>(false, "Not implemented");
    }

    /**
     * @brief Remove an entity from the repository by ID.
     * @param id The ID of the entity to remove.
     * @return Result indicating success or failure.
     * @note Default implementation returns "Not implemented".
     */
    virtual Result<bool> remove(int id)
    {
        return Result<bool>(false, "Not implemented");
    }
};

#endif
