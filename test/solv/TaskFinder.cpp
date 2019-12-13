//
// Created by Qiu Haoze on 9/12/19.
//
#include <string>

#include <libsolidity/parsing/Parser.h>
#include <liblangutil/ErrorReporter.h>
#include <liblangutil/Scanner.h>

#include <libsolidity/ast/ASTPrinter.h>
#include <liblangutil/SourceLocation.h>

#include <solv/task/TaskFinder.h>
#include <solv/task/ImmutabilityCheck/ImmutabilityCheckTaskLocator.h>

#include <test/Options.h>

using namespace std;
using namespace langutil;

namespace dev
{
namespace test
{
ASTPointer<SourceUnit> parseText(string const &_source) {
    ErrorList errors;
    ErrorReporter errorReporter(errors);
    ASTPointer<SourceUnit> _sourceUnit = Parser(
            errorReporter,
            dev::test::Options::get().evmVersion(),
            false
    ).parse(std::make_shared<Scanner>(CharStream(_source, "")));
    return _sourceUnit;
}

string source = "pragma solidity >=0.4.22 <0.6.0;\n"    // 33 chars
                "contract Bank {\n"                     // 16 chars
                "    uint a; //@verifier immutable\n"   // 34 chars (first one starts at 33 + 16 = 49, ends at 49 + 34 = 83)
                "    uint b; //@verifier somethingelse\n"   // 38 chars (first one starts at 84, ends at 84 + 38 = 122)
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

BOOST_AUTO_TEST_CASE(test_find_annotations)
{
    TaskFinder* tf = new TaskFinder();
    vector<Annotation> ants = tf->findAnnotations(source);
    // one from 49 to 83, the other one from 84 to 122
    BOOST_CHECK_EQUAL(ants.size(), 2);
    if (ants.size() == 2) {
        BOOST_CHECK_EQUAL(ants[0].m_type, "immutable");
        BOOST_CHECK_EQUAL(ants[0].m_line_location.start, 49);
        BOOST_CHECK_EQUAL(ants[0].m_line_location.end, 83);
        BOOST_CHECK_EQUAL(ants[1].m_type, "somethingelse");
        BOOST_CHECK_EQUAL(ants[1].m_line_location.start, 84);
        BOOST_CHECK_EQUAL(ants[1].m_line_location.end, 122);
    }
}

BOOST_AUTO_TEST_CASE(test_locate_immutability_check_task)
{
    TaskFinder* tf = new TaskFinder();
    vector<Annotation> ants = tf->findAnnotations(source);
    ASTPointer<SourceUnit> _sourceUnit = parseText(source);
    const SourceUnit * sourceUnit = _sourceUnit.get();

    BOOST_CHECK_EQUAL(ants.size(), 2);
    if (ants.size() == 2) {
        // check the first one
        ImmutabilityCheckTaskLocator* firstLocator = new ImmutabilityCheckTaskLocator(sourceUnit, ants[0].m_line_location);
        const VariableDeclaration * firstTarget = firstLocator->locate();
        BOOST_CHECK_EQUAL(firstTarget->id(), 3);
        // check the second one
        ImmutabilityCheckTaskLocator* secondLocator = new ImmutabilityCheckTaskLocator(sourceUnit, ants[1].m_line_location);
        const VariableDeclaration * secondTarget = secondLocator->locate();
        BOOST_CHECK_EQUAL(secondTarget->id(), 5);
    }
}

BOOST_AUTO_TEST_CASE(test_find_targets)
{
    // It actually has all the SourceLocation's in place
//    const SourceUnit * sourceUnit = parseText(source);
//    SourceLocation location = sourceUnit->location();
//
//    ASTPrinter printer(*sourceUnit, source);
//    printer.print(cout);

//    cout << "Source: " << location.text() << endl;
//    cout << "Start: " << location.start << endl;
//    cout << "End: " << location.end << endl;
//    cout << location << endl;


}

BOOST_AUTO_TEST_SUITE_END()

}
}
