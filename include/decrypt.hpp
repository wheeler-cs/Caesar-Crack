/**
 * @file decrypt.hpp
 * @author Drew Wheeler
 * @date 2023-02-11
 * 
 * @brief Contains definitions for the FrequencyTable, VigenereDecipher, and DecryptEngine
 *        classes and several constants.
 * 
 * @see decrypt.cpp
 * 
 */


#ifndef DECRYPT_H
#define DECRYPT_H

#include "StringAnalysis.hpp"

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
    DecryptEngine (const std::string& str)
    {
        ciphertext_info = StringAnalysis (str);
        for (unsigned int i = 0; i < 26; i++)
            correlation_frequency[i] = 0.0;
        plaintext = "";
    }

    // Deciphering Subroutines
    void calc_correlation();
    void analyze_ciphertext ();

private:

    StringAnalysis ciphertext_info;
    double correlation_frequency[26];

    std::string plaintext;

};

#endif
