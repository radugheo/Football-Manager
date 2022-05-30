//
// Created by Radu on 18/05/2022.
//

#include "../headers/Errors.h"

appError::appError(const std::string &arg) : runtime_error(arg) {}
matchError::matchError(const std::string &arg) : appError(arg) {}
