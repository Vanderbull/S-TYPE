#pragma once
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class flog
{
    private:
    public:
        flog();
        void write(int line, std::string file);
        void write_deltatime(float _deltatime);
        void write_score(int _score);
        ~flog();
};