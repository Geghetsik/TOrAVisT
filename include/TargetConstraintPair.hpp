#ifndef TARGET_CONSTRAINT_PAIR_HPP
#define TARGET_CONSTRAINT_PAIR_HPP


class AttributeAxis;
class Constraint;

class Task {
	public:

	private:
		std::vector<AttributeAxis*>	targets;
		std::vector<Constraint*>	constraints;
		QColor				color;
	
};




#endif  // TARGET_CONSTRAINT_PAIR_HPP
