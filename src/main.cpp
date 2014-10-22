#include "BOMFileFinder/MainWindow.h"

#include <QApplication>

#if defined(_WIN32)
#include <windows.h>
#endif

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	app.setOrganizationName("SIB IT");
	app.setOrganizationDomain("sibit.com.br");
	app.setApplicationName("BOMFileFinder");

	BOMFileFinder::MainWindow window;
	window.resize(1024, 768);
	window.show();

	return app.exec();
}

#if defined(_WIN32)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return main(__argc, __argv);
}
#endif
