// currently we only have this tangi header and cpp file but in the future it might be better to seperate this into multiple files

#pragma once

struct tangi
{
    static void render_imgui_file();

    public:
    static inline std::wstring music_folder{L"none selected"};
};