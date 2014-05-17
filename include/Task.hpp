/*!
  \file Task.hpp
  \brief file contains the definition of the class Task.

  \author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <QList>

//! Headers from current project

//! Forward declarations 
class AttributeAxis;
class DataComponent;
class DataEntry;
class PointsOnAxisLink;
class AxesLayout;
class Pattern;

/*!
  \class Task Task.hpp "include/Task.hpp"
  \brief Represents data component on \ref DataPolyline

  This class implements the data component concept.
 */
class Task {

public:
	Task(QString granularity, QString nature, AxesLayout* layout);

	AxesLayout*	getAxesLayout();

	void 	setGranularity(QString granularity);
	void	setNature(QString nature);

	void	addToLastPattern(QList<QGraphicsItem*> dataPoints);
	void	addNewPattern(QList<QGraphicsItem*> dataPoints);
	void	perform();

private:
	void	performElementary();
	void	performSynoptic();
	void	performLookup(); 
	void	performComparison(); 
	QColor* getRandomColor();
	void 	mergePatterns();

protected:

//	void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
//				QWidget* parent = 0);

	
private:

	QString				_granularity;
	QString				_nature;
	QList<Pattern*>		_dataPattern;
	AxesLayout*			_axesLayout;
	
};

