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
        // front and back did not crossover, add char info to list
        if (back >= front + 1) {
            char_freq = ((1 + ((double)(back - 1) - (double)front)) / (double)temp_ct.size());
            set_ciphertext_frequency (ALPHABET[i], char_freq);
        }
    }
}

void DecryptEngine::calc_shift_likelihoods () {
    double shiftkey_summation = 0.0, letter_ct_freq = 0.0, letter_alpha_freq = 0.0;

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

void DecryptEngine::decrypt_caesar_cipher () {
    calc_ciphertext_composition();
    calc_shift_likelihoods();
}

void DecryptEngine::print_ct_table () {
    ciphertext_frequency.print_table();
}

void DecryptEngine::print_keyshift_table() {
    keyshift_table.print_table();
}
