# 2020q3 Homework4 (quiz4)
contributed by < ``yceugene`` >

## 1. Linked psCOMMANDLIST

### add_entry():
```c
void add_entry(node_t **head, int new_value)
{
		node_t **indirect = head;
		node_t *new_node = malloc(sizeof(node_t));
		new_node->value = new_value;
		new_node->next = NULL;
		assert(new_node);
		while (*indirect)
				indirect = &(*indirect)->next;
		*indirect = new_node;
}
```
* 動作說明:
    * 傳入參數 **head, 用來傳入 node list 的根. 在初始狀況時, *head (*indirect) 為 NULL, 則用來傳回第一個 node (root) 的位址.
    * 接著使用 malloc() 來取得 node 的記憶體, 將 value 設定, 因為新加入的 node, 會在 list 的最尾端, 因此一併指定其 next 為 NULL.
    * assert(new_node) 用來確保 new_node 非 NULL. 在此建議將 assert(new_node) 上移緊接著 malloc() 之後, 因為 new_node 一旦為 NULL, 之後的 new_node->value ... 會造成 code dump. 在真正的 application 時, assert() 可能不夠, 必須加入完整的 exception handling, 來確保一旦 malloc() 失敗, new_node 為 NULL時, 系統不會 hang up.
    * 在初始狀態時, *head (即 *indirect) 為 NULL, 因此 while 迴圈不會執行, 只要 malloc() 成功傳會 new_node 非 NULL, 就會由 *indirect (即 *head) 傳回 new_node 當成第一個 node (root)
    * 非初始狀態時, *head (即 *indirect) 非NULL, while 迴圈啟動尋找 next, 直到找到最後一個 node 為 NULL，在將 new_node 接上最後一個 node的 next 並結束執行. 如此 new_node 就變成最後一個 node 了.

### find_entry():
```c=
node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
	        /* interate */;
    return current;
}
```
* 動作說明:
    * 在 for 迴圈中尋找符合 value的 node,找到後, 將該node (即 current) 傳回.
    * 如果 value 在 linked list 裡頭找不到, 則會傳回 NULL. 在呼叫此函式時, 可以加入適當的防呆動作, 確保程式在找不到 value 時, 依然可以正常動作!

### remove_entry():
```c=
void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}
```
* 動作說明:
    * 在 for 迴圈尋找目標 node (這裡是 entry). 找到之後, 將 entry->next 指向前一個 node, 再將 entry 移除 (free()).
    * 當 entry 在 linked list 裡找不到時, 會發生 code dump, 因此建議在找不到 entry 時, 應該及時提醒並適當返回 (如下:)
```c=
void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
    {
        indirect = &(*indirect)->next;
        if( *indirect == NULL ) // protect
            printf("entry(%p) not found!", entry);
            return;
    }

    *indirect = entry->next;
    free(entry);
}
```
### swap_pair():
```c=
node_t *swap_pair(node_t *head)
{
    for (node_t **node = &head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return head;
}
```
* 動作說明:
    * swap_pair() 在 for loop 裡, 每次會處理兩個 node, 依序更新其 next 指標, 並將最後的 next 指向原 next 的下一個 next, 來繼續下一個 swap.
    * 當 linked list 為奇數個時, 最後一個 node 會保留不動作.

### reverse():
```c=
node_t *reverse(node_t *head)
{
    node_t *cursor = NULL;
    while (head) {
        node_t *next = head->next;
        head->next = cursor;
        cursor = head;
        head = next;
    }
    return cursor;
}
```
* 動作說明:
    * cursor 其初始值為 NULL, 會被指定給 head->next 當作reverse()完成後的最後一個 node.
    * next 會指向下個 node, 並在迴圈結束前, 指給當前的 node (head), 以進行下一個迴圈.
    * 當 head 為 NULL 時, cursor 指向原　list 的最後一個 node. 在 reverse() 後, 會被返回 當成新 list 的第一個 node (root).

### execution:
```
	72	@0x5620d678d6b0 next:0x5620d678d6d0
	101 	@0x5620d678d6d0 next:0x5620d678d6f0
	108 	@0x5620d678d6f0 next:0x5620d678d710
	109 	@0x5620d678d710 next:0x5620d678d730
	110 	@0x5620d678d730 next:0x5620d678d750
	111 	@0x5620d678d750 next:(nil)


	72	@0x5620d678d6b0 next:0x5620d678d6f0
	108 	@0x5620d678d6f0 next:0x5620d678d710
	109 	@0x5620d678d710 next:0x5620d678d730
	110 	@0x5620d678d730 next:(nil)

	108 	@0x5620d678d6f0 next:0x5620d678d6b0
	72	@0x5620d678d6b0 next:0x5620d678d730
	110 	@0x5620d678d730 next:0x5620d678d710
	109 	@0x5620d678d710 next:(nil)

	109 	@0x5620d678d710 next:0x5620d678d730
	110 	@0x5620d678d730 next:0x5620d678d6b0
	72	@0x5620d678d6b0 next:0x5620d678d6f0
	108 	@0x5620d678d6f0 next:(nil)
```
> 為提供多一點的訊息來說明動作, 以下將print_list()修改:
```c=
void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d \t@%p next:%p\n", current->value, current, current->next);
    printf("\n");
}
(show value, node and next node address instead of value only!)
```
## extension 1 - 修改 swap_pair() & reverse()

### swap_pair():
```c=
void swap_pair(node_t **_head)
{
    node_t *head = *_head;
    for (node_t **node = &head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    *_head = head;
}
```
* 動作說明:(此修改希望盡可能用最少的修改來完成.)
    * 修改參數成 **_head, 並將返回改為 void.
    * 新增變數 node_t *head = *_head.
    * 用 *_head = head 來取代 return 將 head 傳回.

### reverse():
```c=
void reverse(node_t **_head)
{
    node_t *cursor = NULL;
    node_t *head = *_head;
    while (head) {
        node_t *next = head->next;
        head->next = cursor;
        cursor = head;
        head = next;
    }
    *_head = cursor;
}
```    
* 動作說明:(此修改希望盡可能用最少的修改來完成.)
    * 同　swap_pair(), 修改參數成 **_head, 並將返回值改為 void.
    * 新增變數 node_t *head = *_head.
    * 用 *_head = head 來取代 return 將 head 傳回.

## extension 2 - 使用 recursive 來修改　reverse()
### rev_recursive():
```c=
void rev_recursive(node_t *pPrevNode, node_t *pNode, node_t **root)
{
    if(!pNode)
    {
      *root = pPrevNode;
      return;
    }
    rev_recursive(pNode, pNode->next, root);
    pNode->next = pPrevNode;
    MDebug(pNode);
}
```
### reverse():
```c=
void reverse(node_t **_head)
{
    node_t *cursor = NULL;
    rev_recursive(cursor, *_head, _head);
}
```
* 動作說明: (recursive reverse 主要有三個動作)
    * rev_recursive() 會呼叫自己,因此通常不需要while loop. 並且 recursive 時,必須找到停止點, 即 pNode 為 NULL 時. 此時, 必須將此最後一個 node 傳回當成新 list 的 root (第一個 node)並結束遞迴.
    * 三個參數,  *pPrevNode, *pNode 及 **root, 分別代表前一個 node, 當前 node 及 root. root 用以取回新的 head.
    * 在遞迴中, 依序將 pNode->next 指向 pPrevNode 來完成動作!
    > :warning: 進一步研究能否減少使用參數！
