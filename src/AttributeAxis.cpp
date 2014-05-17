/*!
  \file AttributeAxis.cpp
  \brief file contains the implementation of the class AttributeAxis.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>
#include <list>
#include <iostream>
#include <math.h>

//! Headers from current project
#include <AttributeAxis.hpp>
#include <AxesLayout.hpp>
#include <DataComponent.hpp>
#include <PointOnAxis.hpp>

AttributeAxis::AttributeAxis(QString name, QGraphicsItem* parent)
	: QGraphicsLineItem(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_axisName = new QGraphicsSimpleTextItem(name, this);
	_axisName->setRotation(180);
	_axisName->setPos(_axisName->boundingRect().width() / 2 /*15*/, -10);
}

QRectF AttributeAxis::boundingRect() const
{
	/*
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
				line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
		*/
	return QGraphicsLineItem::boundingRect();
}

QPainterPath AttributeAxis::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	/*
	for (std::map<double, PointOnAxis*>::const_iterator it = 
			_dataPoints.begin();
			it != _dataPoints.end(); ++it) {
		path.addPath(it->second->shape());
	}
	*/
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

void AttributeAxis::setAxisName(QString name)
{
	_axisName->setText(name);
}

QGraphicsSimpleTextItem* AttributeAxis::getAxisName()
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
	PointOnAxis* point;
	double value = dataComponent->getValue();
	dataComponent->setAttributeAxis(this);

	if (_dataPoints.count(value) > 0) {
		point = _dataPoints[value];
		point->addDataComponent(dataComponent);
	} else {
		point = new PointOnAxis(value, dataComponent->getRealValue(), this);
		point->setParentItem(this);
		point->addDataComponent(dataComponent);
		_dataPoints[value] = point;
//	std::cout << "After adding to dataEntry" << std::endl;
	}
	dataComponent->setPointOnAxis(point);
}

void AttributeAxis::remapDataPoints()
{
	if (_dataPoints.empty()) {
		return;
	}
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
		if ((value != map1) && (map2 != value)) {
			double y1 = _dataPoints[map1]->pos().y();
			double y2 = _dataPoints[map2]->pos().y();
			double y = y1 + (y2 - y1) * (value - map1) / (map2 - map1);
			it->second->setPos(line().p1().x(), y);
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

AxesLayout* AttributeAxis::getAxesLayout()
{
	return _axesLayout;
}

void AttributeAxis::setAxesLayout(AxesLayout* layout)
{
	_axesLayout = layout;
}

QList<PointOnAxis*>* AttributeAxis::getPointsOfInterestList()
{
	if (_dataPoints.empty()) {
		return NULL;
	}
	QList<PointOnAxis*>* list = new QList<PointOnAxis*>();
	std::map<double, PointOnAxis*>::iterator it = _dataPoints.begin();
	PointOnAxis* min = it->second;
	list->push_back(min); // min value
	it++;
	for (; it != _dataPoints.end(); ++it) {
		if (it->second->isPointOfInterest()) {
			list->push_back(it->second);
		} 
	}
	PointOnAxis* max = _dataPoints.rbegin()->second; // max value
	if (!list->contains(max)) {
		list->push_back(max); // max value
	}
	return list;
}



void AttributeAxis::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->modifiers() == Qt::SHIFT) {
		setCursor(Qt::ClosedHandCursor);
	}
}

void AttributeAxis::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->modifiers() == Qt::SHIFT) {
		if (QLineF(event->screenPos(), 
					event->buttonDownScreenPos(Qt::LeftButton)).length()
				< QApplication::startDragDistance()) {
			return;
		}
		setPos(mapToParent(event->pos() - 
						   event->buttonDownPos(Qt::LeftButton)));
		update();
		_axesLayout->updateLinks(this);
	}
}

void AttributeAxis::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);
}

void AttributeAxis::mapMinMaxPoints()
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

}


void AttributeAxis::resetMappingPoints()
{
	if (_dataPoints.empty()) {
		return;
	}

	QList<PointOnAxis*>* pointsOfInterest = getPointsOfInterestList();
	int N = pointsOfInterest->size();
	if (N <= 2) {
		return;
	}
	std::cout << "PERFORM Mapping" << std::endl;
	int numSegments = log2 (N - 2);
	std::cout << "num of interest data:" << N << "\nNumSegmentd:" << numSegments  << std::endl;
	for (int i = 1; i < numSegments; ++i) {
		int segmentStartPointIndex = i * N / numSegments;
		PointOnAxis* point = pointsOfInterest->at(segmentStartPointIndex);
		point->setIsMappingPoint(true);
		std::cout << "Add Mapping Point"  << std::endl;
		double y1 = line().p1().y();
		double y2 = line().p2().y();
		double posY = y1 + i * (y2 - y1) / numSegments;
		point->setPos(line().p1().x(), posY);
	}
	delete pointsOfInterest;
}


void AttributeAxis::removeMappingPoints()
{
	if (_dataPoints.empty()) {
		return;
	}
	std::map<double, PointOnAxis*>::iterator it = _dataPoints.begin();
	for (; it != _dataPoints.end(); ++it) {
		it->second->setIsMappingPoint(false);
	}
}
		
void AttributeAxis::setAxisNamePos(qreal x, qreal y)
{
	_axisName->setPos(x, y);
}

bool AttributeAxis::isBetweenNeighbourPositionsOfPoint(PointOnAxis* dataPoint,
														QPointF point)
{
	std::map<double, PointOnAxis*>::iterator it = 
		_dataPoints.find(dataPoint->getValue());
	std::map<double, PointOnAxis*>::iterator prev = --it;
	++it;
	std::map<double, PointOnAxis*>::iterator next = ++it;
	qreal prevY = prev->second->pos().y();
	qreal nextY = next->second->pos().y();
	qreal pointY = point.y();
	return ((prevY <= pointY) && (pointY <= nextY));
}

void AttributeAxis::updateNeighbourLinks()
{
	_axesLayout->updateLinks(this);
}
