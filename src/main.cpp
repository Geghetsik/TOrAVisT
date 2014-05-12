#include <QApplication>
#include <Toravist.hpp>

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	Toravist appWindow;
	appWindow.setGeometry(100, 100, 800, 500);
	appWindow.show();
	return app.exec();

}

