#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TITLE_LENGTH 100

typedef struct Song {
    char title[MAX_TITLE_LENGTH];
    char artist[MAX_TITLE_LENGTH];
    char mood[MAX_TITLE_LENGTH];
    struct Song *prev;
    struct Song *next;
} Song;

Song *head = NULL;
Song *tail = NULL;
int isPremium = 0; // Initially not a premium user

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addMusic() {
    Song *newSong = (Song *)malloc(sizeof(Song));
    printf("Enter song title: ");
    scanf("%99[^\n]", newSong->title);
    clearInputBuffer();
    printf("Enter artist name: ");
    scanf("%99[^\n]", newSong->artist);
    clearInputBuffer();
    printf("Enter mood: ");
    scanf("%99[^\n]", newSong->mood);
    clearInputBuffer();
    newSong->prev = NULL;
    newSong->next = NULL;

    if (head == NULL) {
        head = newSong;
        tail = newSong;
        // Make it circular
        head->next = tail;
        tail->prev = head;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
        // Make it circular
        tail->next = head;
        head->prev = tail;
    }
    printf("Song added to the playlist.\n");
}

void addMusicFromCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char line[MAX_TITLE_LENGTH * 3]; // Assuming each field can be as long as MAX_TITLE_LENGTH
    while (fgets(line, sizeof(line), file)) {
        char *title = strtok(line, ",");
        char *artist = strtok(NULL, ",");
        char *mood = strtok(NULL, "\n"); // Use '\n' as the delimiter for the last field
        if (title && artist && mood) {
            // Check if fields exceed MAX_TITLE_LENGTH and dynamically allocate memory if needed
            if (strlen(title) >= MAX_TITLE_LENGTH || strlen(artist) >= MAX_TITLE_LENGTH || strlen(mood) >= MAX_TITLE_LENGTH) {
                printf("Fields exceed maximum length. Skipping song.\n");
                continue;
            }

            Song *newSong = (Song *)malloc(sizeof(Song));
            strcpy(newSong->title, title);
            strcpy(newSong->artist, artist);
            strcpy(newSong->mood, mood);
            newSong->prev = NULL;
            newSong->next = NULL;

            if (head == NULL) {
                head = newSong;
                tail = newSong;
                // Make it circular
                head->next = tail;
                tail->prev = head;
            } else {
                tail->next = newSong;
                newSong->prev = tail;
                tail = newSong;
                // Make it circular
                tail->next = head;
                head->prev = tail;
            }
        } else {
            printf("Invalid line in CSV file: %s\n", line);
        }
    }

    fclose(file);
}
void removeMusic() {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    char titleToRemove[MAX_TITLE_LENGTH];
    printf("Enter the title of the song to remove: ");
    scanf("%99[^\n]", titleToRemove);
    clearInputBuffer();

    Song *current = head;
    while (current != NULL) {
        if (strcmp(current->title, titleToRemove) == 0) {
            if (current == head) {
                head = current->next;
                head->prev = tail;
                tail->next = head;
            } else if (current == tail) {
                tail = current->prev;
                tail->next = head;
                head->prev = tail;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("Song removed from the playlist.\n");
            return;
        }
        current = current->next;
    }

    printf("Song not found in the playlist.\n");
}

void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    printf("Playlist:\n");
    Song *current = head;
    do {
        printf("Title: %s\nArtist: %s\nMood: %s\n\n", current->title, current->artist, current->mood);
        current = current->next;
    } while (current != head);
}

void searchSongs(char *searchQuery, char *searchBasis) {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    // Convert the search query to lowercase for case-insensitive comparison
    for (int i = 0; searchQuery[i]; i++) {
        searchQuery[i] = tolower(searchQuery[i]);
    }

    printf("Songs found based on %s '%s':\n", searchBasis, searchQuery);
    Song *current = head;
    do {
        char lowercaseTitle[MAX_TITLE_LENGTH];
        char lowercaseArtist[MAX_TITLE_LENGTH];
        char lowercaseMood[MAX_TITLE_LENGTH];

        // Convert titles, artists, and moods to lowercase for comparison
        for (int i = 0; current->title[i]; i++) {
            lowercaseTitle[i] = tolower(current->title[i]);
        }
        lowercaseTitle[strlen(current->title)] = '\0';

        for (int i = 0; current->artist[i]; i++) {
            lowercaseArtist[i] = tolower(current->artist[i]);
        }
        lowercaseArtist[strlen(current->artist)] = '\0';

        for (int i = 0; current->mood[i]; i++) {
            lowercaseMood[i] = tolower(current->mood[i]);
        }
        lowercaseMood[strlen(current->mood)] = '\0';

        // Perform case-insensitive comparison
        if (strcmp(searchBasis, "title") == 0 && strcmp(lowercaseTitle, searchQuery) == 0) {
            printf("Title: %s\nArtist: %s\nMood: %s\n\n", current->title, current->artist, current->mood);
        } else if (strcmp(searchBasis, "artist") == 0 && strcmp(lowercaseArtist, searchQuery) == 0) {
            printf("Title: %s\nArtist: %s\nMood: %s\n\n", current->title, current->artist, current->mood);
        } else if (strcmp(searchBasis, "mood") == 0 && strcmp(lowercaseMood, searchQuery) == 0) {
            printf("Title: %s\nArtist: %s\nMood: %s\n\n", current->title, current->artist, current->mood);
        }
        current = current->next;
    } while (current != head);
}

void premiumFeatures() {
    isPremium = 1;
    printf("Congratulations! You are now a premium user.\n");
}
void playNextSong() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    Song *current = head;
    if (isPremium) {
        int choice;
        printf("Choose playback mode:\n");
        printf("1. Linear\n");
        printf("2. Shuffled\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        if (choice == 2) { // Shuffled playback
            int numSongs = 0;
            Song *temp = head;
            do {
                numSongs++;
                temp = temp->next;
            } while (temp != head);

            // Seed the random number generator
            srand(time(NULL));

            // Generate a random number between 0 and numSongs-1
            int randomIndex = rand() % numSongs;

            // Traverse to the randomly chosen song
            for (int i = 0; i < randomIndex; i++) {
                current = current->next;
            }
        } else { // Linear playback
            current = current->next;
        }
    }   else { // Non-premium user
        // Move to the next song in the playlist
        current = current->next;
    }

    printf("Now playing: %s by %s\n", current->title, current->artist);
}

void playPreviousSong() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    // Move to the previous song in the playlist
    head = head->prev;

    printf("Now playing: %s by %s\n", head->title, head->artist);
}
int main() {
    int choice;

    do {
        printf("\nPlaylist Menu:\n");
        printf("1. Add Music\n");
        printf("2. Add Music by csv file\n");
        printf("3. Remove Music\n");
        printf("4. Display Playlist\n");
        printf("5. Search Songs\n");
        printf("6. Premium Features\n");
        printf("7. Play Next Song\n");
        printf("8. Play Previous Song\n");
        printf("9. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addMusic();
                break;
            case 2:
                addMusicFromCSV("music.csv");
                break;
            case 3:
                removeMusic();
                break;
            case 4:
                displayPlaylist();
                break;
            case 5: {
                char searchQuery[MAX_TITLE_LENGTH];
                char searchBasis[MAX_TITLE_LENGTH];
                printf("Enter search query: ");
                scanf("%99[^\n]", searchQuery);
                clearInputBuffer();
                printf("Enter search basis (title/artist/mood): ");
                scanf("%99[^\n]", searchBasis);
                clearInputBuffer();
                searchSongs(searchQuery, searchBasis);
                break;
            }
            case 6:
                premiumFeatures();
                break;
            case 7:
                playNextSong();
                break;
            case 8:
                playPreviousSong();
                break;
            case 9:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    // Free allocated memory before exiting
    Song *current = head;
    do {
        Song *temp = current;
        current = current->next;
        free(temp);
    } while (current != head);

    return 0;
}