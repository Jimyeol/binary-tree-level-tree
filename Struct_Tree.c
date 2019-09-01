#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///*************************************************
//						Ʈ�� ����ü
///*************************************************
typedef struct TreeNode {
	char data;
	int count;
	struct TreeNode *left, *right;
} TreeNode;
typedef TreeNode* element;


///*************************************************
//						ť ����ü
///*************************************************
typedef struct QueueNode{
	element item;
	struct QueueNode *link;
} QueueNode;
typedef struct {
	QueueNode *front, *rear;
} QueueType;


///*************************************************
//						���� ����ü
///*************************************************
typedef struct StackNode {
	element item;
	struct StackNode *link;
} StackNode;
typedef struct {
	StackNode *top;
} LinkedStackType;



///*************************************************
//					���� �ʱ�ȭ �Լ�
///*************************************************
void stack_init(LinkedStackType *s)
{
	s->top = NULL;
}


///*************************************************
//					���� ������� �Լ�
///*************************************************
int stack_is_empty(LinkedStackType *s)
{
	return (s->top == NULL);
}


///*************************************************
//					���� ����ִ� �Լ�
///*************************************************
void push(LinkedStackType *s, element item)
{
	StackNode *temp=(StackNode *)malloc(sizeof(StackNode));
	if( temp == NULL ){
		printf("�޸� ����\n");
		return;
	}
	else{
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}


///*************************************************
//					���� ������ �Լ�
///*************************************************
element pop(LinkedStackType *s)
{
	if( stack_is_empty(s) ) {
		printf("������ ��� �ֽ��ϴ�\n");
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
//						ť �ʱ�ȭ �Լ�
///*************************************************
void init(QueueType *q)
{
	q->front = q->rear = NULL;
}


///*************************************************
//					ť ���鿩���Լ�
///*************************************************
int is_empty(QueueType *q)
{
	return (q->front == NULL );
}


///*************************************************
//						��ť�Լ�
///*************************************************
void enqueue(QueueType *q, element item)
{
	QueueNode *temp=(QueueNode*)malloc(sizeof(QueueType));
	if(temp==NULL) printf("�޸𸮸� �Ҵ��� �� �����ϴ�.\n");
	else{	//������ ���� �ƴϸ�
		temp->item = item; temp->link = NULL;	//������ ���� �ְ� ��ũ�� ���� �ֽ��ϴ�.
		if (is_empty(q)) q->front = q->rear = temp;	//���� ť�� ��������� ����Ʈ�� ��� temp�� 
													//�ʱ�ȭ�ϰ�
		else { //�װ� �ƴ϶��
			q->rear->link = temp;	//ť�� ���ũ�� temp�� �ְ�
			q->rear = temp;	//ť�� ��� temp�� �ֽ��ϴ�
		}
	}
}


///*************************************************
//						��ť�Լ�
///*************************************************
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	element item;
	if (is_empty(q)) printf("ť�� ��� �ֽ��ϴ�.\n");
	else {
		item = temp->item;		//itemp�� �̾Ƴ� item�� ����ְ�
		q->front = q->front->link;		//����Ʈ�� ����Ʈ�� ��ũ�� �ٲٰ�
		if (q->front == NULL) q->rear = NULL;		//����Ʈ�� ���̸� ��� ���Դϴ�.
		free(temp);		//temp�� �����
		return item;		//�̾Ƴ� item�� ��ȯ���ݴϴ�.
	}
}


///*************************************************
//						������ȸ�Լ�
///*************************************************
void level_order(TreeNode *ptr)	//��ȸ�Լ�
{
	QueueType q;
	init(&q);	//ť�� �ʱ�ȭ �ϰ�
	if (!ptr) return;
	enqueue(&q, ptr);	//ť�� ��带 �ְ�
	while (!is_empty(&q)){		//�Ⱥ��������
		ptr = dequeue(&q);	//�ϳ��� ������.
		printf("%c ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}


///*************************************************
//					���ο��� �����Լ�
///*************************************************
element createNode(char ch)	//���ο� ��带 �����ϰ� �ʱ�ȭ �ϴ� �Լ�
{
	element newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = ch;
	newNode->count = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}


///*************************************************
//						���� üũ �Լ�
///*************************************************
TreeNode* checking_ch(char *pch)
{
	TreeNode *new_node = NULL;		//���ο� ���
	TreeNode *n = NULL;			//��Ʈ���
	int i = 0;
	LinkedStackType *L = (LinkedStackType*)malloc(sizeof(LinkedStackType));	//������ �����Ѵ�.
	stack_init(L);	//������ �ʱ�ȭ�ϰ�

	for( i = 0; pch[i] != NULL; i++)	//���ڿ� NULL�� �ɶ����� ����/
	{
		switch( pch[i] )		//���� �ϳ��ϳ����� ���Ѵ�
		{
		case '(':
			new_node = createNode(pch[++i]);	//(�������� ���ڰ� ���⶧���� Ʈ����带 �����ϰ� new_node�� ����ִ´�
			break;
		case ',':
			new_node->count++;		//','������ŭ ++�Ѵ�
			if( pch[i+1] == '(' ) push(L, new_node);	//���� ','������ '('�̸� ���� ��带 ���ÿ� ���� �ִ´�
			break;
		case ')':
			if( !stack_is_empty(L))		//������ �Ⱥ��������
				n = pop(L);		//��ȣ�� ������ �θ��带 �ٽ� n�� �ִ´�.
			else
				break;

			if( n->count == 1 )	//n�� count�� 1�̸�
				n->left = new_node;	//�θ��� ���ʿ� �ְ�
			else if( n->count == 2)	//2�̸�
				n->right = new_node;	//�����ʿ� �ִ´�.

			new_node = n;	//�׸��� �ٽ� new_node�� n�� �ִ´�.
			break;
		}
	}


	return new_node;	//�������� ��带 ��ȯ�Ѵ�.
}


///*************************************************
//						�����Լ�
///*************************************************
int main()
{
	TreeNode *root= NULL;		//Ʈ�� root ����
	char ch[50];				//���ڿ� ���� char��
	int n = 0;					//���ڿ��� ���� 
	char *pch = NULL;			//������

	printf("�Է� : ");
	scanf("%s", ch);			//���ڸ� �ް�

	n = strlen(ch);				//���ڿ��� ���̸� n�� �����Ѵ�
	pch = (char*)malloc(sizeof(char)*n);	//���ڿ��� ���̸�ŭ ������ �����Ҵ��� �Ѵ�
	strcpy(pch, ch);					//���ڿ��� �����Ϳ� ����

	printf("������ȸ ��� : ");
	root = checking_ch(pch);			//������ ���ڿ��� �ϳ��ϳ��� ���ϴ� �Լ�
	level_order(root);			//������ȸ �Լ�
	printf("\n");
	return 0;
}

