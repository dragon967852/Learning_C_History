#include<stdio.h>
#include<stdlib.h>

int main()
{
  // calloc : void *calloc(unsigned int n, unsigned int size);
  // 比較少用
  // 作用在內存的動態儲存區中分配n個，單位長度為size的連續空間，總共占用n*size個字節
  // 適合唯一維數組開闢動態儲存空間，n個數組元素個數，每個元素長度為size。
  // 相較
  int *p;
  p = (int *)calloc(10, sizeof(int));
  // 檢查分配是否成功
  if (p == NULL) {
      printf("記憶體分配失敗\n");
      return 1;
  }
  // 初始化與使用記憶體
  for (int i = 0; i < 10; i++) {
      p[i] = i + 1; // 將每個元素設置為 i + 1
      printf("p[%d] = %d\n", i, p[i]);
  }
  // 釋放記憶體
  free(p);

  // realloc() : void *realloc(void* p, unsigned int size)
  // 作用: 重新分配malloc()或calloc()函數獲得的動態空間大小
  // 如果新內存塊小於原來的大小，則丟棄超出的部分
  int *b;
  b = (int *)malloc(sizeof(int) * 10);
  printf("%d\n", sizeof(int) * 10);
  b = (int *)realloc(b ,sizeof(int) * 20);
  printf("%d\n", sizeof(int) * 20);
  // 釋放記憶體
  free(b);
}
