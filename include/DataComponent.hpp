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
	DataComponent(qreal numValue, QString realValue);
	
	double getValue ();
	QString getRealValue ();
	PointOnAxis* getPointOnAxis ();
	AttributeAxis* getAttributeAxis ();
	DataEntry* getDataEntry ();

	void setValue (double value);
	void setRealValue (QString realValue);
	void setPointOnAxis (PointOnAxis* point);
	void setAttributeAxis (AttributeAxis* attributeAxis);
	void setDataEntry (DataEntry* dataEntry);
	
private:
	double 						  _value;
	QString						  _realValue;
	PointOnAxis*				  _pointOnAxis;
	AttributeAxis*	  			  _attributeAxis;
	DataEntry*					  _dataEntry;	
	
};

