#pragma once
#include "misc.h"
#include "logging.h"
#include "auth.h"

class APIbase
{
public:
	virtual void recieveAPIRequest(int code, std::string token = "") {};
	virtual bool checkIfTokenValid() { return false; };

private:
	virtual void getBearer() {};
	virtual int authorize(std::string& token) 
	{ return 1; };
	virtual void refreshToken() {};
};

