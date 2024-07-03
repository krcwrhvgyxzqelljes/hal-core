#include "std_functions.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // For std::strtod
#include <regex>
#include <cctype> // For std::toupper

std_functions::std_functions()
{

}


// Function to parse key-value pairs from the input string
std::vector<std::pair<std::string, double>> std_functions::parse_string_to_key_and_value(const std::string& input, int debug) {
    std::vector<std::pair<std::string, double>> result;
    std::string key;
    std::string valueStr;
    const double dummyValue = 0.0; // Dummy value for newline key

    // Iterate through each character in the input string
    for (size_t i = 0; i < input.size(); ++i) {
        // Check if current character is an alphabet character (key identifier) or newline
        if (isalpha(input[i]) || input[i] == '\n') {
            // If we have accumulated a key and a value, store them
            if (!key.empty() && !valueStr.empty()) {
                // Convert valueStr to double
                double value = std::strtod(valueStr.c_str(), nullptr);
                result.emplace_back(key, value);
                key.clear();
                valueStr.clear();
            }

            // Special handling for newline character
            if (input[i] == '\n') {
                key = "newline"; // Set key to a meaningful name
                valueStr = std::to_string(dummyValue);
            } else {
                // Start new key
                key = input[i];
            }
        } else if (isdigit(input[i]) || input[i] == '-' || input[i] == '+' || input[i] == '.') {
            // Accumulate digits, sign character, or decimal point to form value string
            valueStr += input[i];
        } else {
            // Skip any other characters
            continue;
        }
    }

    // If there's a key and valueStr left to be stored after the loop
    if (!key.empty() && !valueStr.empty()) {
        // Convert valueStr to double
        double value = std::strtod(valueStr.c_str(), nullptr);
        result.emplace_back(key, value);
    }

    if (debug) {
        // Print out the parsed key-value pairs
        for (const auto& pair : result) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }

    return result;
}

// Function to remove spaces and newline characters from a string
std::string std_functions::remove_spaces(const std::string& input){
    std::string result;

    // Iterate through each character in the input string
    for (char c : input) {
        // Exclude spaces and newline characters
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

// Function to remove spaces and newline characters from a string
std::string std_functions::remove_spaces_and_newlines(const std::string& input){
    std::string result;

    // Iterate through each character in the input string
    for (char c : input) {
        // Exclude spaces and newline characters
        if (c != ' ' && c != '\n') {
            result += c;
        }
    }

    return result;
}

std::string std_functions::string_to_lower(const std::string& input){
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Function to read text from a file into a string
std::string std_functions::read_file_to_string(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return ""; // Return an empty string if file cannot be opened
    }

    // Read the contents of the file into a string
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Close the file
    file.close();

    return content;
}

// Function to save a string to a file, it overwrites the file.
void std_functions::save_string_to_file(const std::string& content, const std::string& filepath) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filepath << std::endl;
        return;
    }

    // Write the content to the file
    file << content;

    // Close the file
    file.close();

    // std::cout << "File saved successfully: " << filepath << std::endl;
}

// Function to remove the first newline character (\n) from the beginning of a string
std::string std_functions::remove_first_newline(const std::string& str) {
    if (!str.empty() && str[0] == '\n') {
        return str.substr(1); // Return substring starting from index 1 (skipping the first \n)
    }
    return str; // Return original string if it doesn't start with \n
}


int std_functions::digits(double value)
{
    int digits = 0;
    if (value < 0) digits = 1; // remove this line if '-' counts as a digit
    while (value) {
        value /= 10;
        digits++;
    }
    return digits;
}

std::string std_functions::remove_line_nummers_n_and_value(const std::string& input){
    // Define the regular expression to match "N" or "n" followed by one or more digits
    std::regex pattern("(N|n)\\d+");

    // Use regex_replace to remove the matched patterns from the input string
    return std::regex_replace(input, pattern, "");
}

std::string std_functions::remove_left_white_spaces_lines(const std::string& input){
    std::stringstream ss(input);
    std::string line;
    std::stringstream result;

    while (std::getline(ss, line)) {
        size_t start = line.find_first_not_of(" \t");
        if (start != std::string::npos) {
            result << line.substr(start) << "\n";
        } else {
            result << "\n"; // If the line is all whitespace, add a newline
        }
    }

    return result.str(); // Update the original string with the modified lines
}

std::string std_functions::to_capical(std::string input){
    bool insideParentheses = false;

    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '(') {
            insideParentheses = true;
        } else if (input[i] == ')') {
            insideParentheses = false;
        }

        if (!insideParentheses && std::isalpha(input[i])) {
            input[i] = std::toupper(input[i]);
        }
    }
    return input;
}

std::string std_functions::to_lower(std::string input){
    bool insideParentheses = false;

    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '(') {
            insideParentheses = true;
        } else if (input[i] == ')') {
            insideParentheses = false;
        }

        if (!insideParentheses && std::isalpha(input[i])) {
            input[i] = std::tolower(input[i]);
        }
    }
    return input;
}



























