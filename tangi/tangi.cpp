#include <windows.h>
#include <shobjidl.h>
#include <iostream>
#include "../imgui/imgui.h"
#include "tangi.hpp"

namespace fs = std::filesystem;

// 100% pasted from chatgpt need to rewrite this later, works for now
std::wstring select_folder(HWND owner = nullptr)
{
    IFileDialog* pFileDialog = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARGS(&pFileDialog));

    if (FAILED(hr)) return L"";

    DWORD options;
    pFileDialog->GetOptions(&options);
    pFileDialog->SetOptions(options | FOS_PICKFOLDERS); // folder picker mode

    hr = pFileDialog->Show(owner);
    if (FAILED(hr)) { pFileDialog->Release(); return L""; }

    IShellItem* pItem;
    hr = pFileDialog->GetResult(&pItem);
    if (FAILED(hr)) { pFileDialog->Release(); return L""; }

    PWSTR pszFilePath = nullptr;
    pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

    std::wstring folderPath(pszFilePath);
    CoTaskMemFree(pszFilePath);
    pItem->Release();
    pFileDialog->Release();

    return folderPath;
}

std::vector<std::wstring> scan_music_files(const std::wstring& folder)
{
    std::vector<std::wstring> files;
    for (const auto & entry : fs::directory_iterator(folder ))
    {   
        if (entry.is_regular_file())
        {
            auto ext{ entry.path().extension().wstring() };
            if (ext == L".mp3" || ext == L".wav") {
                files.push_back(entry.path().filename().wstring());
                std::wcout << entry.path().filename().wstring() << L'\n';
            }
        }
    }
    return files;
}

void tangi::draw_imgui_menu_bar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("files"))
        {

            if (ImGui::MenuItem("open folder"))
            { 
                music_folder = select_folder();
                music_files = scan_music_files(music_folder);
            };
            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("options"))
        {

            if (ImGui::MenuItem("visualizer(beta)")) {};
            if (ImGui::MenuItem("song metadata previewer")) {};
            if (ImGui::MenuItem("song icons")) { };
            
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

// we probably wanna rework this later its kinda ghetto
void tangi::draw_music_list()
{
    static int selected_index{};
    static float list_size_slider{0.5f};
    ImVec2 sz_viewport{ImGui::GetMainViewport()->Size};

    ImGui::SliderFloat("list size", &list_size_slider, 0.f, 1.f);

    //if (ImGui::BeginListBox("##music_list", ImVec2(-FLT_MIN, list_size_slider * ImGui::GetTextLineHeightWithSpacing())))
    if (ImGui::BeginListBox("##music_list", ImVec2(-FLT_MIN, sz_viewport.y * list_size_slider)))
    {
        for (int i = 0; i < music_files.size(); i++)
        {
            // this seems weird idk if it works how I think
            // in the future we should detect if the song has a title attached to it in the metadata then use that instead of the filename
            std::string file{music_files[i].begin(), music_files[i].end()};

            bool is_selected{selected_index == i};
            if (ImGui::Selectable(file.c_str(), is_selected))
            {
                selected_index = i;
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndListBox();
    }
}

void tangi::draw_player_buttons()
{
        if(ImGui::Button("shuffle"))
    {
        std::cout << "shuffling folder cuh";
    }
    ImGui::SameLine();
    if(ImGui::Button("prev"))
    {
        std::cout << "playing the prev song cuh";
    }
    ImGui::SameLine();
    if(ImGui::Button("play"))
    {
        std::cout << "playing the song cuh";
    }
    ImGui::SameLine();
    if(ImGui::Button("next"))
    {
        std::cout << "playing the next song cuh";
    }
    ImGui::SameLine();
    if(ImGui::Button("loop"))
    {
        std::cout << "playing the same song cuh";
    }
    ImGui::SameLine();
    
}