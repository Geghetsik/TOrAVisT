#ifndef ATTRIBUTE_AXIS_HPP
#define ATTRIBUTE_AXIS_HPP

template <class T>

class MappingPoint<T>;
class DataPoint<T>;

class AttributeAxis {

	public:
		bool isIndependent();
		bool isTarget();
		bool isConstraint();



	private:
		bool 				isIndependent;
		bool 				isTarget;
		bool				isConstraint;

		MappingPoint<T>*		minPoint;
		MappingPoint<T>*		maxPoint;
		std::vector<MappingPoint<T>*>	mappingPoints;

		std::set<DataPoint<T>*>		dataPoints;
	
		double 				positionCoordinate;
};

#endif  // ATTRIBUTE_AXIS_HPP
