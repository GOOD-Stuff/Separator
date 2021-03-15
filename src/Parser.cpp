//
// Created by vldmr on 15.03.21.
//

#include "Parser.h"


Parser::Parser(std::string file_name) : name {std::move(file_name)} {
    result = parse_lines(get_lines());
}


/**
 * @brief Return result of parsing
 * @param none
 *
 * @return parsed substrings concatenated in one string
 */
std::string Parser::GetSubStrings() const {
    return result;
}


/**
 * @brief Return all lines of the file
 * @param none
 *
 * @return pair of strings: first - string for parsing; second - strings of delimiters
 */
std::pair<std::string, std::vector<std::string>> Parser::get_lines() {
    try {
        FileIO fh(name);

        std::string src = fh.Read();
        std::vector<std::string> delims;
        while (fh)
            delims.emplace_back(fh.Read());

        return std::make_pair(src, delims);
    } catch(const std::exception& exp) {
        std::cerr << "<Parser> Catch exception in " << __func__ << ": "
                  << exp.what() << std::endl;
        throw;
    }
}


/**
 * @brief Parse incoming strings and return result substrings
 * @param[in] src_delims - the pair of source string and them delimiters
 *
 * @return parsed substrings - if successfully walk through file
 * @return empty string - if doesn't have separators or catch exception
 */
std::string Parser::parse_lines(std::pair<std::string,
                                          std::vector<std::string>>&& src_delims) {
    try {
        if (src_delims.second.empty())
            return "";

        auto [src, delims] = src_delims;
        for (const auto& del: delims) {
            if (del.size() > 1) {
                // escape boost::...::split_regex due to difficult regexp build
                boost::algorithm::replace_all(src, del, "\n");
                continue;
            }

            std::vector<std::string> lines;
            boost::algorithm::split(lines, src, boost::is_any_of(del),
                                    boost::token_compress_on);
            src = boost::algorithm::join(lines, "\n");
        }

        // remove all empty lines
        std::vector<std::string> lines;
        boost::algorithm::split_regex(lines, src, boost::regex("[\\n]+"));
        src = boost::algorithm::join(lines, "\n");

        if (src.empty())
            return "";

        if (src.front() == '\n') // when string start by delimiter
            src.erase(src.begin());

        if (src.back() != '\n') // for pretty reading from file
            src.push_back('\n');

        return ("[" + name + "]:" + "\n" + src);
    } catch (const std::exception& exp) {
        std::cerr << "<Parser> Catch exception in " << __func__ << ": "
                  << exp.what() << std::endl;
        return "";
    }
}