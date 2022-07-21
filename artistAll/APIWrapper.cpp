#include "APIWrapper.h"


APIWrapper::APIWrapper()
{}

APIWrapper::~APIWrapper()
{
}

void APIWrapper::sendAPIRequest(int APIcode, int code,std::string data)
{
	switch (APIcode) {
		//deviantart
		case 0:
			deviantartAPI API = deviantartAPI();
			API.recieveAPIRequest(code, data);
			break;
	}
}

bool APIWrapper::checkIfTokenApiValid(int APIcode)
{
	if (APIcode == 0) {
		deviantartAPI API = deviantartAPI();
		return API.checkIfTokenValid();
	}
	else {
		return false;
	}
}
