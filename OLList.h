/*
* @Author: bing Jiao
* @Date:   2017-11-28 14:46:46
* @Last Modified by:   bing Jiao
* @Last Modified time: 2017-11-28 15:39:33
*/

#ifndef BING16_OVER_LAPPING_LIST_H_
#define BING16_OVER_LAPPING_LIST_H_ 

#include <stdio.h>
#include <vector>
#include <string>

// ASSERT x is Not a Negative Number (x >= 0)
#define ASSERT_NN(x)			\
		do{						\
			if(x < 0){			\
				fprintf(stderr, "ASSERT_NN: %d is a negative number!\n", x);	\
				fflush(stderr);	\
				exit(1);		\
			}					\
		}while(0);

// ASSERT x is a Positive Number (x > 0)
#define ASSERT_PN(x)			\
		do{						\
			if(x <= 0){			\
				fprintf(stderr, "ASSERT_PN: %d is not a positive number!\n", x);	\
				fflush(stderr);	\
				exit(1);		\
			}					\
		}while(0);

// ASSERT x is Not Zero (x != 0)
#define ASSERT_NZ(x)			\
		do{						\
			if(x == 0){			\
				fprintf(stderr, "ASSERT_NZ: %d is zero!\n", x);	\
				fflush(stderr);	\
				exit(1);		\
			}					\
		}while(0);

// ASSERT x is Not nuLL (x != NULL)
#define ASSERT_NL(x)			\
		do{						\
			if(x == NULL){			\
				fprintf(stderr, "ASSERT_NL: %d is NULL!\n", x);	\
				fflush(stderr);	\
				exit(1);		\
			}					\
		}while(0);

// ASSERT x is Less Than y (x < y)
#define ASSERT_LT(x, y)			\
		do{						\
			if(x >= y){			\
				fprintf(stderr, "ASSERT_LT: %d is not less than %d!\n", x, y);	\
				fflush(stderr);	\
				exit(1);		\
			}					\
		}while(0);

// ASSERT x is Equal to y (x == y)
#define ASSERT_EQ(x, y)			\
		do{						\
			if(x >= y){			\
				fprintf(stderr, "ASSERT_EQ: %d is not equal to %d!\n", x, y);	\
				fflush(stderr);	\
				exit(1);		\
			}					\
		}while(0);

// ASSERT de is BeTween x and y (x < de < y)
#define ASSERT_BT(x, y, de)		\
		do{						\
			if(!(x < de && de < y)){			\
				fprintf(stderr, "ASSERT_BT: %d is not between %d and %d!\n", de, x, y);	\
				fflush(stderr);	\
				exit(1);		\
			}					\
		}while(0);		

#define NUMBER_BT(x, y, de)		(x < de && de < y);

class NInfo
{
public:
	NInfo();
	NInfo(std::string);
	void add(NInfo*);
	void add(std::string);
	std::vector<std::string>::iterator begin();
	std::vector<std::string>::iterator end();
	size_t size();
	void visit();

private:
	std::vector<std::string> info_vc_;
};

class OLLNode
{
public:
	int x_;				// [start, end);
	int y_;				// x must be less than y;
	OLLNode *prev_;		// 
	OLLNode *next_;		// 
	NInfo   *info_;		// infomation;

public:
	OLLNode();
	OLLNode(int x, int y);
	OLLNode(int x, int y, NInfo *info);
	~OLLNode();

	int insert(OLLNode *node);
	int add_info(NInfo *info);
	int split(int de);
	int fission(int de);

// for debug;
public:
	void visit();
};

class OLList
{
public:
	OLList();
	~OLList();
	int add(int x, int y, NInfo *info);
	int add(int x, int y, std::string info);
	int get_num();
	int get_infos();

private:
	OLLNode 	header_;
	int 		noi_;		// number of infomations;
	int 		num_;		// number of nodes;

// for debug;
public:
	void visit();
};

#endif