#ifndef STD_FUNCTIONS_H
#define STD_FUNCTIONS_H

#include <string>
#include <vector>

class std_functions
{
public:
    std_functions();

    static std::vector<std::pair<std::string, double>> parse_string_to_key_and_value(const std::string& input, int debug);
    static std::string remove_spaces(const std::string& input);
    static std::string remove_spaces_and_newlines(const std::string& input);
    static std::string string_to_lower(const std::string& input);
    static std::string read_file_to_string(const std::string& filepath);
    static void save_string_to_file(const std::string& content, const std::string& filepath);
    static std::string remove_first_newline(const std::string& str);
    static int digits(double value);

    static std::string remove_line_nummers_n_and_value(const std::string& input);
    static std::string remove_left_white_spaces_lines(const std::string& input);
    static std::string to_capical(std::string input);
    static std::string to_lower(std::string input);
};

#endif // STD_FUNCTIONS_H
