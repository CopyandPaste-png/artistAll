#pragma once
#include <string>
#include <curl/curl.h>
#include "HTTPrequests.h"
#include "base64.h"
#include "fileMethods.h"

inline std::string generateAuthURL(std::string authEndPoint, int lengthofState) {
    std::string state = generateRandomText(lengthofState);
    std::string authURL = authEndPoint + state;

    return authURL;
}


inline std::string tradeForAuthenticationToken(
    std::string& tokenEndPoint,std::string& clientID, std::string& clientSecret, std::string& redirect_uri,std::string& tempToken) {
    printf("Trading code for OAuth2 token...\n");

    //Creating the POST data for the OAuth2 token request
    std::string postData = 
        "client_id=" + clientID
        + "client_secret=" + clientSecret
        + "&grant_type=authorization_code"
        + "&code=" + tempToken
        + "&redirect_uri="+redirect_uri;

    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in spotify64
    list = curl_slist_append(list, ("Authorization: Basic " + _base64encode(clientID + ":" + clientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer

    std::string readBuffer = performCURLPOST(tokenEndPoint, postData, list);

    return readBuffer;
}


static std::string _extractValueFromAuthJSON(std::string JSON,std::string value) {
    int firstIndex = JSON.find(value) + value.length()+2;
    std::string token = JSON.substr(firstIndex + 1, JSON.find("\"", firstIndex + 5) - firstIndex - 1);
    return token;
}


static void _writeTokensToFiles(std::string entry,std::string& authToken,std::string& refreshToken) {
    logToFile("authentication token acquired for "+ entry +":" + authToken);
    logToFile("refresh token acquired for "+ entry +":" + refreshToken);

    if (_isValueInFile("token.txt", entry)) {
        _editValueInFile("token.txt", entry, authToken);
    }
    else {
        _writeToFile("token.txt", entry, authToken);
    }

    if (_isValueInFile("refreshtoken.txt", entry)) {
        logToFile("HERE");
        _editValueInFile("refreshtoken.txt", entry, refreshToken);
    }
    else {
        logToFile("HERE2");
        _writeToFile("refreshtoken.txt", entry, refreshToken);
    }
}