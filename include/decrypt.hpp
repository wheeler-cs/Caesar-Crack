#ifndef DECRYPT_H
#define DECRYPT_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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
    double get_char_frequency (char);

private:
    std::vector<char> alphabet;
    std::vector<double> frequencies;
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

#endif