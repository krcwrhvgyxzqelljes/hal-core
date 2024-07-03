#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include "functions.h"
#include <std_functions.h>
#include <regex>

std::string edit_key_value(const std::string& input_text, const std::string& key, std::string append_front, std::string append_back) {
    std::string output_text = input_text;
    size_t pos = 0;

    while ((pos = output_text.find(key, pos)) != std::string::npos) {
        size_t value_pos = pos + key.length();

        // Check if the character after the key is a digit, period, or minus sign
        if (value_pos < output_text.length() && (std::isdigit(output_text[value_pos]) || output_text[value_pos] == '.' || output_text[value_pos] == '-')) {
            // Find the end of the value associated with the key
            size_t value_end = output_text.find_first_not_of("0123456789.-", value_pos);
            if (value_end == std::string::npos) {
                value_end = output_text.length();
            }
            std::string value = output_text.substr(value_pos, value_end - value_pos);
            // Replace the value with "(value);"
            output_text.replace(value_pos, value.length(), append_front + value + append_back);
            // Move past the replaced value to continue searching
            pos = value_pos + value.length() + append_front.length() + append_back.length(); // Adjusted to include append_front and append_back lengths
        } else {
            // Move past this key occurrence if not followed by a valid character
            pos = value_pos;
        }
    }
    return output_text;
}

std::string restore_key_value(const std::string& input_text, const std::string& key, const std::string& remove_front, const std::string& remove_back) {
    std::string output_text = input_text;
    size_t pos = 0;

    while ((pos = output_text.find(key, pos)) != std::string::npos) {
        size_t value_start_pos = pos + key.length();

        // Check if the string after the key matches remove_front
        if (output_text.compare(value_start_pos, remove_front.length(), remove_front) == 0) {
            size_t value_start = value_start_pos + remove_front.length();
            size_t value_end_pos = output_text.find(remove_back, value_start);

            if (value_end_pos != std::string::npos) {
                // Extract the value inside the specified delimiters
                std::string value = output_text.substr(value_start, value_end_pos - value_start);

                // Ensure the value contains only digits and periods
                bool is_valid_value = !value.empty() && value.find_first_not_of("0123456789.") == std::string::npos;

                if (is_valid_value) {
                    // Replace "remove_front value remove_back" with "value"
                    output_text.replace(value_start_pos, (value_end_pos + remove_back.length()) - value_start_pos, value);

                    // Move past the replaced value to continue searching
                    pos = value_start_pos + value.length();
                    continue;
                }
            }
        }
        // Move past this key occurrence if it doesn't match the pattern
        pos = value_start_pos;
    }
    return output_text;
}

std::string isolate_comments(const std::string& input_text, const std::string& comment_sign, const std::string& append_front, const std::string& append_back) {
    std::istringstream input_stream(input_text);
    std::ostringstream output_stream;
    std::string line;

    while (std::getline(input_stream, line)) {
        size_t comment_pos = line.find(comment_sign);
        if (comment_pos != std::string::npos) {
            // Extract the comment part and remove leading/trailing whitespace
            std::string comment = line.substr(comment_pos + 2);
            comment.erase(0, comment.find_first_not_of(" \t"));
            comment.erase(comment.find_last_not_of(" \t") + 1);

            // Replace the comment part with the transformed comment
            line = line.substr(0, comment_pos) + append_front + comment + append_back;
        }
        output_stream << line << "\n";
    }

    return output_stream.str();
}

// Function to compile C++ code from a string
bool compile(const std::string& cpp_code, const std::string& output_exe_name = "output", int debug=0) {

    std_functions().save_string_to_file(cpp_code,"temp.cpp");

    // Step 2: Compile the .cpp file to an executable
    std::string compileCommand = "g++ temp.cpp -o " + output_exe_name; // Adjust as per your compiler and options
    int compileResult = std::system(compileCommand.c_str());

    // Step 3: Check if compilation was successful
    if (compileResult != 0) {
        std::cerr << "Error: Compilation failed." << std::endl;
        std::remove("temp.cpp"); // Remove the temporary .cpp file
        return false;
    }

    if(debug){
        std::cout << "Compilation successful. Executable generated: " << output_exe_name << std::endl;
    }

    // Optional: Remove the temporary .cpp file after successful compilation
    std::remove("temp.cpp");

    return true;
}


std::string intro = R"(
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include "functions.h"

int main() {
)";

std::string gcode_sample = R"(

int n=0;
int y=1;

N(n++); // This is a comment.
N(n++); // Also a comment.
N(n++); # Valid comment.

N(n++); M3
N(n++); G0 X-10 Y0 Z0 A0.1 B1.2 C3.6 U8.2 V6.9 W22 W55
N(n++); G54.4 X12 P1.0 Q2.5 R2.6 L12 O12.2
N(n++); X(y+1); Y225.000 // Sample.

int x=0;
while(x<10){
    N(n++); Z10 A(x);
    x++;
}

N(n++); M30

)";

std::string outtro = R"(
return 0;
}
)";

void parse(std::string gcode, int debug){

    if(debug){
        std::cout<<"***** gcode in *****"<<std::endl;
        std::cout<<gcode<<std::endl;
    }

    gcode=isolate_comments(gcode, "//", "COMMENT(\"", "\");");
    gcode=isolate_comments(gcode, "/*", "COMMENT(\"", "\");");
    gcode=isolate_comments(gcode, "#", "COMMENT(\"", "\");");

    if(debug){
        std::cout<<"***** gcode isolate comments *****"<<std::endl;
        std::cout<<gcode<<std::endl;
    }

    // Original keys vector containing all uppercase English alphabet letters
    std::vector<std::string> keys;

    // Populate keys with alphabet letters 'A' to 'Z'
    for (char c = 'A'; c <= 'Z'; ++c) {
        keys.push_back(std::string(1, c)); // Construct a string with 1 character 'c'
    }
    for (const std::string& key : keys) {
        gcode = edit_key_value(gcode, key, "(", ");");
    }

    if(debug){
        std::cout<<"***** gcode isolated *****"<<std::endl;
        std::cout<<gcode<<std::endl;
    }

    std::string program;
    program+=intro;
    program+=gcode;
    program+=outtro;

    if(debug){
        std::cout<<"***** program code *****"<<std::endl;
        std::cout<<program<<std::endl;
    }

    std::remove("out.ngc");
    if (compile(program, "parser",debug)) {
        std::string command = "./parser"; // Example for running on Linux
        std::system(command.c_str());
        std::remove("parser");
    }

    std::string out=std_functions().read_file_to_string("out.ngc");
    // Remove \n at begin of file.
    out=std_functions().remove_first_newline(out);
    // Save again.
    std_functions().save_string_to_file(out,"out.ngc");

    if(debug){
        std::cout<<"***** gcode out *****"<<std::endl;
        std::cout<<out<<std::endl;
    }
}

/* Usage:
            std::string command;
            command+="./code_parser ";
            if(DEBUG){
                command+="--debug ";
            };
            command+=filename;
            std::system(command.c_str()); // Will create out.ngc in ~/bin

   Or:

   functions.h -> exec_parser(....)
*/

int main(int argc, char* argv[]) {

    int debug=0;

    if (argc < 2) {
        // If no argument is provided
        std::cerr << "Usage: " << argv[0] << " <gcode_file>" << std::endl;
        std::cerr << "Parsing gcode sample."<< std::endl;
        debug=1;
        parse(gcode_sample,debug);
        return 1; // Return error code
    }

    // Call parse function with the gcode filename or string
    if (argc >= 3 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0)) {
        debug = 1; // Set debug flag
    }
    parse(std_functions().read_file_to_string(argv[1]),debug);
    return 0;
}














