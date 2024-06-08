#include <stdio.h>//use intput & output library
#include <stdlib.h>//use dynamic, transfer string to digital.....or so
#include <string.h>//use string library
#include <stdbool.h>//use bool library
#include <assert.h>//use assert library
//                                      Memory Allocation
// ----|-----------------------------------------------------------------------------------|0xffffffff
//   1 |                                OS Kernel space                                    |
//   G |             User code cannot read from nor write to these addresses,              |
//   B |                otherwise resulting in a "segmentataion fault"                     |
// ----|-----------------------------------------------------------------------------------|0xc0000000
//     |                                     ↓Stack↓                                       |
//     |  Actomatic variables ( local to a funciton's scope), caller's return address, etc |
//   3 |                    (grows towards lower memory address)                           |
//     |-----------------------------------------------------------------------------------|
//     |                                                                                   |
//     |                                                                                   |
//     |-----------------------------------------------------------------------------------|
//     |                                     ↑Heap↑                                        |
//     |          Dynamic memory allocation through malloc/new free/delete                 |
//     |                  ( grow towards higher memory addresses)                          |
//   G |-----------------------------------------------------------------------------------|
//     |                                     BSS                                           |
//     |             Uninitialized static variables, filled with zero                      |
//     |-----------------------------------------------------------------------------------|
//     |                                     DATA                                          |
//     |                     Staic variable explicitly initialized                         |
//     |-----------------------------------------------------------------------------------|
//     |                                     TEXT                                          |
//     |                   Binary image of the process(e.g./bin/ls)                        |
//     |-----------------------------------------------------------------------------------|0x08048000
//   B |                                                                                   |
//     |                                                                                   |
// ----|-----------------------------------------------------------------------------------|0x00000000
//-----//

//Stack
void functionStack2(int a)
{
    int stackVar = 20;
    printf( "Function2 - stack Variable : %d, Parameter : %d\n", stackVar, a);
    printf( "FunctionStack2 Address of stackvar : %x\n",&stackVar);
}
void functionStack1()
{
    int stackVar= 10;
    printf( "Function1 - stack Variable : %d\n", stackVar);
    functionStack2(stackVar);
    printf( "FunctionStack1 Address of stackvar : %x\n",&stackVar);
}
//Global
int globalVar = 30;
void functionGlobal()
{
    printf("Global Variable : %d\n" ,globalVar);
}
//Static
void staticCounter()
{
    static int counter = 0;//如果寫成int，在每次使用函數都會被初始化，從0+1
    counter++;
    printf( "Static Counter : %d\n", counter);
}
static int staticGlobalVar = 0;
void staticFunctionVar()
{
    staticGlobalVar++;
    printf( "Static Global Var : %d\n", staticGlobalVar);
}
//volatile
//多在嵌入式系統常處裡I／O、中斷、即時操作系統RTOS相關的問題
//因此編譯器不會對該變量進行操作，確保每次操作他都讀取該變數實體位址(硬體暫存器)，而不是讀取暫存器的值
int volatileVaule = 7;
volatile int *hwRegister = &volatileVaule;//模擬一個硬件寄存器 //*在作業系統當中，內存處於保護，不能再編譯時直接指派位址ex : (int *)0x40000000
volatile bool interrupt = false;//旗標中斷
void interrupt_service()//模擬中斷服務
{
    interrupt = true;
    *hwRegister = 70;//*在作業系統當中，內存處於保護，不給訪問
}
//Inline
//因作業體統與C標準協議發生影響
// inline int inlineAdd(int inlineA, int inlineB)
// {
//     return inlineA + inlineB;
// }

//前處裡器
//前處裡器，主要加入檔案的#include，巨集定義#define和#ifndef #endif條件編譯以及引入防護，或著是#pragma
//記得#define變數都要加括號，以免遇到先乘除後加減的問題
//#define
#define PI 3.1415926//常數巨集
#define Sque(x) (x)*(x)//函數巨集
#define Max(MaxA, MaxB) ( (MaxA) > (MaxB) ? (MaxA) : (MaxB) )//條件式
//範例程式 - define
//#ifndef - 檢查宏是否被定義，如果沒被定義，就進入對應的程序。可用來防止重複寫入，就是所謂的引入保護
//#ifdef - 檢查宏是否被定義，如果有定義，就進入對應的程序
//#if則與一般的if一樣，可用於更複雜的條件檢查
// config.h
// #ifndef CONFIG_H//CONFIG_H檢查宏是否被定義
// #define CONFIG_H//定義宏
// #define DEBUG_MODE//用於條件編譯
// #endif//結束條件編譯
// main.c
// #ifdef DEBUG_MODE//檢查是否有定義
// ...
// #endif
//範例程式 - define
//#pragma
//是一個預處裡指令，用於提供特定於編譯器的指示或提示，這些指示會告訴編譯器如何處裡接下來的程式碼
//不同的編譯器會支援不同的#pragma指令，因此跨平台的移植性較低
//pragma的使用方式有許多種，可於自行查詢，以下介紹message以及#pragma once
#pragma message ( "Error message\n")//編譯時，會自動跳出警告的訊息
#pragma once//該指令表示該文件只需編譯過一次

int main(int argc, char const *argv[])
{
    //Stack堆疊
    //堆疊內存用於存儲函數的局部變數和調用信息，快速但大小有限。
    //當函數調用時，這些變數和信息會壓入堆疊；當函數返回時，這些變數和信息會從堆疊彈出並釋放內存。
    //推疊通常從高地指向低地址增長，當函數返回時，內存被釋放，這些地址不再有效。
    functionStack1();//裡面包含另一個函數，可以看到兩個同樣宣告一樣名稱的變數是因為局部變數的關係，且兩個變數的地址不一樣
    printf( "\n-----\n");
    //-----//

    //Heap 堆
    //動態分配，可變大變小，需要手動管理內存
    int *heapVar = (int *)malloc(sizeof(int));
    if(heapVar == NULL){
        printf( "Memory allocation failed\n");
        //return 1; 可以這樣寫，會直接結束main這主程式
    }
    *heapVar = 20;
    printf( "Heap Variable : %d, Address : %x\n", *heapVar, heapVar);
    free(heapVar);//釋放內存，將地址還給系統，不會使heapVar的值變成NULL
    heapVar = NULL;//釋放地址之後，變成為"懸空指針"，要養成良好習慣為指針設為"NULL"
    if(heapVar == NULL){
        printf( "Heap Address : %x\n", heapVar);//釋放之後不要再去訪問*heapVar，會造成潰堤
        printf( "Memory allocation failed\n");
    }
    printf( "\n-----\n");
    //-----//

    //Global全局
    //在程序的整個生命周期內存在，用於多個函數之間共享數據，包含BSS, DATA section, text/code
    //在程序結束時釋放內存
    functionGlobal();
    globalVar = 40;
    functionGlobal();
    printf( "\n-----\n");
    //-----//

    //Static
    //局數靜態變量在函數內部聲明，只保持在整個程序運行期間，表示函數每次都會被調用其值在函數退出後保留
    staticCounter();
    staticCounter();
    staticCounter();
    //全局便量在文件頂端稱明(在函數之外)，作用域使限於該文件，其他文件不能訪問，同樣的函數也是如此－static void function()
    staticFunctionVar();
    staticFunctionVar();
    printf( "\n-----\n");
    //-----//

    //Const
    //只可讀不可寫，用來宣告常數
    //使編譯氣去保護參數
    //相對於define在預處裡階段展開，const則在編譯階段使用。
    //const在編譯階段會被執行類型檢查，define則不會
    //define直接展開不會分配記憶體，const則會在記憶體中分配
    // const int constVar = 10;
    // const int *const constPtr = &constVar; // 常量指针指向常量，嘗試修改指針的指向獲通過指針修改常量的值都會導致編譯錯誤
    // printf("Const Value: %d\n", *constPtr);
    //-----//

    //Volatile
    *hwRegister = 0;//*在作業系統當中，內存處於保護，不能再編譯時直接指派位址ex : (int *)0x40000000
    printf( "Initial hw register value : %d\n", *hwRegister);//*在作業系統當中，內存處於保護，不能再編譯時直接指派位址ex : (int *)0x40000000
    interrupt_service();
    if(interrupt){
        printf( "Interrupt occured!\n");
        printf( "New hw register value : %d\n", *hwRegister);//*在作業系統當中，內存處於保護，不能再編譯時直接指派位址ex : (int *)0x40000000
    }
    printf( "\n-----\n");
    //-----//

    //Inline
    //inline將函數設定為內函式，普通的函式會跳轉作運算，而內函式則利用插入的方式
    //因作業體統與C標準協議發生影響
    // int inlineValueA = 10;
    // int inlineValueB = 20;
    // printf( "inline Result : %d\n",inlineAdd(inlineValueA, inlineValueB));
    //-----//

    //Aserrt
    //幫助在開發和測試階段檢查程序中的假設，如果假設不成立，就會輸出一條錯誤訊息並終止程式執行
    //可用#define NDEBUG來對該文件所有的assert禁用
    int assertValue = 7;
    assert( assertValue != 7) ;//假設如果不成立，會顯示錯誤訊息以及錯誤檔案以及行數
    printf("Test output string\n");//測試是否會停止於前面的訊息
    return 0;
}
