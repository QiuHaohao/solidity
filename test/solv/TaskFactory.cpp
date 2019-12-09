//
// Created by Qiu Haoze on 7/12/19.
//

#include <solv/task/ImmutabilityCheckTask.h>
#include <solv/task/TaskFactory.h>

#include <test/Options.h>

using namespace std;
using namespace langutil;

namespace dev
{
namespace test
{

BOOST_AUTO_TEST_SUITE(TestTaskFactory)

BOOST_AUTO_TEST_CASE(test_create_non_existent_task)
{
    TaskFactory* tf = TaskFactory::Get();
    ITask* task = tf->CreateTask("No such task", ASTPointer<SourceUnit>(), ASTPointer<ASTNode>());
    BOOST_CHECK_EQUAL(task, nullptr);
}

BOOST_AUTO_TEST_CASE(test_create_immutability_check_task)
{
    TaskFactory* tf = TaskFactory::Get();
    ITask* task = tf->CreateTask(ImmutabilityCheckTask::taskName, ASTPointer<SourceUnit>(), ASTPointer<ASTNode>());
    BOOST_CHECK_NE(task, nullptr);
    ImmutabilityCheckTask* icTask = (ImmutabilityCheckTask*)(task);
    BOOST_CHECK_EQUAL(icTask->taskName, ImmutabilityCheckTask::taskName);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
