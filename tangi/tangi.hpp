// currently we only have this tangi header and cpp file but in the future it might be better to seperate this into multiple files

#pragma once
#include <vector>
#include <filesystem>
#include "miniaudio/miniaudio.h"

struct tangi
{
    static void draw_imgui_menu_bar();
    static void draw_music_list();
    static void draw_player_buttons();
    static void draw_mixer_buttons();
    static std::string get_current_song_dir();
    

    public: 
    static inline ma_engine engine;
    //handle to currently playing song
    static inline ma_sound cur_song;
    static inline std::wstring music_folder{L"none selected"};
    static inline std::vector<std::wstring> music_files;
    static inline std::string selected_song{};
};