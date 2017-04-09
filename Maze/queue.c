#include <stdio.h>
#include <stdlib.h>

//队列的节点；
struct node {
    int val;//队列元素；
    struct node* next;//指向下一个元素的指针；
};

static struct node *phead = NULL;//队列的头

static struct node *create_node(int val) {
    struct node *pnode = NULL;
    pnode = (struct node*)malloc(sizeof(struct node));
    if (!pnode) {
        return NULL;
    }
    pnode -> val = val;
    pnode -> next = NULL;
    return pnode;
}//向我们的队列加入元素；

static void destory_single_link() {
    struct node *pnode = NULL;
    while (phead != NULL) {
        pnode = phead;
        phead = phead -> next;//此处是在找队列的队尾；
        free(pnode);
    }
}

static void add(int val) {
    if (!phead) {
        phead = create_node(val);
        return ;
    }
    struct node *pnode = create_node(val);
    struct node *pend = phead;
    while (pend -> next) {
        pend = pend -> next;
    }
    pend -> next = pnode;
}//向我们的队列加入元素；

static int front() {

    if(phead==NULL)
    {
        printf("The queue is empty\n" );
        exit(1);
    }
    return phead ->val;  
}//返回队列的首元素

static int pop() {
    if(phead == NULL){
        printf("The queue is empty!\n" );
        exit(1);
    }
int val;
struct node * pnode;
val=phead->val;
pnode=phead;
phead=phead->next;
free(pnode);
return val;
}//弹出队列的首元素；

static int count() {
    int count = 1;
     struct node *pend = phead;
    while (pend -> next) {
        count++;
        pend = pend -> next;
    }
    return count;   
}//返回队列中元素的个数

static int is_empty() {
    if(phead==NULL)
return 1;
else
return 0;
}//判断队列是否为空；

int main() {
    add(1);
    add(2);
    add(3);
    add(4);
    add(5);
    add(6);
    printf("现在队列的首元素为：%d\n", front());
    printf("弹出队列的首元素为：%d\n", pop());
    printf("现在队列的首元素为：%d\n", front());
    printf("队列中元素个数为：%d\n", count());
    if(is_empty())printf("此时队列为空！\n");
    else printf("此时队列不为空！\n");
    return 0;
}
