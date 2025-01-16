#include<stdio.h>
#include <stdlib.h>
// C 程序的內存分配
// 全局變量和靜態局部變量 : 內存中的靜態存儲區/全局區
// 非靜態的局部變量 : 內存中的動態儲存區stack棧
// 臨時使用的數據 : 建立動態內存分配區域，需要時隨時開闢，不需要時及時釋放 : heap堆，malloc()等函數動態分配的數據
// 根據需要向”系統申請”所需大小的空間，由於未在聲明部分定義其變量或者數組，不能通過變量名或者數組來飲用這些數據，只能通過”指針”來引用
// 記得要初始化，相較於calloc，不一樣

// 聲明結構體
struct Node
{
  int data;
  struct Node *next;
};
typedef struct BTNode
{
  int data;
  struct BTNode *lchild;
  struct BTNode *rchild;
}BTNode;


int main()
{
  // void 指針(無類型指針)
  // 有時候系統請求內存得時候，不確定會有什麼樣的數據寫入內存，需要先獲得內存塊，稍後卻在確定寫入的數據類型
  // 此時C語言提供一種叫void指針，只有內存塊的地址信息，沒有類型信息，等到使用該內存在向編譯器補充說明
  // 可以指向任何類型的數據，但是不能解讀數據。void指針與其他所有類型指針之間是”相互轉換關係”
  int x = 10;
  void *p = &x;
  int *r = p; // int y = *p 會無法解讀出void類型指向的數據
  int z = *((int *)p);// 可以強轉換
  printf("%d\n", z);


  // 內存動態分配函數
  // <stdio.h>聲明了四個關於內存動態分配的函數。所謂的動態分配內存，就是按需分配，申請才能獲得
 
  // malloc : void *malloc( unsigned int size);// 使用頻率高
  // 在內存的動態儲存區(堆區)中分配一個長度為size的”連續空間”。並將該空間的首地址作為函數值返回。如果分配不成功，返回空指針(NULL)。
  // 給int類型的變量分配空間
   int *ptr_i;
  ptr_i = (int *)malloc(sizeof(int));
  *ptr_i = 10;
  printf("%d\n", *ptr_i);
  // 給int類型的數組分配空間
  int arrLen = 10;
  int *ptr_arr;
  ptr_arr = (int *)malloc(arrLen * sizeof(int));
  for(int i = 0; i < arrLen; i++)// 初始化
  {
    ptr_arr[i] = i;
    printf("ptr_arr[%d] = %d\n",i ,i);
  }
  // // 結構體變量分配空間
  struct Node * ptr_node;
  ptr_node = (struct Node *)malloc(sizeof(struct Node));
  BTNode * ptr_btNode;
  ptr_btNode = (BTNode  *)malloc(sizeof(BTNode));
  // 萬一分配失敗的判斷
  if(ptr_node != NULL)// 不為空表示分配成功
  {
    printf("分配成功\n");
  }

  // free : void free(void *p);
  // 釋放指針變量所指向的內存空間，使內存能重新被其他變量使用，否則這個內存塊會一直占用到程序運行結束。
  // 如果函數執行完之後，變數就會找不到，但是內存依然保存住，會發生找不到他，但內存依然存在，會造成內存洩漏
// 不用再double free了
  printf("準備釋放空間\n");
  free(ptr_node);
  free(ptr_arr);
  free(ptr_btNode);

  return  0;
}
