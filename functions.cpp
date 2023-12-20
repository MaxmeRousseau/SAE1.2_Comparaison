/**
 * @file functions.cpp
 * @brief Implementation of the project functions
 * @author Ronan Champagnat - IUT Informatique La Rochelle
 * @date 10/11/2023
 */

#include "typeDef.h"

#include <iostream>
#include <fstream>

using namespace std;


/*
 * Chronographe functions
 */

/**
 * @brief Retourne l'heure courante avec une grande résolution
 */
chrono::time_point<std::chrono::high_resolution_clock> getTime()
{

}

/**
 * @brief Retourne la différence entre deux heures données et convertit en secondes.
 */
double calculateDuration(chrono::time_point<std::chrono::high_resolution_clock> start, chrono::time_point<std::chrono::high_resolution_clock> end)
{

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

}

/**
 * @brief Parcours tous les processus d'une liste et applique clear sur chaque processus
 * puis libère la mémoire de la liste et fait pointer la liste sur nullptr
 */
void clear(ProcessList * aList)
{

}

/**
 * @brief Affiche le nombre d'activité contenu dans le process
 * puis parcours toutes les activités pour les afficher (nom uniquement)
 * comme suit : Nb activités : 3: a b c \n
 */
void displayActivitiesList(Process * aProcess)
{

}

/**
 * @brief Affiche le nombre de processus contenus dans une liste puis parcours la liste
 * pour afficher l'id de chaque processus et ses activités (utilise displayActivitiesList)
 * comme suit : Nombre de processus : 3\n123:\tNb activités : 3: a b c \n456:\tNb activités : 1: b \n789:\tNb activités : 2: a b \n\n
 */
void displayProcessesList(ProcessList * aList)
{

}

/**
 * @brief Si la liste le processus ne contient aucune activité, l'activité est ajouté en tête
 * sinon la liste des activités est parcourue et l'activité est ajoutée en queue.
 * Le nombre d'activités du processus est incrémenté de 1
 */
void push_back(Process * aProcess, Activity* anActivity)
{

}

/**
 * @brief Construit un pointeur de type Activity et l'initialise au valeurs données
 * puis utilise push_back pour ajouter l'activité à la fin de la liste (au processus)
 */
void addActivity(Process * aProcess, string anActivityName, string aTime)
{

}

/**
 * @brief Ajoute un processus (Process) en tête de liste ProcessList
 */
void push_front(ProcessList * aList, Process * aProcess)
{

}

/**
 * @brief Construit un pointeur de type Process, positionne le champ id à la valeur donnée
 * puis utilise addActivity pour ajouter l'activité passée en paramètre au processus créé
 * puis utilise push_front pour ajouter le processus à la liste de processus
 */
void addProcess(ProcessList * aList, int aProcessId, string anActivityName, string aTime)
{

}

/**
 * @brief Parcours la liste des processus
 * quand le processus est trouvé (comparaison des id à aProcessID) on utilise addActivity pour ajouter
 * l'activité donnée au processus trouvé
 */
void insertProcessActivity(ProcessList * aList, int aProcessId, string anActivityName, string aTime)
{

}

/**
 * @brief Parcours la liste des processus
 * Si un processus correspond au process Id donné retourner un pointeur vers ce processus
 * retourne nullptr sinon
 */
Process * processExists(ProcessList * aList, int aProcessId)
{

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

}

/**
 * @brief Initialise une variable somme
 * Parcours la liste des processus puis ajoute le nombre d'activité de chaque processus
 * à la variable somme
 * retourne la moyenne somme/nombre de processus en réel
 */
double averageProcessLength(ProcessList * aList)
{

}

/**
 * @brief Insère une activité dans un processus en respectant l'ordre croissant sur le nom des activités
 * et à condition que le nom de l'activité n'existe pas déjà
 */
void insertActivity(Process * aProcess, Activity* anActivity)
{

}

/**
 * @brief Parcours la liste des processus
 * ajoute la première activité de chaque processus en utilisant
 * insertActivity (pas de doublons)
 */
void startActivities(ProcessList * aProcessList, Process * anActivityList)
{

}

/**
 * @brief Parcours la liste des processus
 * Parcours la liste des activité de chaque processus
 * ajoute la dernière activité de chaque processus en utilisant
 * insertActivity (pas de doublons)
 */
void endActivities(ProcessList * aProcessList, Process * anActivityList)
{

}

/**
 * @brief Parcours la liste des processus
 * pour chaque processus parcours la liste des activités et la compare avec la liste des activité du processus donné
 * retourne vrai si un processus identique est trouvé, faux sinon
 */
bool processAlreadyExists(ProcessList * aProcessList, Process * aProcess)
{

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

}
