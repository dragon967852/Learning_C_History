#include <stdio.h>

void Swap(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}
void PointSwap(int *x, int *y)//int *指向一個變量的地址，指針可以指向不同的變變量
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;

}
//以下C++才有的
// void ReferenceSwap(int &x, int &y)//int &是一個變量，綁訂到一個變量後，就不能再綁定到其他變量，且不能為空，但只要修改此變量，另一個被引用的變量也會被改變。
// {
//     int temp = x;
//     x = y;
//     y = temp;
// }

int main(int argc, char const *argv[])
{
    //Call by Value : 把值複製給對方，拿了值以後做任何改變都不會影響到原本的值
    printf( "Call by Value\n");
    int a = 5, b = 6;
    Swap( a, b);
    printf( "a = %d, b = %d\n", a, b);

    //Call by Address : 提取本身所指向的位址的值執行交換後的記憶體
    printf( "Call by Address\n");
    PointSwap(&a, &b);
    printf( "a = %d, b = %d\n", a, b);

    //Call by Reference : Call by address的進化版，就是所謂的"傳引用"，可以修改傳遞的變量，而不需要使用指針
    //printf( "Call by Reference\n");
    // ReferenceSwap(a, b);
    // printf("a = %d, b = %d\n", a, b);

    return 0;
}
