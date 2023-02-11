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

    // String Manipulation Functions
    void rm_data_string_char (char);

    // Analysis Functions
    void gen_char_instance_profile ();
    void gen_char_frequency_profile ();
    void calculate_IC ();

    // Output Functions
    void print_instance_profile ();
    void print_frequency_profile ();

    // Mutators
    void set_string (const std::string& str) { data_string = str; }

    // Accessors
    std::string get_string () { return data_string; }
    double get_IC () { return index_of_coincidence; }
    double get_char_freq (char);

private:

    /**
     * @var std::string data_string
     *
     * @brief Stores the string to be analyzed.
     * 
     */
    std::string data_string;

    /**
     * @var double index_of_coincidence
     * 
     * @brief Holds the calculated Index of Coincidence (IC) value for a string.
     */
    double index_of_coincidence;

    std::vector <std::pair <char, unsigned int>> char_instances;
    std::vector <std::pair <char, double>> char_frequencies;
};

#endif