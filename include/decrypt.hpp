/**
 * @file decrypt.hpp
 * @author Drew Wheeler
 * @date 2023-02-12
 * 
 * @brief Contains definitions for the DecryptEngine class and a few reference tables.
 * 
 * @see decrypt.cpp
 * 
 */


#ifndef DECRYPT_H
#define DECRYPT_H

#include "StringAnalysis.hpp"

#include <cmath>

// Frequencies of each letter of the alphabet (ignoring case)
const double ALPHABET_FREQUENCIES[] = { 0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060,
                                        0.065, 0.005, 0.005, 0.035, 0.030, 0.070, 0.080, 0.020,
                                        0.002, 0.065, 0.060, 0.090, 0.030, 0.010, 0.015, 0.005,
                                        0.020, 0.002};
/*
 * Index of Coincidence table correlating IC values with key length; the index of the value
 * corresponds to the key length (i.e. [3] = key length of 3
 */
const unsigned int IC_TABLE_SIZE = 12; 
const double IC_KEY_SIZE_TABLE[] = { 1.0000, 0.0660, 0.0520, 0.0473, 0.0449, 0.0435, 0.0426, 0.0419,
                                     0.0414, 0.0410, 0.0407, 0.0388 };


class DecryptEngine {
public:

    // Ctors
    DecryptEngine ()
    {
        ciphertext_info = StringAnalysis();
        highest_correlation = 0;
        plaintext = "";
        key_length = 0;
        calculated_key = "";
    }

    DecryptEngine (const std::string& str)
    {
        ciphertext_info = StringAnalysis (str);
        for (unsigned int i = 0; i < 26; i++)
        {
            correlation_frequency[i] = 0.0;
        }
        highest_correlation = 0;
        plaintext = "";
        key_length = 0;
        calculated_key = "";
    }

    // Deciphering Methods
    void calc_correlations ();
    void decrypt_caesar_cipher (char);
    char decrypt_caesar_cipher (char, char);
    void calc_key_length();
    void split_ciphertext();
    void analyze_ciphertext ();
    void decrypt_vigenere_cipher (std::string, std::string);
    void process_caesar ();
    void process_vigenere ();

    // Output Functions
    void print_correlations();
    void print_deciphered_caesars();
    void print_plaintext() { std::cout << plaintext << '\n'; }
    void print_decrypted_high_corr();
    void print_vigenere_info();

    // Mutators
    void set_ciphertext (const std::string& str){ ciphertext_info.set_string (str); }

    // Accessors
    std::string get_plaintext () { return plaintext; }
    std::string get_ciphertext () { return ciphertext_info.get_string(); }
    double get_IC () { return ciphertext_info.get_IC(); }
    char most_likely_key() { return (char)highest_correlation + 'A'; }

private:

    StringAnalysis ciphertext_info;
    double correlation_frequency[26];
    unsigned int highest_correlation;

    // Output variable for decryption methods
    std::string plaintext;

    // Used mostly for the Vigenere cipher
    unsigned int key_length;
    std::vector <std::string> split_alphabet;
    std::string calculated_key;

};

#endif
