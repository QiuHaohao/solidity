//
// Created by Qiu Haoze on 9/12/19.
//
#include <string>

#include <libsolidity/parsing/Parser.h>
#include <liblangutil/ErrorReporter.h>
#include <liblangutil/Scanner.h>

#include <liblangutil/SourceLocation.h>

#include <solv/task/TaskFinder.h>
#include <solv/task/ImmutabilityCheck/ImmutabilityCheckTask.h>
#include <solv/task/ImmutabilityCheck/ImmutabilityCheckTaskLocator.h>

#include <test/Options.h>
#include <libsolidity/interface/CompilerStack.h>

using namespace std;
using namespace langutil;

namespace dev
{
namespace solidity
{
namespace verifier
{
namespace test
{

string source = "pragma solidity >=0.4.22 <0.6.0;\n"    // 33 chars
                "contract Bank {\n"                     // 16 chars
                "    uint a; //@verifier immutable\n"   // 34 chars (first one starts at 33 + 16 = 49, ends at 49 + 34 = 83)
                "    uint b; //@verifier immutable\n"   // 38 chars (first one starts at 84, ends at 84 + 38 = 122)
                "\n"
                "    function add(uint x, uint y) public returns (uint r, uint s){\n"
                "        return (r,s);\n"
                "    }\n"
                "\n"
                "    function _Main_() public {\n"
                "        a = 5;\n"
                "        b = 4;\n"
                "    }\n"
                "}";

BOOST_AUTO_TEST_SUITE(TestTaskFinder)

BOOST_AUTO_TEST_CASE(test_find_targets) {
        vector<TaskAnnotation> ants = TaskFinder::findAnnotations(source);

        // one from 49 to 83, another one from 84 to 122
        BOOST_CHECK_EQUAL(ants.size(), 2);

        if (ants.size() == 2) {
            BOOST_CHECK_EQUAL(ants[0].m_type, "immutable");
            BOOST_CHECK_EQUAL(ants[0].m_line_location.start, 49);
            BOOST_CHECK_EQUAL(ants[0].m_line_location.end, 83);
            BOOST_CHECK_EQUAL(ants[1].m_type, "immutable");
            BOOST_CHECK_EQUAL(ants[1].m_line_location.start, 84);
            BOOST_CHECK_EQUAL(ants[1].m_line_location.end, 118);
        }

        std::map<std::string, std::string> sourceCodes;
        sourceCodes["s"] = source;

        std::unique_ptr<dev::solidity::CompilerStack> compiler;
        compiler.reset(new CompilerStack());
        compiler->setSources(sourceCodes);
        BOOST_CHECK(compiler->parseAndAnalyze());
        const SourceUnit& sourceUnit = compiler->ast("s");

        if (ants.size() == 2) {
            // check the first one
            ImmutabilityCheckTaskLocator* firstLocator = new ImmutabilityCheckTaskLocator(sourceUnit, ants[0].m_line_location);
            const VariableDeclaration * firstTarget = firstLocator->locate();
            BOOST_CHECK_EQUAL(firstTarget->id(), 3);
            // check the second one
            ImmutabilityCheckTaskLocator* secondLocator = new ImmutabilityCheckTaskLocator(sourceUnit, ants[1].m_line_location);
            const VariableDeclaration * secondTarget = secondLocator->locate();
            cout << "isLocalVariable?: " << secondTarget->isLocalVariable() << endl;
            cout << "isCallableParameter?: " << secondTarget->isCallableParameter() << endl;
            cout << "isReturnParameter?: " << secondTarget->isReturnParameter() << endl;
            cout << "isLocalOrReturn?: " << secondTarget->isLocalOrReturn() << endl;
            cout << "isExternalCallableParameter?: " << secondTarget->isExternalCallableParameter() << endl;
            cout << "isInternalCallableParameter?: " << secondTarget->isInternalCallableParameter() << endl;
            cout << "isLibraryFunctionParameter?: " << secondTarget->isLibraryFunctionParameter() << endl;
            cout << "isEventParameter?: " << secondTarget->isEventParameter() << endl;
//            Can only be called after reference resolution
            cout << "hasReferenceOrMappingType?: " << secondTarget->hasReferenceOrMappingType() << endl;
            cout << "isStateVariable?: " << secondTarget->isStateVariable() << endl;
            cout << "isIndexed?: " << secondTarget->isIndexed() << endl;
            cout << "isConstant?: " << secondTarget->isConstant() << endl;
            BOOST_CHECK_EQUAL(secondTarget->id(), 5);
        }
}

BOOST_AUTO_TEST_CASE(test_find_tasks) {
        std::map<std::string, std::string> sourceCodes;
        sourceCodes["s"] = source;

        std::unique_ptr<dev::solidity::CompilerStack> compiler;
        compiler.reset(new CompilerStack());
        compiler->setSources(sourceCodes);
        BOOST_CHECK(compiler->parseAndAnalyze());
        const SourceUnit& sourceUnit = compiler->ast("s");

    vector<ITask*> tasks = TaskFinder::findTasks(source, sourceUnit);
    if (tasks.size() == 2) {
        BOOST_CHECK(dynamic_cast<ImmutabilityCheckTask*>((ImmutabilityCheckTask*) tasks[0]));
        BOOST_CHECK(dynamic_cast<ImmutabilityCheckTask*>((ImmutabilityCheckTask*) tasks[1]));
    }
}

BOOST_AUTO_TEST_SUITE_END()

}
}
}
}
