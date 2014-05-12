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
class Toravist;
class AttributeAxis;

enum TaskGranularity {ELEMENTARY, SYNOPTIC};
enum TaskNature {LOOKUP, COMPARISON};

class AxesLayout : public QGraphicsScene {

	public:
		AxesLayout(TaskGranularity granularity, TaskNature nature, 
					QObject* parent = 0);

		void addAttributeAxis(AttributeAxis* axis);
		void paintEvent(QPaintEvent*);
		void setAxesLayout(std::vector<AttributeAxis*> axes);
		void arrangeAxes();
		void remapDataPoints();

	private:

		std::vector<AttributeAxis*>	_axesLayout;
		TaskGranularity				_granularity;
		TaskNature					_nature;


};

