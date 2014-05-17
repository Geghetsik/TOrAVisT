/*!
  \file DataComponent.cpp
  \brief file contains the implementation of the class DataComponent.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>

//! Headers from current project
#include <AttributeAxis.hpp>
#include <DataEntry.hpp>

#include <DataComponent.hpp>

DataComponent::DataComponent()
{
	_attributeAxis = NULL;
	_dataEntry = NULL;	
}

double DataComponent::getValue ()
{
	return _value;
}

std::string DataComponent::getRealValue ()
{
	return _realValue;
}

PointOnAxis* DataComponent::getPointOnAxis ()
{
	return _pointOnAxis;
}

AttributeAxis* DataComponent::getAttributeAxis ()
{
	return _attributeAxis;
}

DataEntry* DataComponent::getDataEntry ()
{
	return _dataEntry;
}

void DataComponent::setValue (double value)
{
	_value = value;
}

void DataComponent::setRealValue (std::string realValue)
{
	_realValue = realValue;
}

void DataComponent::setPointOnAxis (PointOnAxis* point)
{
	_pointOnAxis = point;;
}

void DataComponent::setAttributeAxis (AttributeAxis* attributeAxis)
{
	_attributeAxis = attributeAxis;
}

void DataComponent::setDataEntry (DataEntry* dataEntry)
{
	_dataEntry = dataEntry;
}
