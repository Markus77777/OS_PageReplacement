/*課本測資
10
3
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void FIFO(int[],int,int);  //function prototypes
void Optimal(int[],int,int);
void LRU(int[],int,int);

int main()
{
    int pageNum; //行程分頁數
    int memNum; //記憶體欄數
    int rfrStringNum; //請輸入參考字串長度
    cout<<"請輸入行程分頁數: ";
    cin>>pageNum;
    cout<<"請輸入記憶體配置欄數: ";
    cin>>memNum;
    cout<<"請輸入參考字串長度: ";
    cin>>rfrStringNum;
    int rfrString[rfrStringNum]={};
    cout<<"請輸入參考字串: ";
    for(int i=0;i<rfrStringNum;++i){
        cin>>rfrString[i];
    }

    FIFO(rfrString,memNum,rfrStringNum);    //呼叫函式
    Optimal(rfrString,memNum,rfrStringNum);
    LRU(rfrString,memNum,rfrStringNum);

    srand(time(NULL));
    cout<<endl<<endl<<"隨機產生參考字串: "<<endl;
    for(int i=0;i<rfrStringNum;++i){
       rfrString[i]=rand()%pageNum;
    }
    FIFO(rfrString,memNum,rfrStringNum);
    Optimal(rfrString,memNum,rfrStringNum);
    LRU(rfrString,memNum,rfrStringNum);

    return 0;
}

void FIFO(int rfrString[],int memNum,int rfrStringNum){
    cout<<"--------------------------------------------"<<endl;
    cout<<"FIFO分頁替換"<<endl;
    int memFrame[memNum]={};
    for (int i= 0;i<memNum;++i) {  //初始化記憶體欄位為-1
        memFrame[i]=-1;
    }

    int pageErr=0;  //分頁錯誤參數
    int flag=0;     //替換欄位的FIFO參數
    for(int i=0;i<rfrStringNum;++i){    //疊代參考字串
        cout<<endl<<rfrString[i]<<"  ";
        int chk=1;  //紀錄是否有分頁錯誤
        for(int j=0;j<memNum;++j){  //疊代欄位以檢查參考字串和欄位的是否相同
            if(chk>memNum)
                break;
            if(memFrame[j]==rfrString[i])
                continue;
            else if(memFrame[j]!=rfrString[i] && chk==memNum){  //檢查完沒發現欄位有分頁
                memFrame[flag]=rfrString[i];  //替換欄位分頁
                flag++;
                pageErr++;
                if(flag>=memNum){
                    flag=0;
                }
                for(int k=0;k<memNum;++k){  //輸出分頁錯誤
                    if(memFrame[k]==-1)
                        cout<<"_"<<" ";
                    else
                        cout<<memFrame[k]<<" ";
                }
            }
            chk++;
        }
    }
    cout<<endl<<"分頁錯誤次數: "<<pageErr<<"次"<<endl;
}

void Optimal(int rfrString[],int memNum,int rfrStringNum){
     cout<<"--------------------------------------------"<<endl;
    cout<<"最佳分頁替換"<<endl;
    int memFrame[memNum]={};
    for (int i= 0;i<memNum;++i) {  //初始化記憶體欄位為-1
        memFrame[i]=-1;
    }
    int pageErr=0;  //分頁錯誤參數
    for(int i=0;i<rfrStringNum;++i){    //疊代參考字串
        cout<<endl<<rfrString[i]<<"  ";
        int chk=1;
        int flag=0;  //紀錄是否有分頁錯誤
        for(int j=0;j<memNum;++j){  //疊代欄位以檢查參考字串和欄位的是否相同
            if(chk>memNum)
                break;
            if(memFrame[j]==rfrString[i])
                continue;
            else if(memFrame[j]!=rfrString[i] && chk==memNum){  //檢查完沒發現欄位有分頁,分頁錯誤
                pageErr++;
                flag=1;
            }
            chk++;
        }

        int memChk[memNum]={};  //記憶體欄位檢查陣列
        int memflag=0;  //記憶體欄位數量檢查參數
        if(flag==1){    //如果發生分頁錯誤
            for(int k=i;k<rfrStringNum;++k){  //開始執行最佳分頁替換
                for(int m=0;m<memNum;++m){    //疊代當前參考字串以後的陣列,並和欄位比較
                    if(memFrame[m]==-1){        //如果欄位是空欄位就直接加入
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                    if(memFrame[m]==rfrString[k] && memChk[m]==0 && memflag!=memNum-1){
                        memChk[m]=1;            //字串和欄位相同就設定檢查值
                        memflag++;
                        break;
                    }
                    if(memChk[m]==0 && memflag==memNum-1){  //利用檢查值進行替換
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                }

                if(memflag==memNum)
                    break;
                if(memflag!=memNum && k==rfrStringNum-1){     //如果後面參考字串都沒出現，就用LRU替換法
                    for(int n=i;n>=0;--n){  //執行LRU分頁替換
                        for(int m=0;m<memNum;++m){  //疊代當前參考字串之前的陣列,並和欄位比較
                            if(memFrame[m]==-1){
                                memFrame[m]=rfrString[i];
                                memflag=memNum;
                                break;
                            }
                            if(memFrame[m]==rfrString[n] && memChk[m]==0 && memflag!=memNum-1){
                                memChk[m]=1;
                                memflag++;
                                break;
                            }
                            if(memChk[m]==0 && memflag==memNum-1){
                                memFrame[m]=rfrString[i];
                                memflag=memNum;
                                break;
                            }
                        }
                        if(memflag==memNum)
                            break;
                    }
                    break;
                }
            }
            for(int k=0;k<memNum;++k){  //輸出分頁錯誤
                if(memFrame[k]==-1)
                    cout<<"_"<<" ";
                else
                    cout<<memFrame[k]<<" ";
            }
        }
    }
    cout<<endl<<"分頁錯誤次數: "<<pageErr<<"次"<<endl;
}

void LRU(int rfrString[],int memNum,int rfrStringNum){
     cout<<"--------------------------------------------"<<endl;
    cout<<"LRU分頁替換"<<endl;
    int memFrame[memNum]={};
    for (int i= 0;i<memNum;++i) {  //初始化記憶體欄位為-1
        memFrame[i]=-1;
    }
    int pageErr=0;  //分頁錯誤參數
    for(int i=0;i<rfrStringNum;++i){    //疊代參考字串
        cout<<endl<<rfrString[i]<<"  ";
        int chk=1;
        int flag=0;  //紀錄是否有分頁錯誤參數
        for(int j=0;j<memNum;++j){  //疊代欄位以檢查參考字串和欄位的是否相同
            if(chk>memNum)
                break;
            if(memFrame[j]==rfrString[i])
                continue;
            else if(memFrame[j]!=rfrString[i] && chk==memNum){  //檢查完沒發現欄位有分頁,分頁錯誤
                pageErr++;
                flag=1;
            }
            chk++;
        }

        int memChk[memNum]={};  //記憶體欄位檢查陣列
        int memflag=0;  //記憶體欄位數量檢查參數
        if(flag==1){    //如果發生分頁錯誤
            for(int k=i;k>=0;--k){          //開始執行LRU分頁替換
                for(int m=0;m<memNum;++m){      //疊代當前參考字串之前的陣列,並和欄位比較
                    if(memFrame[m]==-1){         //如果欄位是空欄位就直接加入
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                    if(memFrame[m]==rfrString[k] && memChk[m]==0 && memflag!=memNum-1){
                        memChk[m]=1;            //字串和欄位相同就設定檢查值
                        memflag++;
                        break;
                    }
                    if(memChk[m]==0 && memflag==memNum-1){  ////利用檢查值進行替換
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                }
                if(memflag==memNum)
                    break;
            }
            for(int k=0;k<memNum;++k){  //輸出分頁錯誤
                if(memFrame[k]==-1)
                    cout<<"_"<<" ";
                else
                    cout<<memFrame[k]<<" ";
            }
        }
    }
    cout<<endl<<"分頁錯誤次數: "<<pageErr<<"次";

}
