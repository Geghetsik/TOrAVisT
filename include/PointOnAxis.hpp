/*!
  \file PointOnAxis.hpp
  \brief file contains the definition of the class PointOnAxis.

  \author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <list>
#include <string>

#include <QGraphicsObject>

//! Headers from current project

//! Forward declarations 
class QPaintEvent;
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
class PointOnAxis : public QGraphicsObject {

public:
	PointOnAxis(QGraphicsItem* parent = 0);

	bool   	isMappingPoint();
	double  getValue();
	std::string getRealValue();
	std::list<DataComponent*>& getDataComponents();
	AttributeAxis* getAttributeAxis();
	
	void setValue (double value);
	void setRealValue (std::string realValue);
	void setIsMappingPoint(bool isMappingPoint);
	void setAttributeAxis (AttributeAxis* attributeAxis);
	void addDataComponent (DataComponent* dataComponent);
	void drawDataPointLinksToAxis(AttributeAxis* axis, QPainter* painter);

	QRectF boundingRect() const;
	QPainterPath shape() const;

protected:

	void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
				QWidget* parent = 0);

	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
	void mousePressEvent(QMouseEvent *event);
	
private:
	bool						  _isMappingPoint;
	double 						  _value;
	std::string					  _realValue;
	AttributeAxis*	  			  _attributeAxis;
	std::list<DataComponent*>	  _dataComponents;	
	
};

