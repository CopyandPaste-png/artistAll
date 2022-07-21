#include "mainWrapper.h"

mainWrapper::mainWrapper() :wxFrame(nullptr,wxID_ANY,"test",wxDefaultPosition,wxSize(800,800))
{
	apiController = APIWrapper();

	testButton0 = std::make_unique<wxButton>(this,01,"test",wxPoint(100,200),wxSize(100,100));
	testButton1 = std::make_unique<wxButton>(this, 02, "test0", wxPoint(100, 350), wxSize(100, 100));
	testText = std::make_unique<wxTextCtrl>(this, 02, "Enter text here", wxPoint(250, 200), wxSize(500, 100));
	testButton1->Hide();


	Bind(wxEVT_BUTTON, &mainWrapper::test, this, 01);
	Bind(wxEVT_BUTTON, &mainWrapper::test2, this, 02);
}

mainWrapper::~mainWrapper()
{
}

void mainWrapper::test(wxCommandEvent& evt) {
	apiController.sendAPIRequest(0, 2, "");
	logToFile(std::to_string(apiController.checkIfTokenApiValid(0)));

	//deviantartAPI API = deviantartAPI();
	//logToFile(std::to_string(apiController.checkIfTokenApiValid(0)));
	//testButton1->Show();
}

void mainWrapper::test2(wxCommandEvent& evt) {
	std::string temp = std::string(testText->GetValue());
	apiController.sendAPIRequest(0, 1, temp);
}