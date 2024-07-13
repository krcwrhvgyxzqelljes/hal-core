#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

// Author   : Grotius, alias Skynet Cyberdyne
// Year     : 2024
// Licence  : GPL2
// Purpose  : This header contains functions that are needed to parse c, c++ style gcode

// Function to append a letter followed by the value formatted to 3 decimal places to a text file
void append_value_to_file(std::string key, double value, std::string end, int digits) {
    std::ostringstream oss;
    oss << key << std::fixed << std::setprecision(digits) << value << end;
    std::string formatted_value = oss.str();

    std::ofstream file("out.ngc", std::ios::app);
    if (file.is_open()) {
        file << formatted_value;
        file.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

// Function to append a letter followed by the value formatted to 3 decimal places to a text file
void append_string_to_file(std::string key, std::string value, std::string end) {
    std::ostringstream oss;
    oss << key << value << end;
    std::string formatted_value = oss.str();

    std::ofstream file("out.ngc", std::ios::app);
    if (file.is_open()) {
        file << formatted_value;
        file.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

// Define functions A to Z for appending values
void A(double value) {
    append_value_to_file("A", value, " ", 3);
}

void B(double value) {
    append_value_to_file("B", value, " ", 3);
}

void C(double value) {
    append_value_to_file("C", value, " ", 3);
}

void D(double value) {
    append_value_to_file("D", value, " ", 3);
}

void E(double value) {
    append_value_to_file("E", value, " ", 3);
}

void F(double value) {
    append_value_to_file("F", value, " ", 3);
}

void G(int value) {
    append_value_to_file("G", value, " ", 0);
}

void H(int value) {
    append_value_to_file("H", value, " ", 3);
}

void I(int value) {
    append_value_to_file("I", value, " ", 3);
}

void J(int value) {
    append_value_to_file("J", value, " ", 3);
}

void K(int value) {
    append_value_to_file("K", value, " ", 3);
}

void L(int value) {
    append_value_to_file("L", value, " ", 0);
}

void M(double value) {
    append_value_to_file("M", value, " ", 3);
}

void N(double value) {
    append_value_to_file("\nN", value, " ", 0);
}

void O(double value) {
    append_value_to_file("O", value, " ", 3);
}

void P(double value) {
    append_value_to_file("P", value, " ", 3);
}

void Q(double value) {
    append_value_to_file("Q", value, " ", 3);
}

void R(double value) {
    append_value_to_file("R", value, " ", 3);
}

void S(double value) {
    append_value_to_file("S", value, " ", 3);
}

void T(double value) {
    append_value_to_file("T", value, " ", 3);
}

void U(double value) {
    append_value_to_file("U", value, " ", 3);
}

void V(double value) {
    append_value_to_file("V", value, " ", 3);
}

void W(double value) {
    append_value_to_file("W", value, " ", 3);
}

void X(double value) {
    append_value_to_file("X", value, " ", 3);
}

void Y(double value) {
    append_value_to_file("Y", value, " ", 3);
}

void Z(double value) {
    append_value_to_file("Z", value, " ", 3);
}

void COMMENT(std::string value){
    append_string_to_file("(",value,") ");
}

void exec_code_parser(std::string filename, int debug){
    std::string command;
    command+="./code_parser ";
    if(debug){
        command+="--debug ";
    };
    command+=filename;
    std::system(command.c_str()); // Will create out.ngc in ~/bin
}

#endif // FUNCTIONS_H





















