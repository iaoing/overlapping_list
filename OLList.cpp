/*
* @Author: bing Jiao
* @Date:   2017-11-28 14:46:46
* @Last Modified by:   bing Jiao
* @Last Modified time: 2017-12-04 21:24:12
*/

#include "OLList.h"

//////////////////////////////
// NInfo;
NInfo::NInfo(){
}

NInfo::NInfo(const char *ch){
	info_vc_.push_back(std::string(ch));
}

NInfo::NInfo(std::string str){
	info_vc_.push_back(str);
}

NInfo* NInfo::add(NInfo *ni){
	info_vc_.insert(info_vc_.end(), ni->begin(), ni->end());
	return this;
}

NInfo* NInfo::add(std::string str){
	info_vc_.push_back(str);
	return this;
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
		printf("%s, ", info_vc_[i].c_str());
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

OLLNode* OLLNode::add_info(NInfo *info){
	if(info == NULL)
		return 0;
	info_->add(info);
	return this;
}

// split [x,y) to [x,de) and [de,y);
OLLNode* OLLNode::split(int de){
	ASSERT_BT(x_, y_, de);
	NInfo *ii = new NInfo();
	ii->add(info_);
	OLLNode *node = new OLLNode(de, y_, ii);
	insert(node);
	y_ = de;
	return this;
}

OLLNode* OLLNode::replace_by(OLLNode *new_node){
	new_node->next_ = next_;
	new_node->prev_ = prev_;
	next_->prev_ = new_node;
	prev_->next_ = new_node;
	return new_node;
}

bool OLLNode::hit_it(int q){
	if(x_ <= q && q < y_)
		return true;
	return false;
}

bool OLLNode::hit_it(int q_left, int q_right){
	if(    (x_ <= q_left && q_left < y_) 
		|| (x_ < q_right && q_right < y_)
		|| (q_left < x_  && y_ <= q_right) )
		return true;
	return false;	
}

void OLLNode::visit(){
	printf("range: [%8d, %8d); ", x_, y_);
	printf("size of info: %4d\n", info_->size());
	// printf("       infomation: ");
	// info_->visit();
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
	 					ptr = ptr->add_info(info);
	 					x = ptr->y_;
	 				}else if(y == ptr->y_){
	 					ptr = ptr->add_info(info);
	 					return ret;
	 				}else{
	 					ptr = ptr->split(y);
	 					ptr = ptr->add_info(info);
	 					++num_;	
	 					return ret;
	 				}
	 			}
 			}else if(x == ptr->x_){
 				if(y > ptr->y_){
 					ptr = ptr->add_info(info);
 					x = ptr->y_;
 				}else if(y == ptr->y_){
 					ptr = ptr->add_info(info);
 					return ret;
 				}else{
 					ptr = ptr->split(y);
 					ptr = ptr->add_info(info);
 					++num_;	
 					return ret;
 				}
 			}else if(x < ptr->y_){
 				ptr = ptr->split(x);
 				++num_;
 			}
 			ptr = ptr->next_;
 		}
		OLLNode *node = new OLLNode(x, y, info);
		ptr->prev_->insert(node);
		++num_;		
	}
	return ret;
}

// NInfo* OLList::retrive_info(int x){
// 	OLLNode *node;
// 	node = header_.next_;
// 	while(node != &header_){
// 		if(node->hit_it(x)){
// 			return node->info_;
// 		}
// 		node = node->next_;
// 	}
// 	return NULL;
// }

// std::vector<NInfo*> OLList::retrive_info(int x, int y){
// 	ASSERT_LT(x, y);
// 	std::vector<NInfo*> target;
// 	OLLNode *node;
// 	node = header_.next_;
// 	while(node != &header_){
// 		if(node->hit_it(x, y)){
// 			target.push_back(node->info_);
// 		}
// 		node = node->next_;
// 	}
// 	return target;
// }

OLLNode* OLList::retrive_info(int x){
	OLLNode *node;
	node = header_.next_;
	while(node != &header_){
		if(node->hit_it(x)){
			return node;
		}
		node = node->next_;
	}
	return NULL;
}

std::vector<OLLNode*> OLList::retrive_info(int x, int y){
	ASSERT_LT(x, y);
	std::vector<OLLNode*> target;
	OLLNode *node;
	node = header_.next_;
	while(node != &header_){
		if(node->hit_it(x, y)){
			target.push_back(node);
		}
		node = node->next_;
	}
	return target;
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