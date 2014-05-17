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
class QGraphicsSimpleTextItem;
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

		AttributeAxis(QString name, QGraphicsItem* parent = 0);

		double getMinValue();
		double getMaxValue();
		std::map <double, PointOnAxis*>& getDataPointsMap();
		PointOnAxis* getPointOnAxis(double value);
		QGraphicsSimpleTextItem* getAxisName();
		AxesLayout* getAxesLayout();

		void setAxesLayout(AxesLayout* layout);
		void setAxisName(QString name);
		void setAxisNamePos(qreal x, qreal y);
		void addDataPoint(DataComponent* dataComponent);
		void remapDataPoints();
		void fixMappingPoints();
		void mapPointsOnAxis();
		
		void updateNeighbourLinks();

		void resetMappingPoints();
		void removeMappingPoints();
		void mapMinMaxPoints();

		QRectF boundingRect() const;
		QPainterPath shape() const;
		bool isBetweenNeighbourPositionsOfPoint(PointOnAxis* dataPoint,
												QPointF point);

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

		QGraphicsSimpleTextItem*		_axisName;
		std::map <double, PointOnAxis*> _dataPoints;

		AxesLayout*		_axesLayout;

};

