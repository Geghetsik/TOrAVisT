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
	: QGraphicsObject(parent)
{
	_attributeAxis = dynamic_cast<AttributeAxis*> (parent);
	setIsMappingPoint(false);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
}

void PointOnAxis::paint(QPainter* painter, const QStyleOptionGraphicsItem *,
		           		QWidget *)
{
	painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	if (isMappingPoint()) {
		//painter->drawRect(x - 5, y - 5, x + 5, y + 5);
		painter->setBrush(Qt::red);
		painter->drawEllipse(QPointF(0, 0), 5, 5);
	} else {
		painter->setBrush(Qt::blue);
		painter->drawEllipse(QPointF(0, 0), 3, 3);
	}
//	std::cout << "paint POINT on axis: " << _attributeAxis->getAxisName() << "  with value: " << _value << " axisX: " << _attributeAxis->line().p1().x() << std::endl;
//	std::cout << "point POS: " << scenePos().x() << ", " << scenePos().y()<< std::endl;
}

QRectF PointOnAxis::boundingRect() const
{
	if (_isMappingPoint) {
		return QRectF(- 5, - 5, 10, 10);
	} else {
		return QRectF(- 3, - 3, 6, 6);
	}
}

QPainterPath PointOnAxis::shape() const
{
	QPainterPath path;
	if (_isMappingPoint) {
		path.addEllipse(pos(), 5, 5);
	} else {
		path.addEllipse(pos(), 3, 3);
	}
//	QRectF rect = boundingRect();
//	path.addRect(rect);
	return path;
}

void PointOnAxis::dragEnterEvent(QDragEnterEvent *)
{
}
void PointOnAxis::dragMoveEvent(QDragMoveEvent *)
{
}
void PointOnAxis::dropEvent(QDropEvent *)
{
}
void PointOnAxis::mousePressEvent(QMouseEvent *)
{
}







/*
void PointOnAxis::drawDataPointLinksToAxis(AttributeAxis* attrAxis, 
										   QPainter* painter)
{
	for (std::list<DataComponent*>::iterator it = _dataComponents.begin();
			it != _dataComponents.end(); ++it) {
		DataEntry* data = (*it)->getDataEntry();
		double attrValue = data->getDataComponentFor(attrAxis)->getValue();
		PointOnAxis* point = attrAxis->getPointOnAxis(attrValue);
		painter->setPen(Qt::NoPen);
		painter->setBrush(data->getColor());
		painter->drawLine(QPointF (*this), QPointF (*point));
	}
}
*/

std::list<DataComponent*>& PointOnAxis::getDataComponents()
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
}


