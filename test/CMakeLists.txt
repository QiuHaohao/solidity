file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

file(GLOB contracts_sources "contracts/*.cpp")
file(GLOB contracts_headers "contracts/*.h")
file(GLOB libdevcore_sources "libdevcore/*.cpp")
file(GLOB libdevcore_headers "libdevcore/*.h")
file(GLOB liblangutil_sources "liblangutil/*.cpp")
file(GLOB liblangutil_headers "liblangutil/*.h")
file(GLOB libevmasm_sources "libevmasm/*.cpp")
file(GLOB libevmasm_headers "libevmasm/*.h")
file(GLOB libyul_sources "libyul/*.cpp")
file(GLOB libyul_headers "libyul/*.h")
if (LLL)
    file(GLOB liblll_sources "liblll/*.cpp")
    file(GLOB liblll_headers "liblll/*.h")
endif()
file(GLOB libsolidity_sources "libsolidity/*.cpp")
file(GLOB libsolidity_headers "libsolidity/*.h")
file(GLOB libsolidity_util_sources "libsolidity/util/*.cpp")
file(GLOB libsolidity_util_headers "libsolidity/util/*.h")
file(GLOB solv_sources "solv/*.cpp")
file(GLOB solv_headers "solv/*.h")
file(GLOB solv_tasks_sources "solv/tasks/*.cpp")
file(GLOB solv_tasks_headers "solv/tasks/*.h")

add_executable(soltest ${sources} ${headers}
    ${contracts_sources} ${contracts_headers}
    ${libdevcore_sources} ${libdevcore_headers}
    ${liblangutil_sources} ${liblangutil_headers}
    ${libevmasm_sources} ${libevmasm_headers}
    ${libyul_sources} ${libyul_headers}
    ${liblll_sources} ${liblll_headers}
    ${libsolidity_sources} ${libsolidity_headers}
    ${libsolidity_util_sources} ${libsolidity_util_headers}
        ${solv_sources} ${solv_headers}
        ${solv_tasks_sources} ${solv_tasks_headers}
)
target_link_libraries(soltest PRIVATE libsolc yul solidity yulInterpreter evmasm devcore libsolv Boost::boost Boost::program_options Boost::unit_test_framework evmc)


# Special compilation flag for Visual Studio (version 2019 at least affected)
# in order to compile SolidityEndToEndTest.cpp, which is quite huge.
# We can remove this flag once we've extracted the tests.
# TODO: Remove this option as soon as we have reduced the SLoC's in SolidityEndToEndTest.cpp
if (MSVC)
    target_compile_options(soltest PUBLIC "/bigobj")
endif()

if (LLL)
    target_link_libraries(soltest PRIVATE lll)
    target_compile_definitions(soltest PRIVATE HAVE_LLL=1)
endif()

if (NOT Boost_USE_STATIC_LIBS)
    target_compile_definitions(soltest PUBLIC -DBOOST_TEST_DYN_LINK)
endif()

add_subdirectory(tools)
add_subdirectory(evmc)
