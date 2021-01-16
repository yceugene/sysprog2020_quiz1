// AA1
#define AA1 assert(new_node)
// #define AA1 *indirect = new_code

// AA2
// #define AA2 assert(new_node)
#define AA2 *indirect = new_node

// BB1
// #define BB1  node = (*node)->next->next
// #define BB1  *node = (*node)->next->next
// #define BB1  *node = ((*node)->next)->next
// #define BB1  *node = &((*node)->next)->next
#define BB1  node = &(*node)->next->next
// #define BB1  *node = &(*node)->next->next

// BB2
// #define BB2 node = (*node)->next
// #define BB2 node = &(*node)->next
#define BB2 *node = (*node)->next
// #define BB2 *node = &(*node)->next
// #define BB2 *node = &((*node)->next)

// CCC
// #define CCC cursor = head; head->next = cursor
#define CCC {head->next = cursor; cursor = head;}
// #define CCC cursor = head
// #define CCC head->next = cursor
// #define CCC head->next->next = cursor; cursor->next = head
// #define CCC cursor->next = head; head->next->next = cursor
