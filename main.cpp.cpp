#include<iostream>
#include<windows.h>
#include<winuser.h>

using namespace std;
int main(){
    MSG msg;

    while(GetMessage (&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
 return 0;
}
