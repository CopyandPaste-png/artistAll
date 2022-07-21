#pragma once
#include "APIbase.h"

class deviantartAPI : public APIbase
{
public:
	deviantartAPI();
	~deviantartAPI();

public:
	/*
		Controls the flow of API requests and executes API calls

		@param code code corresponding to accompanying API call
		@param token Auth token if needed
		@return executes API call
	*/
	void recieveAPIRequest(int code,std::string token="");

	/*
		Checks if API token is valid
		@return true if token is still valid
	*/
	bool checkIfTokenValid();

private:
	void getBearer();
	int authorize(std::string& token);
	void refreshToken();
	void uploadStash();

	void deltaStash();
	void submitStash();
	void publishStash();
	
};

