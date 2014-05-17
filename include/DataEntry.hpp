/*!
  @file DataEntry.hpp
  @brief file contains the definaion of the class DataEntry.

  @author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <map>

//! Headers from current project

//! Forward declarations
class DataComponent;
class AttributeAxis;
class QColor;


/*!
  \class DataEntry DataEntry.hpp "include/DataEntry.hpp"
  \brief Represents the data entry 

  This class implements data entry concept which is represented as polyline.
 */
class DataEntry {

	public:

		DataEntry();

		QColor	getColor ();
		bool isDataOfInterest ();
		double getValueOf (AttributeAxis* attribute);
		DataComponent* getDataComponentFor (AttributeAxis* attribute);

		void setColor (QColor color);
		void setIsDataOfInterest (bool isDataOfInterest);
		void addDataComponent (AttributeAxis* attribute, 
							   DataComponent* dataComponent);

	private:
		bool 	_isDataOfInterest;
		QColor 	_color;

		std::map<AttributeAxis*, DataComponent*>	_dataComponents;
	
};

