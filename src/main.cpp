#include <iostream>
#include "TaskHandler.h"


int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            throw std::runtime_error("<Separator> You have to pass two " \
                                     "arguments: path to the folder with " \
                                     "files for parsing and name of the " \
                                     "result file");
        }


        TaskHandler handle(argv[1], argv[2]);
        handle.Execute();
    } catch (const std::exception& exp) {
        std::cerr << exp.what() << std::endl;
        return -EXIT_FAILURE;
    }

    return 0;
}
