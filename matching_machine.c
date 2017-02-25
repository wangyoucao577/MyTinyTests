#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

const static char* kPassiveOperationNameTrade = "TRADE";

#define kMaxOperationOrderTypeNameLength 16	// for temporary var 
#define kMaxOrderIdLength 256
#define kMaxPrintBytesPerLine 128

enum OperationType{
	kOperationTypeBuy = 0,
	kOperationTypeSell,
	kOperationTypeCancel,
	kOperationTypeModify,
	kOperationTypePrint,
	// If any new operation type, add them here...

	kOperationTypeCount	//describe total count of the operations
};
const static char* kOperationTypeNameArray[kOperationTypeCount] = {"BUY", "SELL", "CANCEL", "MODIFY", "PRINT"};

enum OrderType{
	kOrderTypeGFD = 0,
	kOrderTypeIOC,
	// If any new operation type, add them here...

	kOrderTypeCount	//describe total count of the order types
};
const static char* kOrderTypeNameArray[kOrderTypeCount] = {"GFD", "IOC"};

struct OrderNode{
	enum OperationType operation_type;
	enum OrderType order_type;
	int64_t price;
	int64_t qty;
	char order_id[kMaxOrderIdLength];

	enum OperationType new_operation_type;	//only if MODIFY

	struct OrderNode * next;
};

struct MatchingCache{

	struct OrderNode* head;
};

static void DumpOrderNode(const struct OrderNode* node){
	printf("%d %d %lld %lld %s %d %p\n", \
		(int)node->operation_type, (int)node->order_type, node->price, node->qty, node->order_id, node->new_operation_type, node->next);
}

//return -1 if failed, otherwise find valid operation type
static int ParseOperationType(const char* str, bool at_head){

	int operation_type = -1;
	for (int i = 0; i < kOperationTypeCount; ++i){
		char * p = strstr(str, kOperationTypeNameArray[i]);
		if (NULL != p){	
			if (!at_head || (at_head && str == p)){ //check whether at the head of the str
				operation_type = i;	//set operation type
				break;
			}
		}
	}
	return operation_type;
}

//return -1 if failed, otherwise find valid order type
static int ParseOrderType(const char* str){
	
	int order_type = -1;
	for (int i = 0; i < kOrderTypeCount; ++i){
		if (NULL != strstr(str, kOrderTypeNameArray[i])){
			order_type = i;	//set order type
			break;
		}
	}
	return order_type;
}

//return NULL if failed, otherwise return a pointer to valid node
static struct OrderNode* ParseCommand(const char* cmd){
	if (NULL == cmd){
		return NULL;
	}

	//find operation 
	int operation_type_i = ParseOperationType(cmd, true);
	if (-1 == operation_type_i){
		return NULL;
	}

	struct OrderNode* order_node = (struct OrderNode*)malloc(sizeof(struct OrderNode));
	memset(order_node, 0, sizeof(struct OrderNode));
	order_node->operation_type = (enum OperationType)operation_type_i;

	char *cmd_after_operation_type = (char*)cmd + strlen(kOperationTypeNameArray[operation_type_i]);
	if (order_node->operation_type == kOperationTypeBuy || order_node->operation_type == kOperationTypeSell){

		char order_type_name[kMaxOperationOrderTypeNameLength] = {0};
		int sscanf_ret = sscanf(cmd_after_operation_type, "%s %lld %lld %s", \
			order_type_name, &order_node->price, &order_node->qty, order_node->order_id);
		if (sscanf_ret == EOF){
			goto Failed;
		}
		int order_type_i = ParseOrderType(order_type_name);
		if (-1 == order_type_i){
			goto Failed;
		}
		order_node->order_type = (enum OrderType)order_type_i;

	}else if (order_node->operation_type == kOperationTypeCancel){
		int sscanf_ret = sscanf(cmd_after_operation_type, "%s", order_node->order_id);
		if (sscanf_ret == EOF){
			goto Failed;
		}
	}else if (order_node->operation_type == kOperationTypeModify){
		char new_operation_type_name[kMaxOperationOrderTypeNameLength] = {0};
		int sscanf_ret = sscanf(cmd_after_operation_type, "%s %s %lld %lld", \
			order_node->order_id, new_operation_type_name, &order_node->price, &order_node->qty);
		if (sscanf_ret == EOF){
			goto Failed;
		}
		int oti = ParseOperationType(new_operation_type_name, false);
		if (-1 != oti && ((enum OperationType)oti == kOperationTypeSell || (enum OperationType)oti == kOperationTypeBuy)){
			order_node->new_operation_type = (enum OperationType)oti;
		}else{
			goto Failed;
		}

	}else if (order_node->operation_type == kOperationTypePrint){
		//nothing to do
	}else{
		assert(0);
	}

	return order_node;	//succeed return

Failed:
	if (order_node){
		free(order_node);
		order_node = NULL;
	}
	return NULL;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    char buff[1024] = {0};
    while (NULL != fgets(buff, sizeof(buff), stdin)){

    	struct OrderNode* node = ParseCommand(buff);
    	if (node){
    		DumpOrderNode(node);
    	}
    	//TODO: jump to different func

    	//printf("%s", buff);
    	memset(buff, 0, sizeof(buff));
    }
    return 0;
}

