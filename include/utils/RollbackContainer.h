#ifndef ROLLBACK_CONTAINER_H
#define ROLLBACK_CONTAINER_H

#include <functional>
#include <stack>

class RollbackContainer {
private:
    std::stack<std::function<void()>> rollbackActions;

public:
    // Add a rollback action
    void addRollbackAction(const std::function<void()>& action) ;

    // Execute all rollback actions
    void executeRollback();

    // Clear all rollback actions without executing
    void clear();
};

#endif // ROLLBACK_CONTAINER_H