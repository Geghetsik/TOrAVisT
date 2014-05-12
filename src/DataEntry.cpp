/*!
  \file DataEntry.cpp
  \brief file contains the implementation of the class DataEntry.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>
#include <iostream>

//! Headers from current project
#include <AttributeAxis.hpp>
#include <DataComponent.hpp>

#include <DataEntry.hpp>

QColor	DataEntry::getColor ()
{
	return _color;
}

bool DataEntry::isDataOfInterest ()
{
	return _isDataOfInterest;
}

double DataEntry::getValueOf (AttributeAxis* attribute)
{
	DataComponent* attr = getDataComponentFor(attribute);
	if (NULL != attr) {
		return attr->getValue();
	}
	return 0;
}

DataComponent* DataEntry::getDataComponentFor (AttributeAxis* attribute)
{
	if (_dataComponents.empty()) {
		return NULL;
	}
	return _dataComponents[attribute];
}

void DataEntry::setColor (QColor color)
{
	_color = color;
}

void DataEntry::setIsDataOfInterest (bool isDataOfInterest)
{
	_isDataOfInterest = isDataOfInterest;
}

void DataEntry::addDataComponent (AttributeAxis* attribute, 
							      DataComponent* dataComponent)
{
//		std::cout << "DataEntry:: add data" << attribute->getAxisName() << " component " << dataComponent->getValue() << std::endl;
	attribute->addDataPoint(dataComponent);
//	std::cout << "After adding to axis" << std::endl;
	dataComponent->setDataEntry(this);
	_dataComponents[attribute] = dataComponent;
}


