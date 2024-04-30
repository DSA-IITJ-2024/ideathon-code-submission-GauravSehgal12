# Playlist Management System

This is a simple command-line program written in C for managing a playlist of songs. It allows users to perform various operations such as adding, removing, displaying songs, searching for songs, and playing songs.

## Features

- **Add Music**: Add a new song to the playlist manually by providing the song title, artist name, and mood.
- **Add Music from CSV**: Add multiple songs to the playlist by reading data from a CSV file.
- **Remove Music**: Remove a song from the playlist based on its title.
- **Display Playlist**: Display the details of all songs currently in the playlist.
- **Search Songs**: Search for songs based on title, artist, or mood.
- **Premium Features**: Unlock premium features such as shuffled playback by becoming a premium user.
- **Play Next Song**: Play the next song in the playlist, with the option for linear or shuffled playback for premium users.
- **Play Previous Song**: Play the previous song in the playlist.

## Getting Started

### Prerequisites

- C Compiler (e.g., GCC)

### Running the Program

1. Compile the program using a C compiler. For example:

2. Run the compiled executable:


3. Follow the on-screen menu to perform various operations on the playlist.

## Usage

- When prompted, input the corresponding number to choose an operation from the menu.
- Follow the instructions to add, remove, search, or play songs.
- Premium features can be unlocked by selecting the "Premium Features" option from the menu.

## File Formats

- **CSV File Format**: The program expects the CSV file to contain song data in the following format: `title,artist,mood`. Each line represents a single song.

## Notes

- The playlist is implemented as a circular doubly linked list, allowing seamless navigation through the songs.
- Premium features are unlocked globally and persist throughout the program's execution.

## Author

This program was written by [Your Name].

