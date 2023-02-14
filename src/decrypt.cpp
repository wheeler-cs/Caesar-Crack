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
        if (plaintext[i] != ' ')
            plaintext[i] = ((((plaintext[i] - 'A') + 26) - (key - 'A')) % 26) + 'A';
    }
}

/**
 * @fn DecryptEngine::decrypt_caesar_cipher
 * 
 * @brief Decrypts a character encrypted with ciphertext 
 * 
 * @param ct The ciphertext character to be decrypted
 * @param key The key that corresponds to ct.
 * @returns The char in plaintext instead of Caesar-based text.
 * 
 * @pre ct and key are matching for a given Caesar cipher.
 * @post The decrypted character for ct is acquired and returned.
 * 
 */
char DecryptEngine::decrypt_caesar_cipher (char ct, char key)
{
    return ((((ct - 'A') + 26) - (key - 'A')) % 26) + 'A';
}

/**
 * @fn DecryptEngine::calc_key_length
 * 
 * @brief Utilizes a formula to calculate an estimated key length for some ciphertext.
 * 
 * @pre ciphertext_info has calculated IC for the string.
 * @post Member data key_length contains an estimated key length for the ciphertext.
 * 
 */
void DecryptEngine::calc_key_length()
{
    double key_estimate = 0.0;

    /*
     * For more information on the formula used here, see this link:
     * https://www.nku.edu/~christensen/1402%20Friedman%20test%202.pdf
     */
    key_estimate = (0.027 * (double)(ciphertext_info.get_string_length())) / 
                   (((double)(ciphertext_info.get_string_length()) - 1)*ciphertext_info.get_IC() + 0.065 - (0.038 * (double)(ciphertext_info.get_string_length())));

    key_length = std::round (key_estimate);
}

/**
 * @fn DecryptEngine::split_ciphertext
 * 
 * @brief Splits a ciphertext into a number of sub-strings based on the estimated length of the key.
 * 
 * @pre Member data key_length has a non-zero value in it.
 * @post Sub-strings of characters from the ciphertext are generated. 
 * 
 */
void DecryptEngine::split_ciphertext()
{
    unsigned int i = 0, ct_length = ciphertext_info.get_string_length();
    std::string temp_ct = get_ciphertext();

    // Initialize vectors needed for split operation
    for (i = 0; i < key_length; i++)
    {
        split_alphabet.push_back("");
    }

    // Generate sub-strings
    for (i = 0; i < ct_length; i++)
    {
        split_alphabet[i % key_length] += temp_ct[i];
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
    //ciphertext_info.rm_data_string_char (' ');
    // Calling calculate_IC should call the needed functions to analyze char instances and frequency
    ciphertext_info.calculate_IC();
    calc_correlations();
    calc_key_length();
}

/**
 * @fn DecryptEngine::decrypt_vigenere_cipher
 * 
 * @brief Calls methods to treat each individual sub-alphabet of the Vigenere cipher as its own
 *        Caesar cipher.
 * 
 * @param ct The input ciphertext being treated as a Caesar cipher.
 * @param key The assumed key to the ciphertext.
 * 
 * @pre ct has some sort of ciphertext that is a Caesar cipher and key has the corresponding key.
 * @post ct is decrypted and stored in plaintext using key.
 * 
 */
void DecryptEngine::decrypt_vigenere_cipher (std::string ct, std::string key)
{
    plaintext = "";

    unsigned int ct_size = ct.size(), k_size = key.size();
    for (unsigned int i = 0; i < ct_size; i++)
    {
        plaintext += decrypt_caesar_cipher (ct[i], key[i % k_size]);
    }
}

/**
 * @fn DecryptEngine::process_caesar
 * 
 * @brief A wrapper for the analyze_ciphertext method.
 * 
 */
void DecryptEngine::process_caesar()
{
    analyze_ciphertext();
    highest_correlation = std::distance (correlation_frequency,
                          std::max_element (correlation_frequency, correlation_frequency + 25));
}

/**
 * @fn DecryptEngine::process_vigenere
 *
 * @brief Wrapper function for all Vigenere cipher-related functions.
 * 
 * @pre Ciphertext has been set in ciphertext_info
 * @post The Vigenere cipher is decoded to a close approximation using formulae.
 *  
 */
void DecryptEngine::process_vigenere()
{
    ciphertext_info.rm_data_string_char (' ');
    analyze_ciphertext();
    split_ciphertext();

    // TODO: Don't do this... Re-instantiating a class every loop iteration is stupid, but currently
    //       there is no member method that changes the needed aspects for changing the ciphertext.
    unsigned int i = 0;
    for (i = 0; i < key_length; i++)
    {
        DecryptEngine temp_dc (split_alphabet[i]);
        temp_dc.process_caesar();
        calculated_key += temp_dc.most_likely_key();
    }

    decrypt_vigenere_cipher (ciphertext_info.get_string(), calculated_key);
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
        std::cout << (char)(i + 'A') << ", "  << correlation_frequency[i] << ": " << plaintext;
        if (i == highest_correlation)
            std::cout << '*';
        std::cout << std::endl;
    }
}

/**
 * @fn DecryptEngine::print_decrypted_high_corr
 * 
 * @brief Prints the plaintext generated by the highest correlation value in the alphabet.
 * 
 */
void DecryptEngine::print_decrypted_high_corr()
{
    std::cout << std::fixed;
    std::cout.precision(4);

    decrypt_caesar_cipher((char)(highest_correlation + 'A'));
    std::cout << "Key: " << (char)(highest_correlation + 'A') << "(" << highest_correlation << ")\n";
    std::cout << plaintext << '\n' << std::endl;
}

/**
 * @fn DecryptEngine::print_vigenere_info
 * 
 * @brief Prints information regarding the decoded Vigenere cipher to terminal. 
 * 
 */
void DecryptEngine::print_vigenere_info()
{
    std::cout << "Key: " << calculated_key << '\n';
    std::cout << plaintext << '\n' << std::endl;
}
