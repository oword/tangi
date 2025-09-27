#include <windows.h>
#include <shobjidl.h>
#include <iostream>
#include "../imgui/imgui.h"
#include "tangi.hpp"

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

void tangi::render_imgui_file()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("files"))
        {

            if (ImGui::MenuItem("open folder"))
            { 
                music_folder = select_folder();
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