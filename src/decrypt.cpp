#include "decrypt.hpp"

/**
 * @fn DecryptEngine::calc_correlation
 * 
 * @brief Calculates the correlation frequency for a given ciphertext.
 * 
 * @pre ciphertext_info has already processed the ciphertext stored.
 * @post Correlation frequency for the ciphertext is calculated and stored in correlation_frequency.
 * 
 */
void DecryptEngine::calc_correlation()
{
    // Implements: PHI(i) = SIGMA(0<=c<=25)(f(c)f'(e-i))
    double char_ciphertext_freq = 0.0, char_alphabet_freq = 0.0, phi_summation = 0.0;
    char ASCII_char_representation = ' ';

    unsigned int i = 0, e = 0;
    for (i = 0; i < 26; i++)
    {
        phi_summation = 0.0;
        for (e = 0; e < 26; e++)
        {
            ASCII_char_representation = e + 'A';
            char_ciphertext_freq = ciphertext_info.get_char_freq(ASCII_char_representation);
            char_alphabet_freq = ALPHABET_FREQUENCIES[((26 + e) - i) % 26];
            phi_summation += char_ciphertext_freq * char_alphabet_freq;
        }
        correlation_frequency[i] = phi_summation;
    }
}

/**
 * @fn DecryptEngine::analyze_ciphertext
 * 
 * @brief Creates an analysis of the ciphertext stored in ciphertext_info.
 * 
 * @pre ciphertext_info has been properly initialized.
 * @post Cryptographic information relating to the ciphertext is generated and stored.
 * 
 */
void DecryptEngine::analyze_ciphertext()
{
    ciphertext_info.rm_data_string_char (' ');
    // Calling calculate_IC should call the needed functions to analyze char instances and frequency
    ciphertext_info.calculate_IC();
    calc_correlation();
}
