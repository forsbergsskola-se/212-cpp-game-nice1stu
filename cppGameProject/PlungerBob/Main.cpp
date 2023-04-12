#include "Application.h"

int main(int argc, char* args[])
{
	CApplication::Initialize();
	
	if (CApplication::GetInstance().Create())
	{
		CApplication::GetInstance().Run();
		CApplication::Deinitialize();
	}

	return 0;
}