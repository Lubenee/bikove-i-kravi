#if !defined(FILE_HANDLER_H)
#define FILE_HANDLER_H

#include <fstream>
#include <iostream>

namespace fh
{
    void record_high_score(int high_score)
    {
        std::ofstream ofs;
        ofs.open("score.dat", std::ios::binary | std::ios::out);
        if (!ofs.is_open())
        {
            ofs.close();
            std::cout << "Score file didn't load properly.\n\n";
            return;
        }
        std::cout << "Recording high score...\n\n";
        ofs.write(reinterpret_cast<const char *>(&high_score), sizeof(int));
        if (ofs.good())
        {
            ofs.close();
        }
        else
        {
            std::cout << "There was an error recording the high score :(, sorry.\n\n";
            ofs.clear();
            ofs.close();
        }
    }

    int read_high_score()
    {
        std::ifstream ifs("score.dat", std::ios::binary | std::ios::in);
        if (!ifs.is_open())
        {
            std::cout << "Scores file wasn't found :(\n";
            return 0;
        }

        int score = 0;
        ifs.read(reinterpret_cast<char *>(&score), sizeof(int));

        if (!ifs.good())
        {
            std::cout << "There was an error reading your high score :(\n\n";
            ifs.clear();
        }
        ifs.close();

        return score;
    }

}

#endif // FILE_HANDLER_H
