//
// Created by Qiu Haoze on 24/11/19.
//
#ifndef SOLIDITY_TASKFACTORY_H
#define SOLIDITY_TASKFACTORY_H

#include <map>
#include <string>

#include <liblangutil/SourceLocation.h>
#include <libsolidity/ast/AST.h>

#include "ITask.h"
#include "TaskAnnotation.h"


namespace dev
{
namespace solidity
{
namespace verifier
{

typedef ITask *(*CreateTaskFn)(const SourceUnit *, const langutil::SourceLocation);

class TaskFactory {
private:
    TaskFactory();

    TaskFactory(const TaskFactory &) {}

    TaskFactory &operator=(const TaskFactory &) { return *this; }

    typedef std::map<std::string, CreateTaskFn> TaskFactoryMap;
    TaskFactoryMap m_FactoryMap;

public:
    ~TaskFactory() { m_FactoryMap.clear(); }

    static TaskFactory *Get() {
        static TaskFactory instance;
        return &instance;
    }

    void Register(const std::string &taskName, CreateTaskFn fnCreate);

    ITask *CreateTask(const TaskAnnotation annotation, const SourceUnit *_ast);
};

}
}
}

#endif //SOLIDITY_TASKFACTORY_H
