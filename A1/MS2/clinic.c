/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ",
               patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData *data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient *patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ",
               patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    int count = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > 0)
        {
            count++;
        }
    }
    if (count <= 0)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        if (fmt == FMT_TABLE)
        {
            displayPatientTableHeader();
        }
        i = 0;
        for (i = 0; i < max; i++)
        {
            if (patient[i].patientNumber > 0)
            {
                displayPatientData(&patient[i], fmt);
            }
        }
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{

    int selection;
    do
    {
        printf(
            "Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i = 0;
    int can_add = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            can_add = 1;
            break;
        }
    }
    if (can_add == 1)
    {
        patient[i].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[i]);
        printf("*** New patient record added ***\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    putchar('\n');
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patient_number = 0;
    int index = 0;
    printf("Enter the patient number: ");
    patient_number = inputInt();
    index = findPatientIndexByPatientNum(patient_number, patient, max);
    putchar('\n');
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patient_number = 0;
    int index = 0;
    char confirmation = 'c';
    printf("Enter the patient number: ");
    patient_number = inputInt();
    index = findPatientIndexByPatientNum(patient_number, patient, max);
    putchar('\n');
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &confirmation);
        clearInputBuffer();
        if (confirmation == 'y')
        {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
    putchar('\n');
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patient_number = 0;
    int index = 0;
    printf("Search by patient number: ");
    patient_number = inputInt();
    index = findPatientIndexByPatientNum(patient_number, patient, max);
    putchar('\n');

    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phone[PHONE_LEN] = {'\0'};
    int i;
    int indexes[max];
    int matchCount = 0;
    printf("Search by phone number: ");
    inputCString(phone, 10, 10);
    putchar('\n');
    for (i = 0; i < max; i++)
    {
        indexes[i] = -1;
        if (strcmp(patient[i].phone.number, phone) == 0)
        {
            indexes[i] = i;
        }
    }
    i = 0;
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (indexes[i] != -1)
        {
            matchCount++;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }
    if (matchCount == 0)
    {
        printf("\n*** No records found ***\n");
    }

    putchar('\n');
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int number = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > number)
        {
            number = patient[i].patientNumber;
        }
    }
    number++;
    return number;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient *patient)
{

    printf("Patient Data Input\n"
           "------------------\n"
           "Number: %05d\n",
           patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone *phone)
{
    int selection = 0;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    switch (selection)
    {
    case 1:
        phone->description[0] = 'C';
        phone->description[1] = 'E';
        phone->description[2] = 'L';
        phone->description[3] = 'L';
        break;
    case 2:
        phone->description[0] = 'H';
        phone->description[1] = 'O';
        phone->description[2] = 'M';
        phone->description[3] = 'E';
        break;
    case 3:
        phone->description[0] = 'W';
        phone->description[1] = 'O';
        phone->description[2] = 'R';
        phone->description[3] = 'K';
        break;
    case 4:
        phone->description[0] = 'T';
        phone->description[1] = 'B';
        phone->description[2] = 'D';
        phone->description[3] = '\0';

        phone->number[0] = '\0';
        break;
    }
    if (selection != 4)
    {
        putchar('\n');
        printf("Contact: %s\nNumber : ", phone->description);
        inputCString(phone->number, 10, 10);
    }
    putchar('\n');
}