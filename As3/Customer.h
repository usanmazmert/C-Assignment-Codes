class Customer {
	public:
		Customer* next;
		double waiting_time;
		double arrival_time;
		double order_time;
		double brew_time;
		double order_price;
		Customer(const double,const double,const double, const double);
		Customer();
		~Customer();
};
