//
// Created by vldmr on 15.03.21.
//

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <utility>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/regex.hpp>

#include "FileIO.h"


/**
 * @class Text file parsing and substring generation
 */
class Parser {
public:
    explicit Parser(std::string);
    ~Parser() = default;
    std::string GetSubStrings() const;
private:
    const std::string name;
    std::string result {""};


    std::pair<std::string, std::vector<std::string>> get_lines();
    std::string parse_lines(std::pair<std::string, std::vector<std::string>>&&);
};


#endif
