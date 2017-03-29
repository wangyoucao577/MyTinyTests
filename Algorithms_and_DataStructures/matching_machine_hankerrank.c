#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>


#define kMaxOperationOrderTypeNameLength 16 // for temporary var 
#define kMaxOrderIdLength 256
#define kMaxReadBytesPerLine 512

#if defined(MY_DEBUG)
#define DEBUG_PRINTF(fmt, args...) printf("\n[DEBUG] " fmt, ##args)
#else
#define DEBUG_PRINTF(fmt, args...) (0)
#endif

enum OperationType{
    kOperationTypeBuy = 0,
    kOperationTypeSell,
    kOperationTypeCancel,
    kOperationTypeModify,
    kOperationTypePrint,
    // If any new operation type, add them here...

    kOperationTypeCount //describe total count of the operations
};
const static char* kOperationTypeNameArray[kOperationTypeCount] = {"BUY", "SELL", "CANCEL", "MODIFY", "PRINT"};
const static int kOperationAppendParamCountArray[kOperationTypeCount] = {4, 4, 1, 4, 0};

const static char* kPrintStringSell = "SELL";
const static char* kPrintStringBuy = "BUY";
const static char* kPrintStringTrade = "TRADE";

enum OrderType{
    kOrderTypeGFD = 0,
    kOrderTypeIOC,
    // If any new operation type, add them here...

    kOrderTypeCount //describe total count of the order types
};
const static char* kOrderTypeNameArray[kOrderTypeCount] = {"GFD", "IOC"};

enum ActionResult{
    kActionResultNodeSaved = 0,
    kActionResultNodeShouldBeFree,
};

enum TradeResult{
    kTradeResultNoTrade = 0,
    kTradeResultOrgPartTraded,      //caching node part traded, new node all traded
    kTradeResultNewPartTraded,      //caching node all traded, new node part traded. if so, the caching node will be freed directly
    kTradeResultAllTraded,          // if so, the caching node will be freed directly
};

struct OrderNode{
    enum OperationType operation_type;
    enum OrderType order_type;
    long long int price;
    long long int qty;
    char order_id[kMaxOrderIdLength];

    enum OperationType new_operation_type;  //only if MODIFY

    struct OrderNode * next;

    enum ActionResult (*Action)(void*, struct OrderNode*);
};

struct MatchingCache{

    struct OrderNode* buy_head;
    struct OrderNode* sell_head;
};

static void ClearMatchingCache(struct MatchingCache* mc){
    while (mc->buy_head){
        struct OrderNode* node = mc->buy_head;
        mc->buy_head = mc->buy_head->next;
        free(node);
    }
    while (mc->sell_head){
        struct OrderNode* node = mc->sell_head;
        mc->sell_head = mc->sell_head->next;
        free(node);
    }

}

//only for debug
static void DumpOrderNode(const struct OrderNode* node){
    if (!node){
        return;
    }

    DEBUG_PRINTF("node_addr:%p %s %s price:%lld qty:%lld order_id:%s new_operation_if_modify:%s next:%p\n", \
        node, \
        kOperationTypeNameArray[(int)node->operation_type], kOrderTypeNameArray[(int)node->order_type], \
        node->price, node->qty, node->order_id, \
        node->operation_type == kOperationTypeModify ? kOperationTypeNameArray[(int)node->new_operation_type] : "none", \
        node->next);
}

//only for debug
static void DumpMatchingCache(const struct MatchingCache* mc, bool dump_node_details){
    assert(NULL != mc);

    int sell_count = 0, buy_count = 0;
    struct OrderNode* p = mc->sell_head;
    while (p){
        ++sell_count;
        if (dump_node_details){
            DumpOrderNode(p);
        }
        p = p->next;
    }
    p = mc->buy_head;
    while (p){
        ++buy_count;
        if (dump_node_details){
            DumpOrderNode(p);
        }
        p = p->next;
    }
    DEBUG_PRINTF("%s sell_count:%d buy_count:%d\n", __func__, sell_count, buy_count);
}

//implement my simple map for sort and print via list
struct SimpleMapNode
{
    long long int key;
    long long int value;

    struct SimpleMapNode* next;
};

//if key not exist, insert it;
//if key exist, modify the value.
//sort as decreasing
static void SimpleMapInsert(struct SimpleMapNode** head_addr, long long int key, long long int value){
    assert(NULL != head_addr && key > 0 && value > 0);

    struct SimpleMapNode* new_node = (struct SimpleMapNode*)malloc(sizeof(struct SimpleMapNode));
    memset(new_node, 0, sizeof(struct SimpleMapNode));
    new_node->key = key;
    new_node->value = value;

    if (NULL == *head_addr){ //empty map, create the first node
        
        *head_addr = new_node;
        return;
    }

    struct SimpleMapNode* p = *head_addr;
    struct SimpleMapNode* prev = NULL;
    while (p){
        if (key == p->key){
            p->value += value;
            free(new_node);
            return;
        }else if (key > p->key){
            if (prev == NULL){  //insert as the head
                new_node->next = p;
                *head_addr = new_node;
                return;
            }else{  //insert between prev and p 
                new_node->next = p;
                prev->next = new_node;
                return;
            }
        }else{  //key < p->key
            if (p->next == NULL){   //append at the end
                p->next = new_node;
                return;
            }else{  //move p
                prev = p;
                p = p->next;
            }
        }
    }
    assert(0);  //won't be here
    return;
}
static void PrintSimpleMap(const struct SimpleMapNode* head){
    const struct SimpleMapNode* p = head;
    while (p){
        printf("%lld %lld\n", p->key, p->value);
        p = p->next;
    }
}
static void ClearSimpleMap(struct SimpleMapNode** head_addr){
    assert(NULL != head_addr);

    struct SimpleMapNode* p = *head_addr;
    while (p){
        struct SimpleMapNode* prev = p;
        p = p->next;
        free(prev);
    }
    *head_addr = NULL;
}

typedef bool (*CompareFunc)(void*, void*);      //compare function type for callback

static bool CompareOrderId(void* base_node, void* order_id_2){
    assert(NULL != base_node && NULL != order_id_2);
    struct OrderNode* node = (struct OrderNode*)base_node;
    assert(strlen(node->order_id) > 0 && strlen((char*)order_id_2) > 0);

    if (0 == strcmp(node->order_id, (char*)order_id_2)){
        return true;
    }
    return false;
}

//return true if base_node->price >= new_price
static bool ComparePriceAbove(void* base_node, void* new_node){
    assert(NULL != base_node && NULL != new_node);
    struct OrderNode* node = (struct OrderNode*)base_node;
    struct OrderNode* node2 = (struct OrderNode*)new_node;
    

    if (node->price >= node2->price){
        return true;
    }
    return false;
}
//return true if base_node->price <= new_price
static bool ComparePriceBelow(void* base_node, void* new_node){
    assert(NULL != base_node && NULL != new_node);
    struct OrderNode* node = (struct OrderNode*)base_node;
    struct OrderNode* node2 = (struct OrderNode*)new_node;

    if (node->price <= node2->price){
        return true;
    }
    return false;
}

//only for debug
static void DumpCompareCallbackFunctions(){
    DEBUG_PRINTF("%s CompareOrderId %p\n", __func__, CompareOrderId);
    DEBUG_PRINTF("%s ComparePriceAbove %p\n", __func__, ComparePriceAbove);
    DEBUG_PRINTF("%s ComparePriceBelow %p\n", __func__, ComparePriceBelow);

}

#define REMOVE_NODE_FROM_LIST(head, p, prev) ({\
    if (prev){\
        prev->next = p->next; \
    }else{ \
        (head) = (head)->next; \
    } \
    p->next = NULL; \
})

static void AppendToList(struct OrderNode** head_addr, struct OrderNode* node){
    assert(NULL != head_addr);
    struct OrderNode* head = *head_addr;
    if (!head){
        *head_addr = node;
        return;
    }

    struct OrderNode* p = head;
    while (p->next){
        p = p->next;
    }
    p->next = node;
}

static struct OrderNode* PopNodeViaCondition(struct OrderNode** head_addr, void* param, CompareFunc comp_func){
    assert(NULL != head_addr && NULL != comp_func && NULL != param);
    if (!(*head_addr)){
        return NULL;
    }

    struct OrderNode* p = *head_addr;
    struct OrderNode* prev = NULL;
    while (p){
        if (comp_func(p, param)){       //found
            REMOVE_NODE_FROM_LIST(*head_addr, p, prev);
            return p;
        }

        prev = p;
        p = p->next;
    }
    return NULL;
}

static enum TradeResult TryTrade(struct OrderNode** head_addr, struct OrderNode* new_node, CompareFunc comp_func){
    assert(NULL != head_addr && NULL != comp_func && NULL != new_node);
    if (!(*head_addr)){
        return kTradeResultNoTrade;
    }
    DEBUG_PRINTF("%s %p %p %p\n", __func__, *head_addr, new_node, comp_func);

    struct OrderNode* p = *head_addr;
    struct OrderNode* prev = NULL;
    while (p){
        if (comp_func(p, new_node)){        //tradeable
            long long int traded_qty = p->qty >= new_node->qty ? new_node->qty : p->qty;
            printf("%s %s %lld %lld %s %lld %lld\n", kPrintStringTrade, \
                p->order_id, p->price, traded_qty, new_node->order_id, new_node->price, traded_qty);

            if (p->qty == new_node->qty){
                //all Traded
                REMOVE_NODE_FROM_LIST(*head_addr, p, prev);
                free(p);
                return kTradeResultAllTraded;
            }else if (p->qty > new_node->qty){
                //new part traded
                p->qty -= new_node->qty;

                return kTradeResultNewPartTraded;
            }else {
                //old part traded
                new_node->qty -= p->qty;
                REMOVE_NODE_FROM_LIST(*head_addr, p, prev);
                free(p);

                //continue the loop until nothing can be traded.
                p = NULL == prev ? *head_addr : prev->next;
                continue;
                //return kTradeResultOrgPartTraded;
            }
        }

        prev = p;
        p = p->next;
    }
    return kTradeResultNoTrade;
}

static enum ActionResult (*kActionArray[])(void*, struct OrderNode*);       //declare first, will be used in ActionModify

static enum ActionResult ActionBuy(void* base_mc, struct OrderNode* node){
    DEBUG_PRINTF("%s %p %p\n", __func__, base_mc, node);
    assert(NULL != base_mc && NULL != node);
    struct MatchingCache* mc = (struct MatchingCache*)base_mc;

    while (true){
        enum TradeResult tr = TryTrade(&mc->sell_head, node, ComparePriceBelow);
        switch(tr){
            case kTradeResultNoTrade:
                if (node->order_type == kOrderTypeGFD){
                    AppendToList(&mc->buy_head, node);
                    return kActionResultNodeSaved; 
                }else{
                    //IOC
                    return kActionResultNodeShouldBeFree;
                }
            // case kTradeResultOrgPartTraded:
            //     //should try trade again
            //     break;
            case kTradeResultAllTraded:
            case kTradeResultNewPartTraded:
                return kActionResultNodeShouldBeFree;
            default:
                assert(0);
                break;
        }
    }
}
static enum ActionResult ActionSell(void* base_mc, struct OrderNode* node){
    DEBUG_PRINTF("%s %p %p\n", __func__, base_mc, node);
    assert(NULL != base_mc && NULL != node);
    struct MatchingCache* mc = (struct MatchingCache*)base_mc;

    while (true){
        enum TradeResult tr = TryTrade(&mc->buy_head, node, ComparePriceAbove);
        switch(tr){
            case kTradeResultNoTrade:
                if (node->order_type == kOrderTypeGFD){
                    AppendToList(&mc->sell_head, node);
                    return kActionResultNodeSaved; 
                }else{
                    //IOC
                    return kActionResultNodeShouldBeFree;
                }
            // case kTradeResultOrgPartTraded:
            //     //should try trade again
            //     break;
            case kTradeResultAllTraded:
            case kTradeResultNewPartTraded:
                return kActionResultNodeShouldBeFree;
            default:
                assert(0);
                break;
        }
    }
}
static enum ActionResult ActionCancel(void* base_mc, struct OrderNode* node){
    DEBUG_PRINTF("%s %p %p\n", __func__, base_mc, node);
    assert(NULL != base_mc && NULL != node);
    struct MatchingCache* mc = (struct MatchingCache*)base_mc;

    struct OrderNode* org_node = PopNodeViaCondition(&mc->buy_head, node->order_id, CompareOrderId);
    if (NULL == org_node){
        org_node = PopNodeViaCondition(&mc->sell_head, node->order_id, CompareOrderId);
    }
    if (NULL != org_node){
        assert(NULL == org_node->next);
        free(org_node);
        org_node = NULL;
    }else{
        DEBUG_PRINTF("CANCEL command ignored casued by order_id:%s not found.\n", \
            node->order_id);
    }

    return kActionResultNodeShouldBeFree;
}
static enum ActionResult ActionModify(void* base_mc, struct OrderNode* node){
    DEBUG_PRINTF("%s %p %p\n", __func__, base_mc, node);
    assert(NULL != base_mc && NULL != node);
    struct MatchingCache* mc = (struct MatchingCache*)base_mc;

    //pop first
    struct OrderNode* org_node = PopNodeViaCondition(&mc->buy_head, node->order_id, CompareOrderId);
    if (NULL == org_node){
        org_node = PopNodeViaCondition(&mc->sell_head, node->order_id, CompareOrderId);
    }
    if (NULL == org_node){
        //not find this order, ignore it
        DEBUG_PRINTF("MODIFY command ignored casued by order_id:%s not found.\n", \
            node->order_id);
        return kActionResultNodeShouldBeFree;
    }

    //re-assembly org_node
    assert(NULL == org_node->next);
    org_node->price = node->price;
    org_node->qty = node->qty;
    org_node->operation_type = node->new_operation_type;
    org_node->Action = kActionArray[(int)org_node->operation_type];
    enum ActionResult ar = org_node->Action(base_mc, org_node);
    if (ar == kActionResultNodeShouldBeFree){
        free(org_node);
        org_node = NULL;
    }

    return kActionResultNodeShouldBeFree;       //tell caller to free node
}
static enum ActionResult ActionPrint(void* base_mc, struct OrderNode* node){
    DEBUG_PRINTF("%s %p %p\n", __func__, base_mc, node);
    assert(NULL != base_mc && NULL != node);
    struct MatchingCache* mc = (struct MatchingCache*)base_mc;

    // The price for SELL section must be decreasing and corresponding the price for BUY section must be decreasing.
    
    struct SimpleMapNode* sell_map_head = NULL;

    struct OrderNode * p = mc->sell_head;
    while (p){
        SimpleMapInsert(&sell_map_head, p->price, p->qty);
        p = p->next;
    }

    printf("%s:\n", kPrintStringSell);
    PrintSimpleMap(sell_map_head);
    ClearSimpleMap(&sell_map_head);

    struct SimpleMapNode* buy_map_head = NULL;
    p = mc->buy_head;
    while (p){
        SimpleMapInsert(&buy_map_head, p->price, p->qty);
        p = p->next;
    }
    printf("%s:\n", kPrintStringBuy);
    PrintSimpleMap(buy_map_head);
    ClearSimpleMap(&buy_map_head);
    
    return kActionResultNodeShouldBeFree;
}

static enum ActionResult (*kActionArray[])(void*, struct OrderNode*) = {        //definition here
    ActionBuy,
    ActionSell,
    ActionCancel,
    ActionModify,
    ActionPrint
};


//return -1 if failed, otherwise find valid operation type
static int ParseOperationType(const char* str){

    char operation_name[kMaxOperationOrderTypeNameLength] = {0};
    int s_ret = sscanf(str, "%s", operation_name);
    if (1 != s_ret){
        return -1;
    }

    int operation_type = -1;
    for (int i = 0; i < kOperationTypeCount; ++i){
        if (0 == strcmp(operation_name, kOperationTypeNameArray[i])){
            operation_type = i; //set operation type
            break;
        }
    }
    return operation_type;
}

//return -1 if failed, otherwise find valid order type
static int ParseOrderType(const char* str){

    int order_type = -1;
    for (int i = 0; i < kOrderTypeCount; ++i){
        if (0 == strcmp(str, kOrderTypeNameArray[i])){
            order_type = i; //set order type
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

    struct OrderNode* order_node = NULL;

    //find operation 
    int operation_type_i = ParseOperationType(cmd);
    if (-1 == operation_type_i){
        goto Failed;
    }

    order_node = (struct OrderNode*)malloc(sizeof(struct OrderNode));
    memset(order_node, 0, sizeof(struct OrderNode));
    order_node->operation_type = (enum OperationType)operation_type_i;

    char *cmd_after_operation_type = (char*)cmd + strlen(kOperationTypeNameArray[operation_type_i]);
    if (order_node->operation_type == kOperationTypeBuy || order_node->operation_type == kOperationTypeSell){

        char order_type_name[kMaxOperationOrderTypeNameLength] = {0};
        int sscanf_ret = sscanf(cmd_after_operation_type, "%s %lld %lld %s", \
            order_type_name, &order_node->price, &order_node->qty, order_node->order_id);
        if (sscanf_ret != kOperationAppendParamCountArray[operation_type_i]){
            goto Failed;
        }
        int order_type_i = ParseOrderType(order_type_name);
        if (-1 == order_type_i){
            goto Failed;
        }
        order_node->order_type = (enum OrderType)order_type_i;

        if (order_node->price <= 0 || order_node->qty <= 0){        //make sure price and quantity valid
            goto Failed;
        }

    }else if (order_node->operation_type == kOperationTypeCancel){
        int sscanf_ret = sscanf(cmd_after_operation_type, "%s", order_node->order_id);
        if (sscanf_ret != kOperationAppendParamCountArray[operation_type_i]){
            goto Failed;
        }
    }else if (order_node->operation_type == kOperationTypeModify){
        char new_operation_type_name[kMaxOperationOrderTypeNameLength] = {0};
        int sscanf_ret = sscanf(cmd_after_operation_type, "%s %s %lld %lld", \
            order_node->order_id, new_operation_type_name, &order_node->price, &order_node->qty);
        if (sscanf_ret != kOperationAppendParamCountArray[operation_type_i]){
            goto Failed;
        }
        int oti = ParseOperationType(new_operation_type_name);
        if (-1 != oti && ((enum OperationType)oti == kOperationTypeSell || (enum OperationType)oti == kOperationTypeBuy)){
            order_node->new_operation_type = (enum OperationType)oti;
        }else{
            goto Failed;
        }

        if (order_node->price <= 0 || order_node->qty <= 0){        //make sure price and quantity valid
            goto Failed;
        }

    }else if (order_node->operation_type == kOperationTypePrint){
        //nothing to do
    }else{
        assert(0);
    }

    if (order_node->operation_type != kOperationTypePrint){
        if (strlen(order_node->order_id) <= 0 || !isprint(order_node->order_id[0])){     //make sure order_id valid
            goto Failed;
        }
    }


    order_node->Action = kActionArray[(int)order_node->operation_type]; //initialize action
    return order_node;  //succeed return

Failed:
    DEBUG_PRINTF("%s this command ignored.\n", __func__);
    if (order_node){
        free(order_node);
        order_node = NULL;
    }
    return NULL;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    //DumpCompareCallbackFunctions();

    struct MatchingCache mc;
    memset(&mc, 0, sizeof(struct MatchingCache));

    char buff[kMaxReadBytesPerLine] = {0};
    while (NULL != fgets(buff, sizeof(buff), stdin)){

        DEBUG_PRINTF("org-->%s, len:%d", buff, (int)strlen(buff));

        struct OrderNode* node = ParseCommand(buff);
        if (node){
            //DumpOrderNode(node);

            // call different action func
            enum ActionResult ar = node->Action((void*)&mc, node);
            if (ar == kActionResultNodeShouldBeFree){
                free(node);
                node = NULL;
            }

#if defined(MY_DEBUG)
            DumpMatchingCache(&mc, false);
#endif
        }

        //printf("%s", buff);
        memset(buff, 0, sizeof(buff));
    }

    //clear before exit
    ClearMatchingCache(&mc);
    return 0;
}

