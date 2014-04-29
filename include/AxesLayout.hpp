#ifndef AXES_LAYOUT_HPP
#define AXES_LAYOUT_HPP

class AttributeAxis;

class DataPoint {

	public:
		double getXCoordinate();
		double getYCoordinate();

	private:
		double		  	layoutWidth;
		double		  	layoutLength;

		std<AttributeAxis*>	axesLayout;

};

#endif  // AXES_LAYOUT_HPP
