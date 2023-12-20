/**
 * @file main.cpp
 * @brief
 * @author Ronan Champagnat - IUT Informatique
 * @date 10/11/2023
 */


#include <iostream>

using namespace std;

#include "typeDef.h"
#include "functions.h"
#include "tests.h"
#include <fstream>


/**
* @brief Function to execute the analysis of the log file.
**/
void launchProcessAnalysis()
{
    // Your code

}

/**
* @brief Launches the testing suite.
* This function runs a suite of tests to validate the functions.
*/
void launchTests()
{
    cout << endl << "********* Start testing *********" << endl << endl;
    // Here you can use tests functions

    cout << endl << "********** End testing **********" << endl << endl;
}

/**
* @brief Main function of the program.
* Entry point to process analysis. It can be used to start the analysis or run the tests.
* @return 0 for successful execution.
*/
int main()
{
    cout << "Prenom Nom groupeTP" << endl;

    // Uncomment the line below to run tests
    // launchTests();
    // Start the process analysis
    launchProcessAnalysis();

    return 0;
}
