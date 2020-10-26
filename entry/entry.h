//
// Created by shine on 10/22/2020.
//

#ifndef ENTRY_ENTRY_H
#define ENTRY_ENTRY_H

#include <sys/types.h>
#include <iostream>

extern "C" void Injection(pid_t pid, std::string pattern, std::string newData);

#endif //ENTRY_ENTRY_H
