#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///*************************************************
//						트리 구조체
///*************************************************
typedef struct TreeNode {
	char data;
	int count;
	struct TreeNode *left, *right;
} TreeNode;
typedef TreeNode* element;


///*************************************************
//						큐 구조체
///*************************************************
typedef struct QueueNode{
	element item;
	struct QueueNode *link;
} QueueNode;
typedef struct {
	QueueNode *front, *rear;
} QueueType;


///*************************************************
//						스택 구조체
///*************************************************
typedef struct StackNode {
	element item;
	struct StackNode *link;
} StackNode;
typedef struct {
	StackNode *top;
} LinkedStackType;



///*************************************************
//					스택 초기화 함수
///*************************************************
void stack_init(LinkedStackType *s)
{
	s->top = NULL;
}


///*************************************************
//					스택 공백상태 함수
///*************************************************
int stack_is_empty(LinkedStackType *s)
{
	return (s->top == NULL);
}


///*************************************************
//					스택 집어넣는 함수
///*************************************************
void push(LinkedStackType *s, element item)
{
	StackNode *temp=(StackNode *)malloc(sizeof(StackNode));
	if( temp == NULL ){
		printf("메모리 에러\n");
		return;
	}
	else{
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}


///*************************************************
//					스택 꺼내는 함수
///*************************************************
element pop(LinkedStackType *s)
{
	if( stack_is_empty(s) ) {
		printf("스택이 비어 있습니다\n");
		exit(1);
	}
	else{
		StackNode *temp=s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}

///*************************************************
//						큐 초기화 함수
///*************************************************
void init(QueueType *q)
{
	q->front = q->rear = NULL;
}


///*************************************************
//					큐 공백여부함수
///*************************************************
int is_empty(QueueType *q)
{
	return (q->front == NULL );
}


///*************************************************
//						인큐함수
///*************************************************
void enqueue(QueueType *q, element item)
{
	QueueNode *temp=(QueueNode*)malloc(sizeof(QueueType));
	if(temp==NULL) printf("메모리를 할당할 수 없습니다.\n");
	else{	//템프가 널이 아니면
		temp->item = item; temp->link = NULL;	//템프에 값을 넣고 링크는 널을 넣습니다.
		if (is_empty(q)) q->front = q->rear = temp;	//만약 큐가 비어있으면 프론트와 리어를 temp로 
													//초기화하고
		else { //그게 아니라면
			q->rear->link = temp;	//큐의 리어링크를 temp를 넣고
			q->rear = temp;	//큐의 리어에 temp를 넣습니다
		}
	}
}


///*************************************************
//						디큐함수
///*************************************************
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	element item;
	if (is_empty(q)) printf("큐가 비어 있습니다.\n");
	else {
		item = temp->item;		//itemp에 뽑아낼 item을 집어넣고
		q->front = q->front->link;		//프론트는 프론트의 링크로 바꾸고
		if (q->front == NULL) q->rear = NULL;		//프론트가 널이면 리어도 널입니다.
		free(temp);		//temp를 지우고
		return item;		//뽑아낸 item을 반환해줍니다.
	}
}


///*************************************************
//						레벨순회함수
///*************************************************
void level_order(TreeNode *ptr)	//순회함수
{
	QueueType q;
	init(&q);	//큐를 초기화 하고
	if (!ptr) return;
	enqueue(&q, ptr);	//큐에 노드를 넣고
	while (!is_empty(&q)){		//안비어있으면
		ptr = dequeue(&q);	//하나씩 꺼낸다.
		printf("%c ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}


///*************************************************
//					새로운노드 생성함수
///*************************************************
element createNode(char ch)	//새로운 노드를 생성하고 초기화 하는 함수
{
	element newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = ch;
	newNode->count = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}


///*************************************************
//						문자 체크 함수
///*************************************************
TreeNode* checking_ch(char *pch)
{
	TreeNode *new_node = NULL;		//새로운 노드
	TreeNode *n = NULL;			//루트노드
	int i = 0;
	LinkedStackType *L = (LinkedStackType*)malloc(sizeof(LinkedStackType));	//스택을 생성한다.
	stack_init(L);	//스택을 초기화하고

	for( i = 0; pch[i] != NULL; i++)	//문자열 NULL이 될때까지 포문/
	{
		switch( pch[i] )		//문자 하나하나씩을 비교한다
		{
		case '(':
			new_node = createNode(pch[++i]);	//(다음에는 문자가 오기때문에 트리노드를 생성하고 new_node에 집어넣는다
			break;
		case ',':
			new_node->count++;		//','갯수만큼 ++한다
			if( pch[i+1] == '(' ) push(L, new_node);	//만약 ','다음이 '('이면 현재 노드를 스택에 집어 넣는다
			break;
		case ')':
			if( !stack_is_empty(L))		//스택이 안비어있으면
				n = pop(L);		//괄호가 끝나면 부모노드를 다시 n에 넣는다.
			else
				break;

			if( n->count == 1 )	//n이 count가 1이면
				n->left = new_node;	//부모노드 왼쪽에 넣고
			else if( n->count == 2)	//2이면
				n->right = new_node;	//오른쪽에 넣는다.

			new_node = n;	//그리고 다시 new_node에 n을 넣는다.
			break;
		}
	}


	return new_node;	//최종적인 노드를 반환한다.
}


///*************************************************
//						메인함수
///*************************************************
int main()
{
	TreeNode *root= NULL;		//트리 root 생성
	char ch[50];				//문자열 받을 char형
	int n = 0;					//문자열의 길이 
	char *pch = NULL;			//포인터

	printf("입력 : ");
	scanf("%s", ch);			//문자를 받고

	n = strlen(ch);				//문자열의 길이를 n에 저장한다
	pch = (char*)malloc(sizeof(char)*n);	//문자열의 길이만큼 포인터 동적할당을 한다
	strcpy(pch, ch);					//문자열을 포인터에 저장

	printf("레벨순회 출력 : ");
	root = checking_ch(pch);			//포인터 문자열을 하나하나씩 비교하는 함수
	level_order(root);			//레벨순회 함수
	printf("\n");
	return 0;
}

