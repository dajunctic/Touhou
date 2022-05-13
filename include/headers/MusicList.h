#if !defined(MUSIC_LIST_H)
#define MUSIC_LIST_H

#include "Touhou.h"

struct Song
{
    /* data */
    Mix_Music * music = NULL;
    string name = "none";
    Song* next;
};

class SongList
{
    private:
        Song * head;
        int __number__songs_;

    public:
        SongList();
        ~SongList();

        void readFile(string);
        void loadMusic(string);
        void insertSong(string);
        void print();
        void play(int);
        int size();
        string at(int);

};

#endif // MUSIC_LIST_H

