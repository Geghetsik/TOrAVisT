/*!
  @file AttributeAxis.hpp
  @brief file contains the definaion of the class AttributeAxis.

  @author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <QLineF>
#include <map>

#include <QGraphicsLineItem>

//! Headers from current project

//! Forward declarations
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;


class AxesLayout;
class PointOnAxis;
class DataComponent;



/*!
  \class AttributeAxis AttributeAxis.hpp "include/AttributeAxis.hpp"
  \brief Represents the attribute axis 

  This class implements the attribute axis concept.
 */
class AttributeAxis : public QGraphicsLineItem {

	public:

		AttributeAxis(QGraphicsItem* parent = 0);

		double getMinValue();
		double getMaxValue();
		std::map <double, PointOnAxis*>& getDataPointsMap();
		PointOnAxis* getPointOnAxis(double value);
		std::string& getAxisName();
		AxesLayout* getAxesLayout();

		void setAxesLayout(AxesLayout* layout);
		void setAxisName(std::string name);
		void addDataPoint(DataComponent* dataComponent);
		void remapDataPoints();
		void fixMappingPoints();
		void mapPointsOnAxis();

		void updateNeighbourPositions(PointOnAxis* point, qreal dy);
		void resetMappingPoints();
		void removeMappingPoints();
		void mapMinMaxPoints();

		QRectF boundingRect() const;
		QPainterPath shape() const;

		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	private:
		std::list<double>* getMappingPointValues();
		QList<PointOnAxis*>* getPointsOfInterestList();

	protected:
		void paint(QPainter* painter, 
					const QStyleOptionGraphicsItem *option,
					QWidget* parent = 0);

	private:

		std::string		_axisName;
		std::map <double, PointOnAxis*> _dataPoints;

		AxesLayout*		_axesLayout;

};

