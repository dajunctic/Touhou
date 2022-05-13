#include <MusicList.h>

SongList::SongList()
{
    head = NULL;
    __number__songs_ = 0;
}
SongList::~SongList()
{

}

void SongList::readFile(string __path_)
{
    ifstream file(__path_);

    while(!file.eof())
    {
        string __name_;
        getline(file, __name_);

        __number__songs_ ++;
        insertSong(__name_);
    }
}

void SongList::loadMusic(string __path_)
{
    ifstream file(__path_);

    Song * p = head;

    while(!file.eof() and  p!=NULL)
    {
        string __name_;
        getline(file, __name_);

        __name_ =  "res/bgm/" + __name_ + ".mp3";

        p->music = Mix_LoadMUS(__name_.c_str());
        p = p->next;
    }
}

void SongList::insertSong(string __name_)
{
    if(head == NULL)
    {
        head = new Song();
        head->name = __name_;
        head->next = NULL;
    }
    else
    {
        Song * p = head;
        while(p->next != NULL)
        {
            p = p->next;
        }

        p->next = new Song();
        p = p->next;
        p->name = __name_;
        p->next = NULL;
    }
}

void SongList::print()
{
    Song * p = head;
    while(p != NULL)
    {
        p = p->next; 
    }
}

void SongList::play(int __numberical__order_)
{
    if(__number__songs_ <= __numberical__order_) return;

    Song * p = head;

    while(p != NULL and __numberical__order_){
        __numberical__order_ --;
        p = p->next;
    }
    
    Mix_PlayMusic(p->music, -1);
}

int SongList::size()
{
    return __number__songs_;
}

string SongList::at(int __numberical__order_)
{
    if(__number__songs_ <= __numberical__order_) return "invalid";

    Song * p = head;

    while(p != NULL and __numberical__order_){
        __numberical__order_ --;
        p = p->next;
    }
    return p->name;
}