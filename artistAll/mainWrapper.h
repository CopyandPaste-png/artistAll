#pragma once
#include "wx/wx.h"
#include "wx/textctrl.h"
#include <memory>
#include "HTTPrequests.h"
#include "APIWrapper.h"

class mainWrapper : public wxFrame
{
public:
	mainWrapper();
	~mainWrapper();

public:
	std::unique_ptr<wxButton>testButton0;
	std::unique_ptr<wxButton>testButton1;
	std::unique_ptr<wxTextCtrl>testText;
	APIWrapper apiController;

public:
	void test(wxCommandEvent& evt);
	void test2(wxCommandEvent& evt);
};

