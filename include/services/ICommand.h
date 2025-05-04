#ifndef ICOMMAND_H
#define ICOMMAND_H
#include "../../include/models/User.h"
class ICommand{
    public:
    virtual void execute(User user) = 0;
    virtual ~ICommand() {}
};
#endif