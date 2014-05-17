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

DataComponent::DataComponent(qreal numValue, QString realValue)
{
	_attributeAxis = NULL;
	_dataEntry = NULL;	
	_value = numValue;
	_realValue = realValue;
}

double DataComponent::getValue ()
{
	return _value;
}

QString DataComponent::getRealValue ()
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

void DataComponent::setRealValue (QString realValue)
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
