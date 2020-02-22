//
// Created by Qiu Haoze on 20/2/20.
//
#include <libsolidity/interface/CompilerStack.h>

#include <test/Options.h>

#include <solv/task/TaskFinder.h>
#include <solv/task/IReportItem.h>
#include <solv/task/FixedAfterInitCheck/FixedAfterInitCheckTask.h>
#include <solv/task/FixedAfterInitCheck/FixedAfterInitReportItem.h>
#include <solv/task/FixedAfterInitCheck/FixedAfterInitCheckTaskLocator.h>

using namespace std;

namespace dev {
namespace solidity {
namespace verifier {
namespace test {
BOOST_AUTO_TEST_SUITE(TestFixedAfterInitCheckTask)
    BOOST_AUTO_TEST_CASE(test_modified_in_constructor) {
        string modifiedInPublicFuncContract = "pragma solidity >=0.4.22 <0.6.0;\n"
                                              "contract ModifiedInPublicFuncContract {\n"
                                              "    address owner; //@verifier fixed-after-init\n"
                                              "    constructor () public {\n"
                                              "        owner = msg.sender;\n"
                                              "    }\n"
                                              "}";
        std::map<std::string, std::string> sourceCodes;
        sourceCodes["s"] = modifiedInPublicFuncContract;

        std::unique_ptr<dev::solidity::CompilerStack> compiler;
        compiler.reset(new CompilerStack());
        compiler->setSources(sourceCodes);
        BOOST_CHECK(compiler->parseAndAnalyze());
        const SourceUnit& sourceUnit = compiler->ast("s");

        vector<ITask*> tasks = TaskFinder::findTasks(modifiedInPublicFuncContract, sourceUnit);
        BOOST_CHECK_EQUAL(1, tasks.size());

        vector<IReportItem*> reportItems = tasks[0]->execute();
        BOOST_CHECK_EQUAL(0, reportItems.size());
    }
    BOOST_AUTO_TEST_CASE(test_modified_in_public_func) {
        string modifiedInPublicFuncContract = "pragma solidity >=0.4.22 <0.6.0;\n"
                                              "contract ModifiedInPublicFuncContract {\n"
                                              "    address owner; //@verifier fixed-after-init\n"
                                              "    function changeOwner () public {\n"
                                              "        owner = msg.sender;\n"
                                              "    }\n"
                                              "}";
        std::map<std::string, std::string> sourceCodes;
        sourceCodes["s"] = modifiedInPublicFuncContract;

        std::unique_ptr<dev::solidity::CompilerStack> compiler;
        compiler.reset(new CompilerStack());
        compiler->setSources(sourceCodes);
        BOOST_CHECK(compiler->parseAndAnalyze());
        const SourceUnit& sourceUnit = compiler->ast("s");

        vector<ITask*> tasks = TaskFinder::findTasks(modifiedInPublicFuncContract, sourceUnit);
        BOOST_CHECK_EQUAL(1, tasks.size());

        vector<IReportItem*> reportItems = tasks[0]->execute();
        BOOST_CHECK_EQUAL(1, reportItems.size());

        IReportItem* reportItem = reportItems[0];
        BOOST_CHECK(dynamic_cast<FixedAfterInitReportItem*>(reportItem));

        FixedAfterInitReportItem* fixedAfterInitReportItem = dynamic_cast<FixedAfterInitReportItem*>(reportItem);
        BOOST_CHECK_EQUAL("changeOwner", fixedAfterInitReportItem->getCaller());
        BOOST_CHECK_EQUAL("changeOwner", fixedAfterInitReportItem->getAssigner());
        BOOST_CHECK_EQUAL("owner", fixedAfterInitReportItem->getVariable());

        reportItem->report();
    }
    BOOST_AUTO_TEST_CASE(test_modified_in_private_private_public) {
        string modifiedInPublicFuncContract = "pragma solidity >=0.4.22 <0.6.0;\n"
                                              "contract ModifiedInPublicFuncContract {\n"
                                              "    address owner; //@verifier fixed-after-init\n"
                                              "    function somePublicFunc () public {\n"
                                              "        somePrivateFunc();\n"
                                              "    }\n"
                                              "    function somePrivateFunc () private {\n"
                                              "        changeOwner();\n"
                                              "    }\n"
                                              "    function changeOwner () private {\n"
                                              "        owner = msg.sender;\n"
                                              "    }\n"
                                              "}";
        std::map<std::string, std::string> sourceCodes;
        sourceCodes["s"] = modifiedInPublicFuncContract;

        std::unique_ptr<dev::solidity::CompilerStack> compiler;
        compiler.reset(new CompilerStack());
        compiler->setSources(sourceCodes);
        BOOST_CHECK(compiler->parseAndAnalyze());
        const SourceUnit& sourceUnit = compiler->ast("s");

        vector<ITask*> tasks = TaskFinder::findTasks(modifiedInPublicFuncContract, sourceUnit);
        BOOST_CHECK_EQUAL(1, tasks.size());

        vector<IReportItem*> reportItems = tasks[0]->execute();
        BOOST_CHECK_EQUAL(1, reportItems.size());

        IReportItem* reportItem = reportItems[0];
        BOOST_CHECK(dynamic_cast<FixedAfterInitReportItem*>(reportItem));

        FixedAfterInitReportItem* fixedAfterInitReportItem = dynamic_cast<FixedAfterInitReportItem*>(reportItem);
        BOOST_CHECK_EQUAL("somePublicFunc", fixedAfterInitReportItem->getCaller());
        BOOST_CHECK_EQUAL("changeOwner", fixedAfterInitReportItem->getAssigner());
        BOOST_CHECK_EQUAL("owner", fixedAfterInitReportItem->getVariable());

        reportItem->report();
    }
}
}
}
}
}