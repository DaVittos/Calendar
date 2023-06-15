#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure representing an event
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    char description[100];
} Event;

// Function to display the current date
void displayCurrentDate() {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    printf("Current date: %02d.%02d.%d\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

// Function to add a new event
void addEvent(Event *events, int *eventCount) {
    if (*eventCount >= 100) {
        printf("Maximum number of events reached.\n");
        return;
    }

    printf("Enter the event date (in format dd.mm.yyyy): ");
    scanf("%d.%d.%d", &events[*eventCount].day, &events[*eventCount].month, &events[*eventCount].year);

    printf("Enter the event description: ");
    scanf(" %[^\n]", events[*eventCount].description);

    printf("Enter the event time (in format HH:MM): ");
    scanf("%d:%d", &events[*eventCount].hour, &events[*eventCount].minute);

    (*eventCount)++;
    printf("Event added.\n");
}

// Function to display the list of events
void displayEvents(Event *events, int eventCount) {
    if (eventCount == 0) {
        printf("No scheduled events.\n");
        return;
    }

    printf("Event List:\n");
    for (int i = 0; i < eventCount; i++) {
        printf("%d. [%02d.%02d.%d %02d:%02d] %s\n", i + 1,
               events[i].day, events[i].month, events[i].year,
               events[i].hour, events[i].minute,
               events[i].description);
    }
}

// Function to delete an event
void deleteEvent(Event *events, int *eventCount, int index) {
    if (index < 0 || index >= *eventCount) {
        printf("Invalid event index.\n");
        return;
    }

    for (int i = index; i < *eventCount - 1; i++) {
        events[i] = events[i + 1];
    }

    (*eventCount)--;
    printf("Event deleted.\n");
}

// Function to edit an event
void editEvent(Event *events, int eventCount, int index) {
    if (index < 0 || index >= eventCount) {
        printf("Invalid event index.\n");
        return;
    }

    printf("Enter the new event date (in format dd.mm.yyyy): ");
    scanf("%d.%d.%d", &events[index].day, &events[index].month, &events[index].year);

    printf("Enter the new event description: ");
    scanf(" %[^\n]", events[index].description);

    printf("Enter the new event time (in format HH:MM): ");
    scanf("%d:%d", &events[index].hour, &events[index].minute);

    printf("Event updated.\n");
}

int main() {
    Event events[100];
    int eventCount = 0;
    int choice;

    do {
        printf("\n--- MAIN MENU ---\n");
        displayCurrentDate();
        printf("1. Display events for today\n");
        printf("2. Add an event\n");
        printf("3. Display event list\n");
        printf("4. Delete an event\n");
        printf("5. Edit an event\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Events for Today ---\n");
                // Search and display events for today
                break;
            case 2:
                printf("\n--- Add an Event ---\n");
                addEvent(events, &eventCount);
                break;
            case 3:
                printf("\n--- Event List ---\n");
                displayEvents(events, eventCount);
                break;
            case 4:
                printf("\n--- Delete an Event ---\n");
                if (eventCount == 0) {
                    printf("No events to delete.\n");
                } else {
                    int deleteIndex;
                    printf("Enter the index of the event to delete: ");
                    scanf("%d", &deleteIndex);
                    deleteEvent(events, &eventCount, deleteIndex - 1);
                }
                break;
            case 5:
                printf("\n--- Edit an Event ---\n");
                if (eventCount == 0) {
                    printf("No events to edit.\n");
                } else {
                    int editIndex;
                    printf("Enter the index of the event to edit: ");
                    scanf("%d", &editIndex);
                    editEvent(events, eventCount, editIndex - 1);
                }
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}