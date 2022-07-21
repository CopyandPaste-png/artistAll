#pragma once
#include <string>
#include <windows.h>

static std::string generateRandomText(int length) {
    char c;
    std::string message;

    for (int i = 0; i < length; i++) {
        int selection = rand() % 2;
        int random = rand() % 26;

        (selection == 0) ? c = 'a' + random : c = 'A' + random;

        message += c;
    }

    return message;
}

inline void executeSearchWebBrowser(std::string requestedURL) {

    //Converts to LPCWSTR so requestURL can be used in the shell

    std::wstring temp = std::wstring(requestedURL.begin(), requestedURL.end());
    LPCWSTR search = temp.c_str();

    //Opens the shell to open the browser and redirect to the requestURL
    ShellExecute(0, 0, search, 0, 0, SW_SHOW);
}
