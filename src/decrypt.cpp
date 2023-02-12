/**
 * @file decrypt.cpp
 * @author Drew Wheeler
 * @date 2023-02-12
 * 
 * @brief Contains function definitions for the DecryptEngine class.
 * 
 * @see decrypt.hpp
 * 
 */

#include "decrypt.hpp"


// === Deciphering Methods ========================================================================

/**
 * @fn DecryptEngine::calc_correlation
 * 
 * @brief Calculates the correlation frequency for a given ciphertext.
 * 
 * @pre ciphertext_info has already processed the ciphertext stored.
 * @post Correlation frequency for the ciphertext is calculated and stored in correlation_frequency.
 * 
 */
void DecryptEngine::calc_correlations()
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
 * @fn DecryptEngine::decrypt_caesar_cipher
 * 
 * @brief Decrypts the data_string stored in ciphertext_info using the given character and the
 *        Caesar cipher algorithm.
 * 
 * @param char key: The character (in ASCII) to be used as the decryption key.
 * 
 * @pre ciphertext_info should be storing a string encrypted using the Caesar cipher.
 * @post The string in ciphertext_info is decrypted using the Caesar cipher and the key character
 *       and the result is stored in 
 * 
 */
void DecryptEngine::decrypt_caesar_cipher (char key)
{
    plaintext = ciphertext_info.get_string();

    unsigned int i = 0, str_len = plaintext.size();
    for (i = 0; i < str_len; i++)
    {
        plaintext[i] = ((((plaintext[i] - 'A') + 26) - (key - 'A')) % 26) + 'A';
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
    calc_correlations();
}


// === Output Functions ===========================================================================

/**
 * @fn DecryptEngine::print_correlations
 * 
 * @brief Prints the character of the alphabet followed by it's correlation frequency
 */
void DecryptEngine::print_correlations()
{
    for (unsigned int i = 0; i < 26; i++)
    {
        std::cout << (char)(i + 'A') << ": " << correlation_frequency[i] << '\n';
    }
}

/**
 * @fn DecryptEngine::print_deciphered_caesars
 * 
 * @brief Prints all possible deciphered Caesar ciphers, along with their key and corresponding
 *        correlation frequency.
 * 
 */
void DecryptEngine::print_deciphered_caesars()
{
    std::cout << std::fixed;
    std::cout.precision(4);

    unsigned int i = 0;
    for (i = 0; i < 26; i++)
    {
        decrypt_caesar_cipher((char)(i + 'A'));
        std::cout << (char)(i + 'A') << ", "  << correlation_frequency[i] << ": " << plaintext
                  << std::endl;
    }
}
