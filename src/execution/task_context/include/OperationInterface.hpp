#ifndef ORO_OPERATION_INTERFACE_HPP
#define ORO_OPERATION_INTERFACE_HPP

#include <string>
#include "CommandRepository.hpp"
#include "MethodRepository.hpp"

namespace RTT
{
    /**
     * The interface for accessing and executing 'operations', being commands
     * and methods.
     */
    class OperationInterface
    {
    public:
        virtual ~OperationInterface() {}
        virtual const std::string& getName() const = 0;
        virtual const std::string& getDescription() const = 0;
        virtual CommandRepository* commands() = 0;

        virtual MethodRepository* methods() = 0;
    };


    /**
     * A task object groups a set of commands and methods (operations)
     * which may be invoked.
     */
    class TaskObject
        : public OperationInterface
    {
        const std::string mname;
        const std::string mdescription;

        CommandRepository mcommands;

        MethodRepository mmethods;
    public:
        TaskObject(std::string name, std::string description ="A Task Object.")
            : mname(name), mdescription(description)
        {}

        const std::string& getName() const { return mname; }

        const std::string& getDescription() const { return mdescription; }

        virtual CommandRepository* commands() { return &mcommands; }

        virtual MethodRepository* methods() { return &mmethods;}
    };
}


#endif