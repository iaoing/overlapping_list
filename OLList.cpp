/*
* @Author: bing Jiao
* @Date:   2017-11-28 14:46:46
* @Last Modified by:   bing Jiao
* @Last Modified time: 2017-11-29 17:00:00
*/

#include "OLList.h"

//////////////////////////////
// OLLNode;
OLLNode::OLLNode() :
	prev_(NULL),
	next_(NULL),
	info_(NULL){
	// printf("** %s %d\n", __FUNCTION__, __LINE__);
}

OLLNode::OLLNode(int x, int y) :
	x_(x),
	y_(y),
	prev_(NULL),
	next_(NULL),
	info_(NULL){
	// printf("** %s %d\n", __FUNCTION__, __LINE__);
}

OLLNode::OLLNode(int x, int y, NInfo *info) :
	x_(x),
	y_(y),
	prev_(NULL),
	next_(NULL),
	info_(info){
	// printf("** %s %d\n", __FUNCTION__, __LINE__);
}

OLLNode::~OLLNode(){
	// printf("** %s %d\n", __FUNCTION__, __LINE__);
}

// insert node in this->next_
int OLLNode::insert(OLLNode *node){
	ASSERT_NL(node);
	node->next_ = next_;
	node->prev_ = this;
	this->next_->prev_ = node;
	next_ = node;
	return 0;
}

int OLLNode::add_info(NInfo *info){
	if(info == NULL)
		return 0;
	for(int i = 0; i < info->file_nos.size(); ++i){
		info_->file_nos.push_back(info->file_nos[i]);
	}
}

int OLLNode::split(int de){
	ASSERT_BT(x_, y_, de);
	NInfo *ii = new NInfo();
	for(auto i : info_->file_nos){
		ii->file_nos.push_back(i);
	}
	OLLNode node(de, y_, ii);
	insert(&node);
	y_ = de;
	return 0;
}

int OLLNode::fission(int de){
	// if()
}

void OLLNode::visit(){
	printf("range: [%8d, %8d); ", x_, y_);
	printf("size of info: %4d\n", info_->file_nos.size());
	printf("       infomation: ");
	// if(!info_->file_nos.empty()){
	// 	for(int i = 0; i < info_->file_nos.size(); ++i){
	// 		printf("%s, ", info_->file_nos[i].c_str());
	// 	}
	// }
	printf("\n");
}

//////////////////////////////
// OLList;
OLList::OLList():
	noi_(0),
	num_(0){
	header_.next_ = &header_;
	header_.prev_ = &header_;
}

OLList::~OLList(){

}

int OLList::add(int x, int y, NInfo *info){
	ASSERT_LT(x, y);
	int ret = 0;
	++noi_;
	if(num_ == 0){
		OLLNode *node = new OLLNode(x, y, info);
		node->prev_ = &header_;
		node->next_ = &header_;
		header_.prev_ = node;
		header_.next_ = node;
		++num_;
	}else{
		OLLNode *ptr = header_.next_;
		while(ptr != (&header_)){
 			if(x < ptr->x_){
 				if(y <= ptr->x_){
					OLLNode *node = new OLLNode(x, y, info);
	 				ptr->prev_->insert(node);
	 				++num_; 
	 				return ret;					
 				}else{
 					// ptr->add_info(info);
	 				OLLNode *node = new OLLNode(x, ptr->x_, info);
	 				ptr->prev_->insert(node);
	 				++num_;
	 				if(y > ptr->y_){
	 					ptr->add_info(info);
	 					x = ptr->y_;
	 				}else if(y == ptr->y_){
	 					ptr->add_info(info);
	 					return ret;
	 				}else{
	 					ptr->split(y);
	 					ptr->add_info(info);
	 					++num_;	
	 					return ret;
	 				}
	 			}
 			}else if(x < ptr->y_){
 				if(y <= ptr->y_){
					ptr->add_info(info);
	 				return ret;					
 				}else{
 					ptr->add_info(info);
 					x = ptr->y_;
	 			}
 			}
 			ptr = ptr->next_;
 		}
		OLLNode *node = new OLLNode(x, y, info);
		ptr->prev_->insert(node);
		++num_;		
	}
	return ret;
}

int OLList::get_num(){
	ASSERT_NN(num_);
	return num_;
}

int OLList::get_infos(){
	ASSERT_NN(noi_);
	return noi_;
}

void OLList::visit(){
	OLLNode *ptr = (header_.next_);
	while(ptr != (&header_)){
		ptr->visit();
		ptr = ptr->next_;
	}
	printf("num_: %d, noi_: %d\n", num_, noi_);
}