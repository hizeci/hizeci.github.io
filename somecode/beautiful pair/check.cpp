#include<cstdio>
#include<cstdlib>
#include<ctime>

int main()
{   long s,t;
    while(1){
        system("cls");
        do{
            system("data.exe > try.in"); //data���������ɳ���
            s=clock();
            system("my.exe < try.in > try1.out");  //a��Ҫ���ĳ���
            t=clock();
            system("std.exe < try.in > try2.out");  //b����ȷ�ĳ���
            if(system("fc try1.out try2.out > nul"))
                break;
            else printf("AC time: %ldms\n",t-s);
        }while(1);
        printf("WA time: %ldms\n",t-s);  //����ʱ�� 
        system("fc try1.out try2.out");
        system("pause>nul");
    }
    return 0;
}
