//
// Created by Qiu Haoze on 24/11/19.
//

#include <map>
#include <libsolidity/ast/AST.h>
#include "ITask.h"

#ifndef SOLIDITY_TASKFACTORY_H
#define SOLIDITY_TASKFACTORY_H

typedef ITask* (*CreateTaskFn)(const ASTPointer<SourceUnit>, const ASTPointer<ASTNode>);

using namespace std;
class TaskFactory {
private:
    TaskFactory();
    TaskFactory(const TaskFactory &) { }
    TaskFactory &operator=(const TaskFactory &) { return *this; }

    typedef map<string, CreateTaskFn> TaskFactoryMap;
    TaskFactoryMap m_FactoryMap;

public:
    ~TaskFactory() { m_FactoryMap.clear(); }

    static TaskFactory *Get() {
        static TaskFactory instance;
        return &instance;
    }

    void Register(const string &taskName, CreateTaskFn fnCreate);
    ITask *CreateTask(const string &taskName, const ASTPointer<SourceUnit> _ast, const ASTPointer<ASTNode> _target);
};


#endif //SOLIDITY_TASKFACTORY_H
