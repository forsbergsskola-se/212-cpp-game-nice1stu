#include "Application.h"

int main(int argc, char* args[])
{
	CApplication::Initialize();
	CApplication::GetInstance().Run();
	CApplication::Deinitialize();

	return 0;
}