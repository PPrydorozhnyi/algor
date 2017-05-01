#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

typedef int T;  // тип элементов
typedef long long int hashTableIndex; // индекс в хеш-таблице
#define compEQ(a,b) (a == b)
typedef struct Node_ {
       T data;// данные, хранящиеся в вершине
       struct Node_ *next; // следующая вершина
} Node;

Node **hashTable;
Node **hashTable2;
int hashTableSize;
hashTableIndex myhash(T data);
Node *insertNode2(T data);
void deleteNode2(T data);
Node *findNode2 (T data);

hashTableIndex myhash2(T data);
Node *insertNode(T data);
void deleteNode(T data);
Node *findNode (T data);

std::clock_t start, endd;

int main(){
  int i, *a, maxnum;
  cout << "Enter amount of elements maxnum : ";
  cin >> maxnum;
  cout << "Enter size of hash-table HashTableSize : ";
  cin >> hashTableSize;
  a = new int[maxnum];

  hashTable = new Node*[hashTableSize];

  hashTable2 = new Node*[hashTableSize];

  for (i = 0; i < hashTableSize; i++)
    hashTable[i] = NULL;

  for (i = 0; i < hashTableSize; i++)
    hashTable2[i] = NULL;
  // генерация массива

  for (i = 0; i < maxnum; i++)
    a[i] = rand();
  // заполнение хеш-таблицы элементами массива

  for (i = 0; i < maxnum; i++) {
    insertNode(a[i]);
  }

  for (i = 0; i < maxnum; i++) {
    insertNode2(a[i]);
  }
  // поиск элементов массива по хеш-таблице
  start = std::clock();
  for (i = maxnum-1; i >= 0; i--) {
    if (!findNode(a[17]) ) {
        insertNode(a[17]);
    }
  }
  endd = std::clock();
  std::cout << "Time: " << 1000000.0 * (endd - start) / CLOCKS_PER_SEC << " (in mks)" << std::endl;

  start = std::clock();
  for (i = maxnum-1; i >= 0; i--) {
    if (!findNode2(a[17]) ) {
        insertNode2(a[17]);
    }
  }
  endd = std::clock();
  std::cout << "Time: " << 1000.0 * (endd - start) / CLOCKS_PER_SEC << " (in ms)" << std::endl;

  // вывод элементов массива в файл List.txt
  ofstream out("List.txt");
  for (i = 0; i < maxnum; i++){
    out << a[i];
    if ( i < maxnum - 1 ) out << "\t";
  }
  out.close();
  // сохранение хеш-таблицы в файл HashTable.txt
  out.open("HashTable.txt");
  for (i = 0; i < hashTableSize; i++){
    out << i << "  :  ";
    Node *Temp = hashTable[i];
    while ( Temp ){
      out << Temp->data << " -> ";
      Temp = Temp->next;
    }
    out << endl;
  }
  out.close();
  // очистка хеш-таблицы
    for (i = maxnum-1; i >= 0; i--) {
        deleteNode(a[i]);
    }
  system("pause");
  return 0;
}

// хеш-функция размещения вершины
hashTableIndex myhash(T data) {
  return (data % hashTableSize);
}

// функция поиска местоположения и вставки вершины в таблицу
Node *insertNode(T data) {
  Node *p, *p0;
  hashTableIndex bucket;
  // вставка вершины в начало списка
  bucket = myhash(data);
  if ((p = new Node) == 0) {
    fprintf (stderr, "Memory prob (insertNode)\n");
    exit(1);
  }
  p0 = hashTable[bucket];
  hashTable[bucket] = p;
  p->next = p0;
  p->data = data;
  return p;
}

//функция удаления вершины из таблицы
void deleteNode(T data) {
  Node *p0, *p;
  hashTableIndex bucket;
  p0 = 0;
  //hashing
  bucket = myhash(data);
  p = hashTable[bucket];
  while (p && !compEQ(p->data, data)) {
    p0 = p;
    p = p->next;
  }
  if (!p) return;
  if (p0)
    p0->next = p->next;
  else
    hashTable[bucket] = p->next;
  delete p;
}

// функция поиска вершины со значением data
Node *findNode (T data) {
  Node *p;
  p = hashTable[myhash(data)];
  while (p && !compEQ(p->data, data))
    p = p->next;
  return p;
}



// хеш-функция размещения вершины
hashTableIndex myhash2(T data) {
    hashTableIndex K;
    hashTableIndex hashValue;
    if((log(hashTableSize)/log(2))<8) K = 158;
    if((log(hashTableSize)/log(2))<16 && (log(hashTableSize)/log(2))>8) K = 40503;
    if((log(hashTableSize)/log(2))<32 && (log(hashTableSize)/log(2))>16) K = 2654435769;
    hashValue = (hashTableIndex)(K * data*(pow(2,16)/pow(2,31))*(log(hashTableSize)/log(2)));
    hashValue = hashValue%hashTableSize;
    return (hashValue);
//  return (data % hashTableSize);
}

// функция поиска местоположения и вставки вершины в таблицу
Node *insertNode2(T data) {
  Node *p, *p0;
  hashTableIndex bucket;
  // вставка вершины в начало списка
  bucket = myhash2(data);
  if ((p = new Node) == 0) {
    fprintf (stderr, "Memory prob (insertNode)\n");
    exit(1);
  }
  p0 = hashTable2[bucket];
  hashTable2[bucket] = p;
  p->next = p0;
  p->data = data;
  return p;
}

//функция удаления вершины из таблицы
void deleteNode2(T data) {
  Node *p0, *p;
  hashTableIndex bucket;
  p0 = 0;
  //hashing
  bucket = myhash2(data);
  p = hashTable2[bucket];
  while (p && !compEQ(p->data, data)) {
    p0 = p;
    p = p->next;
  }
  if (!p) return;
  if (p0)
    p0->next = p->next;
  else
    hashTable2[bucket] = p->next;
  delete p;
}

// функция поиска вершины со значением data
Node *findNode2 (T data) {
  Node *p;
  p = hashTable2[myhash2(data)];
  while (p && !compEQ(p->data, data))
    p = p->next;
  return p;
}
