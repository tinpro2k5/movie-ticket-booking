#ifndef ICOMMAND_H
#define ICOMMAND_H
#include "../../include/models/User.h"

class wxWindow; // Forward declaration
class ICommand{
    public:
    virtual void execute(User user) = 0;
    virtual void executeUI(User user, wxWindow* parent) { }
    virtual ~ICommand() {}
};
#endif