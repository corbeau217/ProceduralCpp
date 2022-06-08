#ifndef LIB_HPP
#define LIB_HPP

#include <string>
#include "Seeder.hpp"


// apparently we can do this
// namespace fs = std::filesystem;

class Lib{
    public:
    // this is set to whatever the seed is in our settings file
    static unsigned *seedFromFile;
    

    /**
     * @brief return if there is a settings file already created
     * 
     */
    static bool settingsFileExists();

    /**
     * @brief creates a new settings with defaults
     * 
     */
    static void createSettingsFile();

    /**
     * @brief Get the seed from the settings file
     * 
     */
    static void getSeedFromSettingsFile();


    /**
     * @brief landing point for this class from Main.cpp
     * 
     */
    static void setup();

    /**
     * @brief handles saving information etc.
     * 
     */
    static void closingApp();

    /**
     * @brief 
     * 
     * @return unsigned 
     */
    static unsigned getSeed();


};


#endif