#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <string>

#include "symbol.h"
#include "token.h"
#include "error_handler.h"
#include "id_table.h"
#include "scanner.h"

using namespace std;

class parser {
private:
	error_handler* error;
	id_table* id_tab;
	scanner* scan;
	token* current_tok;

	parser();

	void prog();
	void block();
	void declaration();
	void type();
	void param_list();
	void param();
	void ident_list();
	void param_kind();
	void statement_list();
	void statement();
	void simple_statement();
	void compound_statement();
	void if_statement();
	void while_statement();
	void for_statement();
	void loop_statement();
	void range();
	void expr();
	void boolean();
	void relop();
	void simple_expr();
	void stringop();
	void expr2();
	void addop();
	void term();
	void multop();
	void factor();
	void primary();
	void string();
	void ident();
	void number();
	void pragma();
	void get_token();


public:
	void parse();
	symbol::symbol_type get_symbol();
	bool have(symbol::symbol_type s);
	void must_be(symbol::symbol_type s);

	parser(error_handler* e, id_table* id_t, scanner* s);
};

#endif