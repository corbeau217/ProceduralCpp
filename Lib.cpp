#include "Lib.hpp"
#include "Util.hpp"
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


#define SETTINGS_FIELD_COUNT 10


// filename
#define OUR_SETTINGS_FILENAME "settings.txt"

// this is set to whatever the seed is in our settings file
unsigned *Lib::seedFromFile;
string ***Lib::settingsList;

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
    // maybe we should setup a way to new settings etc and have the
    //      file generated based on a dictionary of field names and
    //      default values
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
        seedFromFile = Util::strtou(seedString);
    }
    else
        seedFromFile = new unsigned{0U};
    settingsFile.close();
}

/**
 * @brief landing point for this class from Main.cpp
 * 
 */
void Lib::setup(){
    setupSettingsFields();
    scrapeSettingsFile();

    // create settings file if one doesnt exist
    if(!settingsFileExists())
        createSettingsFile();

    // then access it to setup our seed
    if(settingsFileExists()){
        scrapeSettingsFile();
        getSeedFromSettingsFile();
    }
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
    //delete seedFromFile;
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

/**
 * @brief returns the count of legitimate fields in the settings
 *      file
 * 
 */
int Lib::settingsFileFieldCount(){
    // check for file doesnt exist and return 0 elements
    if(!settingsFileExists())
        return 0;
}

int Lib::settingsFieldCount(){
    return SETTINGS_FIELD_COUNT;
}

/**
 * @brief scrapes the settings file, ignoring lines with double
 *      # characters at the start, then has a 2d array of string
 *      pointers that is returned 
 * 
 * @return string*** 
 */
void Lib::scrapeSettingsFile(){
    // check for file doesnt exist and return nullptr
    if(!settingsFileExists())
        settingsList = nullptr;
    // see if we need to setup the list first
    if(!settingsList || settingsList==nullptr)
        setupSettingsFields();
    // now we fill it with values from the file
    // open the file
    fstream settingsFile;
    settingsFile.open(OUR_SETTINGS_FILENAME, ios::in);
    // check we opened
    if(settingsFile.is_open()){
        // current line container
        string currLine;
        int fieldsHandled = 0;
        while(getline(settingsFile, currLine)){
            // ignore empty/short lines
            if(currLine.length() > 2)
                // ignore our placeholder comments
                if( currLine.find("##") == -1U){
                    // not a comment line
                    settingsList[fieldsHandled][0] = new string{currLine.c_str()};
                    // check we have '=' in our line
                    if((*settingsList[fieldsHandled][0]).find("=") != -1){
                        // yucky string manipulation, we could do this better with hash and regex
                        // shave off before the =
                        settingsList[fieldsHandled][1] = new string{
                                (*settingsList[fieldsHandled][0]).substr(
                                        (*settingsList[fieldsHandled][0]).find("=")+1
                                    )
                            };
                        // shave off after the =
                        settingsList[fieldsHandled][0] = new string{
                                (*settingsList[fieldsHandled][0]).substr(
                                         0,
                                        (*settingsList[fieldsHandled][0]).find("=")
                                    )
                            };
                    }
                } 
        }
    }
    settingsFile.close();
}

void Lib::setupSettingsFields(){
    int fieldCount = settingsFieldCount();
    // now make the list
    settingsList = new string**[fieldCount];
    for(int i = 0; i < fieldCount; i++){
        settingsList[i] = new string*[2];
        settingsList[i][0] = new string{""};
        settingsList[i][1] = new string{""};
    }
    
}
