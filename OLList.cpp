/*
* @Author: bing Jiao
* @Date:   2017-11-28 14:46:46
* @Last Modified by:   bing Jiao
* @Last Modified time: 2017-12-02 23:40:30
*/

#include "OLList.h"

//////////////////////////////
// NInfo;
NInfo::NInfo(){
}

NInfo::NInfo(std::string str){
	info_vc_.push_back(str);
}

void NInfo::add(NInfo *ni){
	info_vc_.insert(info_vc_.end(), ni->begin(), ni->end());
}

void NInfo::add(std::string str){
	info_vc_.push_back(str);
}

std::vector<std::string>::iterator NInfo::begin(){
	return info_vc_.begin();
}

std::vector<std::string>::iterator NInfo::end(){
	return info_vc_.end();
}

size_t NInfo::size(){
	return info_vc_.size();
}

void NInfo::visit(){
	for(int i = 0; i < info_vc_.size(); ++i){
		printf("%s, ", info_vc_[i]);
	}
	printf("\n");
}

//////////////////////////////
// OLLNode;
OLLNode::OLLNode() :
	x_(-1),
	y_(-1),
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
	info_->add(info);
}

// split [x,y) to [x,de) and [de,y);
int OLLNode::split(int de){
	ASSERT_BT(x_, y_, de);
	NInfo *ii = new NInfo();
	ii->add(info_);
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
	printf("size of info: %4d\n", info_->size());
	printf("       infomation: ");
	info_->visit();
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