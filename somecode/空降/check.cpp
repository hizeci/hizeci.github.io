#include<cstdio>
#include<cstdlib>
#include<ctime>

int main()
{   long s,t;
    while(1){
        system("cls");
        do{
            system("data.exe > try.in"); //data��?��y?Y����3��3��D��
            s=clock();
            system("my.exe < try.in > try1.out");  //a��?��a??��?3��D��
            t=clock();
            system("std.exe < try.in > try2.out");  //b��??y������?3��D��
            if(system("fc try1.out try2.out > nul"))
                break;
            else printf("AC time: %ldms\n",t-s);
        }while(1);
        printf("WA time: %ldms\n",t-s);  //??DD����?? 
        system("fc try1.out try2.out");
        system("pause>nul");
    }
    return 0;
}

