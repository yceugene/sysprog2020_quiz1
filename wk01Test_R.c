#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ansWK01Test.h"

#define MDebug    //printNode

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d \t@%p next:%p\n", current->value, current, current->next);
    printf("\n");
}

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;
    AA1;
    while (*indirect)
        indirect = &(*indirect)->next;
    AA2;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void swap_pair(node_t **_head)
{
    node_t *head = *_head;
    for (node_t **node = &head; *node && (*node)->next; BB1) {
        node_t *tmp = *node;
        BB2;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    *_head = head;
}

void printNode(node_t *p)
{
  printf("%d \t@%p next:%p\n", p->value, p, p->next);
}

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
// original: head -> n1 -> n2 -> n3
// will be : head <- n1 <- n2 <- n3
void reverse(node_t **_head)
{
    node_t *cursor = NULL;
    rev_recursive(cursor, *_head, _head);
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    swap_pair(&head);
    print_list(head);

    reverse(&head);
    print_list(head);

    return 0;
}
