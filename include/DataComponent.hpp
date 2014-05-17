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
class AttributeAxis;
class PointOnAxis;
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
	PointOnAxis* getPointOnAxis ();
	AttributeAxis* getAttributeAxis ();
	DataEntry* getDataEntry ();

	void setValue (double value);
	void setRealValue (std::string realValue);
	void setPointOnAxis (PointOnAxis* point);
	void setAttributeAxis (AttributeAxis* attributeAxis);
	void setDataEntry (DataEntry* dataEntry);
	
private:
	double 						  _value;
	std::string					  _realValue;
	PointOnAxis*				  _pointOnAxis;
	AttributeAxis*	  			  _attributeAxis;
	DataEntry*					  _dataEntry;	
	
};

