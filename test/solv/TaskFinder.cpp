//
// Created by Qiu Haoze on 9/12/19.
//

#include <solv/task/TaskFinder.h>

#include <test/Options.h>

using namespace std;
using namespace langutil;

namespace dev
{
namespace test
{

BOOST_AUTO_TEST_SUITE(TestTaskFinder)

BOOST_AUTO_TEST_CASE(test_find_annotations)
{
    string source = "pragma solidity >=0.4.22 <0.6.0;\n"    // 33 chars
                    "contract Bank {\n"                     // 16 chars
                    "    uint a; //@verifier immutable\n"   // 12 + 22 = 24 chars (first one at 33 + 16 + 12 = 61)
                    "    uint b; //@verifier somethingelse\n"   // 12 + 22 = 24 chars (second one at 61 + 22 + 12 = 95)
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
    TaskFinder* tf = new TaskFinder();
    vector<Annotation> ants = tf->findAnnotations(source);
    // one at 61, one at 75
    BOOST_CHECK_EQUAL(ants.size(), 2);
    if (ants.size() == 2) {
        BOOST_CHECK_EQUAL(ants[0].type, "immutable");
        BOOST_CHECK_EQUAL(ants[0].position, 61);
        BOOST_CHECK_EQUAL(ants[1].type, "somethingelse");
        BOOST_CHECK_EQUAL(ants[1].position, 95);
    }

}

BOOST_AUTO_TEST_SUITE_END()

}
}
