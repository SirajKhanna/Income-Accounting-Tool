//Written by Siraj Khanna
#ifndef _HISTORY_TRANSACTION_CPP_
#define _HISTORY_TRANSACTION_CPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////

// Constructor
Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,
		unsigned int month_date,  unsigned year_date,
		bool buy_sell_trans,  unsigned int number_shares,
		double trans_amount ){
	acb = 0.0;
	acb_per_share = 0.0;
	share_balance = 0;
	cgl = 0.0;
	day = day_date;
	month = month_date;
	year = year_date;
	shares = number_shares;
	amount = trans_amount;
	symbol = ticker_symbol;
	if(buy_sell_trans == true){
		trans_type = "Buy";
	}else{
		trans_type = "Sell";
	}

	trans_id = assigned_trans_id;
	assigned_trans_id++;
	p_next = nullptr;
}

// Destructor
Transaction::~Transaction(){

}

// Overloaded < operator
bool Transaction::operator<(Transaction const &other){
	bool is_true{false};
	if (this ->year < other.year){

		is_true = true;

	}else{
		if(this->year == other.year){
			if(this ->month < other.month){
				is_true = true;
			}else{
				if(this ->month == other.month){
					if(this ->day < other.day){
						is_true = true;
					}
				}
			}
		}
	}
	return is_true;
}
// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << std::setw(4) << get_trans_id() << " "
			<< std::setw(4) << get_symbol() << " "
			<< std::setw(4) << get_day() << " "
			<< std::setw(4) << get_month() << " "
			<< std::setw(4) << get_year() << " ";


	if ( get_trans_type() ) {
		std::cout << "  Buy  ";
	} else { std::cout << "  Sell "; }

	std::cout << std::setw(4) << get_shares() << " "
			<< std::setw(10) << get_amount() << " "
			<< std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
			<< std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
			<< std::setw(10) << std::setprecision(3) << get_cgl()
			<< std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
History::History(){
	p_head = nullptr;
}

// Destructor
History::~History(){
	Transaction *p_temp = p_head;
	while(p_temp != nullptr){
		p_temp = p_temp->get_next(); //use this
		delete p_head;
		p_head = p_temp;
		//p_temp = p_temp->get_next(); //gets a stackdump
	}
}

// read_transaction(...): Read the transaction history from file.
//use the provided ece150::____ to read the elements of the file and assign to the private member variables in Transaction.hpp
void History::read_history(){
	ece150::open_file();

	while(ece150::next_trans_entry() == true){

		Transaction *new_transaction = new Transaction{
			ece150::get_trans_symbol(),
					ece150::get_trans_day(),
					ece150::get_trans_month(),
					ece150::get_trans_year(),
					ece150::get_trans_type(),
					ece150::get_trans_shares(),
					ece150::get_trans_amount()};

		//	std::cout << "before insert" << std::endl;
		History::insert(new_transaction);

	}
	//	std::cout << "end of while" << std::endl;
	ece150::close_file();

}
// insert(...): Insert transaction into linked list.
void History::insert(Transaction *p_new_trans){
	//empty case
	//std::cout << "inside insert" << std::endl;
	if(p_head == nullptr){
		//	std::cout << "inside if" << std::endl;
		p_head = p_new_trans;

	}else{
		//all other cases
		//std::cout << "inside else" << std::endl;
		Transaction *p_temp = p_head;

		while(p_temp ->get_next() != nullptr){
			//	std::cout << "inside while" << std::endl;
			//			p_temp -> print();
			p_temp = p_temp ->get_next();
		}
		//		std::cout << std::endl;
		//		std::cout <<"p_temp" << p_temp << std::endl;
		//		std::cout <<"ptemp next" <<p_temp->get_next() << std::endl;
		//		p_temp -> print();
		p_temp->set_next(p_new_trans);
		//		std::cout << "ptemp get_next" << p_temp->get_next() << std::endl;
		//		std::cout << "ptemp symbol" << p_temp->get_symbol() << std::endl;
		//		p_temp->get_next()->print();

	}

}

// sort_by_date(): Sort the linked list by trade date.
void History::sort_by_date(){
	if (this ->p_head == nullptr || this ->p_head->get_next() == nullptr){
		return;
	}else{
		//create new list
		Transaction *p_head_sorted{nullptr};
		//		Transaction *p_trans_move{p_head};
		//		this->p_head = this->p_head->get_next();
		//		p_trans_move->set_next(nullptr);

		//p_head_sorted = p_trans_move;

		while(this ->p_head != nullptr){
			//remove node from original list

			Transaction *p_trans_move{p_head};
			this->p_head = this->p_head->get_next();
			p_trans_move->set_next(nullptr);

			//insert at the top
			if(p_head_sorted == nullptr){
				p_head_sorted = p_trans_move;

			}else if (*p_trans_move < *p_head_sorted){
				p_trans_move ->set_next(p_head_sorted);
				p_head_sorted = p_trans_move;
			}else{
				//insert somewhere in the middle


				Transaction *p_prev{nullptr};
				Transaction *p_traverse{p_head_sorted};

				while(p_traverse != nullptr){
					if(!(*p_traverse < *p_trans_move)){

						p_prev->set_next(p_trans_move);
						p_trans_move->set_next(p_traverse);
						break;
					}

					p_prev = p_traverse;
					p_traverse = p_traverse->get_next();
				}

				//insert at end of list
				if(p_traverse == nullptr){

					//p_traverse = p_trans_move;
					p_prev->set_next(p_trans_move);
				}
			}
		}
		p_head = p_head_sorted;
	}
	//p_head = p_head_sorted;
}

// update_acb_cgl(): Updates the ACB and CGL values.
void History::update_acb_cgl(){
	//acb, share balance, acb per share, cgl
	//set variables to hold each thing, if you use acb etc. directly it might get messed up
	//just run through project description for these 4 calculations
	double hold_acb = 0.0;
	unsigned int hold_share_balance = 0;
	double hold_acb_shares = 0.0;
	double hold_cgl = 0.0;
	double previous_acb = 0.0;
	Transaction *p_temp = p_head;

	while(p_temp != nullptr){

		if(p_temp ->get_trans_type() == true){ //it is a buy here

			hold_acb += p_temp->get_amount();
			hold_share_balance += p_temp->get_shares();
			hold_acb_shares = p_temp->get_acb() / p_temp->get_share_balance();
			//dont compute cgl for a buy

		}else{ //its a sell here

			hold_acb = previous_acb - (p_temp->get_shares() * hold_acb_shares);
			hold_share_balance -= p_temp->get_shares();
			hold_acb_shares = p_temp->get_acb() / p_temp->get_share_balance();
			hold_cgl = p_temp->get_amount() - (p_temp->get_shares() * hold_acb_shares);
		}

		previous_acb = hold_acb;

		p_temp->set_acb(hold_acb);
		p_temp->set_share_balance(hold_share_balance);
		p_temp->set_acb_per_share(hold_acb_shares);
		p_temp->set_cgl(hold_cgl);

		p_temp = p_temp->get_next();
	}
}

// compute_cgl(): )Compute the ACB, and CGL.
double History::compute_cgl(unsigned int year){
	Transaction *p_temp = p_head;
	double hold_cgl = 0.0;

	while(p_temp != nullptr){
		//runs through the list, now see if assigned year is the p_temp->get_year()

		if(year == p_temp->get_year()){
			//update hold_cgl

			hold_cgl += p_temp->get_cgl();
		}

		p_temp = p_temp->get_next();
	}

	return hold_cgl;
}

// print() Print the transaction history.
void History::print(){
	//include the ==start== at the start and ==end== at the end
	Transaction *p_next_print{p_head};
	//	unsigned int id_to_print = 0;

	std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;

	while(p_next_print != nullptr){

		p_next_print -> print();
		//	std::cout << *p_next_print << std::endl;// -----> prints addresses

		p_next_print = p_next_print -> get_next();
	}
	std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}
//}

// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }


#endif
