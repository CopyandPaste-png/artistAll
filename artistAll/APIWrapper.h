#pragma once
#include <string>
#include "deviantartAPI.h"

class APIWrapper
{

public:
	APIWrapper();
	~APIWrapper();

public:
	/*
		Controller to interact with the various API's

		@param APIcode API to interact with.
		0 - deviantart;
		@param code code within the API to interact with
		@data data such as token's that wants to be passed
	*/
	void sendAPIRequest(int APIcode, int code,std::string data);

	/*
		Checks if API token is still valid
		@param APIcode API to interact with
		@return true if token is still valid, else false
	*/
	bool checkIfTokenApiValid(int APIcode);
};

