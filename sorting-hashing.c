/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
        printf("               [----- [������] [2019068057] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)  //array �迭�� NULL�� �ƴϸ� �޸� ��ȯ
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {  //array�� ��������� �����޽��� ���
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //�迭 �ִ�ġ���� "a[i]" ��� (00)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //�迭 �ִ�ġ���� a[i]�� �� ��� (00000)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)  //��������
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //���� �� �迭 ���

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  //0���� �迭 �ִ�ġ�� �� ������
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)  //i+1�� j�� �迭 �ִ�ġ�� �� ������ 1�� �÷����鼭
		{
			if (min > a[j])  //a[i] (�ּڰ�)���� a[j]�� ������
			{
				min = a[j];  //�ּڰ��� a[j]�� ����
				minindex = j;  //�ּڰ��� �ε����� j�� ����
			}
		}
		a[minindex] = a[i];  //�ּڰ��� �ε��� �ڸ��� a[i]�� �ִ´�
		a[i] = min;  //a[i]�� �ּڰ����� �����Ѵ�

        //i�� 0���� �迭 �ִ�ġ���� ���������� a[i]�� Ȯ���ϸ鼭 i���� ū ���鿡�� a[i]���� ���� ���� ã�� �ּڰ����� �����Ѵ�
        //���� a[i]���� �۾� �ּڰ��� ������ a[j]�� a[i]�� ���� �ְ� ������ a[i]�� a[j]�� �ִ� �ּڰ��� �־� �����Ѵ�
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //���� �� �迭 ���
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //���� �� �迭 ���

	for(i = 1; i < MAX_ARRAY_SIZE; i++)  //0���� �迭 �ִ�ġ�� �� ������
	{
		t = a[i];  //a[i]�� ���� �����ϴ� t
		j = i;  //�ε��� (i)�� �����ϴ� j
		while (a[j-1] > t && j > 0)  //���� ĭ�� ���� ���� ĭ�� ������ ũ��, j�� 0���� ũ�ٸ�
		{
			a[j] = a[j-1];  //���� ĭ�� ���� ���� ĭ�� ������ ���´�
			j--;  //j�� 1 ���δ�
		}
		a[j] = t;  //�ݺ����� ���� a[j]�� ���� a[i]�� ������ ���´�

	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //���� �� �迭 ���

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //���� �� �迭 ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++)  //0���� �迭 �ִ�ġ�� �� ������ �� i����
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)  //0���� �迭 �ִ�ġ�� �� ������ �� j����
		{
			if (a[j-1] > a[j])  //���� ĭ���� ���� ĭ�� ���� �� ũ�ٸ�
			{
				t = a[j-1];  //�ӽ� t�� ����Ͽ� jĭ�� j-1ĭ�� ���� ����
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //���� �� �迭 ���

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //���� �� �迭 ���

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)  //h�� �迭 �߾Ӱ����� �ϰ�, h�� 0�� �Ǳ� ������ ������ ������
	{
		for (i = 0; i < h; i++)  //i�� h���� ���� ����
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)  //i+h�� �迭 �ִ�ġ���� ���� ���� h�� ���ذ��鼭
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)  //i+h�� h-1���� ũ�鼭 a[i]�� ���� a[i+h] (�߾��� �������� �����ؼ� a[i]�� ��ġ) ���� Ŭ ��
				{
					a[k] = a[k-h];  //a[k]�� �� (�߾��� �������� a[i]�� ��)�� a[k-h] (0�� �������� a[i]�� ��)���� ���
					k -= h;  //k���� h�� ���� (0�� �������� �� ������ �̵�)
				}
				a[k] = v;  //a[k] (0�� �������� �� a[i]�� ��) �� �����س��� a[j]�� ���� ���
			}

            //h��� �迭�� �߾� ������ �����ϰ� 0~h-1 �� �ִ� ���� h~MAX_ARRAY_SIZE �� �ִ� ������ ������� ������Ű��
            //���� 0~h-1 ���� ���� �� �ݴ����� ������ ũ�� �� ���� ���� �ڹٲٴ� ����
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);  //���� �� �迭 ���

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];  //�Ǻ���
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);  //a[0]���� �Ǻ����� ���ϸ� i�� ���� ������Ŵ
			while(a[--j] > v);  //a[j]�� �Ǻ����� ���ϸ� j�� ���� ���ҽ�Ŵ

			if (i >= j) break;  //i�� j���� ũ�ų� �۾����� �ݺ��� ����
			t = a[i];  //�ӽ� �� t�� ����Ͽ� a[i]�� a[j]�� ���� ��ü
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];  //�ӽ� �� t�� ����Ͽ� a[i]�� a[n-1]�� ���� ��ü
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);  //i�� ���Ͽ� ����� ���
		quickSort(a+i+1, n-i-1);  //�迭�� a+i+1�� n-i-1�� ���Ͽ� ����� ���
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)  //�ؽ� ���̺��� ��� ���� -1�� ����
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];  //a[i]�� key�� �Ͽ� �ؽ� �ڵ� ����
		hashcode = hashCode(key);

		if (hashtable[hashcode] == -1)  //�ؽ� ���̺����� �ؽ� �ڵ� ĭ�� ���� -1�̸�
		{
			hashtable[hashcode] = key;  //key�� ����
		} else 	{

			index = hashcode;  //�ƴϸ� index�� �ؽ� �ڵ�� ����

			while(hashtable[index] != -1)  //�ؽ� ���̺����� �ε��� ĭ ���� -1�� �ƴҶ�����
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;  //�ε��� ���� 1�� �ø��鼭 �ؽ� �ڵ� �����
			}
			hashtable[index] = key;  //-1�� �Ǹ� �ؽ� ���̺��� �ε��� ĭ ���� key�� ����
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);  //�Էµ� key�� ���� �ؽ��ڵ� ����

	if(ht[index] == key)  //�ؽ� ���̺����� index ���� �Է��� key�� ���ٸ� index ����
		return index;

	while(ht[++index] != key)  //�ؽ� ����Ʋ������ index���� 1�� �÷����鼭 key���� ���� ���� ����
	{
		index = index % MAX_HASH_TABLE_SIZE;  //�ε��� ���� ���� �ؽ� �ڵ� �����
	}
	return index;  //key�� �������� index ����
}


