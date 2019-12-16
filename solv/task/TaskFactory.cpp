//
// Created by Qiu Haoze on 24/11/19.
//

#include "TaskFactory.h"
#include "solv/task/ImmutabilityCheck/ImmutabilityCheckTask.h"

using namespace std;
using namespace langutil;

namespace dev
{
namespace solidity
{
namespace verifier {

TaskFactory::TaskFactory() {
    Register(ImmutabilityCheckTask::taskName, &ImmutabilityCheckTask::Create);
}

void TaskFactory::Register(const string &taskName, CreateTaskFn fnCreate) {
    m_FactoryMap[taskName] = fnCreate;
}

ITask *TaskFactory::CreateTask(const TaskAnnotation annotation, const SourceUnit *_ast) {
    string taskName = annotation.m_type;
    SourceLocation line_location = annotation.m_line_location;
    TaskFactoryMap::iterator it = m_FactoryMap.find(taskName);
    if (it != m_FactoryMap.end()) {
        return it->second(_ast, line_location);
    }
    return NULL;
}

}
}
}