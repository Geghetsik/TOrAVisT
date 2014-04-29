#ifndef MAPPING_POINT_HPP
#define MAPPING_POINT_HPP

class DataPoint;
class AttributeValue;

class MappingPoint {

public:
	double getXCoordinate();
	double getYCoordinate();
	
private:
	AttributeValue	  attributeValue;
	DataPoint*	  dataPoint;	
	double		  coordinateOnAxis;
	
};

#endif  // MAPPING_POINT_HPP
