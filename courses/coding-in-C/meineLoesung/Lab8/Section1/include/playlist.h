#ifndef PLAYLIST_H
#define PLAYLIST_H
#define MAX_SONGS 50

typedef struct Song
{
    char *title;
    char *artist;

    struct Song *p_nextSong;
} Song;

typedef struct Playlist
{
    Song *p_head;
} Playlist;
/**
 * @brief Initialize a new playlist
 *
 * @param p_playlist pointer the playlist
 */
void init_playlist(Playlist *p_playlist);

/**
 * @brief add a new song to the end of the playlist
 *
 * @param playlist pointer to playlist
 * @param title    title of the new song
 * @param artist   artist of the new song
 */
void add_song(Playlist *playlist, const char *title, const char *artist);
/**
 * @brief print out all songs of the playlist
 *
 * @param playlist pointer to playlist
 */
void print_playlist(Playlist *playlist);

/**
 * @brief delete the first song of the playlist
 *
 * @param playlist pointer to playlist
 */
void delete_firstSong(Playlist *playlist);

/**
 * @brief delete playlist and free up memory
 *
 * @param playlist pointer to playlist
 */
void delete_playlist(Playlist *playlist);
#endif /* PLAYLIST_H */


