#ifndef ROLLBACK_CONTAINER_H
#define ROLLBACK_CONTAINER_H

#include <functional>
#include <stack>

class RollbackContainer {
private:
    std::stack<std::function<void()>> rollbackActions;

public:
    // Add a rollback action
    void addRollbackAction(const std::function<void()>& action) {
        rollbackActions.push(action);
    }

    // Execute all rollback actions
    void executeRollback() {
        while (!rollbackActions.empty()) {
            rollbackActions.top()(); // Execute the action
            rollbackActions.pop();   // Remove it from the stack
        }
    }

    // Clear all rollback actions without executing
    void clear() {
        while (!rollbackActions.empty()) {
            rollbackActions.pop();
        }
    }
};

#endif // ROLLBACK_CONTAINER_H