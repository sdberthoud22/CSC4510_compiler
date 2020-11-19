#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cctype>
#include <cmath>

#include "symbol.h"
#include "error_handler.h"
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "lille_exception.h"

using namespace std;

parser::parser() {
	error = NULL;
	id_tab = NULL;
	scan = NULL;
}

parser::parser(error_handler* e, id_table* id_t, scanner* s) : parser::parser() {
	error = e;
	id_tab = id_t;
	scan = s;
	current_tok = s->get_token();
}

int parser_error_message(symbol::symbol_type s) {
	switch (s) {
	case symbol::identifier:
		return 0;
		break;
	case symbol::strng:
		return 1;
		break;
	case symbol::real_num:
		return 2;
		break;
	case symbol::integer:
		return 3;
		break;
	case symbol::end_of_program:
		return 4;
		break;
	case symbol::semicolon_sym:
		return 5;
		break;
	case symbol::colon_sym:
		return 6;
		break;
	case symbol::comma_sym:
		return 7;
		break;
	case symbol::equals_sym:
		return 8;
		break;
	case symbol::not_equals_sym:
		return 9;
		break;
	case symbol::less_than_sym:
		return 10;
		break;
	case symbol::greater_than_sym:
		return 11;
		break;
	case symbol::less_or_equal_sym:
		return 12;
		break;
	case symbol::greater_or_equal_sym:
		return 13;
		break;
	case symbol::plus_sym:
		return 14;
		break;
	case symbol::minus_sym:
		return 15;
		break;
	case symbol::slash_sym:
		return 16;
		break;
	case symbol::asterisk_sym:
		return 17;
		break;
	case symbol::power_sym:
		return 18;
		break;
	case symbol::ampersand_sym:
		return 19;
		break;
	case symbol::left_paren_sym:
		return 20;
		break;
	case symbol::right_paren_sym:
		return 21;
		break;
	case symbol::range_sym:
		return 22;
		break;
	case symbol::becomes_sym:
		return 23;
		break;
	case symbol::and_sym:
		return 24;
		break;
	case symbol::begin_sym:
		return 25;
		break;
	case symbol::boolean_sym:
		return 26;
		break;
	case symbol::constant_sym:
		return 27;
		break;
	case symbol::else_sym:
		return 28;
		break;
	case symbol::elsif_sym:
		return 29;
		break;
	case symbol::end_sym:
		return 30;
		break;
	case symbol::eof_sym:
		return 31;
		break;
	case symbol::exit_sym:
		return 32;
		break;
	case symbol::false_sym:
		return 33;
		break;
	case symbol::for_sym:
		return 34;
		break;
	case symbol::function_sym:
		return 35;
		break;
	case symbol::if_sym:
		return 36;
		break;
	case symbol::in_sym:
		return 37;
		break;
	case symbol::integer_sym:
		return 38;
		break;
	case symbol::is_sym:
		return 39;
		break;
	case symbol::loop_sym:
		return 40;
		break;
	case symbol::not_sym:
		return 41;
		break;
	case symbol::null_sym:
		return 42;
		break;
	case symbol::odd_sym:
		return 43;
		break;
	case symbol::or_sym:
		return 44;
		break;
	case symbol::pragma_sym:
		return 45;
		break;
	case symbol::procedure_sym:
		return 46;
		break;
	case symbol::program_sym:
		return 47;
		break;
	case symbol::read_sym:
		return 48;
		break;
	case symbol::real_sym:
		return 49;
		break;
	case symbol::ref_sym:
		return 50;
		break;
	case symbol::return_sym:
		return 51;
		break;
	case symbol::reverse_sym:
		return 52;
		break;
	case symbol::string_sym:
		return 53;
		break;
	case symbol::then_sym:
		return 54;
		break;
	case symbol::true_sym:
		return 55;
		break;
	case symbol::value_sym:
		return 56;
		break;
	case symbol::when_sym:
		return 57;
		break;
	case symbol::while_sym:
		return 58;
		break;
	case symbol::write_sym:
		return 59;
		break;
	case symbol::writeln_sym:
		return 60;
		break;
	default:
		throw lille_exception("Unexpected symbol passed to Error_Message inside Scanner.");
		break;
	}
}

void parser::get_token() {
	current_tok = scan->get_token();
}

symbol::symbol_type parser::get_symbol() {
	return current_tok->get_sym();
}

bool parser::have(symbol::symbol_type s) {
	if(get_symbol() == s)
		return true;
	else
		return false;
}

void parser::must_be(symbol::symbol_type s) {
	if(get_symbol() == s)
		get_token();
	else {
		error->flag(current_tok, parser_error_message(s));
		exit(1);
	}

}

void parser::prog() {
	printf("start prog()\n");
	must_be(symbol::program_sym);
	ident();
	must_be(symbol::is_sym);
	block();
	must_be(symbol::semicolon_sym);
	printf("end prog()\n");
}

void parser::block() {
	printf("start block()\n");
	while(!have(symbol::begin_sym)) {
		declaration();
	}

	must_be(symbol::begin_sym);
	statement_list();
	must_be(symbol::end_sym);
	if(!have(symbol::semicolon_sym))
		ident();
	printf("end block()\n");
}

void parser::declaration() {
	printf("start declaration()\n");
	switch(get_symbol()) {
	case symbol::identifier:
		ident_list();
		must_be(symbol::colon_sym);
		if(have(symbol::constant_sym))
			must_be(symbol::constant_sym);
		type();
		if(have(symbol::becomes_sym)) {
			must_be(symbol::becomes_sym);
			if(have(symbol::integer) || have(symbol::real_num))
				number();
			else if(have(symbol::strng))
				string();
			else if(have(symbol::true_sym) || have(symbol::false_sym))
				boolean();
		}
		must_be(symbol::semicolon_sym);
		break;
	case symbol::procedure_sym:
		must_be(symbol::procedure_sym);
		ident();
		if(have(symbol::left_paren_sym)) {
			must_be(symbol::left_paren_sym);
			param_list();
			must_be(symbol::right_paren_sym);
		}
		must_be(symbol::is_sym);
		block();
		must_be(symbol::semicolon_sym);
		break;
	case symbol::function_sym:
		must_be(symbol::function_sym);
		ident();
		if(have(symbol::left_paren_sym)) {
			must_be(symbol::left_paren_sym);
			param_list();
			must_be(symbol::right_paren_sym);
		}
		must_be(symbol::return_sym);
		type();
		must_be(symbol::is_sym);
		block();
		must_be(symbol::semicolon_sym);
		break;
	}
	printf("end declaration()\n");
}

void parser::type() {
	printf("start type()\n");
	switch(get_symbol()) {
	case symbol::integer_sym:
		must_be(symbol::integer_sym);
		break;
	case symbol::real_sym:
		must_be(symbol::real_sym);
		break;
	case symbol::string_sym:
		must_be(symbol::string_sym);
		break;
	case symbol::boolean_sym:
		must_be(symbol::boolean_sym);
		break;
	}
	printf("end type()\n");
}

void parser::param_list() {
	printf("start param_list()\n");
	param();
	while(have(symbol::semicolon_sym)) {
		must_be(symbol::semicolon_sym);
		param();
	}
	printf("end param_list()\n");
}

void parser::param() {
	printf("start param()\n");
	ident_list();
	must_be(symbol::colon_sym);
	param_kind();
	type();
	printf("end param()\n");
}

void parser::ident_list() {
	printf("start ident_list()\n");
	ident();
	while(have(symbol::comma_sym)) {
		must_be(symbol::comma_sym);
		ident();
	}
	printf("end ident_list()\n");
}

void parser::param_kind() {
	printf("start param_kind()\n");
	switch(get_symbol()) {
	case symbol::value_sym:
		must_be(symbol::value_sym);
		break;
	case symbol::ref_sym:
		must_be(symbol::ref_sym);
		break;
	}
	printf("end param_kind()\n");
}

void parser::statement_list() {
	printf("start statement_list()\n");
	statement();
	must_be(symbol::semicolon_sym);
	while(!have(symbol::end_sym) && !have(symbol::elsif_sym) && !have(symbol::else_sym)) {
		statement();
		must_be(symbol::semicolon_sym);
	}
	printf("end statement_list()\n");
}

void parser::statement() {
	printf("start statement()\n");
	if(have(symbol::identifier) || have(symbol::exit_sym) || have(symbol::return_sym) || have(symbol::read_sym) || have(symbol::write_sym) || have(symbol::writeln_sym) || have(symbol::null_sym))
		simple_statement();
	else if(have(symbol::if_sym) || have(symbol::loop_sym) || have(symbol::for_sym) || have(symbol::while_sym))
		compound_statement();
	printf("end statement()\n");
}

void parser::simple_statement() {
	printf("start simple_statement()\n");
	switch(get_symbol()) {
	case symbol::identifier:
		must_be(symbol::identifier);
		if(have(symbol::becomes_sym)) {
			must_be(symbol::becomes_sym);
			expr();
		} else {
			if(have(symbol::left_paren_sym)) {
				must_be(symbol::left_paren_sym);
				expr();
				while(have(symbol::comma_sym)) {
					must_be(symbol::comma_sym);
					expr();
				}
				must_be(symbol::right_paren_sym);
			}
		}
		break;
	case symbol::exit_sym:
		must_be(symbol::exit_sym);
		if(have(symbol::when_sym)) {
			must_be(symbol::when_sym);
			expr();
		}
		break;
	case symbol::return_sym:
		must_be(symbol::return_sym);
		if(!have(symbol::semicolon_sym))
			expr();
		break;
	case symbol::read_sym:
		must_be(symbol::read_sym);
		if(have(symbol::left_paren_sym))
			must_be(symbol::left_paren_sym);
		ident();
		while(have(symbol::comma_sym)) {
			must_be(symbol::comma_sym);
			ident();
		}
		if(have(symbol::right_paren_sym)) 
			must_be(symbol::right_paren_sym);
		break;
	case symbol::write_sym:
		must_be(symbol::write_sym);
		if(have(symbol::left_paren_sym))
			must_be(symbol::left_paren_sym);
		expr();
		while(have(symbol::comma_sym)) {
			must_be(symbol::comma_sym);
			expr();
		}
		if(have(symbol::right_paren_sym)) 
			must_be(symbol::right_paren_sym);
		break;
	case symbol::writeln_sym:
		must_be(symbol::writeln_sym);
		if(have(symbol::left_paren_sym))
			must_be(symbol::left_paren_sym);
		if(!have(symbol::semicolon_sym) && !have(symbol::right_paren_sym)) {
			expr();
			while(have(symbol::comma_sym)) {
				must_be(symbol::comma_sym);
				ident();
			}
		}
		if(have(symbol::right_paren_sym)) 
			must_be(symbol::right_paren_sym);
		break;
	case symbol::null_sym:
		must_be(symbol::null_sym);
		break;
	}
	printf("end simple_statement()\n");
}

void parser::compound_statement() {
	printf("start compound_statement()\n");
	switch(get_symbol()) {
	case symbol::if_sym:
		if_statement();
		break;
	case symbol::loop_sym:
		loop_statement();
		break;
	case symbol::for_sym:
		for_statement();
		break;
	case symbol::while_sym:
		while_statement();
		break;
	}
	printf("end compound_statement()\n");
}

void parser::if_statement() {
	printf("start if_statement()\n");
	must_be(symbol::if_sym);
	expr();
	must_be(symbol::then_sym);
	statement_list();
	while(have(symbol::elsif_sym)) {
		must_be(symbol::elsif_sym);
		expr();
		must_be(symbol::then_sym);
		statement_list();
	}
	if(have(symbol::else_sym)) {
		must_be(symbol::else_sym);
		statement_list();
	}
	must_be(symbol::end_sym);
	must_be(symbol::if_sym);
	printf("end if_statement()\n");
}

void parser::while_statement() {
	printf("start while_statement()\n");
	must_be(symbol::while_sym);
	expr();
	loop_statement();
	printf("end while_statement()\n");
}

void parser::for_statement() {
	printf("start for_statement()\n");
	must_be(symbol::for_sym);
	ident();
	must_be(symbol::in_sym);
	if (have(symbol::reverse_sym))
		must_be(symbol::reverse_sym);
	range();
	loop_statement();
	printf("end for_statement()\n");
}

void parser::loop_statement() {
	printf("start loop_statement()\n");
	must_be(symbol::loop_sym);
	statement_list();
	must_be(symbol::end_sym);
	must_be(symbol::loop_sym);
	printf("end loop_statement()\n");
}

void parser::range() {
	printf("start range()\n");
	simple_expr();
	must_be(symbol::range_sym);
	simple_expr();
	printf("end range()\n");
}

void parser::expr() {
	printf("start expr()\n");
	simple_expr();
	if(have(symbol::in_sym)) {
		must_be(symbol::in_sym);
		range();
	} else {
		if(have(symbol::greater_than_sym) || have(symbol::less_than_sym) || have(symbol::equals_sym) || have(symbol::not_equals_sym) || have(symbol::less_or_equal_sym) || have(symbol::greater_or_equal_sym)) {
			relop();
			simple_expr();
		}
	}
	printf("end expr()\n");
}

void parser::boolean() {
	printf("start boolean()\n");
	switch(get_symbol()) {
	case symbol::true_sym:
		must_be(symbol::true_sym);
		break;
	case symbol::false_sym:
		must_be(symbol::false_sym);
		break;
	}
	printf("end boolean()\n");
}

void parser::relop() {
	printf("start relop()\n");
	switch(get_symbol()) {
	case symbol::greater_than_sym:
		must_be(symbol::greater_than_sym);
		break;
	case symbol::less_than_sym:
		must_be(symbol::less_than_sym);
		break;
	case symbol::equals_sym:
		must_be(symbol::equals_sym);
		break;
	case symbol::not_equals_sym:
		must_be(symbol::not_equals_sym);
		break;
	case symbol::less_or_equal_sym:
		must_be(symbol::less_or_equal_sym);
		break;
	case symbol::greater_or_equal_sym:
		must_be(symbol::greater_or_equal_sym);
		break;
	}
	printf("end relop()\n");
}

void parser::simple_expr() {
	printf("start simple_expr()\n");
	expr2();
	while(have(symbol::ampersand_sym)) {
		stringop();
		expr2();
	}
	printf("end simple_expr()\n");
}

void parser::stringop() {
	printf("start stringop()\n");
	must_be(symbol::ampersand_sym);
	printf("end stringop()\n");
}

void parser::expr2() {
	printf("start expr2()\n");
	term();
	while(have(symbol::plus_sym) || have(symbol::minus_sym) || have(symbol::or_sym)) {
		if(have(symbol::plus_sym) || have(symbol::minus_sym))
			addop();
		else if(have(symbol::or_sym))
			must_be(symbol::or_sym);
		term();
	}
	printf("end expr2()\n");
}

void parser::addop() {
	printf("start addop()\n");
	switch(get_symbol()) {
	case symbol::plus_sym:
		must_be(symbol::plus_sym);
		break;
	case symbol::minus_sym:
		must_be(symbol::minus_sym);
		break;
	}
	printf("end addop()\n");
}

void parser::term() {
	printf("start term()\n");
	factor();
	while(have(symbol::asterisk_sym) || have(symbol::slash_sym) || have(symbol::and_sym)) {
		if(have(symbol::asterisk_sym) || have(symbol::slash_sym))
			multop();
		else if(have(symbol::and_sym))
			must_be(symbol::and_sym);
		factor();
	}
	printf("end term()\n");
}

void parser::multop() {
	printf("start multop()\n");
	switch(get_symbol()) {
	case symbol::asterisk_sym:
		must_be(symbol::asterisk_sym);
		break;
	case symbol::slash_sym:
		must_be(symbol::slash_sym);
		break;
	}
	printf("end multop()\n");
}

void parser::factor() {
	printf("start factor()\n");
	bool factor1 = false;
	if(have(symbol::plus_sym) || have(symbol::minus_sym)) {
		addop();
		factor1 = true;
	}
	primary();
	if(have(symbol::power_sym) && !factor1) {
		must_be(symbol::power_sym);
		primary();
	}
	printf("end factor()\n");
}

void parser::primary() {
	printf("start primary()\n");
	switch(get_symbol()) {
	case symbol::not_sym:
		must_be(symbol::not_sym);
		expr();
		break;
	case symbol::odd_sym:
		must_be(symbol::odd_sym);
		expr();
		break;
	case symbol::left_paren_sym:
		must_be(symbol::left_paren_sym);
		simple_expr();
		must_be(symbol::right_paren_sym);
	case symbol::identifier:
		ident();
		if(have(symbol::left_paren_sym)) {
			must_be(symbol::left_paren_sym);
			expr();
			while(have(symbol::comma_sym)) {
				must_be(symbol::comma_sym);
				expr();
			}
			must_be(symbol::right_paren_sym);
		}
		break;
	case symbol::integer:
		number();
		break;
	case symbol::real_num:
		number();
		break;
	case symbol::strng:
		string();
		break;
	case symbol::boolean_sym:
		boolean();
		break;
	}
	printf("end primary()\n");
}

void parser::string() {
	printf("start string()\n");
	must_be(symbol::strng);
	printf("end string()\n");
}

void parser::ident() {
	printf("start ident()\n");
	must_be(symbol::identifier);
	printf("end ident()\n");
}

void parser::number() {
	printf("start number()\n");
	switch(get_symbol()) {
	case symbol::integer:
		must_be(symbol::integer);
		break;
	case symbol::real_num:
		must_be(symbol::real_num);
		break;
	}
	printf("end number()\n");
}

void parser::pragma() {
	printf("start pragma()\n");
	must_be(symbol::pragma_sym);
	ident();
	if(have(symbol::left_paren_sym)) {
		must_be(symbol::left_paren_sym);
		if(have(symbol::integer))
			number();
		if(have(symbol::identifier))
			ident();
	}
	printf("end pragma()\n");
}

void parser::parse() {
	prog();
	if(have(symbol::end_of_program))
		printf("COMPLETE\n");
}