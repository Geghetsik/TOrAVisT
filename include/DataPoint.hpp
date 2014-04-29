#ifndef DATA_POINT_HPP
#define DATA_POINT_HPP

class AttributeAxis;
class DataPolyline;

class DataPoint {

public:
	double getXCoordinate();
	double getYCoordinate();
	
private:
	AttributeAxis<T>* attributeAxis;
	T 		  attributeValue;
	DataPolyline*	  dataPolyline;	
	double		  coordinateOnAxis;
	
};




#endif  // DATA_POINT_HPP
