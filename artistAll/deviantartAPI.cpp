#include "deviantartAPI.h"

deviantartAPI::deviantartAPI() {}
deviantartAPI::~deviantartAPI(){}

void deviantartAPI::recieveAPIRequest(int code, std::string token){
	switch (code) {
		case 0:
			getBearer();
			break;
		case 1:
			authorize(token);
			break;
		case 2:
			refreshToken();
			break;
		case 3:
			uploadStash();
			break;
		default:
			break;
	}
}

void deviantartAPI::getBearer(){
	//https://www.deviantart.com/oauth2/authorize
	//https://www.deviantart.com/developers/authentication

	std::string authEndPoint =
		"https://www.deviantart.com/oauth2/authorize?response_type=code&client_id=19426&redirect_uri=https://www.google.com/&scope=stash&state=";

	std::string authURL = generateAuthURL(authEndPoint, 11);

	executeSearchWebBrowser(authURL);

}

int deviantartAPI::authorize(std::string& token) {

	std::string temp = token.substr(token.find("code")+5, token.find("&") - token.find("code")-5);


	std::string tokenURL =
		"https://www.deviantart.com/oauth2/token";


	std::string clientID = "19426";
	std::string clientSecret = "b03d23d16ce50f561b84c4c8d29344bf";
	std::string redirectURI = "https://www.google.com/";

	std::string buffer = tradeForAuthenticationToken(tokenURL, clientID, clientSecret,redirectURI, temp);


	if (buffer.find("success") != std::string::npos) {
		std::string authToken = _extractValueFromAuthJSON(buffer, "access_token");
		std::string refreshToken = _extractValueFromAuthJSON(buffer, "refresh_token");

		_writeTokensToFiles("deviantart", authToken, refreshToken);
		return 1;
	}
	else {
		std::string error = _extractValueFromAuthJSON(buffer, "error");
		std::string errorDescription = _extractValueFromAuthJSON(buffer, "error_description");
		logToFile("Error occured:" + error + "=>" + errorDescription);
		logToFile(buffer);
		return -1;
	}
}

void deviantartAPI::refreshToken() {
	
	std::string URL = "https://www.deviantart.com/oauth2/token";

	std::string clientID = "19426";
	std::string clientSecret = "b03d23d16ce50f561b84c4c8d29344bf";
	std::string redirectURI = "https://www.google.com/";
	std::string grantType = "refresh_token";
	std::string refreshToken = _readTokenFile("refreshtoken.txt", "deviantart");
	logToFile(refreshToken);

	if (refreshToken != "NONE") {
		
		struct curl_slist* list = NULL;

		std::string postData = 
			+ "client_id=" + clientID
			+ "&client_secret=" + clientSecret
			+ "&grant_type=" + grantType
			+ "&refresh_token=" + refreshToken;
		

		std::string buffer = performCURLPOST(URL, postData, list);


		if (buffer.find("success") != std::string::npos) {
			std::string authToken = _extractValueFromAuthJSON(buffer, "access_token");
			std::string refreshToken = _extractValueFromAuthJSON(buffer, "refresh_token");
			logToFile("Refresh token for deviant art acquired:");
			_writeTokensToFiles("deviantart", authToken, refreshToken);
			
		}
		else {
			std::string error = _extractValueFromAuthJSON(buffer, "error");
			std::string errorDescription = _extractValueFromAuthJSON(buffer, "error_description");
			logToFile("Error occured:" + error + "=>" + errorDescription);
		}
	}

}



/**/
bool deviantartAPI::checkIfTokenValid()
{

	std::string postData = "?access_token="+_readTokenFile("token.txt", "deviantart");

	if (postData.find("NONE")==std::string::npos) {
		std::string URL =
			"https://www.deviantart.com/api/v1/oauth2/placebo" + postData;

		std::string buffer = performSimpleCURLGET(URL);

		return (buffer.find("success") != std::string::npos);
	}
	
	return false;
}


void deviantartAPI::uploadStash() {}

void deviantartAPI ::deltaStash() {
	std::string postData = "?access_token=" + _readTokenFile("token.txt", "deviantart");

	if (postData.find("NONE") == std::string::npos) {

		std::string URL = "https://www.deviantart.com/api/v1/oauth2/stash/delta" + postData;

		std::string buffer = performSimpleCURLGET(URL);

		if (buffer.find("error") == std::string::npos) {
			_appendToFileDirectory("devientData", "stash.txt", buffer);
		}
	}
}


void deviantartAPI::submitStash() {
	//https://www.deviantart.com/api/v1/oauth2/stash/submit
	//https://www.deviantart.com/developers/http/v1/20210526/stash_submit/0f1832daa6b58a05841ec6058520c4f3


}

void deviantartAPI::publishStash() {
	//https://www.deviantart.com/developers/http/v1/20210526/stash_publish/a799a5c0967dca14e854286df9746793

}


