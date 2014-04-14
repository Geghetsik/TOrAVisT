#ifndef TARGET_CONSTRAINT_PAIR_HPP
#define TARGET_CONSTRAINT_PAIR_HPP


class AttributeAxis;
class Constraint;
class Color;

class Task {
	public:

	private:
		std::vector<AttributeAxis*>	targets;
		std::vector<Constraint*>	constraints;
		Color				color;
	
};




#endif  // TARGET_CONSTRAINT_PAIR_HPP
