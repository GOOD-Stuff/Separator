//
// Created by vldmr on 15.03.21.
//

#ifndef FILEIO_H
#define FILEIO_H


#include <fstream>
#include <ios>
#include <mutex>
#include <string>


/**
 * @class Wrapper for work with text file
 */
class FileIO {
public:
    explicit FileIO(const std::string&, std::ios_base::
                                            openmode mode = std::ios_base::in);
    ~FileIO();

    void Write(const std::string&);
    std::string Read();

    explicit operator bool() const { // for std::getline compatibility
        return !fh.fail();
    }
private:
    std::fstream fh;
    std::mutex mute;
};


#endif
