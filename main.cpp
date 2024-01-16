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
    auto *aProcessList = new ProcessList;
    string aPath = "C:\\Users\\Dexea\\CLionProjects\\SAE1.02_Comparaison\\smallDataset.txt";
    string aLargePath = "C:\\Users\\Dexea\\CLionProjects\\SAE1.02_Comparaison\\largeDataset.txt";
    chrono::time_point start = getTime();
    cout << "Debut extraction des processus"<<endl<<"taille : " << nbOfLines(aLargePath)<< endl;
    extractProcesses(aProcessList,aLargePath);
    chrono::time_point end = getTime();
    cout << endl << "Durée de l'extraction des processus :" << calculateDuration(start,end)<<" s"<<endl;
    cout << "Nombre de Processus :" << aProcessList->size<<endl;
    if (aProcessList->size < 15)
    {
        displayProcessesList(aProcessList);
    }
    cout << "Nombre de Processus :" << aProcessList->size<<endl;
    cout << "Longueur moyenne des Processus : " << averageProcessLength(aProcessList)<<endl;

    cout << "Debut de la recherche des activités de début" << endl;
    Process *startA = new Process;
    start = getTime();
    startActivities(aProcessList,startA);
    end = getTime();
    cout << "Durée de recherche des activités de début :" << calculateDuration(start,end)<<" s"<<endl;
    displayActivitiesList(startA);

    cout << "Debut de la recherche des activités de fin" << endl;
    Process *endA = new Process;
    start = getTime();
    endActivities(aProcessList,endA);
    end = getTime();
    cout << "Durée de recherche des activités de fin :" << calculateDuration(start,end)<<" s"<<endl;
    displayActivitiesList(endA);

    auto *aVariantList = new ProcessList;
    cout << "Début de la recherche des variants"<<endl;
    start = getTime();
    variants(aProcessList,aVariantList);
    end = getTime();
    cout << endl << "Durée de recherche des variants :" << calculateDuration(start,end)<<" s"<<endl;
    cout << "Nombre de Processus :" << aVariantList->size<<endl;
    if (aVariantList->size < 10){
        displayProcessesList(aVariantList);
    }






}

/**
* @brief Launches the testing suite.
* This function runs a suite of tests to validate the functions.
*/
void launchTests()
{
    cout << endl << "********* Start testing *********" << endl << endl;
    //test_nbOfLines();
    //test_displayActivitiesList();
    //test_push_back();
    //test_push_front();
    //test_addActivity();
    //test_addProcess();
    //test_insertProcessActivity();
    //test_processExists();
    //test_extractProcesses();
    //test_averageProcessLength();
    //test_insertActivity();
    //test_startActivities();
    //test_endActivities();
    //test_processAlreadyExists();
    //test_variants();
    cout << endl << "********** End testing **********" << endl << endl;
}

/**
* @brief Main function of the program.
* Entry point to process analysis. It can be used to start the analysis or run the tests.
* @return 0 for successful execution.
*/
int main()
{
    cout << "Maxime Rousseau B2" << endl;

    // Uncomment the line below to run tests
    launchTests();
    // Start the process analysis
    launchProcessAnalysis();

    return 0;
}
