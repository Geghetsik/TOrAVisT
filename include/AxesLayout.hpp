/*!
  @file AxesLayout.hpp
  @brief file contains the definaion of the class AxesLayout.

  @author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <QGraphicsScene>
#include <string>

//! Headers from current project

//! Forward declarations
class QGraphicsRectItem;

class Toravist;
class AttributeAxis;
class AxesPairLink;
class DataEntry;
class Task;


class AxesLayout : public QGraphicsScene {

	Q_OBJECT

	public:

		AxesLayout(QString granularity, QString nature, 
					QObject* parent = 0);

		QList<DataEntry*>* getData();
		void setData (QList<DataEntry*>* data);

		QList<AttributeAxis*>& getAxes();

		void addAttributeAxis (AttributeAxis* axis);
		void addAttributeAxes (std::vector<AttributeAxis*> axes);
		void setAxesLayout (std::vector<AttributeAxis*> axes);
		void arrangeAxes ();
		void remapDataPoints ();
		void setTaskToDefault();
		void setTaskGranularuty(QString granularity);
		void setTaskNature(QString nature);
		void taskPerform();

		void createLinkedAxesPairs();
		void updateLinks(AttributeAxis* axis);
		void updateAllLinks();
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


	private:

		QList<AttributeAxis*>	_axes;
		QList<DataEntry*>*		_data;

		QList<AxesPairLink*>	_linkedAxesPairs;
		QGraphicsRectItem*		_selectionAreaRect;
		Task*					_task;

};

