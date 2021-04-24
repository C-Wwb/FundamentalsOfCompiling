#include<cstring>
#include <iostream>
using namespace std;
/*
 *1、词法分析含义：A->C->B，如同C的作用，将A的输入文件，将其中元素分离，然后根据语
言的文法，分析这些元素，并组合表达意思。
 *2、词法分析定义：词法分析器的功能输入源程序，按照构词规则分解成一系列单词符号。
单词是语言中具有独立意义的最小单位，包括关键字、标识符、运算符、界符和常量等。
(1) 关键字 是由程序语言定义的具有固定意义的标识符。
 例如，Pascal 中的begin，end，if，while都是保留字。这些字通常不用作一般标识符。
(2) 标识符 用来表示各种名字，如变量名，数组名，过程名等等。
(3) 常数  常数的类型一般有整型、实型、布尔型、文字型等。
(4) 运算符 如+、-、*、/等等。
(5) 界符  如逗号、分号、括号、等等。
 *3、输出：词法分析器所输出单词符号常常表示成如下的二元式：
(单词种别，单词符号的属性值)
单词种别通常用整数编码。标识符一般统归为一种。常数则宜按类型（整、实、布尔等）分种。
关键字可将其全体视为一种。运算符可采用一符一种的方法。界符一般用一符一种的方法。
对于每个单词符号，除了给出了种别编码之外，还应给出有关单词符号的属性信息。
单词符号的属性是指单词符号的特性或特征。
 *4、词种对应：
 1-自变量
 2-数字
 3-关键字词组
 4-基本运算符
 5-分隔符
 */
char prog[80]/*存放输入字符串数组*/,token[8]/*存放单词自身字符串*/;
char ch/*当前字符*/;
int syn/*单词种别码*/,p/*指针*/,m=0/*指针*/,n,row,sum=0/*整形常数*/;
char *rwtab[6]={"begin","if","then","while","do","end"};
//关键字数组，关键字均为小写

void scaner()
{
/*
共分为三大块，分别是标示符、数字、符号
*/
    for(n=0;n<8;n++) token[n]='\0';
    ch=prog[p++];
    while(ch==' ')//若当前字符为空格，则指针p+1，遍历下一字符
    {
        ch=prog[p];
        p++;
    }
    if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))  //可能是标示符或者变量名
    {
        m=0;
        while((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
        {
            token[m++]=ch;//将当前字符压入token数组中预处理
            ch=prog[p++];//跳转到下一字符
        }
        token[m++]='\0';//若不匹配关键字数组，则将token数组重置，若匹配，则将当前元素的下一元素置空
        p--;//指针指向当前元素的上一元素进行处理
        syn=1;//变量词种为10
        for(n=0;n<6;n++)  //将识别出来的token预处理数组中的字符（eg if与关键字数组中的元素进行比较）
            if(strcmp(token,rwtab[n])==0)//如果对应的上，则单词种类+1
            {
                syn=3;
                break;
            }
    }
    else if((ch>='0'&&ch<='9'))  //数字
    {
        {
            sum=0;
            while((ch>='0'&&ch<='9'))
            {
                sum=sum*10+ch-'0';//判断组合数字（eg 15）
                ch=prog[p++];
            }
        }
        p--;
        syn=2;//数字的词种为11
        if(sum>32767)
            syn=-1;
    }
    else switch(ch)   //其他字符,每一个对应操作下，都设有在当前元素处理后，把下一元素入数组操作，判断与前一元素是否为组合元素
        {
            case'<':m=0;token[m++]=ch;
                ch=prog[p++];
                if(ch=='>')
                {
                    syn=4;
                    token[m++]=ch;
                }
                else if(ch=='=')
                {
                    syn=4;
                    token[m++]=ch;
                }
                else
                {
                    syn=4;
                    p--;
                }
                break;
            case'>':m=0;token[m++]=ch;
                ch=prog[p++];
                if(ch=='=')//判断是否为>=形式的组合字符
                {
                    syn=4;//>=词种为24
                    token[m++]=ch;
                }
                else
                {
                    syn=4;
                    p--;
                }
                break;
            case':':m=0;token[m++]=ch;
                ch=prog[p++];
                if(ch=='=')//如果当前元素的下一元素为“=”，则当前元素与“=”为组合符号
                {
                    syn=4;//将与等号组合符号词种设为18
                    token[m++]=ch;
                }
                else
                {
                    syn=4;
                    p--;
                }
                break;
            case'*':syn=4;token[0]=ch;break;
            case'/':syn=4;token[0]=ch;break;
            case'+':syn=4;token[0]=ch;break;
            case'-':syn=4;token[0]=ch;break;
            case'=':syn=4;token[0]=ch;break;
            case';':syn=5;token[0]=ch;break;
            case'(':syn=4;token[0]=ch;break;
            case')':syn=4;token[0]=ch;break;
            case',':syn=5;token[0]=ch;break;
            case'.':syn=5;token[0]=ch;break;
            case'#':syn=0;token[0]=ch;break;//判断结束的符号
            case'\n':syn=-2;break;
            default: syn=-1;break;
            /*
             * 对于每个输入，判断后跳转到相应的状态
             */
        }
}

int main()
{
    p=0;//指针
    row=1;
    cout<<"Please input string:"<<endl;
    do//将字符串中的字符，逐个压入prog数组中，准备接下来的处理
    {
        cin.get(ch);
        prog[p++]=ch;
    }
    while(ch!='#');//若字符串中识别到“#”，则结束识别
    p=0;
    do
    {
        scaner();
        switch(syn)//ASCLL中没有相应字符
        {
            case 2: cout<<"("<<syn<<","<<sum<<")"<<endl; break;//11
            case -1: cout<<"Error in row "<<row<<"!"<<endl; break;//ASCLL值为-1表示错误字符
            case -2: row=row++;break;//ASCLL值为-2表示组合字符
            default: cout<<"("<<syn<<","<<token<<")"<<endl;break;
        }
    }
    while (syn!=0);
}
//if i>=15 then x := y;