#include "log.h"

flog::flog()
{

}

void flog::write(int line, std::string file)
{
    std::ofstream log("./logs/lastrun.txt");
    std::streambuf *save = std::cerr.rdbuf();
    // Redirect stream buffers
    if (log.is_open())
        std::cerr.rdbuf(log.rdbuf());

    std::cerr << __LINE__ << " " << __FILE__ << endl;
    std::cerr << line << " " << file.c_str() << endl;

    // Restore cerr's stream buffer before terminating
    if (log.is_open())
        std::cerr.rdbuf(save);

}

flog::~flog()
{

}