/*�ҥ�����
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
    int pageNum; //��{������
    int memNum; //�O�������
    int rfrStringNum; //�п�J�ѦҦr�����
    cout<<"�п�J��{������: ";
    cin>>pageNum;
    cout<<"�п�J�O����t�m���: ";
    cin>>memNum;
    cout<<"�п�J�ѦҦr�����: ";
    cin>>rfrStringNum;
    int rfrString[rfrStringNum]={};
    cout<<"�п�J�ѦҦr��: ";
    for(int i=0;i<rfrStringNum;++i){
        cin>>rfrString[i];
    }

    FIFO(rfrString,memNum,rfrStringNum);    //�I�s�禡
    Optimal(rfrString,memNum,rfrStringNum);
    LRU(rfrString,memNum,rfrStringNum);

    srand(time(NULL));
    cout<<endl<<endl<<"�H�����ͰѦҦr��: "<<endl;
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
    cout<<"FIFO��������"<<endl;
    int memFrame[memNum]={};
    for (int i= 0;i<memNum;++i) {  //��l�ưO������쬰-1
        memFrame[i]=-1;
    }

    int pageErr=0;  //�������~�Ѽ�
    int flag=0;     //������쪺FIFO�Ѽ�
    for(int i=0;i<rfrStringNum;++i){    //�|�N�ѦҦr��
        cout<<endl<<rfrString[i]<<"  ";
        int chk=1;  //�����O�_���������~
        for(int j=0;j<memNum;++j){  //�|�N���H�ˬd�ѦҦr��M��쪺�O�_�ۦP
            if(chk>memNum)
                break;
            if(memFrame[j]==rfrString[i])
                continue;
            else if(memFrame[j]!=rfrString[i] && chk==memNum){  //�ˬd���S�o�{��즳����
                memFrame[flag]=rfrString[i];  //����������
                flag++;
                pageErr++;
                if(flag>=memNum){
                    flag=0;
                }
                for(int k=0;k<memNum;++k){  //��X�������~
                    if(memFrame[k]==-1)
                        cout<<"_"<<" ";
                    else
                        cout<<memFrame[k]<<" ";
                }
            }
            chk++;
        }
    }
    cout<<endl<<"�������~����: "<<pageErr<<"��"<<endl;
}

void Optimal(int rfrString[],int memNum,int rfrStringNum){
     cout<<"--------------------------------------------"<<endl;
    cout<<"�̨Τ�������"<<endl;
    int memFrame[memNum]={};
    for (int i= 0;i<memNum;++i) {  //��l�ưO������쬰-1
        memFrame[i]=-1;
    }
    int pageErr=0;  //�������~�Ѽ�
    for(int i=0;i<rfrStringNum;++i){    //�|�N�ѦҦr��
        cout<<endl<<rfrString[i]<<"  ";
        int chk=1;
        int flag=0;  //�����O�_���������~
        for(int j=0;j<memNum;++j){  //�|�N���H�ˬd�ѦҦr��M��쪺�O�_�ۦP
            if(chk>memNum)
                break;
            if(memFrame[j]==rfrString[i])
                continue;
            else if(memFrame[j]!=rfrString[i] && chk==memNum){  //�ˬd���S�o�{��즳����,�������~
                pageErr++;
                flag=1;
            }
            chk++;
        }

        int memChk[memNum]={};  //�O��������ˬd�}�C
        int memflag=0;  //�O�������ƶq�ˬd�Ѽ�
        if(flag==1){    //�p�G�o�ͤ������~
            for(int k=i;k<rfrStringNum;++k){  //�}�l����̨Τ�������
                for(int m=0;m<memNum;++m){    //�|�N��e�ѦҦr��H�᪺�}�C,�éM�����
                    if(memFrame[m]==-1){        //�p�G���O�����N�����[�J
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                    if(memFrame[m]==rfrString[k] && memChk[m]==0 && memflag!=memNum-1){
                        memChk[m]=1;            //�r��M���ۦP�N�]�w�ˬd��
                        memflag++;
                        break;
                    }
                    if(memChk[m]==0 && memflag==memNum-1){  //�Q���ˬd�ȶi�����
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                }

                if(memflag==memNum)
                    break;
                if(memflag!=memNum && k==rfrStringNum-1){     //�p�G�᭱�ѦҦr�곣�S�X�{�A�N��LRU�����k
                    for(int n=i;n>=0;--n){  //����LRU��������
                        for(int m=0;m<memNum;++m){  //�|�N��e�ѦҦr�ꤧ�e���}�C,�éM�����
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
            for(int k=0;k<memNum;++k){  //��X�������~
                if(memFrame[k]==-1)
                    cout<<"_"<<" ";
                else
                    cout<<memFrame[k]<<" ";
            }
        }
    }
    cout<<endl<<"�������~����: "<<pageErr<<"��"<<endl;
}

void LRU(int rfrString[],int memNum,int rfrStringNum){
     cout<<"--------------------------------------------"<<endl;
    cout<<"LRU��������"<<endl;
    int memFrame[memNum]={};
    for (int i= 0;i<memNum;++i) {  //��l�ưO������쬰-1
        memFrame[i]=-1;
    }
    int pageErr=0;  //�������~�Ѽ�
    for(int i=0;i<rfrStringNum;++i){    //�|�N�ѦҦr��
        cout<<endl<<rfrString[i]<<"  ";
        int chk=1;
        int flag=0;  //�����O�_���������~�Ѽ�
        for(int j=0;j<memNum;++j){  //�|�N���H�ˬd�ѦҦr��M��쪺�O�_�ۦP
            if(chk>memNum)
                break;
            if(memFrame[j]==rfrString[i])
                continue;
            else if(memFrame[j]!=rfrString[i] && chk==memNum){  //�ˬd���S�o�{��즳����,�������~
                pageErr++;
                flag=1;
            }
            chk++;
        }

        int memChk[memNum]={};  //�O��������ˬd�}�C
        int memflag=0;  //�O�������ƶq�ˬd�Ѽ�
        if(flag==1){    //�p�G�o�ͤ������~
            for(int k=i;k>=0;--k){          //�}�l����LRU��������
                for(int m=0;m<memNum;++m){      //�|�N��e�ѦҦr�ꤧ�e���}�C,�éM�����
                    if(memFrame[m]==-1){         //�p�G���O�����N�����[�J
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                    if(memFrame[m]==rfrString[k] && memChk[m]==0 && memflag!=memNum-1){
                        memChk[m]=1;            //�r��M���ۦP�N�]�w�ˬd��
                        memflag++;
                        break;
                    }
                    if(memChk[m]==0 && memflag==memNum-1){  ////�Q���ˬd�ȶi�����
                        memFrame[m]=rfrString[i];
                        memflag=memNum;
                        break;
                    }
                }
                if(memflag==memNum)
                    break;
            }
            for(int k=0;k<memNum;++k){  //��X�������~
                if(memFrame[k]==-1)
                    cout<<"_"<<" ";
                else
                    cout<<memFrame[k]<<" ";
            }
        }
    }
    cout<<endl<<"�������~����: "<<pageErr<<"��";

}
