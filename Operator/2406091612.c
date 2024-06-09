#include <stdio.h>
#include <string.h>

//Struct
struct StructName
{
    char name[16];
    int age;
    struct StructName *StructPtr;//不能含有自己，但可以有自己的型別指標
    //指向自身的結構體可在建構各種複雜的數據結構，不需重複定義
};
//Typedef
//保留字可以為資料型態建立別名，使程式更容易閱讀理解
typedef struct StructName2
{
    char name[16];
    int age;
} typedefStruct;
//enum列舉
//是一種常數定義方式，裡面的識別字會以int的型態從指定的值開始遞增排列
enum//也可以寫成typedef enum//不可修改的
{
    Sun = 0, Mon, Tue, Wed, Thu, Fri, Sat
};
enum enumWeek
{
    Sun2 = 0, Mon2, Tue2, Wed2, Thu2, Fri2, Sat2
};
//union
//主要是因為早期電腦架構記憶體空間不足，因此需要使用共用結構讓個變數共用一塊記憶體
//所需的記憶體空間大小由最大的成員變數決定
//在任意時刻只能存儲一個成員的值，修改一個成員會影響到其他成員
union unionData
{
    int i;
    float f;
    char str[20];
};

int main(int argc, char const *argv[])
{
    //bit operator
    //1 byte = 8 bit
    //short = 16bit
    //int = 32 bit
    //long = 64bit
    //char = 8 bit
    //float = 32 bit
    //double = 64 bit
    unsigned long num_a = 0x00001111;
    unsigned long num_b = 0x00000202;
    unsigned long num_c;

    num_c = num_a & (~num_b);
    num_c = num_c | num_b ;

    printf( "~num_b = %lx\n", ~num_b);//complement
    printf( "num_c = num_a & num_b = %lx\n", num_a & (~num_b) );//AND
    printf( "num_c = num_c | num_b = %lx\n", num_c);//OR
    printf( "num_a = num_a | 7 = %lx\n", num_a | 7);//OR
    printf( "!7 = %d\n", (!7) );//NOT
    printf( "(~7) = %x\n", (~7));
    printf( "num_a & (~7) = %lx\n", num_a & (~7));
    printf( "num_a ^ 7 = %lx\n", num_a ^ 7);//XOR
    printf( "num_a << 16 = %lx\n", num_a << 16);//left shift
    printf( "num_a >> 15 = %lx\n", num_a >> 12);//right shift

    printf( "char = %x\n", sizeof(char) );
    printf( "\n-----\n");
    //-----//

    //memcpy & strcpy 記憶體複製 與 字串複製
    //memcpy 可以複製任何類型資料，不處理字串結束/0的情況
    //strcpy 只能用於字串複製，不需要指定長度，會自動偵測\0為結尾
    const char *cpyStr1 = "abc\0def";
    char cpyStr2[16] = {0};
    char cpyStr3[16] = {0};
    memcpy( cpyStr2, cpyStr1, sizeof(cpyStr3));//memcpy(目標, 來源, 長度)
    strcpy( cpyStr3, cpyStr1);//strcpy(目標, 來源)
    printf( "cpyStr1 = %s\n", cpyStr1);//printf會遇到\0停止印出//cpyStr1是一個指針，指向的字符串的第一個字符，要用array觀念去想
    printf( "cpyStr2 = %s\n", cpyStr2);
    printf( "cpyStr3 = %s\n", cpyStr3);
    printf( "\n-----\n");
    //-----//

    //Struct
    struct StructName *PersonStructPtr;
    struct StructName PersonStruct = { "Jen", 30};
    PersonStructPtr = &PersonStruct;
    PersonStruct.age = 18;//'.'用於直接訪問結構體對象成員
    PersonStructPtr->age = 19;//'->'用於通過指向結構體對象的指針訪問結構體對象成員
    printf( "PersonStruct.name = %s\n", PersonStruct.name);
    printf( "PersonStruct.age = %d\n", PersonStruct.age);
    printf( "&PersonStruct.age = %x\n", &PersonStruct.age);//取值
    printf( "&PersonStruct = %x\n", &PersonStruct);
    printf( "PersonStructPtr->age = %d\n", PersonStructPtr->age);
    printf( "(*PersonStructPtr).age = %d\n", (*PersonStructPtr).age);
    printf( "&PersonStructPtr->age = %x\n", &PersonStructPtr->age);
    printf( "\n-----\n");
    //typedef
    typedefStruct typedefStructPerson = {"Jen", 32};
    printf( "typedefStructPerson.name = %s\n",typedefStructPerson.name);
    printf( "typedefStructPerson.age = %d\n", typedefStructPerson.age); 
    printf( "\n-----\n");
    //-----//
    
    //enum
    printf( "Sun = %d, Sat = %d\n", Sun, Sat);
    enum enumWeek enumWeekTest;
    enumWeekTest = Mon;
    printf( "enumWeekTest = %d\n", enumWeekTest);
    printf( "enumWeekTest = %d\n", Mon2);
    printf( "\n-----\n");
    //-----//

    //union
    //以下展示，只要改任何一個元素，裡面的記憶體就會被共用，導致其他元素的變數失真
    union unionData unionData;
    unionData.i = 10;
    printf( "After setting unionData.i:\n");
    printf( "unionData.i = %d\n", unionData.i);
    printf( "unionData.f = %f\n", unionData.f);
    printf( "unionData.str = %s\n", unionData.str);
    unionData.f = 220.5;
    printf( "After setting unionData.f:\n");
    printf( "unionData.i = %d\n", unionData.i);
    printf( "unionData.f = %f\n", unionData.f);
    printf( "unionData.str = %s\n", unionData.str);
    strcpy( unionData.str, "Hello, World!");
    printf( "After setting unionData.str:\n");
    printf( "unionData.i = %d\n", unionData.i);
    printf( "unionData.f = %f\n", unionData.f);
    printf( "unionData.str = %s\n", unionData.str);
    printf( "\n-----\n");
    //-----//
    //i++ & ++i
    int addI = 10;
    printf( "addI = %d\n", addI);
    printf( "addI++ = %d\n", addI++);
    printf( "++addI = %d\n", ++addI);
    addI = 10;
    printf( "addI++ + ++addI = %d\n", addI++ + ++addI);
    printf( "\n-----\n");
    //-----//
    return 0;
}
