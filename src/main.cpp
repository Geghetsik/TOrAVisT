#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QLabel *label = new QLabel("Linux is wonderful", 0);
//	app.setMainWidget(label);
	label->show();
	return app.exec();
}

