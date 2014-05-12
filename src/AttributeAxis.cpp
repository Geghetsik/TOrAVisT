/*!
  \file AttributeAxis.cpp
  \brief file contains the implementation of the class AttributeAxis.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>
#include <list>
#include <iostream>

//! Headers from current project
#include <AttributeAxis.hpp>
#include <AxesLayout.hpp>
#include <DataComponent.hpp>
#include <PointOnAxis.hpp>

AttributeAxis::AttributeAxis(QGraphicsItem* parent)
	: QGraphicsLineItem(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF AttributeAxis::boundingRect() const
{
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
				line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

QPainterPath AttributeAxis::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	for (std::map<double, PointOnAxis*>::const_iterator it = 
			_dataPoints.begin();
			it != _dataPoints.end(); ++it) {
		path.addPath(it->second->shape());
	}
	return path;
}

void AttributeAxis::paint(QPainter* painter, 
		const QStyleOptionGraphicsItem* option,
		QWidget* widget)
{
	QGraphicsLineItem::paint(painter, option, widget);
//	std::cout << "Axis: paint start " << getAxisName() << std::endl;
//	painter->setPen(pen());
//	painter->setBrush(pen().color());
//	painter->drawLine(line());
//	std::cout << "Axis:: paint end " << std::endl;
}

void AttributeAxis::setAxisName(std::string name)
{
	_axisName = std::string(name);
}

std::string& AttributeAxis::getAxisName()
{
	return _axisName;
}
double AttributeAxis::getMinValue()
{
	if (!_dataPoints.empty()) {
		return _dataPoints.begin()->first;
	}
	return 0;
}

double AttributeAxis::getMaxValue()
{	
	if (!_dataPoints.empty()) {
		return _dataPoints.rbegin()->first;
	}
	return 0;
}

std::map <double, PointOnAxis*>& AttributeAxis::getDataPointsMap()
{
	return _dataPoints;
}

PointOnAxis* AttributeAxis::getPointOnAxis(double value)
{
	return _dataPoints.find(value)->second;
}

void AttributeAxis::addDataPoint(DataComponent* dataComponent)
{
	double value = dataComponent->getValue();
	dataComponent->setAttributeAxis(this);

	if (_dataPoints.count(value) > 0) {
		PointOnAxis* point = _dataPoints[value];
		point->addDataComponent(dataComponent);
	} else {
		PointOnAxis* point = new PointOnAxis(this);
		point->setParentItem(this);
		point->setValue(value);
		point->setRealValue(dataComponent->getRealValue());
		point->addDataComponent(dataComponent);
		_dataPoints[value] = point;
//	std::cout << "After adding to dataEntry" << std::endl;
	}
}

void AttributeAxis::remapDataPoints()
{
	if (_dataPoints.empty()) {
		return;
	}
	fixMappingPoints();
	mapPointsOnAxis();
	
}

void AttributeAxis::fixMappingPoints()
{
	if (_dataPoints.empty()) {
		return;
	}
	PointOnAxis* minPoint = _dataPoints[getMinValue()];
	minPoint->setIsMappingPoint(true);
	minPoint->setFlag(QGraphicsItem::ItemIsMovable, false);
	minPoint->setPos(line().p1());

	PointOnAxis* maxPoint = _dataPoints[getMaxValue()];
	maxPoint->setIsMappingPoint(true);
	maxPoint->setFlag(QGraphicsItem::ItemIsMovable, false);
	maxPoint->setPos(line().p2());
	// TODO: add mapping points for values of interest
}

void AttributeAxis::mapPointsOnAxis()
{
	if (_dataPoints.empty()) {
		return;
	}
	std::list<double>* mapValues = getMappingPointValues();
	std::list<double>::iterator map = mapValues->begin();
	double map1 = *map;
	double map2 = *(++map);
	for(std::map<double, PointOnAxis*>::iterator it = _dataPoints.begin(); 
			it != _dataPoints.end(); ++it) {
		double value = it->first;
//		std::cout << "Value: " << value << std::endl;
//		std::cout << "map1: " << map1 << std::endl;
//		std::cout << "map2: " << map2 << std::endl;
		if ((value != map1) && (map2 != value)) {
			double y1 = _dataPoints[map1]->pos().y();
			double y2 = _dataPoints[map2]->pos().y();
			double y = y1 + (y2 - y1) * (value - map1) / (map2 - map1);
			it->second->setPos(line().p1().x(), y);
//			std::cout << "Map value: " << value << " on point: " << it->second->pos().x() << ", " << it->second->pos().y() << std::endl;
//			std::cout << "Map value: " << value << " on point: " << it->second->pos().x() << ", " << it->second->scenePos().y() << std::endl;
		} else if (value == map2) {
			map1 = map2;
			map2 = *(++map);
		}		
	}
	delete mapValues;

}

std::list<double>* AttributeAxis::getMappingPointValues()
{
	if (_dataPoints.empty()) {
		return NULL;
	}
	//std::cout << "MAP points on axis: " << getAxisName() << std::endl;
	std::list<double>* list = new std::list<double>();
	for (std::map<double, PointOnAxis*>::iterator it = _dataPoints.begin();
			it != _dataPoints.end(); ++it) {
		if (it->second->isMappingPoint()) {
			list->push_back(it->first);
		} 
	}
	return list;
}

/*
std::list<double>* AttributeAxis::getValuesOfInterestList()
{
	if (_dataPoints.empty()) {
		return;
	}
	std::list<double>* list = new std::list<double>();
	std::map<double, PointOnAxis*>::iterator it = _dataPoints.begin();
	list->push_back(it->first); // min value
	it++;
	for (; it != _dataPoints.rbegin(); ++it) {
		if (it->second->isValueOfInterest()) {
			list->push_back(it->first);
		} 
	}
	list->push_back(it->first); // max value
}
*/
