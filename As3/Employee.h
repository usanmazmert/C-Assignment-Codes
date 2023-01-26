#include "Queue.h"
class Employee {
	public:
		Customer* order;
		int id;
		bool is_available;
		double total_time;	
		double busy_time;
		virtual Employee* operator<(Employee*)=0;
		Employee();
		~Employee();
};