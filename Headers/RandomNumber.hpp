#if !defined RANDOM_NUMBER_H
#define RANDOM_NUMBER_H

#include <string>
#include <random>

using namespace std::chrono;
/**
 * Generates a random n-digit number with unique digits.
 * Digits may include 0 and can appear as the first digit.
 */
std::string get_random_n_digit_number(int n) {
    if (n < 4 || n > 6)
        throw std::invalid_argument("Number should be according to the game's difficulty, e.g. 4,5,6.\n");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<char> digits = {'0','1','2','3','4','5','6','7','8','9'};

    std::string result;
    for (int i = 0; i < n; ++i) {
        std::uniform_int_distribution<> dist(0, digits.size() - 1);
        char chosen = digits[dist(gen)];
        result += chosen;
        digits.erase(std::remove(digits.begin(), digits.end(), chosen), digits.end());
    }

    return result;
}

#endif // RANDOM_NUMBER_H
