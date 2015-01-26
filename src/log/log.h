#pragma once
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;



class flog
{
    private:
        std::ofstream log;
    public:
        flog();
        void write(int line, std::string file);
        void write_deltatime(float _deltatime);
        void write_score(int _score);
        ~flog();

        // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
        const std::string currentDateTime() {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
            // for more information about date/time format
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

            return buf;
        }
};