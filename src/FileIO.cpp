//
// Created by vldmr on 15.03.21.
//

#include "FileIO.h"


FileIO::FileIO(const std::string& name, std::ios_base::openmode mode)
                                                            : fh(name, mode) {
    if (!fh.is_open())
        throw std::runtime_error("<FileIO> Can't open file " + name);
}


FileIO::~FileIO() {
    if (fh.is_open())
        fh.close();
}


/**
 * @brief Write string to the file
 * @param[in] data - string for write
 *
 * @return none
 * @note It is assumed that the method is called in parallel, so it contains
 *   the mutex for synchronization
 */
void FileIO::Write(const std::string& data) {
    std::scoped_lock lock(mute);
    fh.write(data.c_str(), data.size());
}


/**
 * @brief Read line from the file and return it
 * @param none
 *
 * @return string separated by '\n'
 */
std::string FileIO::Read() {
    std::string line;
    std::getline(fh, line);
    return line;
}