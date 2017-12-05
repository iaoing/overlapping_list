/*
* @Author: bing Jiao
* @Date:   2017-11-29 14:51:42
* @Last Modified by:   bing Jiao
* @Last Modified time: 2017-12-05 18:53:04
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
		int x = i*2+1;
		int y = i*2+2;
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
		// printf("[%5d, %5d]\n", x, y);
	}
	ot.visit();
	printf("\n");
	free(buf);
}

///////////////////// query seq one ///////////////
void TEST_query_seq_one(int N){
	printf("#### TEST_query_seq_one: %d\n", N);
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
	free(buf);

	// query;
	OLLNode *target;
	int query_count = 10;
	for(int i = 0; i < query_count; ++i){
		int x = abs(((int)rand()) * ((int)rand())) % (2*N);
		target = ot.retrive_info(x);
		if(target == NULL){
			printf("%5d is not in this list.\n", x);
		}else{
			printf("%5d is founded! OLLNode's range: [%5d, %5d]; NInfo's size: %d\n", x, target->x_, target->y_, target->info_->size());
			// target->visit();
			// printf("\n\n");
		}
	}	
}

///////////////////// query seq range ///////////////
void TEST_query_seq_range(int N){
	printf("#### TEST_query_seq_range: %d\n", N);
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
	free(buf);

	// query;
	int query_count = 10;
	std::vector<OLLNode*> target;
	for(int i = 0; i < query_count; ++i){
		int x = abs(((int)rand()) * ((int)rand())) % (2*N);
		int y = x + abs(((int)rand()) * ((int)rand())) % (N/10) + 1;
		// int x = 1;
		// int y = 20;
		target = ot.retrive_info(x, y);
		if(target.empty()){
			printf("[%5d, %5d] is not in this list.\n", x, y);
		}else{
			printf("[%5d, %5d] is founded! Target's size: %d\n", x, y, target.size());
			for (int i = 0; i < target.size(); ++i)
			{
				printf("[%5d, %5d]: %3d; ", target[i]->x_, target[i]->y_, target[i]->info_->size());
			}
			printf("\n\n");
		}
	}	
}

///////////////////// query random one ///////////////
void TEST_query_random_one(int N){
	printf("#### TEST_query_random_one: %d\n", N);
	OLList ot;
	char *buf;
	buf = (char*)malloc(99);
	for(int i = 0; i < N; ++i){
		sprintf(buf, "seq-%04d", i+1);
		int x = abs(((int)rand()) * ((int)rand())) % 10000;
		int y = x + abs((((int)rand()) * ((int)rand())) % 10000);
		NInfo *info = new NInfo(buf);
		ot.add(x, y, info);
	}	
	free(buf);

	// query;
	OLLNode *target;
	int query_count = 10;
	for(int i = 0; i < query_count; ++i){
		int x = abs(((int)rand()) * ((int)rand())) % 10000;
		target = ot.retrive_info(x);
		if(target == NULL){
			printf("%5d is not in this list.\n", x);
		}else{
			printf("%5d is founded! OLLNode's range: [%5d, %5d]; NInfo's size: %d\n", x, target->x_, target->y_, target->info_->size());
			// target->visit();
			printf("\n\n");
		}
	}	
}

///////////////////// query random range ///////////////
void TEST_query_random_range(int N){
	printf("#### TEST_query_random_range: %d\n", N);
	OLList ot;
	char *buf;
	buf = (char*)malloc(99);
	for(int i = 0; i < N; ++i){
		sprintf(buf, "seq-%04d", i+1);
		int x = abs(((int)rand()) * ((int)rand())) % 10000;
		int y = x + abs((((int)rand()) * ((int)rand())) % 10000);
		NInfo *info = new NInfo(buf);
		ot.add(x, y, info);
	}	
	free(buf);

	// query;
	int query_count = 10;
	std::vector<OLLNode*> target;
	for(int i = 0; i < query_count; ++i){
		int x = abs(((int)rand()) * ((int)rand())) % 10000;
		int y = x + abs((((int)rand()) * ((int)rand())) % 100);
		target = ot.retrive_info(x, y);
		if(target.empty()){
			printf("[%5d, %5d] is not in this list.\n", x, y);
		}else{
			printf("[%5d, %5d] is founded! Target's size: %d\n", x, y, target.size());
			for (int i = 0; i < target.size(); ++i)
			{
				printf("[%5d, %5d]: %3d; ", target[i]->x_, target[i]->y_, target[i]->info_->size());
			}
			printf("\n\n");
		}
	}	
}

///////////////////// custom test ///////////////
void TEST_tmp(){
	OLList ot;
	char buf1[] = "aaaa";
	char buf2[] = "bbbb";
	char buf3[] = "cccc";
	ot.add(1,2,new NInfo(buf1));
	ot.add(2,3,new NInfo(buf2));
	ot.add(3,4,new NInfo(buf3));
	ot.visit();
}

///////////////////// error argv ///////////////
void err_usage(const char *cmd){
	printf("usage: %s --type=<int>(1:seq; 2:random; 3:query_random_one, 4:query_random_range; 5:query_seq_one, 6:query_seq_range;) --num=<int>([1-999])\n", cmd);
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
			if(!(type==0 || type==1 || type==2 || type==3 || type==4 || type==5 || type==6)){
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
	}else if(type==3){
		TEST_query_random_one(N);
	}else if(type==4){
		TEST_query_random_range(N);
	}else if(type==5){
		TEST_query_seq_one(N);
	}else if(type==6){
		TEST_query_seq_range(N);
	}else if(type==0){
		TEST_tmp();
	}
	
	return 0;
}