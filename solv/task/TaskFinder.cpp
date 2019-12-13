//
// Created by Qiu Haoze on 25/11/19.
//
#include <regex>
#include <vector>

#include "TaskFinder.h"

using namespace std;

namespace dev
{
namespace solidity
{
namespace verifier
{

const regex TaskFinder::annotationPattern("(?:\n|^).+//@verifier ([a-z- ]+)");

vector<TaskAnnotation> TaskFinder::findAnnotations(const string& source) {
    vector<TaskAnnotation> result;
    int current_position = 0;
    string s = source;
    smatch m;
    regex re = annotationPattern;
    while (std::regex_search (s,m,re)) {
        // if there is only one captured
        if (m.size() == 2) {
            string matched = m[0];
            string captured = m[1];
            // + 1 because don't need the first line change
            int this_delta_position = m.position() + 1;
            int this_line_start = current_position + this_delta_position;
            int this_line_end = this_line_start + matched.length();
            TaskAnnotation this_annotation = TaskAnnotation(captured, this_line_start, this_line_end);
            result.push_back(this_annotation);
            s = m.suffix().str();
            current_position = this_line_end;
        }
    }
    return result;
}

}
}
}