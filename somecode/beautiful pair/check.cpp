#include<cstdio>
#include<cstdlib>
#include<ctime>

int main()
{   long s,t;
    while(1){
        system("cls");
        do{
            system("data.exe > try.in"); //data是数据生成程序
            s=clock();
            system("my.exe < try.in > try1.out");  //a是要交的程序
            t=clock();
            system("std.exe < try.in > try2.out");  //b是正确的程序
            if(system("fc try1.out try2.out > nul"))
                break;
            else printf("AC time: %ldms\n",t-s);
        }while(1);
        printf("WA time: %ldms\n",t-s);  //运行时间 
        system("fc try1.out try2.out");
        system("pause>nul");
    }
    return 0;
}
