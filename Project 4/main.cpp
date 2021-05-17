#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
	//Transaction first = Transaction("VRGO", 10, 02, 2019, true, 150, 10300.14);
	//Transaction second = Transaction("VRGO", 10, 01, 2019, true, 150, 10300.14);
	//std :: cout << first;
	//	if(first < second){
	//		std::cout << "first is first";
	//	}else{
	//		std::cout << "second is first";
	//	}
	History trans_history{};
	trans_history.read_history();

	std::cout << "[Starting history]:" << std::endl;
	trans_history.print();
	trans_history.sort_by_date();

	std::cout << "[Sorted          ]:" << std::endl;
	trans_history.print();

	trans_history.update_acb_cgl();
	trans_history.print();

	std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
	std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

	return 0;
}
#endif
