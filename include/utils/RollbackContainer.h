#ifndef ROLLBACK_CONTAINER_H
#define ROLLBACK_CONTAINER_H

#include <functional>
#include <stack>

/**
 * @class RollbackContainer
 * @brief Container for managing and executing rollback actions.
 *
 * Stores a stack of rollback actions (as std::function<void()>) that can be executed in reverse order.
 * Useful for implementing transactional behavior or undo operations.
 */
class RollbackContainer {
private:
    std::stack<std::function<void()>> rollbackActions; /**< Stack of rollback actions */

public:
    /**
     * @brief Add a rollback action to the container.
     * @param action The rollback action as a std::function<void()>
     */
    void addRollbackAction(const std::function<void()>& action) ;

    /**
     * @brief Execute all rollback actions in reverse order.
     */
    void executeRollback();

    /**
     * @brief Clear all rollback actions without executing them.
     */
    void clear();
};

#endif // ROLLBACK_CONTAINER_H