/**
 * @file functions.cpp
 * @brief Implementation of the project functions
 * @author Ronan Champagnat - IUT Informatique La Rochelle
 * @date 10/11/2023
 */

#include "typeDef.h"

#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;


/*
 * Chronographe functions
 */

/**
 * @brief Retourne l'heure courante avec une grande résolution
 */
chrono::time_point<std::chrono::high_resolution_clock> getTime()
{
    return std::chrono::high_resolution_clock::now();
}

/**
 * @brief Retourne la différence entre deux heures données et convertit en secondes.
 */
double calculateDuration(chrono::time_point<std::chrono::high_resolution_clock> start, chrono::time_point<std::chrono::high_resolution_clock> end)
{
    std::chrono::duration<double> duration = end - start;
    return  duration.count();
}


/*
 * Utility functions
 */

/**
 * @brief Ouvre le fichier passer en paramètres et le parcours intégralement en comptant le nombre
 * de ligne. Le fichier est fermé avant de retourner le nombre de lignes trouvé.
 */
int nbOfLines(string aFileName)
{
    int result = 0;
    string dummy;
    ifstream iFile(aFileName);
    if (iFile.is_open()){
        while (!iFile.eof()){
            getline(iFile,dummy);
            result++;
        }
        iFile.close();
        return result-1;
    } else{
        cout << "Erreur de lecture !" <<endl;
        return 0;
    }
}

/**
 * @brief Affiche une barre de progression au format :
 * [############                  ] 42%
 * Utilisation de \r (voir premier cours de Dév)
 * le nombre de # est proportionnel nb (nombre d'itérations) par rapport à max
 * le pourcentage est la proportion de nb sur max
 */
void printProgressBar(int nb, int max)
{
    int lastProgressPercentage = int((nb - 1) * 100.0 / max);

    int progressBarWidth = 30;
    int progressPercentage = int((nb * 100.0) / max);
    int numHashes = (progressPercentage * progressBarWidth) / 100;

    if (progressPercentage != lastProgressPercentage)
    {
        cout << "\r[";
        for (int i = 0; i < progressBarWidth; i++)
        {
            if (i < numHashes)
                cout << "#";
            else
                cout << " ";
        }

        cout << "] " << progressPercentage << "%" << flush;
    }
}


/*
 * Utility functions for data structure
 */

/**
 * @brief Parcours une liste de type Process afin de libérer la mémoire de toutes les activités
 * puis libère la mémoire de la liste de type Process
 * Chaque élément libéré est mis à pointer sur nullpointer
 */
void clear(Process * aList)
{
    Activity *currentActivity = aList->firstActivity;
    while (currentActivity != nullptr){
        Activity *tempActivity = currentActivity;
        currentActivity = currentActivity->nextActivity;
        tempActivity = nullptr;
    }

    //Reset it
    aList->nbActivities = 0;
    aList->firstActivity = nullptr;
}

/**
 * @brief Parcours tous les processus d'une liste et applique clear sur chaque processus
 * puis libère la mémoire de la liste et fait pointer la liste sur nullptr
 */
void clear(ProcessList * aList)
{
    Process *currentProcess = aList->firstProcess;
    while (currentProcess != nullptr){
        Process *tempProcess = currentProcess;
        currentProcess = currentProcess->nextProcess;
        clear(tempProcess); //clear temp
        tempProcess = nullptr;
    }
    aList->firstProcess = nullptr;
    aList->size = 0;
}

/**
 * @brief Affiche le nombre d'activité contenu dans le process
 * puis parcours toutes les activités pour les afficher (nom uniquement)
 * comme suit : Nb activités : 3: a b c \n
 */
void displayActivitiesList(Process * aProcess)
{
    Activity *currentActivity = aProcess->firstActivity;
    cout<<"Nb activités : " <<aProcess->nbActivities <<":";
    while (currentActivity != nullptr){
        cout<<" "<<currentActivity->name;
        currentActivity = currentActivity->nextActivity;
    }
    cout<<" \n";
}

/**
 * @brief Affiche le nombre de processus contenus dans une liste puis parcours la liste
 * pour afficher l'id de chaque processus et ses activités (utilise displayActivitiesList)
 * comme suit : Nombre de processus : 3\n123:\tNb activités : 3: a b c \n456:\tNb activités : 1: b \n789:\tNb activités : 2: a b \n\n
 */
void displayProcessesList(ProcessList * aList)
{
    Process *currentProcess = aList->firstProcess;
    while (currentProcess != nullptr){
        cout << currentProcess->id << "  : ";
        displayActivitiesList(currentProcess);
        currentProcess = currentProcess->nextProcess;
    }
    cout<<"\n\n";
}

/**
 * @brief Si la liste le processus ne contient aucune activité, l'activité est ajouté en tête
 * sinon la liste des activités est parcourue et l'activité est ajoutée en queue.
 * Le nombre d'activités du processus est incrémenté de 1
 */
void push_back(Process * aProcess, Activity* anActivity)
{
    if(aProcess->firstActivity == nullptr){
        aProcess->firstActivity = anActivity;
    }
    else{
        Activity *currentActivity = aProcess->firstActivity;
        while (currentActivity->nextActivity != nullptr){
            currentActivity = currentActivity->nextActivity;
        }
        currentActivity->nextActivity = anActivity;
    }
    aProcess->nbActivities++;
}

/**
 * @brief Construit un pointeur de type Activity et l'initialise au valeurs données
 * puis utilise push_back pour ajouter l'activité à la fin de la liste (au processus)
 */
void addActivity(Process * aProcess, string anActivityName, string aTime)
{
    auto *newActivity = new Activity;
    if (newActivity != nullptr){
        newActivity->name = anActivityName;
        newActivity->time = aTime;
        push_back(aProcess,newActivity);
    }
}

/**
 * @brief Ajoute un processus (Process) en tête de liste ProcessList
 */
void push_front(ProcessList * aList, Process * aProcess)
{
    if(aList->firstProcess == nullptr){
        aList->firstProcess = aProcess;
    } else{
        aProcess->nextProcess = aList->firstProcess;
        aList->firstProcess = aProcess;
    }
    aList->size++;
}

/**
 * @brief Construit un pointeur de type Process, positionne le champ id à la valeur donnée
 * puis utilise addActivity pour ajouter l'activité passée en paramètre au processus créé
 * puis utilise push_front pour ajouter le processus à la liste de processus
 */
void addProcess(ProcessList * aList, int aProcessId, string anActivityName, string aTime)
{
    auto *newProcess = new Process;
    if(newProcess != nullptr){
        newProcess->id = aProcessId;
        addActivity(newProcess,anActivityName,aTime);
        push_front(aList,newProcess);
    }
}

/**
 * @brief Parcours la liste des processus
 * quand le processus est trouvé (comparaison des id à aProcessID) on utilise addActivity pour ajouter
 * l'activité donnée au processus trouvé
 */
void insertProcessActivity(ProcessList * aList, int aProcessId, string anActivityName, string aTime)
{
    Process *currentProcess = aList->firstProcess;
    while (currentProcess != nullptr){
        if (currentProcess->id == aProcessId){
            addActivity(currentProcess,anActivityName,aTime);
            return;
        }
        currentProcess = currentProcess->nextProcess;
    }
}

/**
 * @brief Parcours la liste des processus
 * Si un processus correspond au process Id donné retourner un pointeur vers ce processus
 * retourne nullptr sinon
 */
Process * processExists(ProcessList * aList, int aProcessId)
{
    Process *currentProcess = aList->firstProcess;
    while (currentProcess!= nullptr){
        if(currentProcess->id == aProcessId){
            return currentProcess;
        }
        currentProcess = currentProcess->nextProcess;
    }
    return nullptr;
}


/*
 * Processes Functions
 */

/**
 * @brief Affiche la taille du fichier à analyser (en utilisant nbOfLines)
 * Puis parcours le fichier
 * met à jour la barre de progression en utilisant pringProgressBar
 * utilise cin pour récupérer l'identifiant du processus, le nom de l'activité et la date de l'activité
 * si le processus existe (id déjà présent, pour cela on utilise processExist)
 * l'activité est ajoutée au processus trouvé en utilisant insertProcessActivity
 * ajoute le processus à la liste des processus sinon en utilisant addProcess
 * Ne pas oublier de fermer le fichier
 */
void extractProcesses(ProcessList* aList, string aFileName)
{
    string name, date;
    int id;

    ifstream aFile(aFileName);
    if (aFile.is_open())
    {
        int nbLines = nbOfLines(aFileName);
        cout << "Taille du fichier a extraire : " << nbLines;

        for (int i = 0; i < nbLines; i++)
        {
            printProgressBar(i, nbLines);
            aFile >> id >> name >> date;
            if (processExists(aList, id) != nullptr)
            {
                insertProcessActivity(aList, id, name, date);
            }
            else
            {
                addProcess(aList, id, name, date);
            }
        }

        aFile.close();
    }
    else
    {
        cout << "\nERREUR : Ouverture du fichier\n";
    }
}

/**
 * @brief Initialise une variable somme
 * Parcours la liste des processus puis ajoute le nombre d'activité de chaque processus
 * à la variable somme
 * retourne la moyenne somme/nombre de processus en réel
 */
double averageProcessLength(ProcessList * aList)
{
    Process *curr = aList->firstProcess;
    double moyenne = 0.0;
    while (curr != nullptr){
        moyenne += curr->nbActivities;
        curr = curr->nextProcess;
    }
    return moyenne/aList->size;
}

/**
 * @brief Insère une activité dans un processus en respectant l'ordre croissant sur le nom des activités
 * et à condition que le nom de l'activité n'existe pas déjà
 */
void insertActivity(Process * aProcess, Activity* anActivity)
{
    if (aProcess->firstActivity == nullptr || anActivity->name < aProcess->firstActivity->name)
    {
        anActivity->nextActivity = aProcess->firstActivity;
        aProcess->firstActivity = anActivity;
        aProcess->nbActivities++;
    }
    else
    {
        Activity *current = aProcess->firstActivity;
        while (current->nextActivity != nullptr && current->nextActivity->name <= anActivity->name)
        {
            current = current->nextActivity;
        }
        if (current->name != anActivity->name)
        {
            // Insert the activity into the process
            anActivity->nextActivity = current->nextActivity;
            current->nextActivity = anActivity;
            aProcess->nbActivities++;
        }
    }
}

/**
 * @brief Parcours la liste des processus
 * ajoute la première activité de chaque processus en utilisant
 * insertActivity (pas de doublons)
 */
void startActivities(ProcessList * aProcessList, Process * anActivityList)
{
    Process *curr = aProcessList->firstProcess;

    while (curr != nullptr)
    {
        insertActivity(anActivityList,curr->firstActivity);
        curr = curr->nextProcess;
    }
}

/**
 * @brief Parcours la liste des processus
 * Parcours la liste des activité de chaque processus
 * ajoute la dernière activité de chaque processus en utilisant
 * insertActivity (pas de doublons)
 */
void endActivities(ProcessList * aProcessList, Process * anActivityList)
{
    Process *currentProcess = aProcessList->firstProcess;

    while (currentProcess != nullptr)
    {
        // Check if the process has at least one activity
        if (currentProcess->firstActivity != nullptr)
        {
            // Traverse the list of activities to find the last activity
            Activity *lastActivity = currentProcess->firstActivity;
            while (lastActivity->nextActivity != nullptr)
            {
                lastActivity = lastActivity->nextActivity;
            }

            // Assuming insertActivity inserts an activity into the anActivityList
            insertActivity(anActivityList, lastActivity);
        }

        // Move to the next process in the list
        currentProcess = currentProcess->nextProcess;
    }
}

/**
 * @brief Parcours la liste des processus
 * pour chaque processus parcours la liste des activités et la compare avec la liste des activité du processus donné
 * retourne vrai si un processus identique est trouvé, faux sinon
 */
bool processAlreadyExists(ProcessList * aProcessList, Process * aProcess)
{
    for (Process *currentProcess = aProcessList->firstProcess; currentProcess != nullptr; currentProcess = currentProcess->nextProcess)
    {
        if (currentProcess->nbActivities == aProcess->nbActivities)
        {
            Activity *currentActivity1 = currentProcess->firstActivity;
            Activity *currentActivity2 = aProcess->firstActivity;

            while (currentActivity1 != nullptr && currentActivity2 != nullptr)
            {
                if (currentActivity1->name != currentActivity2->name)
                {
                    return false;
                }

                currentActivity1 = currentActivity1->nextActivity;
                currentActivity2 = currentActivity2->nextActivity;
            }

            if (currentActivity1 == nullptr && currentActivity2 == nullptr)
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Parcours la liste des processus
 * affiche la barre de progression en utilisant pringProgressBar
 * pour chaque processus vérifie qu'il n'est pas déjà dans la lite des variants
 * (utilise processAlreadyExists)
 * si c'est un nouveau variant créer un nouveau processus
 * y ajouter toutes les activités en utilisant addActivity
 * puis utiliser push_front pour ajouter le processus à la liste des variants
 */
void variants(ProcessList * aProcessList, ProcessList * aVariant)
{
    Process * curr = aProcessList->firstProcess;

    for (int i = 0; curr != nullptr; i++){
        printProgressBar(i,aProcessList->size);
        if (!processAlreadyExists(aVariant,curr)){
            auto *newVarient = new Process;
            newVarient->id = curr->id;
            push_front(aVariant,newVarient);

            Activity *currA = curr->firstActivity;
            while (currA != nullptr){
                addActivity(newVarient,currA->name,currA->time);
                currA = currA->nextActivity;
            }
        }
        curr = curr->nextProcess;
    }
}
