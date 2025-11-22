/*
 * OPERATION 6: Delete Function
 * This function deletes a student record by ID.
*/

#define _CRT_SECURE_NO_WARNINGS
#include "student_db.h"

void deleteRecord(void) {
    int searchId;
    int i;
    int j;
    int found;
    char confirm;
    int pos;

//prompt for student ID including error handling
    printf("Enter student ID to delete: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input. Operation cancelled.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        audit_log("DELETE", NULL, NULL, "FAIL(INVALID_INPUT)");
        return;
    }

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

    if (found == 0) {
        printf("Record not found.\n");
        audit_log("DELETE", NULL, NULL, "FAIL(NOT_FOUND)");
        return;
    }

    printf("Are you sure you want to delete this record? (y/n): ");
    if (scanf(" %c", &confirm) != 1) {
        printf("Input error. Deletion cancelled.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        audit_log("DELETE", NULL, NULL, "FAIL(INVALID_CONFIRMATION)");
        return;
    }
    
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {} // clears the input buffer after reading confirmation

    if (confirm == 'y' || confirm == 'Y') {
        audit_log("DELETE", &records[i], NULL, "SUCCESS");

        j = i;
        while (j < recordCount - 1) {
            records[j] = records[j + 1];
            j = j + 1;
        }
        recordCount = recordCount - 1;

        index_rebuild(records, recordCount);

        printf("Record deleted successfully.\n");
    }
    else if (confirm == 'n' || confirm == 'N') {
        printf("Deletion cancelled.\n");
        audit_log("DELETE", NULL, NULL, "CANCELLED");
    }
    else {
        printf("Input error. Deletion cancelled.\n");
        audit_log("DELETE", NULL, NULL, "FAIL(INVALID_CONFIRMATION)");
    }
}
