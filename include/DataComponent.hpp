/*!
  \file DataComponent.hpp
  \brief file contains the definition of the class DataComponent.

  \author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <string>

//! Headers from current project

//! Forward declarations 
class QPaintEvent;
class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;

class AttributeAxis;
class DataEntry;

/*!
  \class DataComponent DataComponent.hpp "include/DataComponent.hpp"
  \brief Represents data component on \ref DataPolyline

  This class implements the data component concept.
 */
class DataComponent {

public:
	DataComponent();
	
	double getValue ();
	std::string getRealValue ();
	AttributeAxis* getAttributeAxis ();
	DataEntry* getDataEntry ();

	void setValue (double value);
	void setRealValue (std::string realValue);
	void setAttributeAxis (AttributeAxis* attributeAxis);
	void setDataEntry (DataEntry* dataEntry);
	
private:
	double 						  _value;
	std::string					  _realValue;
	AttributeAxis*	  			  _attributeAxis;
	DataEntry*					  _dataEntry;	
	
};

