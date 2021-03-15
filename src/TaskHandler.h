//
// Created by vldmr on 15.03.21.
//

#ifndef TASKHANDLER_H
#define TASKHANDLER_H


#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>

#include <boost/filesystem.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/range/iterator_range.hpp>

#include "FileIO.h"
#include "Parser.h"


/**
 * @class
 */
class TaskHandler {
public:
    TaskHandler(const std::string&, const std::string&);
    void Execute();

    ~TaskHandler();
private:
    std::unique_ptr<FileIO> result_fh;

    const boost::filesystem::path files;
    std::vector<std::thread> threads;


    void separate(boost::filesystem::directory_entry&&);
};


#endif
