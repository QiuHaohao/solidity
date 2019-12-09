//
// Created by Qiu Haoze on 25/11/19.
//
#include <regex>
#include <vector>

#include "TaskFinder.h"

using namespace std;

const regex TaskFinder::annotationPattern("//@verifier ([a-z- ]+)");

vector<Annotation> TaskFinder::findAnnotations(const string& source) {
    vector<Annotation> result;
    int current_position = 0;
    string s = source;
    smatch m;
    regex re = annotationPattern;
    while (std::regex_search (s,m,re)) {
        // if there is only one captured
        if (m.size() == 2) {
            string matched = m[0];
            string captured = m[1];
            int this_delta_position = m.position();
            int this_position = current_position + this_delta_position;
            Annotation this_annotation = Annotation(captured, this_position);
            result.push_back(this_annotation);
            s = m.suffix().str();
            current_position += this_delta_position + matched.length();
        }
    }
    return result;
}