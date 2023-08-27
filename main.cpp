#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define FILEPATH "C:\\Users\\siddhi shukla\\Desktop\\Playlists\\"
using namespace std;

struct Song {
    string title;
    string artist;
    int duration;
};

struct Playlist {
    string name;
    vector<Song> songs;
};

// Function prototypes
void addSong(Playlist& playlist);
void displayPlaylist(const Playlist& playlist);
void savePlaylist(const Playlist& playlist);
void loadPlaylist(Playlist& playlist);
void addPlaylist(vector<Playlist>& playlists);
void displayAllPlaylists(const vector<Playlist>& playlists);
int selectPlaylist(const vector<Playlist>& playlists);

int main() {
    
    vector<Playlist> playlists;
    int choice;
    do {
        cout << "\nMENU:\n";
        cout << "---------------------------------------\n";
        cout << "1. Create a new playlist\n";
        cout << "2. Add a song to a playlist\n";
        cout << "3. Display a playlist\n";
        cout << "4. Save a playlist to file\n";
        cout << "5. Load a playlist from file\n";
        cout << "6. Display all playlists\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        switch(choice) {
            case 1: {
                addPlaylist(playlists);
                break;
            }
            case 2: {
                int playlistIndex = selectPlaylist(playlists);
                if (playlistIndex != -1) {
                    addSong(playlists[playlistIndex]);
                }
                break;
            }
            case 3: {
                int playlistIndex = selectPlaylist(playlists);
                if (playlistIndex != -1) {
                    displayPlaylist(playlists[playlistIndex]);
                }
                break;
            }
            case 4: {
                int playlistIndex = selectPlaylist(playlists);
                if (playlistIndex != -1) {
                    savePlaylist(playlists[playlistIndex]);
                }
                break;
            }
            case 5: {
                int playlistIndex = selectPlaylist(playlists);
                if (playlistIndex != -1) {
                    loadPlaylist(playlists[playlistIndex]);
                }
                break;
            }
            case 6: {
                displayAllPlaylists(playlists);
                break;
            }
            case 7: {
                cout << "Exiting program...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 7);
    return 0;
}

void addSong(Playlist& playlist) {
    Song song;
    cout << "Enter song title: ";
    cin.ignore();
    getline(cin, song.title);
    cout << "Enter artist name: ";
    getline(cin, song.artist);
    cout << "Enter song duration (in seconds): ";
    cin >> song.duration;
    playlist.songs.push_back(song);
    cout << "Song added to playlist successfully.\n";
}

void displayPlaylist(const Playlist& playlist) {
    cout << "Playlist name: " << playlist.name << endl;
    cout << "---------------------------------------\n";
    if (playlist.songs.empty()) {
        cout << "No songs in playlist yet.\n";
    } else {
        for (int i = 0; i < playlist.songs.size(); i++) {
            cout << i+1 << ". " << playlist.songs[i].title << " - "
                 << playlist.songs[i].artist << " (" << playlist.songs[i].duration
                 << " seconds)" << endl;
        }
    }
}

void savePlaylist(const Playlist& playlist) {
    ofstream outFile(FILEPATH + playlist.name + ".txt");
    if (!outFile) {
        cout << "Error: Unable to create file.\n";
    } else {
        for (int i = 0; i < playlist.songs.size(); i++) {
            outFile << playlist.songs[i].title << "|" << playlist.songs[i].artist << "|"
                    << playlist.songs[i].duration << endl;
        }
        cout << "Playlist saved to file successfully.\n";
    }
}

void loadPlaylist(Playlist& playlist) {
    ifstream inFile(FILEPATH + playlist.name + ".txt");
    if (!inFile) {
        cout << "Error: Unable to open file.\n";
    } else {
        playlist.songs.clear();
        Song song;
        string line;
        while (getline(inFile, line)) {
            int pos1 = line.find("|");
            int pos2 = line.find("|", pos1+1);
            song.title = line.substr(0, pos1);
            song.artist = line.substr(pos1+1, pos2-pos1-1);
            song.duration = stoi(line.substr(pos2+1));
            playlist.songs.push_back(song);
        }
        cout << "Playlist loaded from file successfully.\n";
    }
}

void addPlaylist(vector<Playlist>& playlists) {
    Playlist playlist;
    cout << "Enter playlist name: ";
    cin.ignore();
    getline(cin, playlist.name);
    playlists.push_back(playlist);
    cout << "Playlist added successfully.\n";
}

void displayAllPlaylists(const vector<Playlist>& playlists) {
    cout << "PLAYLISTS:\n";
    cout << "---------------------------------------\n";
    if (playlists.empty()) {
        cout << "No playlists created yet.\n";
    } else {
        for (int i = 0; i < playlists.size(); i++) {
            cout << i+1 << ". " << playlists[i].name << endl;
        }
    }
}

int selectPlaylist(const vector<Playlist>& playlists) {
    int playlistIndex;
    cout << "SELECT A PLAYLIST:\n";
    cout << "---------------------------------------\n";
    if (playlists.empty()) {
        cout << "No playlists created yet.\n";
        playlistIndex = -1;
    } else {
        for (int i = 0; i < playlists.size(); i++) {
            cout << i+1 << ". " << playlists[i].name << endl;
        }
        cout << "Enter playlist number (1-" << playlists.size() << "): ";
        cin >> playlistIndex;
        if (playlistIndex < 1 || playlistIndex > playlists.size()) {
            cout << "Invalid playlist number. Please try again.\n";
            playlistIndex = -1;
        } else {
            playlistIndex--;
        }
    }
    return playlistIndex;
}
