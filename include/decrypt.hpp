/**
 * @file decrypt.hpp
 * @author Drew Wheeler
 * @date 2023-02-09
 * 
 * @brief Contains definitions for the FrequencyTable and DecryptEngine classes and several
 *        constants.
 * 
 * @see decrypt.cpp
 * 
 */


#ifndef DECRYPT_H
#define DECRYPT_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/*
 * Constants here are just to make getting a MVP out. Realistically this information should be
 * stored in and read from a file.
 */
const char ALPHABET_SIZE = 26;
const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                         'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const double FREQUENCIES[] = { 0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060, 0.065, 0.005,
                               0.005, 0.035, 0.030, 0.070, 0.080, 0.020, 0.002, 0.065, 0.060, 0.090,
                               0.030, 0.010, 0.015, 0.005, 0.020, 0.002};

class FrequencyTable {
public:

    FrequencyTable() {
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++)
        {
            alphabet.push_back(ALPHABET[i]);
            frequencies.push_back(FREQUENCIES[i]);
        }
    }

    FrequencyTable(double d) {
        if(d > 1) d = 1;
        else if (d < 0) d = 0;
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++)
        {
            alphabet.push_back(ALPHABET[i]);
            frequencies.push_back(d);
        }
    }

    void print_table();

    void set_char_value (char, double);
    char get_char_by_index (unsigned int idx) { return alphabet[idx]; }
    double get_char_frequency (char);
    unsigned int get_alphabet_size() { return alphabet.size(); }
    void sort_data();

private:
    /**
     * @var std::vector<char> alphabet
     * 
     * Holds a list of characters that are part of the alphabet being worked with.
     */
    std::vector<char> alphabet;

    /**
     * @var std::vector<double> frequencies
     * 
     * Stores frequencies of characters in the alphabet vector. Context of values may vary. 
     */
    std::vector<double> frequencies;
};
/**
 * @class FrequencyTable "include/decrypt.hpp"
 * 
 * @brief Table containing char-double pairs used as part of the decryption process.
 * 
 * Used in different contexts to store paired data correlating a character to a frequency.
 */





class VigenereDecipher {
public:

    VigenereDecipher() {
        ciphertext = plaintext = "";
        index_of_coincidence = 0.0;
        for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            alphabet.push_back(ALPHABET[i]);
            char_occurrences.push_back(0);
        }
    }

    VigenereDecipher (std::string ct) {
        ciphertext = ct;
        plaintext = "";
        index_of_coincidence = 0.0;
        for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            alphabet.push_back(ALPHABET[i]);
            char_occurrences.push_back(0);
        }
    }

    void calculate_char_instances();
    void calculate_ioc();
    void set_char_occurrence(char, unsigned int);

private:
    std::string ciphertext;
    std::string plaintext;
    double index_of_coincidence;

    std::vector<char> alphabet;
    std::vector<unsigned int> char_occurrences;
};





class DecryptEngine {
public:
    DecryptEngine() {
        ciphertext = plaintext = "";
        alphabet_frequency = FrequencyTable();
        ciphertext_frequency = FrequencyTable(0);
        keyshift_table = FrequencyTable(0);
    }

    DecryptEngine (std::string ct) {
        ciphertext = ct;
        plaintext = "";
        alphabet_frequency = FrequencyTable();
        ciphertext_frequency = FrequencyTable(0);
        keyshift_table = FrequencyTable(0);
    }

    double get_alphabet_frequency (char);
    void set_ciphertext_frequency (char, double);
    double get_ciphertext_frequency (char);
    void set_keyshift_table_value (char, double);
    void calc_ciphertext_composition();
    void calc_shift_likelihoods();
    void sort_keyshift_table();
    std::string decrypt_ciphertext(std::string, std::string);
    void print_caesar_results();


    void decrypt_caesar_cipher();

    void print_ct_table();
    void print_keyshift_table();


private:
    std::string ciphertext;
    std::string plaintext;
    FrequencyTable alphabet_frequency;
    FrequencyTable ciphertext_frequency;
    FrequencyTable keyshift_table;
};
/**
 * @class DecryptEngine "include/decrypt.hpp"
 * 
 * @brief Class responsible for implementing algorithms to decrypt enciphered data.
 * 
 * All decryption operations are performed through the DecryptEngine class. Contains several
 * instances of the FrequencyTable class to assist with statistical analysis.
 */

#endif