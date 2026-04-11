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
