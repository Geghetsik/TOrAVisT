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

	createGranularityGroup();
	createNatureGroup();

	_axesLayout = new AxesLayout(ELEMENTARY, COMPARISON, this);
//	_axesLayout->setSceneRect(0, 0, 5000, 5000);
	_axesLayout->setSceneRect(geometry());

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(_taskGranularityGroup);
	hbox->addWidget(_taskNatureGroup);

	QWidget *topFiller = new QWidget;
	topFiller->setLayout(hbox);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(topFiller);
	_view = new QGraphicsView(_axesLayout);
	layout->addWidget(_view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setWindowTitle(tr("Toravist"));
}

Toravist::~Toravist()
{
	for (std::list<DataEntry*>::iterator it = _data.begin();
			it != _data.end(); ++it) {
		delete (*it);
	}
}

void Toravist::createGranularityGroup()
{
	_taskGranularityGroup = new QGroupBox(tr("Task Granularity"));

	_elementaryTaskRadioBtn = new QRadioButton(tr("&Elementary"));
	_synopticTaskRadioBtn = new QRadioButton(tr("&Synoptic"));
	_elementaryTaskRadioBtn->setChecked(true);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(_elementaryTaskRadioBtn);
	vbox->addWidget(_synopticTaskRadioBtn);
	vbox->addStretch(1);
	_taskGranularityGroup->setLayout(vbox);

}

void Toravist::createNatureGroup()
{
	_taskNatureGroup = new QGroupBox(tr("Task Nature"));

	_lookupTaskRadioBtn = new QRadioButton(tr("&Lookup"));
	_comparisonTaskRadioBtn = new QRadioButton(tr("&Comparison"));
	_comparisonTaskRadioBtn->setChecked(true);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(_comparisonTaskRadioBtn);
	vbox->addWidget(_lookupTaskRadioBtn);
	vbox->addStretch(1);
	_taskNatureGroup->setLayout(vbox);

}

void Toravist::loadData()
{
	std::cout << "Load Data start" << std::endl;
	if(!_data.empty()) {
		std::cout << " Data is already loaded" << std::endl;
		return;
	}
	std::vector<AttributeAxis*> axes;
	for (int i = 0; i < 5; i++) {
		axes.push_back (new AttributeAxis());
		char axisName[20];
		sprintf(axisName, "axis[%i]", i);
		axes[i]->setAxisName(axisName);
		_axesLayout->addAttributeAxis(axes[i]);
		std::cout << "create axis : " << axes[i]->getAxisName() << std::endl;
	}


	for (int i = 0; i < 6; i++) {
		DataEntry* data = new DataEntry();
		data->setIsDataOfInterest(false);
		QColor color = QColor::fromHsv(i*(360/7), 180, 255);
		data->setColor(color);
		std::cout << "create data" << i << std::endl;
		for (int j = 0; j<5; j++) {
			char buf[10];
			sprintf(buf, "%d", i);
			std::string realValue (buf);
			double assignedValue;
			if (j%3 == 0) 
				assignedValue = i;
			if (j%3 == 1)
				assignedValue = 100 / (i+1);
			if (j%3 == 2)
				assignedValue = 10 + i*i;
			DataComponent* dataComponent = new DataComponent();
			dataComponent->setValue(assignedValue);
			dataComponent->setRealValue(realValue);
		//std::cout << "Toravist:: create data" << i << " component " << j << "  " << assignedValue << std::endl;
			data->addDataComponent(axes[j], dataComponent);/* must perform 
												dataComponent->setDataEntry
												axis->addDataPoint
													which must perform
													dataComponent->setAxis.*/

		}
		_data.push_back(data);
	}

	_axesLayout->arrangeAxes();
//	std::cout << "AFTER ArrangeAxes" << std::endl;
	_axesLayout->remapDataPoints();
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

	_taskMenu = menuBar()->addMenu(tr("&Task"));

	_helpMenu = menuBar()->addMenu(tr("&Help"));
	_helpMenu->addAction(_aboutAct);

}
