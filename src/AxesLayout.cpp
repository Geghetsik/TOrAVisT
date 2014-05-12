/*!
  \file AxesLayout.cpp
  \brief file contains the implementation of the class AxesLayout.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>
#include <iostream>

//! Headers from current project
#include <AttributeAxis.hpp>
#include <AxesLayout.hpp>
#include <DataComponent.hpp>
#include <PointOnAxis.hpp>

AxesLayout::AxesLayout (TaskGranularity granularity, TaskNature nature, 
						QObject* parent)
	: QGraphicsScene(parent)
{
	_granularity = granularity;
	_nature = nature;
}

void AxesLayout::addAttributeAxis(AttributeAxis* axis)
{
	addItem(axis);
	_axesLayout.push_back(axis);
}

void AxesLayout::arrangeAxes()
{
	if (_axesLayout.empty()) {
		std::cout << "Axes layout is empty" << std::endl;
		return;
	}
	int size = _axesLayout.size();
	qreal length = 8 * height() / 10;
	qreal axisPosY = 9 * height() / 10;
//	qreal axisY2 = height() / 10;
	qreal offset = width() / (size + 1);
	//std::cout << "ARRANGE AXES =============== " << offset << std::endl;
	for (int i = 0; i  < size; ++i) {
		AttributeAxis* axis = _axesLayout[i];
		qreal axisPosX = (i + 1) * offset;
		axis->setPos(axisPosX, axisPosY);
		axis->setRotation(-180);
		axis->setLine(0, 0, 0, length);
	}
}
void AxesLayout::remapDataPoints()
{
	if (_axesLayout.empty()) {
		std::cout << "Axes layout is empty" << std::endl;
		return;
	}
	for (unsigned i = 0; i  < _axesLayout.size(); ++i) {
		_axesLayout[i]->remapDataPoints();
	}

}
/*
void AxesLayout::paintEvent(QPaintEvent* event)
{
	QScrollArea::paintEvent(event);
	std::cout << "Axes layout start" << std::endl;
	// draw links between data points
	if (_axesLayout.empty()) {
		std::cout << "Axes layout is empty" << std::endl;
		return;
	}
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	for (int i = 1; (i + 1) < _axesLayout.size(); ++i) {
		AttributeAxis* axis1 = _axesLayout[i];
		AttributeAxis* axis2 = _axesLayout[i+1];
		std::map<double, PointOnAxis*>& map = axis1->getDataPointsMap();
		std::map<double, PointOnAxis*>::iterator it;
		for (it = map.begin(); it != map.end(); ++it) {
			it->second->drawDataPointLinksToAxis(axis2, &painter);
		}
	}
	std::cout << "Axes layout end" << std::endl;
}

	*/


