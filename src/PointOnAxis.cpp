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

PointOnAxis::PointOnAxis(qreal numValue, QString value, QGraphicsItem* parent)
	: QGraphicsLineItem(parent)
{
	_attributeAxis = dynamic_cast<AttributeAxis*> (parent);
	setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setAcceptHoverEvents(true);
	_value = numValue;
	_realValue = new QGraphicsSimpleTextItem(value, this);
	_realValue->setRotation(180);
	_realValue->setPos(-10, 10);
	setIsMappingPoint(false);
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

QGraphicsSimpleTextItem* PointOnAxis::getRealValue ()
{
	return _realValue;
}


void PointOnAxis::setValue (double value)
{
	_value = value;
}

void PointOnAxis::setRealValue (QString realValue)
{
	_realValue->setText(realValue);
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
		_realValue->show();
	} else {
		setLine(-5, 0, 5, 0);
		_realValue->hide();
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
		if (isBetweenNeighbourPositions(dy)) {
			setPos(mapToParent(0, dy));
			_attributeAxis->updateNeighbourLinks();
		};
		update();
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

void PointOnAxis::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
	if (!isMappingPoint()) {
		_realValue->show();
	}
}

void PointOnAxis::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
	if (!isMappingPoint()) {
		_realValue->hide();
	}
}

bool PointOnAxis::isBetweenNeighbourPositions(qreal dy)
{
	return _attributeAxis->isBetweenNeighbourPositionsOfPoint(this, 
															mapToParent(0, dy));
}
