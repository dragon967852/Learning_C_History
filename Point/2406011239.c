#include <stdio.h>
#include <stdlib.h>

char PrintfUppercase(char x)
{
    return x;
}
int main(int argc, char const *argv[])
{
    int a = 7;
    int *b, **c;

    b = &a;
    c = &b;

    printf( "a = %d\n", a);
    printf( "&a = %x\n", &a);
    printf( "b = &a = %x\n", b);
    printf( "*b = a = %x\n", *b);
    printf( "&b = %x\n", &b);
    printf( "c = &b = %x\n", c);
    printf( "&c = %x\n", &c);
    printf( "*c = b = &a = %x\n", *c);
    printf( "**c = *b = a = %d\n", **c);
    printf( "\n-----\n");
    //-----//

    int size = 3;
    char a_array[3] = {'1', '2', '3'};
    char *b_array[size];//是一個陣列，包含三個指向整數的指標，每個元素都是一個指標
    char (*c_array)[size];//是一個指標，指向陣列的第一個元素
    const char *d_array = "123\0abc";//指派，只有唯讀，不能寫

    for (int i = 0; i <= (size-1); i++)
    {
        /* code */
        b_array[i] = &a_array[i];
    }
    c_array = &a_array;

    for (int i = 0; i <= (size-1); i++)
    {
        /* code */
        printf( "a_array[%d] = %c\t", i, a_array[i]);
        printf( "&a_array[%d] = %x\n", i, &a_array[i]);
        printf("b_array[%d] = %x\t", i, b_array[i]);
        printf( "*b_array[%d] = %c\t", i, *b_array[i]);
        printf( "&b_array[%d] = %x\n", i, &b_array[i]);
        printf( "c_array + %d = %x\t", i, c_array + i);//當i>0，也就是指向第一個元素之後做的偏移是沒有意義的。在此偏移後的地址是char[3]
        printf( "(*c_array)[%d] = %c\t", i, (*c_array)[i]);
        printf( "&(*c_array)[%d] = %x\t", i, &(*c_array)[i]);
        printf( "&c_array + %d = %x\n", i, &c_array + i);//當i>0，也就是指向第一個元素之後做的偏移是沒有意義的，在此偏移後的char (*)[3]
        //printf( "%d \n", sizeof(char *[3]));
        printf( "d_array = %s\n", d_array);//d_array是一個指針，指向的是字符串的第一個字符，printf只印到停止\0的地方
        printf( "&d_array = %x\n", &d_array);

        printf( "\n");
    }
    printf( "\n-----\n");
    //-----//
    char (*d)(char);
    
    d = PrintfUppercase;//等同於 d = &PrintfUppercase;

    printf( "char PrintfUppercase = %x\n", &PrintfUppercase);
    printf( "char (*d)(char) = %c\t", d('T'));
    printf( "*d = %x\t", *d);//存放所指向的函數地址
    printf( "&d = %x\n", &d);//本身為指標函數，所以取址，取出自己的地址
    printf( "char PrintfUppercase(char x) = %c\t", PrintfUppercase('T'));
    
    printf( "\n-----\n");
    //-----//
    char (*e[size])(char);

    printf( "PrintfUppercase = %x\n", &PrintfUppercase);

    for (int i = 0; i <= (size - 1); i++)
    {
        /* code */
        e[i] = PrintfUppercase;//等同於 e[i] = &PrintfUppercase;
        printf( "e[%d] = %c\t", i, e[i]('T'));
        printf( "*e[%d] = %x\t", i, *e[i]);
        printf( "&e[%d] = %x\n", i, &e[i]);
    }
    printf( "\n-----\n");
    //-----//
    int g = 7;
    int h = 9;
    int * const f = &g;//要立即初始化，不能寫分開，存放的變數可以修改但是地址不能
    
    printf( "*f = g = %d\t", *f);
    printf( "&g = %x\t", &g);
    printf( "f = %x\t", f);
    printf( "&f = %x\t", &f);
    printf( " *f = h = %d\t", *f = h);
    printf( " g  = %d\n", g);

    g = 7;
    int const * const j = &g;//宣告出一個變數常量且是常量的指標，所以存放的變數不能更改，存放的指標地址也不能更改
    printf( "*j = g = %d\t", *j);
    printf( "&g = %x\t", &g);
    printf( "j = %x\t", j);
    printf( "&j = %x\t", &j);
    printf( "\n-----\n");
    //-----//
    return 0;
}
