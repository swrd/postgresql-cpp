/*-------------------------------------------------------------------------
 *
 * parse_oper.h
 *		handle operator__ things for parser
 *
 *
 * Portions Copyright (c) 1996-2015, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/parser/parse_oper.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef PARSE_OPER_H
#define PARSE_OPER_H

#include "access/htup.h"
#include "parser/parse_node.h"


typedef HeapTuple operator__;

/* Routines to look up an operator__ given name and exact input type(s) */
extern Oid LookupOperName(ParseState *pstate, List *opername,
			   Oid oprleft, Oid oprright,
			   bool noError, int location);
extern Oid LookupOperNameTypeNames(ParseState *pstate, List *opername,
						typename__ *oprleft, typename__ *oprright,
						bool noError, int location);

/* Routines to find operators matching a name and given input types */
/* NB: the selected operator__ may require coercion of the input types! */
extern operator__ oper(ParseState *pstate, List *op, Oid arg1, Oid arg2,
	 bool noError, int location);
extern operator__ right_oper(ParseState *pstate, List *op, Oid arg,
		   bool noError, int location);
extern operator__ left_oper(ParseState *pstate, List *op, Oid arg,
		  bool noError, int location);

/* Routines to find operators that DO NOT require coercion --- ie, their */
/* input types are either exactly as given, or binary-compatible */
extern operator__ compatible_oper(ParseState *pstate, List *op,
				Oid arg1, Oid arg2,
				bool noError, int location);

/* currently no need for compatible_left_oper/compatible_right_oper */

/* Routines for identifying "<", "=", ">" operators for a type */
extern void get_sort_group_operators(Oid argtype,
						 bool needLT, bool needEQ, bool needGT,
						 Oid *ltOpr, Oid *eqOpr, Oid *gtOpr,
						 bool *isHashable);

/* Convenience routines for common calls on the above */
extern Oid	compatible_oper_opid(List *op, Oid arg1, Oid arg2, bool noError);

/* Extract operator__ OID or underlying-function OID from an operator__ tuple */
extern Oid	oprid(operator__ op);
extern Oid	oprfuncid(operator__ op);

/* Build expression tree for an operator__ invocation */
extern Expr *make_op(ParseState *pstate, List *opname,
		Node *ltree, Node *rtree, int location);
extern Expr *make_scalar_array_op(ParseState *pstate, List *opname,
					 bool useOr,
					 Node *ltree, Node *rtree, int location);

#endif   /* PARSE_OPER_H */