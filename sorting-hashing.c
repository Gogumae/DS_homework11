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

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
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
        printf("               [----- [이찬희] [2019068057] -----]\n");
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

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)  //array 배열이 NULL이 아니면 메모리 반환
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {  //array가 비어있으면 오류메시지 출력
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //배열 최대치까지 "a[i]" 출력 (00)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //배열 최대치까지 a[i]의 값 출력 (00000)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)  //선택정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  //0부터 배열 최대치가 될 때까지
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)  //i+1인 j가 배열 최대치가 될 때까지 1씩 늘려가면서
		{
			if (min > a[j])  //a[i] (최솟값)보다 a[j]가 작으면
			{
				min = a[j];  //최솟값을 a[j]로 설정
				minindex = j;  //최솟값의 인덱스를 j로 설정
			}
		}
		a[minindex] = a[i];  //최솟값의 인덱스 자리에 a[i]를 넣는다
		a[i] = min;  //a[i]를 최솟값으로 설정한다

        //i가 0부터 배열 최대치까지 순차적으로 a[i]를 확인하면서 i보다 큰 값들에서 a[i]보다 작은 값을 찾아 최솟값으로 설정한다
        //이후 a[i]보다 작아 최솟값이 들어가야할 a[j]에 a[i]의 값을 넣고 원래의 a[i]에 a[j]에 있던 최솟값을 넣어 정렬한다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 후 배열 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)  //0부터 배열 최대치가 될 때까지
	{
		t = a[i];  //a[i]의 값을 저장하는 t
		j = i;  //인덱스 (i)를 저장하는 j
		while (a[j-1] > t && j > 0)  //이전 칸의 값이 현재 칸의 값보다 크고, j가 0보다 크다면
		{
			a[j] = a[j-1];  //현재 칸의 값을 이전 칸의 값으로 덮는다
			j--;  //j를 1 줄인다
		}
		a[j] = t;  //반복문이 끝난 a[j]의 값을 a[i]의 값으로 덮는다

	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 후 배열 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)  //0부터 배열 최대치가 될 때까지 매 i마다
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)  //0부터 배열 최대치가 될 때까지 매 j마다
		{
			if (a[j-1] > a[j])  //현재 칸보다 이전 칸의 값이 더 크다면
			{
				t = a[j-1];  //임시 t를 사용하여 j칸과 j-1칸의 값을 변경
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 후 배열 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)  //h를 배열 중앙값으로 하고, h가 0이 되기 전까지 반으로 나눈다
	{
		for (i = 0; i < h; i++)  //i가 h보다 작은 동안
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)  //i+h가 배열 최대치보다 작을 동안 h를 더해가면서
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)  //i+h가 h-1보다 크면서 a[i]의 값이 a[i+h] (중앙을 기준으로 시작해서 a[i]의 위치) 보다 클 때
				{
					a[k] = a[k-h];  //a[k]의 값 (중앙을 기준으로 a[i]의 값)을 a[k-h] (0을 기준으로 a[i]의 값)으로 덮어씀
					k -= h;  //k에서 h를 뺀다 (0을 기준으로 한 값으로 이동)
				}
				a[k] = v;  //a[k] (0을 기준으로 한 a[i]의 값) 에 저장해놓은 a[j]의 값을 덮어씀
			}

            //h라는 배열의 중앙 기준을 설정하고 0~h-1 에 있는 값과 h~MAX_ARRAY_SIZE 에 있는 값들을 순서대로 대응시키고
            //만약 0~h-1 쪽의 값이 그 반대쪽의 값보다 크면 그 값을 서로 뒤바꾸는 정렬
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 후 배열 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];  //피봇값
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);  //a[0]부터 피봇값과 비교하며 i의 값을 증가시킴
			while(a[--j] > v);  //a[j]를 피봇값과 비교하며 j의 값을 감소시킴

			if (i >= j) break;  //i가 j보다 크거나 작아지면 반복문 종료
			t = a[i];  //임시 값 t를 사용하여 a[i]와 a[j]의 값을 교체
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];  //임시 값 t를 사용하여 a[i]와 a[n-1]의 값을 교체
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);  //i에 대하여 재귀적 사용
		quickSort(a+i+1, n-i-1);  //배열의 a+i+1과 n-i-1에 대하여 재귀적 사용
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)  //해쉬 테이블의 모든 값을 -1로 설정
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];  //a[i]를 key로 하여 해쉬 코드 생성
		hashcode = hashCode(key);

		if (hashtable[hashcode] == -1)  //해쉬 테이블에서의 해쉬 코드 칸의 값이 -1이면
		{
			hashtable[hashcode] = key;  //key로 변경
		} else 	{

			index = hashcode;  //아니면 index를 해쉬 코드로 설정

			while(hashtable[index] != -1)  //해쉬 테이블에서의 인덱스 칸 값이 -1이 아닐때까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;  //인덱스 값을 1씩 늘리면서 해쉬 코드 재생성
			}
			hashtable[index] = key;  //-1이 되면 해쉬 테이블의 인덱스 칸 값을 key로 변경
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);  //입력된 key에 대해 해쉬코드 생성

	if(ht[index] == key)  //해쉬 테이블에서의 index 값이 입력한 key와 같다면 index 리턴
		return index;

	while(ht[++index] != key)  //해쉬 테이틀에서의 index값을 1씩 늘려가면서 key값과 같지 않을 동안
	{
		index = index % MAX_HASH_TABLE_SIZE;  //인덱스 값을 토대로 해쉬 코드 재생성
	}
	return index;  //key와 같아지면 index 리턴
}


