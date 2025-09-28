// currently we only have this tangi header and cpp file but in the future it might be better to seperate this into multiple files

#pragma once
#include <vector>
#include <filesystem>

struct tangi
{
    static void draw_imgui_menu_bar();
    static void draw_music_list();
    static void draw_player_buttons();

    public:
    static inline std::wstring music_folder{L"none selected"};
    static inline std::vector<std::wstring> music_files;
};