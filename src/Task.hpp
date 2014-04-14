#ifndef TASK_HPP
#define TASK_HPP

enum TaskNature = {LOOKUP, COMPARISON};
enum TaskGranularity = {ELEMENTARY, SYNOPTIC};

class AxisLayout;
class TargetConstraintPair;

class Task {
	public:

	private:
		AxisLayout* 				axisLayout;
		std::vector<TargetConstraintPair*>	targetConstraintsPair;
		TaskNature				nature;
		TaskGranularity				granularity;	
	
};




#endif  // TASK_HPP
