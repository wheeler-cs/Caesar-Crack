/**
 * @file StringAnalysis.hpp
 * 
 * @author Drew Wheeler
 * @date 2023-02-11
 * 
 * @brief Contains class definitions for the StringAnalysis class, which is used to analyze the
 *        composition of strings.
 * 
 * @see StringAnalysis.cpp
 * 
 */

#ifndef STRINGANALYSIS_HPP
#define STRINGANALYSIS_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class StringAnalysis {
public:
    // Ctors
    StringAnalysis ();
    StringAnalysis (const std::string&);

    // String Manip Functions
    void rm_data_string_char (char);

    // Analysis Functions
    void gen_instance_profile ();
    void gen_frequency_profile ();
    void calculate_IC ();

    // Output Functions
    void print_instance_profile ();
    void print_frequency_profile ();

private:

    /**
     * @var std::string data_string
     *
     * @brief Stores the string to be analyzed.
     * 
     */
    std::string data_string;

    double index_of_coincidence;

    std::vector<std::pair <char, unsigned int>> char_instances;
    std::vector<std::pair <char, double>> char_frequencies;
};

#endif