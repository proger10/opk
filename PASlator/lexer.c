#include "lexer.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "d_str.h"
#include <ctype.h>

Lexer *lex_create(Stream *in_stream){
	Lexer *result = malloc(sizeof(Lexer));
	if (result == NULL)
		return result;
	result->inp = in_stream;
	result->state = ST_SEP;
	return result;
}

static int lowercase(int a){
	if ((a >= 'A') && (a <= 'Z'))
		return a - 'A' + 'a';
	return a;
}

static int is_az(int a){
	return ((a >= 'a') && (a <= 'z'));
}

static int is_09(int a){
	return ((a >= '0') && (a <= '9'));
}

static int is_space(int a){
	return (isspace(a) || (a==EOF));
}

Lex *lex_next(Lexer *lexer){
	String *str = str_create();
	int ret = 0;

	while (!ret) {
		int c = stream_next(lexer->inp);
		c = lowercase(c);
		
		if (c == EOF){
			ret = 1;
		}

		switch (lexer->state){
		//Starting
		case ST_SEP:
			if (is_az(c)){
				lexer->state = ST_WORD;
				break;
			}
			if (is_space(c))
				lexer->state = ST_SEP;
			break;

		//Word state
		case ST_WORD:
			if (is_az(c) || is_09(c)){
				break;
			}
			if (is_space(c))
				lexer->state = ST_SEP;
			break;
		default:
			state = ST_ERROR;
			lex_type = LEX_UNKNOWN;
			break;
		}
		if (state != ST_ERROR){
			str_add(str, c);
			stream_read(lexer->inp);
		}
	}


	Lex *result = NULL;
	if (lex_type != LEX_NO){
		result = malloc(sizeof(Lex));
		if (result == NULL)
			return NULL;
		else{
			switch (lex_type){
			case LEX_WORD:
				result->type = LEX_WORD;
				result->value = str->str;
				free(str);//todo
				break;
			default:
				result->type = LEX_UNKNOWN;
				result->value = NULL;
				break;
			}
		}
	}
	return result;
}

void lex_free(Lex *lex){
	if (lex == NULL)
		return;
	free(lex->value);
	free(lex);
}

void lex_destroy(Lexer *lexer){
	free(lexer);
}
