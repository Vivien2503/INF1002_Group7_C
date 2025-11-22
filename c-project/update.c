/*
 * OPERATION 5: Update Function
 * This function updates an existing student record by ID.
*/

#define _CRT_SECURE_NO_WARNINGS
#include "student_db.h"

void updateRecord(void) {
    int searchId;
    int i;
    int j;
    int found;
    char input[MAX_NAME_LEN];
    float newMark;
    int pos;

    printf("Enter student ID to update: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input. Update cancelled.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        audit_log("UPDATE", NULL, NULL, "FAIL(INVALID_INPUT)");
        return;
    }
    getchar();

    found = 0;
    if (index_get(searchId, &pos)) {
        found = 1;
        i = pos;
    } else {
        i = 0;
        while (i < recordCount) {
            if (records[i].id == searchId) {
                found = 1;
                break;
            }
            i = i + 1;
        }
    }

    if (found == 0) { // error if record not found
        printf("Record not found.\n");
        return;
    }

    StudentRecord before = records[i];
    // new name
    printf("Enter new name (or press enter to skip): ");
    fgets(input, MAX_NAME_LEN, stdin);

    if (input[0] != '\n') {
        j = 0;
        while (input[j] != '\0') {
            if (input[j] == '\n') {
                input[j] = '\0';
                break;
            }
            j = j + 1;
        }

        j = 0;
        while (input[j] != '\0') {
            records[i].name[j] = input[j];
            j = j + 1;
        }
        records[i].name[j] = '\0';
    }
    // new programme
    printf("Enter new programme (or press enter to skip): ");
    fgets(input, MAX_PROG_LEN, stdin);

    if (input[0] != '\n') {
        j = 0;
        while (input[j] != '\0') {
            if (input[j] == '\n') {
                input[j] = '\0';
                break;
            }
            j = j + 1;
        }

        j = 0;
        while (input[j] != '\0') {
            records[i].programme[j] = input[j];
            j = j + 1;
        }
        records[i].programme[j] = '\0';
    }

    // new mark
    printf("Enter new mark (or -1 to skip): ");
    if (scanf("%f", &newMark) != 1) {
        printf("Invalid input. Mark not updated.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        newMark = -1;
    }

    if (newMark >= 0) {
        records[i].mark = newMark;
    }

    printf("Record updated successfully.\n");
    audit_log("UPDATE", &before, &records[i], "SUCCESS");
}
