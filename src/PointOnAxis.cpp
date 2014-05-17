/*!
  \file PointOnAxis.cpp
  \brief file contains the implementation of the class \ref PointOnAxis.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>
#include <iostream>

//! Headers from current project
#include <AttributeAxis.hpp>
#include <DataComponent.hpp>
#include <DataEntry.hpp>

#include <PointOnAxis.hpp>

PointOnAxis::PointOnAxis(QGraphicsItem* parent)
	: QGraphicsLineItem(parent)
{
	_attributeAxis = dynamic_cast<AttributeAxis*> (parent);
	setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setIsMappingPoint(false);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
}



QList<DataComponent*>& PointOnAxis::getDataComponents()
{
	return _dataComponents;
}

AttributeAxis* PointOnAxis::getAttributeAxis()
{
	return _attributeAxis;
}

bool PointOnAxis::isMappingPoint()
{
	return _isMappingPoint;
}

double PointOnAxis::getValue()
{
	return _value;
}

std::string PointOnAxis::getRealValue ()
{
	return _realValue;
}


void PointOnAxis::setValue (double value)
{
	_value = value;
}

void PointOnAxis::setRealValue (std::string realValue)
{
	_realValue = realValue;
}

void PointOnAxis::setAttributeAxis (AttributeAxis* attributeAxis)
{
	_attributeAxis = attributeAxis;
}

void PointOnAxis::addDataComponent (DataComponent* dataComponent)
{
	_dataComponents.push_back(dataComponent);
}

void PointOnAxis::setIsMappingPoint(bool isMappingPoint)
{
	_isMappingPoint = isMappingPoint;
	if (isMappingPoint) {
	setLine(-8, 0, 8, 0);
	} else {
	setLine(-5, 0, 5, 0);
	}
}

void PointOnAxis::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->modifiers() == Qt::SHIFT) {
		setCursor(Qt::ClosedHandCursor);
		QGraphicsLineItem::mousePressEvent(event);
	}
}

void PointOnAxis::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->modifiers() == Qt::SHIFT) {
		if (QLineF(event->screenPos(), 
				event->buttonDownScreenPos(Qt::LeftButton)).length()
			   	< QApplication::startDragDistance()) {
			return;
		}
		qreal dy = event->pos().y();
		_attributeAxis->updateNeighbourPositions(this, dy);
		setPos(mapToParent(0, event->pos().y()));
		update();
	}
}

void PointOnAxis::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->modifiers() == Qt::SHIFT) {
		setCursor(Qt::OpenHandCursor);
	}
}

bool PointOnAxis::isPointOfInterest()
{
	for (int i = 0; i < _dataComponents.size(); ++i) {
		DataEntry* data = _dataComponents.at(i)->getDataEntry(); 
		if (data->isDataOfInterest()) {
			return true;
		}
	}
	return false;
}
