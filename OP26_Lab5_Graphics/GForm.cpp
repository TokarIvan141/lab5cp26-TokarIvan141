#include "GForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	OP26_Lab5_Graphics::GForm form;
	Application::Run(% form);

	return 0;
}