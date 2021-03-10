#include<cstdio>
#include<cstdlib>
#include<ctime>

int main()
{   long s,t;
    while(1){
        system("cls");
        do{
            system("data.exe > try.in"); //data¨º?¨ºy?Y¨¦¨²3¨¦3¨¬D¨°
            s=clock();
            system("my.exe < try.in > try1.out");  //a¨º?¨°a??¦Ì?3¨¬D¨°
            t=clock();
            system("std.exe < try.in > try2.out");  //b¨º??y¨¨¡¤¦Ì?3¨¬D¨°
            if(system("fc try1.out try2.out > nul"))
                break;
            else printf("AC time: %ldms\n",t-s);
        }while(1);
        printf("WA time: %ldms\n",t-s);  //??DD¨º¡À?? 
        system("fc try1.out try2.out");
        system("pause>nul");
    }
    return 0;
}

