//
// Created by Qiu Haoze on 24/11/19.
//

#include "TaskFactory.h"
#include "solv/task/ImmutabilityCheck/ImmutabilityCheckTask.h"

TaskFactory::TaskFactory() {
    Register(ImmutabilityCheckTask::taskName, &ImmutabilityCheckTask::Create);
}

void TaskFactory::Register(const string &taskName, CreateTaskFn fnCreate) {
    m_FactoryMap[taskName] = fnCreate;
}

ITask *TaskFactory::CreateTask(const string &taskName, const SourceUnit * _ast, const ASTNode * _target) {
    TaskFactoryMap::iterator it = m_FactoryMap.find(taskName);
    if ( it != m_FactoryMap.end() ) {
        return it->second(_ast, _target);
    }
    return NULL;
}