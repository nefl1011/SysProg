#ifndef NODETYPE_H_
#define NODETYPE_H_

enum NodeType {
	NO_TYPE,
	INT,
	INT_ARRAY,
	WRITE,
	NODE_ERROR,
	OP_PLUS_TYPE,
	OP_MINUS_TYPE,
	OP_MULT_TYPE,
	OP_COL_TYPE,
	OP_SMALLER_TYPE,
	OP_GREATER_TYPE,
	OP_EQUAL_TYPE,
	OP_SPECIAL_TYPE,
	OP_AND_TYPE
};

#endif /* NODETYPE_H_ */
