#include "decrypt.hpp"

void FrequencyTable::print_table () {
    for (unsigned int i = 0; i < alphabet.size(); i++) {
        std::cout << alphabet[i] << ": " << frequencies[i] << std::endl;
    }
}


void FrequencyTable::set_char_value (char tab_char, double char_freq) {
    for (unsigned int i = 0; i < alphabet.size(); i++) {
        if (tab_char == alphabet[i]) {
            frequencies[i] = char_freq;
            break;
        }
    }
}

double FrequencyTable::get_char_frequency (char key) {
    for (unsigned int i = 0; i < alphabet.size(); i++) {
        if (alphabet[i] == key)
            return (frequencies[i]);
    }

    return 0.0;
}

void FrequencyTable::sort_data() {
    // Implements a selection sort because the data set is small and it's easy to implement
    unsigned int i, j, min;

    for (i = 0; i < (frequencies.size() - 1); i++) {
        min = i;
        for (j = i + 1; j < frequencies.size(); j++) {
            if (frequencies[j] < frequencies[min]) {
                min = j;
            }
        }
        if (min != i) {
            // Swap the alphabet and frequencies in tandem
            std::swap (frequencies[i], frequencies[min]);
            std::swap (alphabet[i], alphabet[min]);
        }
    }
}





void VigenereDecipher::calculate_char_instances() {
    std::string temp_ct = ciphertext;

    std::sort(temp_ct.begin(), temp_ct.end());

    // Remove all spaces from string
    for (unsigned int i = 0; i < temp_ct.size();) {
        if (temp_ct[i] == ' ')
            temp_ct.erase(temp_ct.begin() + i);
        else
            i++;
    }

    unsigned int front = 0, back = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (front = 0; front < temp_ct.size(); front++) {
            if (temp_ct[front] == ALPHABET[i])
                break;
        }

        for (back = temp_ct.size(); back > 0; back--) {
            if (temp_ct[back - 1] == ALPHABET[i])
                break;
        }
        /*
         * front and back did not crossover, add char info to list
         *
         * Had to do this weird thing because size of vectors is an unsigned int and the
         * compiler yells at me if I use signed values. 
         */
        if (back >= front + 1) {
            set_char_occurrence(ALPHABET[i], (back - front) + 1);
        }
    }
}

void VigenereDecipher::calculate_ioc() {
    std::string temp_ct = ciphertext;

    // Remove all spaces from string
    for (unsigned int i = 0; i < temp_ct.size();) {
        if (temp_ct[i] == ' ')
            temp_ct.erase(temp_ct.begin() + i);
        else
            i++;
    }

    double summation_multiplier = (double)(1/((double)temp_ct.size() * ((double)temp_ct.size() - 1)));
    unsigned int summation = 0;

    for (unsigned int i = 0; i < char_occurrences.size(); i++) {
        if (char_occurrences[i] != 0)
            summation += (char_occurrences[i] * (char_occurrences[i] - 1));
    }

    index_of_coincidence = summation_multiplier * (double)(summation);
    std::cout << index_of_coincidence;
}

void VigenereDecipher::set_char_occurrence(char c, unsigned int ui) {
    for (unsigned int i = 0; i < alphabet.size(); i++) {
        if (alphabet[i] == c) {
            char_occurrences[i] = ui;
            break;
        }
    }
}

double DecryptEngine::get_alphabet_frequency (char key) {
    return (alphabet_frequency.get_char_frequency (key));
}

void DecryptEngine::set_ciphertext_frequency (char ct_char, double char_freq) {
    ciphertext_frequency.set_char_value (ct_char, char_freq);
}

double DecryptEngine::get_ciphertext_frequency (char key) {
    return (ciphertext_frequency.get_char_frequency (key));
}

void DecryptEngine::set_keyshift_table_value (char key, double value) {
    keyshift_table.set_char_value (key, value);
}

void DecryptEngine::calc_ciphertext_composition () {
    std::string temp_ct = ciphertext;
    std::sort(temp_ct.begin(), temp_ct.end());

    // Remove all spaces from string
    for (unsigned int i = 0; i < temp_ct.size();) {
        if (temp_ct[i] == ' ')
            temp_ct.erase(temp_ct.begin() + i);
        else
            i++;
    }

    // Calculate the number of each character in the sorted string
    unsigned int front = 0, back = 0;
    double char_freq = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (front = 0; front < temp_ct.size(); front++) {
            if (temp_ct[front] == ALPHABET[i])
                break;
        }
        for (back = temp_ct.size(); back > 0; back--) {
            if (temp_ct[back - 1] == ALPHABET[i])
                break;
        }
        /*
         * front and back did not crossover, add char info to list
         *
         * Had to do this weird thing because size of vectors is an unsigned int and the
         * compiler yells at me if I use signed values. 
         */
        if (back >= front + 1) {
            char_freq = ((1 + ((double)(back - 1) - (double)front)) / (double)temp_ct.size());
            set_ciphertext_frequency (ALPHABET[i], char_freq);
        }
    }
}

void DecryptEngine::calc_shift_likelihoods () {
    double shiftkey_summation = 0.0, letter_ct_freq = 0.0, letter_alpha_freq = 0.0;

    // phi(i) = sigma(0<=c<=25)(f(c)f'(e-i))
    for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
        shiftkey_summation = 0.0;
        for (unsigned int e = 0; e < ALPHABET_SIZE; e++) {
            letter_ct_freq = get_ciphertext_frequency(ALPHABET[e]);
            letter_alpha_freq = get_alphabet_frequency(ALPHABET[((26 + e) - i) % 26]);
            shiftkey_summation += letter_ct_freq * letter_alpha_freq;
        }
        set_keyshift_table_value (ALPHABET[i], shiftkey_summation);
    }
}

void DecryptEngine::sort_keyshift_table() {
    keyshift_table.sort_data();
}

std::string DecryptEngine::decrypt_ciphertext(std::string ct, std::string key) {
    unsigned int ct_size = ct.size(), key_size = key.size();

    plaintext = "";
    for (unsigned int i = 0; i < ct_size; i++) {
        if (ct[i] != ' ') {
            plaintext += ((ct[i] - (key[i % key_size]) + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        }
        else {
            plaintext += ' ';
        }
    }

    return plaintext;
}

void DecryptEngine::print_caesar_results() {
    std::string char_converter = "";
    std::cout << "Most Likely to Least Likely" << std::endl;
    for (unsigned int i = keyshift_table.get_alphabet_size() - 1; i > 0; i--) {
        char_converter = ""; // Character must be converted to string to be used in decryption
        char_converter += keyshift_table.get_char_by_index(i);
        std::cout << char_converter << "(" << (short)(char_converter[0] - 'A') << "): "
                  << decrypt_ciphertext(ciphertext, char_converter) << std::endl;
        if (i == 0) break; // End loop because i is unsigned
    }
}

void DecryptEngine::decrypt_caesar_cipher () {
    calc_ciphertext_composition();
    calc_shift_likelihoods();
    sort_keyshift_table();
    print_caesar_results();
}

void DecryptEngine::print_ct_table () {
    ciphertext_frequency.print_table();
}

void DecryptEngine::print_keyshift_table() {
    keyshift_table.print_table();
}
