#include "app.h"

IMPLEMENT_APP(cApp);

cApp::cApp() {
}

cApp::~cApp() {
}


bool cApp::OnInit() {
	if (!wxApp::OnInit())
		return false;

	mainController = std::make_unique<mainWrapper>();

	mainController->Show();

	logToFile("APP STARTED");

	return true;
};

int cApp::OnExit()
{
	logToFile("APP ENDED");
	return 0;
}