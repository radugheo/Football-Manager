//
// Created by Radu on 18/05/2022.
//

#ifndef OOP_ERRORS_H
#define OOP_ERRORS_H

#include <stdexcept>

class appError : public std::runtime_error {
public:
    explicit appError(const std::string &arg);
};

class matchError : public appError {
public:
    explicit matchError(const std::string &arg);
};

#endif //OOP_ERRORS_H
