/*
* @Author: bing Jiao
* @Date:   2017-11-29 14:51:42
* @Last Modified by:   bing Jiao
* @Last Modified time: 2017-12-03 19:48:17
*/

#include "OLList.h"

///////////////////// NULL ///////////////
void TEST_print_null(){
	printf("#### TEST_print_null:\n");
	OLList ot;
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
	ot.add( 1,  6, info3);
	ot.visit();
	printf("\n");		
}

void OV_type2(){
	printf("#### OV_type2\n");
	OLList ot;
	NInfo *info1 = new NInfo("aaaa");
	NInfo *info2 = new NInfo("bbbb");
	NInfo *info3 = new NInfo("cccc");
	ot.add(10, 20, info1);
	ot.add(15, 25, info2);
	ot.add(24, 26, info3);
	ot.visit();
	printf("\n");		
}

void OV_type3(){
	printf("#### OV_type3\n");
	OLList ot;
	NInfo *info1 = new NInfo("aaaa");
	NInfo *info2 = new NInfo("bbbb");
	NInfo *info3 = new NInfo("cccc");
	ot.add(10, 20, info1);
	ot.add(13, 19, info2);
	ot.add(13, 20, info3);
	ot.visit();
	printf("\n");		
}

void OV_type4(){
	printf("#### OV_type4\n");
	OLList ot;
	NInfo *info1 = new NInfo("aaaa");
	NInfo *info2 = new NInfo("bbbb");
	NInfo *info3 = new NInfo("cccc");
	ot.add(10, 20, info1);
	ot.add( 5, 25, info2);
	ot.add(13, 20, info3);
	ot.visit();
	printf("\n");		
}

///////////////////// seq (No Overlapping) ///////////////
void TEST_seq(int N){
	printf("#### TEST_seq: %d\n", N);
	OLList ot;
	char *buf;
	buf = (char*)malloc(99);
	for(int i = 0; i < N; ++i){
		sprintf(buf, "seq-%04d", i+1);
		int x = i+1;
		int y = i+2;
		NInfo *info = new NInfo(buf);
		ot.add(x, y, info);
	}
	ot.visit();
	printf("\n");
	free(buf);
}

///////////////////// random (Overlapping) ///////////////
void TEST_random(int N){
	printf("#### TEST_random: %d\n", N);
	OLList ot;
	char *buf;
	buf = (char*)malloc(99);
	for(int i = 0; i < N; ++i){
		sprintf(buf, "seq-%04d", i+1);
		// std::string str = std::to_string(((size_t)rand())*((size_t)rand()));
		int x = abs(((int)rand()) * ((int)rand())) % 10000;
		int y = x + abs((((int)rand()) * ((int)rand())) % 10000);
		NInfo *info = new NInfo(buf);
		ot.add(x, y, info);
	}
	ot.visit();
	printf("\n");
	free(buf);
}

///////////////////// error argv ///////////////
void err_usage(const char *cmd){
	printf("usage: %s --type=<int>(1:seq; 2:random) --num=<int>([1-999])\n", cmd);
	exit(1);	
}

int main(int argc, char const *argv[])
{
	int N, type;
	if(argc < 3){
		err_usage(argv[0]);
	}else{
		char junk;
		if(sscanf(argv[1], "--type=%d%c", &type, &junk) == 1){
			if(!(type==1 || type==2)){
				err_usage(argv[0]);
			}
		}else{
			err_usage(argv[0]);
		}
		if(sscanf(argv[2], "--num=%d%c", &N, &junk) == 1){
			if(N < 1 || N >= 1000){
				err_usage(argv[0]);
			}				
		}else{
			err_usage(argv[0]);
		}
	}	

	// NULL;
	// TEST_print_null();

	// no overlapping;
	// NO_type1();
	// NO_type2();

	// overlapping;
	// OV_type1();
	// OV_type2();
	// OV_type3();
	// OV_type4();
	
	if(type == 1){
		TEST_seq(N);
	}else if(type ==2){
		TEST_random(N);
	}
	
	return 0;
}