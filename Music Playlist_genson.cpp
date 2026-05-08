#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Song {
    char title[100];
    char artist[100];
    int duration;
    struct Song* next;
} Song;


Song* head = NULL;
Song* tail = NULL;


void menu(){
    printf("\n*MUSIC PLAYLIST (LINKED LIST QUEUE) ***\n");
    printf("1. Add Song to Playlist\n");
    printf("2. View Current Playlist\n");
    printf("3. Play Next Song\n");
    printf("4. Show Total Duration\n");
    printf("5. Exit\n");
    printf("-----------------------------\n");
    printf("Enter your choice: ");
}


void addSong(){
    Song newNode = (Song)malloc(sizeof(Song));

    getchar();
    printf("Enter song title: ");
    fgets(newNode->title, 100, stdin);
    newNode->title[strcspn(newNode->title, "\n")] = '\0';

    printf("Enter artist: ");
    fgets(newNode->artist, 100, stdin);
    newNode->artist[strcspn(newNode->artist, "\n")] = '\0';

    printf("Enter duration (sec): ");
    scanf("%d", &newNode->duration);

    newNode->next = NULL;

    if(head == NULL){
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    printf("-> Added: %s by %s\n", newNode->title, newNode->artist);
}


void viewPlaylist(){
    if(head == NULL){
        printf("ERROR: Playlist is empty!\n");
        return;
    }

    Song* current = head;
    int index = 1;

    printf("\n--- Current Playlist (Next Up is Song 1) ---\n");

    while(current != NULL){
        printf("[%d] %s (%s) - %d sec\n",
               index,
               current->title,
               current->artist,
               current->duration);
        current = current->next;
        index++;
    }

    printf("---------------------------------------------\n");
}


void playNext(){
    if(head == NULL){
        printf("ERROR: The playlist is currently empty! Add some songs first.\n");
        return;
    }

    Song* temp = head;

    printf("\n... Now Playing ...\n");
    printf("-> Dequeued and Played: %s (%s)\n",
           temp->title,
           temp->artist);

    head = head->next;
    free(temp);

    if(head == NULL){
        tail = NULL;
    }
}


void totalDuration(){
    if(head == NULL){
        printf("Playlist is empty!\n");
        return;
    }

    int total = 0;
    Song* current = head;

    while(current != NULL){
        total += current->duration;
        current = current->next;
    }

    int minutes = total / 60;
    int seconds = total % 60;

    printf("Total Duration of Playlist: %d seconds (%d min, %d sec)\n",
           total, minutes, seconds);
}


int main() {
    int choice;

    while(1){
        menu();
        scanf("%d", &choice);

        switch(choice){
            case 1:
                addSong();
                break;
            case 2:
                viewPlaylist();
                break;
            case 3:
                playNext();
                break;
            case 4:
                totalDuration();
                break;
            case 5:
                printf("Exiting Playlist Program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char title[100];
    char artist[100];
    float duration;
    struct Node *next;
} Node;


typedef struct {
    char title[100];
    char artist[100];
    float duration;
} Song;


Song library[10] = {
    {"Lonely", "Akon", 3.56},
    {"Smack That", "Akon", 3.32},
    {"Right Now", "Akon", 4.01},
    {"Beautiful", "Akon", 5.13},
    {"Don't Matter", "Akon", 4.52},
    {"Yellow", "Coldplay", 4.29},
    {"Paradise", "Coldplay", 4.20},
    {"Fix You", "Coldplay", 4.55},
    {"Viva La Vida", "Coldplay", 4.02},
    {"A Sky Full of Stars", "Coldplay", 4.28}
};


void displayLibrary(Song lib[], int size);
void displayMenu();
void addSong(Node **head, Node **tail, Song lib[]);
void viewPlaylist(Node *head);
void playNext(Node **head, Node **tail);
void totalDuration(Node *head);

int main() {
    Node *head = NULL;
    Node *tail = NULL;

    int choice;

    printf("\n+================================+\n");
    printf("|     Music Playlist Manager     |\n");
    printf("+================================+\n");

    do {
        displayMenu();
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addSong(&head, &tail, library);
                break;

            case 2:
                viewPlaylist(head);
                break;

            case 3:
                playNext(&head, &tail);
                break;

            case 4:
                totalDuration(head);
                break;

            case 5:
                printf("\nGoodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while(choice != 5);

    return 0;
}


void displayLibrary(Song lib[], int size) {
    printf("\n--- Song Library ---\n");

    for(int i = 0; i < size; i++) {
        printf("[%d] %-25s - %s\n",
               i + 1,
               lib[i].title,
               lib[i].artist);
    }

    printf("---------------------\n");
}


void displayMenu() {
    printf("\n------ MENU ------\n");
    printf("1. Add Song\n");
    printf("2. View Playlist\n");
    printf("3. Play Next Song\n");
    printf("4. Show Total Duration\n");
    printf("5. Exit\n");
    printf("------------------\n");
}


void addSong(Node **head, Node **tail, Song lib[]) {
    int num;

    displayLibrary(lib, 10);

    printf("Enter song number (1-10): ");
    scanf("%d", &num);

    if(num < 1 || num > 10) {
        printf("Invalid song number.\n");
        return;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->title, lib[num - 1].title);
    strcpy(newNode->artist, lib[num - 1].artist);
    newNode->duration = lib[num - 1].duration;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }

    printf("\nSong Added: \"%s\" by %s\n",
           newNode->title,
           newNode->artist);
}


void viewPlaylist(Node *head) {
    if(head == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    Node *current = head;
    int i = 1;

    printf("\n=== Your Playlist ===\n");

    while(current != NULL) {
        printf("[%d] %-25s - %-15s %.2f min\n",
               i,
               current->title,
               current->artist,
               current->duration);

        current = current->next;
        i++;
    }

    printf("======================\n");
}


void playNext(Node **head, Node **tail) {
    if(*head == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    Node *temp = *head;

    printf("\nNow Playing: \"%s\" by %s\n",
           temp->title,
           temp->artist);

    *head = (*head)->next;

    free(temp);

    if(*head == NULL) {
        *tail = NULL;
    }
}

void totalDuration(Node *head) {
    if(head == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    float total = 0;
    Node *current = head;

    while(current != NULL) {
        total += current->duration;
        current = current->next;
    }

    printf("\nTotal Playlist Duration: %.2f minutes\n", total);
}
