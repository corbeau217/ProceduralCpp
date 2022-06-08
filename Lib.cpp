#include "Lib.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>


/*
handy future ideas links:
    - reference to filesystem library
    https://en.cppreference.com/w/cpp/header/filesystem
    - reference to file_size thingy
    https://en.cppreference.com/w/cpp/filesystem/file_size

 */

// apparently we can do this
namespace fs = std::filesystem;

// typing it every time is yuck
using namespace std;




// filename
#define OUR_SETTINGS_FILENAME "settings.txt"

// this is set to whatever the seed is in our settings file
unsigned *Lib::seedFromFile;

/**
 * @brief return if there is a settings file already created
 * 
 */
bool Lib::settingsFileExists(){
    // get our path var
    fs::path f{ OUR_SETTINGS_FILENAME };

    // ask the filesystem::exists( filesystem::path )
    return fs::exists(f);
}

/**
 * @brief creates a new settings with defaults
 * 
 */
void Lib::createSettingsFile(){

    // create and open our settings file
    ofstream f(OUR_SETTINGS_FILENAME);

    // write out our standard stuff
    f << "## change 0 in seed value to unsigned int ##" << endl;
    f << "##     to generate a specific map seed    ##" << endl;
    f << "seed=0" << endl;

    // close the filed
    f.close();
}

/**
 * @brief Get the seed from the settings file
 * 
 */
void Lib::getSeedFromSettingsFile(){
    // open the file
    fstream settingsFile;
    settingsFile.open(OUR_SETTINGS_FILENAME, ios::in);

    // check we opened fully
    if(settingsFile.is_open()){
        // getting here means there was a file already i think?

        // our container for a line with our seed
        string seedString;
        // our container for current settings line
        string currLine;
        // loop through lins and find it then dump into container
        while(getline(settingsFile, currLine)){
            // int idx = currLine.find("seed="); // this was here for debugging
            if(currLine.find("seed=") != -1)
                seedString = currLine;
        }
        // tidy up the string
        seedString = seedString.substr(5);
        if(seedString.find("U") != -1)
            seedString = seedString.substr(0,seedString.length());
        // now convert from string to unsigned int
        // use nullptr for 2nd arg bc it wants yucky stuff that i cbf with
        seedFromFile = new unsigned{strtoul(seedString.c_str(), nullptr, 10)};
    }
    else
        seedFromFile = new unsigned{0U};
}

/**
 * @brief landing point for this class from Main.cpp
 * 
 */
void Lib::setup(){

    // create settings file if one doesnt exist
    if(!settingsFileExists())
        createSettingsFile();

    // then access it to setup our seed
    if(settingsFileExists())
        getSeedFromSettingsFile();
    else
        // to handle failed to create
        seedFromFile = new unsigned{0U};
    
}

/**
 * @brief handles saving information etc.
 * 
 */
void Lib::closingApp(){
    //todo
    delete seedFromFile;
}

unsigned Lib::getSeed(){
    // if not setup, setup
    if(!seedFromFile)
        setup();

    // if empty, make off time
    if(*seedFromFile == 0U)
        *seedFromFile = (unsigned)time(NULL);

    // done
    return *seedFromFile;
}
