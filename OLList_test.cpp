/*
* @Author: bing Jiao
* @Date:   2017-11-29 14:51:42
* @Last Modified by:   bing Jiao
* @Last Modified time: 2017-12-02 21:26:43
*/

#include "OLList.h"

void TEST_print_null(){
	printf("#### TEST_print_null:\n");
	OLList ot;
	ot.visit();
	printf("\n");
}

void TEST_add_one(){
	printf("#### TEST_add_seq:\n");
	OLList ot;
	NInfo info("aaa");
	ot.add(13, 123, &info);
	ot.visit();
	printf("\n");	
}

void TEST_add_two_seq(){
	printf("#### TEST_add_seq:\n");
	OLList ot;
	NInfo info("aaa");
	ot.add(13, 123, &info);
	ot.add(200, 300, &info);
	ot.visit();
	printf("\n");	
}

void TEST_add_all_seq(){
	printf("#### TEST_add_seq:\n");
	OLList ot;
	NInfo info("aaa");
	for(int i = 0; i < 10; ++i){
		ot.add(i, i + 1, &info);
	}
	ot.visit();
	printf("\n");
}

void TEST_add_two_ol_type1(){
	printf("#### TEST_add_two_ol_type1: [10,20) + [5,15)\n");
	OLList ot;
	NInfo info1("aaa");
	NInfo info2("bbb");
	ot.add(10, 20, &info1);
	ot.add(5, 15, &info2);
	ot.visit();
	printf("\n");	
}

void TEST_add_two_ol_type2(){
	printf("#### TEST_add_two_ol_type2: [10,20) + [15,25)\n");
	OLList ot;
	NInfo info1("aaa");
	NInfo info2("bbb");
	ot.add(10, 20, &info1);
	ot.add(15, 25, &info2);
	ot.visit();
	printf("\n");	
}

void TEST_add_two_ol_type3(){
	printf("#### TEST_add_two_ol_type3: [10,20) + [15,20)\n");
	OLList ot;
	NInfo info1("aaa");
	NInfo info2("bbb");
	ot.add(10, 20, &info1);
	ot.add(15, 20, &info2);
	ot.visit();
	printf("\n");	
}

void TEST_add_two_ol_type4(){
	printf("#### TEST_add_two_ol_type4: [10,20) + [9,21)\n");
	OLList ot;
	NInfo info1("aaa");
	NInfo info2("bbb");
	ot.add(10, 20, &info1);
	ot.add(9, 21, &info2);
	ot.visit();
	printf("\n");	
}


void TEST_add_two_ol_num(int N){
	printf("#### TEST_add_two_ol_num: %d\n", N);
	OLList ot;
	for(int i = 0; i < N; ++i){
		std::string str = std::to_string(((size_t)rand())*((size_t)rand()));
		int x = (((int)rand()) * ((int)rand())) % 10000;
		int y = x + abs((((int)rand()) * ((int)rand())) % 10000);
		NInfo *info = new NInfo(str);
		ot.add(x, y, info);
	}
	ot.visit();
	printf("\n");
}

///////////////////// No Overlapping ///////////////
void NO_type1(){
	printf("#### NO_type1\n");
	OLList ot;
	NInfo *info1 = new NInfo("aaaa");
	NInfo *info2 = new NInfo("bbbb");
	NInfo *info3 = new NInfo("cccc");
	ot.add(10, 20, info1);
	ot.add(1, 5, info2);
	ot.add(5, 10, info3);
	ot.visit();
	printf("\n");	
}

void NO_type2(){
	printf("#### NO_type2\n");
	OLList ot;
	NInfo *info1 = new NInfo("aaaa");
	NInfo *info2 = new NInfo("bbbb");
	NInfo *info3 = new NInfo("cccc");
	ot.add(10, 20, info1);
	ot.add(34, 55, info2);
	ot.add(20, 34, info3);
	ot.visit();
	printf("\n");	
}

///////////////////// OverLapping ///////////////
void OV_type1(){
	printf("#### OV_type1\n");
	OLList ot;
	NInfo *info1 = new NInfo("aaaa");
	NInfo *info2 = new NInfo("bbbb");
	NInfo *info3 = new NInfo("cccc");
	ot.add(10, 20, info1);
	ot.add( 5, 15, info2);
	// ot.add( 1,  6, info3);
	ot.visit();
	printf("\n");		
}

int main(int argc, char const *argv[])
{
	// int N;
	// if(argc < 2){
	// 	printf("usage: %s --N=<int>\n", argv[0]);
	// 	exit(1);
	// }else{
	// 	char junk;
	// 	if(sscanf(argv[1], "--N=%d%c", &N, &junk) == 1){
	// 		if(N < 1 || N > 1000){
	// 			printf("N should be a positive number and no more than 1000\n");
	// 			printf("Your set --N=%d\n", N);
	// 			exit(1);
	// 		}				
	// 	}else{
	// 		printf("usage: %s --N=<int>\n", argv[0]);
	// 		exit(1);
	// 	}
	// }
	

	// NULL;
	// TEST_print_null();

	// no overlapping;
	// NO_type1();
	// NO_type2();

	// overlapping;
	OV_type1();
	
	
	// TEST_add_two_ol_num(N);

	return 0;
}