//
// Created by vldmr on 15.03.21.
//

#include "TaskHandler.h"

namespace boost_fs = boost::filesystem;


TaskHandler::TaskHandler(const std::string& path, const std::string& file)
                    : result_fh(std::make_unique<FileIO>(file,
                                                         std::ios_base::trunc |
                                                         std::ios_base::out))
                    , files(path) {
    if (!boost_fs::exists(files) || !boost_fs::is_directory(files)) {
        throw std::runtime_error("<TaskHandler> Pass non exist directories: "
                                 + path);
    }
}


TaskHandler::~TaskHandler() {
    if (!threads.empty()) {
        for (auto&& thread: threads) {
            if (thread.joinable())
                thread.join();
        }
    }
}


/**
 * @brief Launch separator: parse all files in directory and chop strings by them
 *   delimeters
 * @param none
 *
 * @return none
 * @note Each file parsing in separate thread
 */
void TaskHandler::Execute() {
    auto start = std::chrono::high_resolution_clock::now();
    for(auto entry: boost::make_iterator_range(boost_fs::directory_iterator(files), {})) {
        threads.emplace_back(std::thread(&TaskHandler::separate, this,
                             std::move(entry)));
    }
    auto end = std::chrono::high_resolution_clock::now();

    for (auto&& thread: threads) {
        if (thread.joinable())
            thread.join();
    }
    threads.clear();

    std::chrono::duration<double, std::milli> fp_ms = end - start;
    std::cout << "Elapsed: " << fp_ms.count() << " ms" << std::endl;
}


/**
 * @brief Separate data string by delimiters and write them in result file
 * @param[in] file - information about file for parsing
 *
 * @return none
 */
void TaskHandler::separate(boost_fs::directory_entry&& file) {
    try {
        Parser parser(file.path().string());

        auto result = parser.GetSubStrings();
        result_fh->Write(result);
    } catch(const std::exception& exp) {
        std::cerr << "<TaskHandler> Catch exception in " << __func__ << ": "
                  << exp.what() << std::endl;
    }
}