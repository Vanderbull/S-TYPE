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

void flog::write_deltatime(float _deltatime = 0)
{
    std::ofstream log("./logs/fps.txt", ios::out | ios::app);

    if (log.is_open())
    {
        log << _deltatime << endl;
    }
    // Close stream buffer before exiting
    if (log.is_open())
    {
        log.close();
    }
}

void flog::write_score(int _score)
{
    std::ofstream log("./logs/score.txt", ios::out | ios::app);

    if (log.is_open())
    {
        log << _score << endl;
    }
    // Close stream buffer before exiting
    if (log.is_open())
    {
        log.close();
    }
}

flog::~flog()
{

}