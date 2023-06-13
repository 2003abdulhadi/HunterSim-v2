#ifndef VIEW_H
#define VIEW_H

#include <iostream>

/// @brief View class display simple menu to interact with the program.
/// All options are presented in the display method
class View
{
public:
    View();
    ~View();
    void display(int &);
};

#endif