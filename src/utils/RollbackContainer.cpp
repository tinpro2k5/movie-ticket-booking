#include "../../include/utils/RollbackContainer.h"

void RollbackContainer::addRollbackAction(const std::function<void()>& action) {
    rollbackActions.push(action);
}

// Execute all rollback actions
void RollbackContainer::executeRollback() {
    while (!rollbackActions.empty()) {
        rollbackActions.top()(); // Execute the action
        rollbackActions.pop();   // Remove it from the stack
    }
}

// Clear all rollback actions without executing
void RollbackContainer::clear() {
    while (!rollbackActions.empty()) {
        rollbackActions.pop();
    }
}