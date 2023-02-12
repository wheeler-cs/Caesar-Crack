/**
 * @file StringAnalysis.cpp
 * 
 * @author Drew Wheeler
 * @date 2023-02-11
 * 
 * @brief Contains function definitions for the StringAnalysis class.
 * 
 * @see StringAnalysis.hpp
 * 
 */


#include "StringAnalysis.hpp"

// === Ctors ======================================================================================

StringAnalysis::StringAnalysis ()
{
    data_string = "";
    index_of_coincidence = 0.0;
}

StringAnalysis::StringAnalysis (const std::string& str)
{
    data_string = str;
    index_of_coincidence = 0.0;
}


// === String Manipulation Functions ==============================================================

/**
 * @fn StringAnalysis::rm_data_string_char
 * 
 * @param rm: The character to be removed from data_string.
 * 
 * @brief Removes all instances of character specified from data_string (if applicable).
 * 
 * @pre data_string has been initialized.
 * @post All instances of character specified in parameter are removed from data_string.
 * 
 */
void StringAnalysis::rm_data_string_char (char rm)
{
    data_string.erase (std::remove (data_string.begin(), data_string.end(), rm), data_string.end());
}


// === Analysis Functions =========================================================================

/**
 * @fn StringAnalysis::gen_char_instance_profile
 * 
 * @brief Counts the number of instances of each character in a string.
 * 
 * @pre Member variable data_string has been initialized with a string.
 * @post Quantities of each character in data_string are counted and stored in char_instances.
 * 
 */
void StringAnalysis::gen_char_instance_profile ()
{
    // Store length as a temporary variable to avoid calling .size() repeatidly
    unsigned int str_len = data_string.size();

    // Get number of instances of each char in `data_string`
    for (unsigned int i = 0; i < str_len; i++)
    {
        if (char_instances.size() != 0)
        {
            for (unsigned int j = 0; j < char_instances.size(); j++)
            {
                // One instance of char already exists in the string, increment its counter instead
                if (char_instances[j].first == data_string[i])
                {
                    char_instances[j].second++;
                    break;
                }

                // New character found, add it to the list
                else if (j == char_instances.size() - 1)
                {
                    char_instances.push_back (std::make_pair (data_string[i], 1));
                    break;
                }
            }
        }

        // Starting with an empty list, initialize first character encountered
        else
        {
            char_instances.push_back (std::make_pair (data_string[i], 1));
        }
    }

    std::sort(char_instances.begin(), char_instances.end());
}

/**
 * @fn StringAnalysis::gen_char_frequency_profile
 * 
 * @brief Generates a table containing the frequencies of each character in data_string. If no data
 *        exists in char_instances, it will call gen_instance_profile first.
 * 
 * @pre data_string has a string; char_instances has evaluated data_string.
 * @post Character frequencies for data_string are calculated.
 * 
 */
void StringAnalysis::gen_char_frequency_profile ()
{
    // If a valid string is stored, but its composition has not been analyzed, do that first
    if ((data_string.size() > 0) && (char_instances.size() == 0))
        gen_char_instance_profile();
    
    // Variables used as part of the frequency calculation
    double frequency = 0.0;
    unsigned int str_length = data_string.size();

    // Calculate frequencies for each character in the sub-alphabet of `data_string`
    unsigned int instance_list_length = char_instances.size();
    for (unsigned int i = 0; i < instance_list_length; i++)
    {
        frequency = (double)char_instances[i].second / (double)str_length;
        char_frequencies.push_back (std::make_pair (char_instances[i].first, frequency));
    }
}

/**
 * @fn StringAnalysis::calculate_IC
 * 
 * @brief Calculates the Index of Coincidence for data_string.
 * 
 */
void StringAnalysis::calculate_IC ()
{
    // Generate a frequency profile if one doesn't exist yet
    if ((char_frequencies.size() == 0) && (data_string.size() > 0))
        gen_char_frequency_profile();

    // Calculate the IC summation's multiplier based on input string size
    double IC_mult = 1.0 / (((double)data_string.size()) * ((double)data_string.size() - 1.0));
    unsigned int IC_summation = 0;

    // Calculate the summation portion of the IC
    unsigned int instance_list_length = char_instances.size();
    for (unsigned int i = 0; i < instance_list_length; i++)
    {
        IC_summation += (char_instances[i].second * (char_instances[i].second - 1));
    }

    index_of_coincidence = IC_mult * (double)(IC_summation);
}


// === Output Functions ===========================================================================

/**
 * @fn StringAnalysis::print_instance_profile
 * 
 * @brief Prints the number of instances for each character in data_string.
 * 
 */
void StringAnalysis::print_instance_profile ()
{
    unsigned int instance_list_length = char_instances.size();

    for (unsigned int i = 0; i < instance_list_length; i++)
    {
        std::cout << char_instances[i].first << ": " << char_instances[i].second << '\n';
    }
}

/**
 * @fn StringAnalysis::print_frequency_profile
 * 
 * @brief Prints the frequencies for each character in data_string.
 * 
 */
void StringAnalysis::print_frequency_profile ()
{
    unsigned int frequency_list_length = char_frequencies.size();

    for (unsigned int i = 0; i < frequency_list_length; i++)
    {
        std::cout << char_frequencies[i].first << ": " << char_frequencies[i].second << '\n';
    }
}


// === Accessors ==================================================================================

/**
 * @fn StringAnalysis::get_char_freq
 * 
 * @brief Returns the frequency of a character within the stored data_string
 * 
 * @param c The character to be searched for within the char_frequencies array.
 * @return A double containing the frequency of the character; defaults to 0.0 if not found.
 * 
 * @pre char_frequencies should be properly initialized using gen_char_frequency_profile.
 * 
 */
double StringAnalysis::get_char_freq (char c)
{
    unsigned int frequency_list_length = char_frequencies.size();
    for (unsigned int i = 0; i < frequency_list_length; i++)
    {
        if (c == char_frequencies[i].first)
            return char_frequencies[i].second;
    }

    return 0.0;
}
