/*!
  \file PointOnAxis.hpp
  \brief file contains the definition of the class PointOnAxis.

  \author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <list>
#include <string>

#include <QGraphicsLineItem>

//! Headers from current project

//! Forward declarations 
class QPaintEvent;
class QGraphicsLineItem;
class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
class QRectF;
class QPainterPath;

class AttributeAxis;
class DataComponent;

/*!
  \class PointOnAxis PointOnAxis.hpp "include/PointOnAxis.hpp"
  \brief Represents data component on \ref DataPolyline

  This class implements the data component concept.
 */
class PointOnAxis : public QGraphicsLineItem {

public:
	enum { Type = UserType + 1 };

	int type() const
	{
		// Enable the use of qgraphicsitem_cast with this item.
		return Type;
	}

	PointOnAxis(QGraphicsItem* parent = 0);

	bool   	isMappingPoint();
	double  getValue();
	std::string getRealValue();
	QList<DataComponent*>& getDataComponents();
	AttributeAxis* getAttributeAxis();
	
	void setValue (double value);
	void setRealValue (std::string realValue);
	void setIsMappingPoint(bool isMappingPoint);
	void setAttributeAxis (AttributeAxis* attributeAxis);
	void addDataComponent (DataComponent* dataComponent);

	bool isPointOfInterest();

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	
private:
	bool					_isMappingPoint;
	double 					_value;
	std::string				_realValue;
	AttributeAxis*	  		_attributeAxis;
	QList<DataComponent*>	_dataComponents;	
	
};

