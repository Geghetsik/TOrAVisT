/*!
  \file Toravist.cpp
  \brief file contains the implementation of the class \ref Toravist.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>
#include <QColor>
#include <string>
#include <stdio.h>
#include <iostream>

//! Headers from current project
#include <Toravist.hpp>
#include <DataComponent.hpp>
#include <DataEntry.hpp>
#include <AxesLayout.hpp>
#include <AttributeAxis.hpp>


Toravist::Toravist()
{
	createActions();
	createMenus();

	createTaskToolbar();

	_axesLayout = new AxesLayout(_taskGranularityCombo->currentText(),
		   						 _taskNatureCombo->currentText(), this);
	_axesLayout->setSceneRect(geometry());


	QVBoxLayout *layout = new QVBoxLayout;
	_view = new QGraphicsView(_axesLayout);
	layout->addWidget(_view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setWindowTitle(tr("Toravist"));
}

void Toravist::loadData()
{
	std::cout << "Load Data start" << std::endl;
	if(!_data.empty()) {
		std::cout << " Data is already loaded" << std::endl;
		setTaskDefault();
		return;
	}
	std::vector<AttributeAxis*> axes;
	for (int i = 0; i < 5; i++) {
//		char axisName[20];
//		sprintf(axisName, "axis[%i]", i);
		axes.push_back (new AttributeAxis(QString(QObject::tr("axis")) +
										  QString::number(i)));
//		axes[i]->setAxisName(axisName);
//		std::cout << "create axis : " << axes[i]->getAxisName() << std::endl;
	}


	for (int i = 0; i < 8; i++) {
		DataEntry* data = new DataEntry();
		data->setIsDataOfInterest(false);
	//	QColor color = QColor::fromHsv(i*(360/7), 180, 255);
	//	data->setColor(color);
		std::cout << "create data" << i << std::endl;
		for (int j = 0; j<5; j++) {
			char buf[10];
			sprintf(buf, "%d", i);
			double assignedValue;
			if (j%4 == 0) { 
				assignedValue = i;
			}
			if (j%4 == 1)
				assignedValue = 100 / (i+1);
			if (j%4 == 2)
				assignedValue = 10 + i*i;
			if (j%4 == 3)
				assignedValue = 20 - 2*i;
			QString realValue = QString::number(assignedValue);
			if (j == 0) { 
				realValue += QString(QObject::tr("color"));
			}
		std::cout << "Toravist:: create data" << i << " component " << j << "  " << assignedValue << std::endl;
			DataComponent* dataComponent = new DataComponent(assignedValue,
															 realValue);
		//	dataComponent->setValue(assignedValue);
		//	dataComponent->setRealValue(realValue);
			data->addDataComponent(axes[j], dataComponent);/* must perform 
												dataComponent->setDataEntry
												axis->addDataPoint
													which must perform
													dataComponent->setAxis.*/

		}
		_data.append(data);
	}
	std::cout << "AFTER Creating data" << std::endl;

	_axesLayout->setData(&_data);
	_axesLayout->addAttributeAxes(axes);
	//_axesLayout->arrangeAxes();
	std::cout << "AFTER Set/Arrange Axes" << std::endl;
	_axesLayout->taskPerform();
	//_axesLayout->remapDataPoints();
//	std::cout << "AFTER remapDataPoints" << std::endl;
	_axesLayout->update();
	_view->update();
	std::cout << "Load Data end" << std::endl;
}


void Toravist::about()
{
	QMessageBox::about(this, tr("About Menu"),
			tr("The <b>Menu</b> example shows how to create "
				"menu-bar menus and context menus."));
}

void Toravist::createActions()
{

	_loadDataAct = new QAction(tr("&LoadData..."), this);
	_loadDataAct->setShortcuts(QKeySequence::Open);
	_loadDataAct->setStatusTip(tr("Load data from an existing file"));
	connect(_loadDataAct, SIGNAL(triggered()), this, SLOT(loadData()));

	_exitAct = new QAction(tr("E&xit"), this);
	_exitAct->setShortcuts(QKeySequence::Quit);
	_exitAct->setStatusTip(tr("Exit the application"));
	connect(_exitAct, SIGNAL(triggered()), this, SLOT(close()));

	_aboutAct = new QAction(tr("&About"), this);
	_aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void Toravist::createMenus()
{
	_fileMenu = menuBar()->addMenu(tr("&File"));
	_fileMenu->addAction(_loadDataAct);
	_fileMenu->addSeparator();
	_fileMenu->addAction(_exitAct);

	_helpMenu = menuBar()->addMenu(tr("&Help"));
	_helpMenu->addAction(_aboutAct);

}
void Toravist::createToolBox()
{

}

void Toravist::createTaskToolbar()
{
	_taskGranularityCombo = new QComboBox;
	QStringList granularityValues;
	granularityValues << tr("Elementary") << tr("Synoptic");
	_taskGranularityCombo->addItems(granularityValues);
	_taskGranularityCombo->setCurrentIndex(0);
	connect(_taskGranularityCombo, SIGNAL(currentIndexChanged(QString)),
			this, SLOT(taskGranularityChanged(QString)));

	_taskNatureCombo = new QComboBox;
	QStringList natureValues;
	natureValues << tr("Comparison") << tr("Lookup");
	_taskNatureCombo->addItems(natureValues);
	_taskNatureCombo->setCurrentIndex(0);
	connect(_taskNatureCombo, SIGNAL(currentIndexChanged(QString)),
			this, SLOT(taskNatureChanged(QString)));
	
	_defaultViewBtn = new QPushButton("&Clear");
	connect(_defaultViewBtn, SIGNAL(clicked(bool)), 
			this, SLOT(taskClear()));
			//this, SLOT(setTaskDefault()));

	_taskToolBar = addToolBar(tr("Task"));
	_taskToolBar->addWidget(_taskGranularityCombo);
	_taskToolBar->addWidget(_taskNatureCombo);
	_taskToolBar->addWidget(_defaultViewBtn);
}

void Toravist::taskGranularityChanged(QString newValue)
{
	_axesLayout->setTaskGranularuty(newValue);
	_axesLayout->taskPerform();
}
	
void Toravist::taskNatureChanged(QString newValue)
{
	_axesLayout->setTaskNature(newValue);
	_axesLayout->taskPerform();
}

void Toravist::setTaskDefault()
{
	_axesLayout->setTaskToDefault();
	_axesLayout->arrangeAxes();
	_axesLayout->taskPerform();
	_taskNatureCombo->setCurrentIndex(0);
	_taskGranularityCombo->setCurrentIndex(0);
}	

void Toravist::taskClear()
{
	_axesLayout->taskClear();
}

Toravist::~Toravist()
{
	for (int i = 0; i < _data.size(); ++i) {
		delete _data.at(i);
	}
	delete _axesLayout;
}
