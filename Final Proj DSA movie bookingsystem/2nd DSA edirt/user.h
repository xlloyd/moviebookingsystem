#ifndef USER_H
#define USER_H

#include "admin.h"
#include "utils.h"
#include "fileio.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

void showUserConsole();
void bookMovie();
void displaySeats(const std::vector<User>& users);

#endif // USER_H
