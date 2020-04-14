#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//ПРИМЕЧАНИЕ
//У меня был 15 вариант задания, я не смог реализовать алгоритм для быстрого перебора всех чисел на проверку того, являются ли они действительными числами или нет
//Вместо этого я создал программу для выполнения большинства базовых операций связанных с длинной арифметикой
//Моя программа частично решает варианты заданий(осталось только реализовать алгоритм быстрого перебора всех простых чисел для указанного):2,10,15,
//И полностью решает варианты:4,7,12,14,19,21,24,26,29
//Надеюсь, для хорошей оценки этого будет достаточно





const int BASE = 10;

struct Queue{
    int info;
    struct Queue * next;
    struct Queue * prev;
};



void Delete_Queue(struct Queue** beg){
        struct Queue* t;
        while(*beg != NULL) {
                t = *beg;
                *beg = (*beg) -> next;
                free(t);
        }

}


void Convert(int n,char s[154]){
    char str[154];
    int i=0;
    while(n>0){
        str[i]=(n%10)+'0';
        n/=10;
        i++;
    }
    str[i]='\0';
    i=0;
    for(int j=strlen(str)-1;j>=0;j--){
        s[i]=str[j];
        i++;
    }
    s[i]='\0';
}


void Substract(struct Queue **beg1,struct Queue **end1,struct Queue *beg2,struct Queue *end2, int*  _is_negative1,int* _is_negative2);
void Push_back(struct Queue** beg,struct Queue** end,int value){
        struct Queue *new_item=NULL;
        if(*beg==NULL){
            if(!(new_item=(struct Queue*)malloc(sizeof(struct Queue)))){
                 printf("Can't alloc memory\n");
                 exit(-1);
            }
            new_item->info=value;
            new_item->next=new_item->prev=NULL;
            *beg=*end=new_item;
        }
        else{
           if(!(new_item=(struct Queue*)malloc(sizeof(struct Queue)))){
                printf("Can't alloc memory\n");
                exit(-1);
           }
           new_item->info=value;
           new_item -> next = NULL; 		// Следующего нет
           new_item -> prev = *end;		// Связываем новый с последним
           (*end) -> next = new_item; 		// Изменяем адрес next бывшего последнего
           *end =new_item;
        }		// Изменяем указатель end

}


int SIZE(struct Queue *beg){
    struct Queue * t=beg;
    int n=0;
    while(t!=NULL){
        n++;
        t=t->next;
    }
    return n;
}
void Pop_back(struct Queue** end){
        if(*end!=NULL){
            struct Queue *removed=*end;
            (*end) = (*end) -> prev;
            if(*end!=NULL){
                (*end) -> next = NULL;
            }
            free (removed);
        }
}

void PrintBigInt(struct Queue *t,int _is_negative){
    if(t==NULL){
        printf("0");
    }
    if(_is_negative==1){
        printf("-");
    }
    while(t!=NULL){
        printf("%d",t->info);
        t=t->prev;
    }
    printf("\n");
}


int CreateBigInt(struct Queue **beg,struct Queue **end, char str[]){
    if(str[0]=='-'){
        for(int i=strlen(str)-1;i>=1;i--){
            Push_back(beg,end,(int)(str[i]-'0'));
        }
        return 1;
    }
    else {
        for(int i=strlen(str)-1;i>=0;i--){
            Push_back(beg,end,(int)(str[i]-'0'));
        }
        return 0;
    }
    return -1;
}

void RemoveLeadingZeros(struct Queue **beg,struct Queue **end,int * _is_negative) {
        while (SIZE(*beg)> 1 && (*end)->info == 0) {
                Pop_back(end);
        }


        if ( SIZE(*beg) == 1) {
            if((*beg)->info == 0){
                 *_is_negative = 0;
            }

        }
}



int Equals(struct Queue *beg1,struct Queue *beg2, int  _is_negative1,int  _is_negative2){
    if(_is_negative1!=_is_negative2){
        return 0;
    }
    if(SIZE(beg1)==0){
        if(SIZE(beg2)==0||(SIZE(beg2)==1&&beg2->info==0))return 1;
            else return 0;
    }
    if(SIZE(beg2)==0){
        if(SIZE(beg1)==0||(SIZE(beg1)==1&&beg1->info==0))return 1;
            else return 0;
    }
    if(SIZE(beg1)!=SIZE(beg2)) return 0;
    struct Queue * t1=beg1;
    struct Queue * t2=beg2;
    while(t1!=NULL){
        if(t1->info!=t2->info){
            return 0;
        }
        t1=t1->next;
        t2=t2->next;
    }
    return 1;

}

int NotEquals(struct Queue *beg1,struct Queue *beg2, int  _is_negative1,int  _is_negative2){
    return !(Equals(beg1,beg2,_is_negative1,_is_negative2));
}




int StrictlyLess(struct Queue *beg1,struct Queue *beg2,struct Queue *end1,struct Queue *end2, int  _is_negative1,int  _is_negative2){

    if(Equals(beg1,beg2,_is_negative1,_is_negative2)){
        return 0;
    }
    if(_is_negative1==1&&_is_negative2==0){
        return 1;
    }
    if(_is_negative1==0&&_is_negative2==1){
        return 0;
    }
    if(_is_negative1==1&&_is_negative2==1){
        _is_negative1=0;
        _is_negative2=0;
        return !StrictlyLess(beg1,beg2,end1,end2, _is_negative1, _is_negative2);
    }
    if(_is_negative1==0&&_is_negative2==0){
        if(SIZE(beg1)!=SIZE(beg2)){
            if(SIZE(beg1)-SIZE(beg2)>0){
                return 0;
            }
            else return 1;
        }
        else {
            struct Queue * t1=end1;
            struct Queue * t2=end2;
            while(t1!=NULL){
                if(t1->info!=t2->info){
                    if(t1->info>t2->info){
                        return 0;
                    }
                    else return 1;
                }
                t1=t1->prev;
                t2=t2->prev;
            }
            return 0;
        }
    }
    return -1;
}







int Less(struct Queue *beg1,struct Queue *beg2,struct Queue *end1,struct Queue *end2, int  _is_negative1,int  _is_negative2){
    return ((StrictlyLess(beg1,beg2, end1,end2,   _is_negative1,  _is_negative2))||(Equals(beg1,beg2,_is_negative1,_is_negative2)));
}


int StrictlyMore(struct Queue *beg1,struct Queue *beg2,struct Queue *end1,struct Queue *end2, int  _is_negative1,int  _is_negative2){
    return !(Less(beg1,beg2, end1,end2,   _is_negative1,  _is_negative2));
}


int More(struct Queue *beg1,struct Queue *beg2,struct Queue *end1,struct Queue *end2, int  _is_negative1,int  _is_negative2){
    return !(StrictlyLess(beg1,beg2, end1,end2,   _is_negative1,  _is_negative2));
}


void Add(struct Queue **beg1,struct Queue **end1,struct Queue *beg2,struct Queue *end2, int*  _is_negative1,int* _is_negative2){

    if (*_is_negative1!=0) {
            if (* _is_negative2!=0) {
                *_is_negative1=1;
            }
            else {
                *_is_negative1=0;
                if(StrictlyLess(*beg1,beg2,*end1,end2,*_is_negative1,*_is_negative2)!=0){
                    Substract(&beg2,&end2,*beg1,*end1,_is_negative1,_is_negative2);
                }
                else {
                    Substract(beg1,end1,beg2,end2,_is_negative1,_is_negative2);
                    *_is_negative1=1;
                }
                return;

            }
    }
    else if (*_is_negative2!=0) {
        *_is_negative2=0;
        Substract(beg1,end1,beg2,end2,_is_negative1,_is_negative2);
        *beg1=beg2;
        *end1=end2;
        return;
    }
    int carry=0;
    struct Queue * t1=*beg1;
    struct Queue * t2=beg2;
    while(t1!=NULL||t2!=NULL||carry!=0){
        if(t1==NULL){
            Push_back(beg1,end1,0);
            t1=*end1;
        }
        (t1)->info+=carry+(t2!=NULL ? t2->info : 0);
        carry= t1->info >= BASE;
        if(carry!=0){
            (t1)->info -= BASE;
        }
        (t1)=(t1)->next;
        if(t2!=NULL){
            t2=t2->next;
        }
    }
}










void Substract(struct Queue **beg1,struct Queue **end1,struct Queue *beg2,struct Queue *end2, int*  _is_negative1,int* _is_negative2){

    if(*_is_negative2!=0){
        *_is_negative2=0;
        Add(beg1,end1,beg2,end2,_is_negative1,_is_negative2);
        return;
    }
    else if(*_is_negative1!=0){
        *_is_negative1=0;
        Add(beg1,end1,beg2,end2,_is_negative1,_is_negative2);
        *_is_negative1=1;
        return;
    }
    else if(StrictlyLess(*beg1,beg2,*end1,end2,*_is_negative1,*_is_negative2)!=0){
        Substract(&beg2,&end2,*beg1,*end1,_is_negative1,_is_negative2);
        *beg1=beg2;
        *end1=end2;
        *_is_negative1=1;
        return;
    }
    int carry=0;
    struct Queue * t1=*beg1;
    struct Queue * t2=beg2;
    while(t2!=NULL||carry!=0){
            t1->info-=carry+(t2!=NULL ? t2->info : 0);
            carry=t1->info<0;
            if(carry!=0)t1->info+=BASE;
            t1=t1->next;
            if(t2!=NULL){
                t2=t2->next;
            }

    }
    RemoveLeadingZeros(beg1,end1,_is_negative1);
}




void Multiply(struct Queue **beg1,struct Queue **end1,struct Queue *beg2,int*  _is_negative1,int _is_negative2){
    struct Queue* t=*beg1;
    struct Queue* begout=NULL;
    struct Queue* endout=NULL;
    while(t!=NULL){
        Push_back(&begout,&endout,0);
        t=t->next;
    }
    t=beg2;
    while(t!=NULL){
        Push_back(&begout,&endout,0);
        t=t->next;
    }
    t=*beg1;
    int n=0;
    while(t!=NULL){
        int carry=0;
        struct Queue* t1=beg2;
        int m=0;
        while(t1!=NULL||carry!=0){
            struct Queue* t2=begout;
            for(int i=0;i<(n+m);i++){
                t2=t2->next;
            }
            long long cur=t2->info+t->info*(t1!=NULL ? t1->info : 0)+ carry;
            t2->info=(int)cur%BASE;
            carry=(int)cur/BASE;
            if(t1!=NULL){
                t1=t1->next;
            }
            m++;
        }
        t=t->next;
        n++;
    }
    Delete_Queue(beg1);
    *beg1=begout;
    *end1=endout;
    int help=0;
    RemoveLeadingZeros(beg1,end1,&help);
    if((*_is_negative1!=0&&_is_negative2==0)||(*_is_negative1==0&&_is_negative2!=0)){
        *_is_negative1=1;
    }
    else *_is_negative1=0;

}



void ShiftRight(struct Queue **beg,struct Queue **end){
    if(*beg==NULL){
        Push_back(beg,end,0);
        return;
    }
    Push_back(beg,end,(*end)->info);
    struct Queue* t=*end;
    while(t->prev!=NULL){
        t->info=t->prev->info;
        t=t->prev;
    }
    t->info=0;
}



void Divide(struct Queue **beg1,struct Queue **end1,struct Queue *beg2,int*  _is_negative1,int _is_negative2){
    struct Queue* helpbeg=NULL;
    struct Queue* helpend=NULL;
    int help_is_negative=0;
    Push_back(&helpbeg,&helpend,0);
    if(Equals(beg2,helpbeg,_is_negative2,help_is_negative)){
        printf("Division by zero is incorrect\n");
        return;
    }
    struct Queue* t=*beg1;
    struct Queue* begout=NULL;
    struct Queue* endout=NULL;
    struct Queue* currentbeg=NULL;
    struct Queue* currentend=NULL;
    int current_is_negative=0;
    while(t!=NULL){
        Push_back(&begout,&endout,0);
        t=t->next;
    }
    t=*end1;
    struct Queue* t1=endout;
    while(t!=NULL){
        ShiftRight(&currentbeg,&currentend);
        currentbeg->info=t->info;
        RemoveLeadingZeros(&currentbeg,&currentend,&current_is_negative);
        int x=0, l=0, r=BASE;
        while(l<=r){
            int m=(l+r)/2;
            struct Queue* begit=NULL;
            struct Queue* endit=NULL;
            Push_back(&begit,&endit,m);
            Multiply(&begit,&endit,beg2,&help_is_negative,help_is_negative);
            if(Less(begit,currentbeg,endit,currentend,help_is_negative,help_is_negative)){
                x=m;
                l=m+1;
            }
            else r=m-1;
            Delete_Queue(&begit);

        }
        t1->info=x;
        struct Queue* begit=NULL;
        struct Queue* endit=NULL;
        Push_back(&begit,&endit,x);
        Multiply(&begit,&endit,beg2,&help_is_negative,help_is_negative);
        Substract(&currentbeg,&currentend,begit,endit,&help_is_negative,&help_is_negative);
        Delete_Queue(&begit);
        t=t->prev;
        t1=t1->prev;
    }
    if((*_is_negative1!=0&&_is_negative2==0)||(*_is_negative1==0&&_is_negative2!=0)){
        *_is_negative1=1;
    }
    else *_is_negative1=0;
    *beg1=begout;
    *end1=endout;
    int help=0;
    RemoveLeadingZeros(beg1,end1,&help);

}




void Residue(struct Queue **beg1,struct Queue **end1,struct Queue *beg2,struct Queue *end2,int*  _is_negative1,int _is_negative2){
    struct Queue* begout=*beg1;
    struct Queue* endout=*end1;
    int help=*_is_negative1;
    Divide(&begout,&endout,beg2,&help,_is_negative2);
    Multiply(&begout,&endout,beg2,&help,_is_negative2);
    Substract(beg1,end1,begout,endout,_is_negative1,&help);
    if(*_is_negative1){
        Add(beg1,end1,beg2,end2,_is_negative1,&_is_negative2);
    }
}







int Odd(struct Queue* beg) {
        if (beg == NULL) return 0;
        if((beg->info&1)==0){
            return 0;
        }
        else return 1;
}


int Even(struct Queue*beg){
    return !Odd(beg);
}


void Power(struct Queue **beg1,struct Queue **end1,struct Queue *beg2,struct Queue *end2,int*  _is_negative1,int _is_negative2){
    if(Even(beg2)){
        *_is_negative1=0;
    }
    struct Queue* begout=NULL;
    struct Queue* endout=NULL;
    Push_back(&begout,&endout,1);
    struct Queue* helpbeg=NULL;
    struct Queue* helpend=NULL;
    int help_is_negative=0;
    Push_back(&helpbeg,&helpend,0);
    if(Less(beg2,helpbeg,end2,helpend,_is_negative2,help_is_negative)){
        printf("Input power>0\n");
        return;
    }
    while(!Equals(beg2,helpbeg,_is_negative2,help_is_negative)){
        if(Odd(beg2)){
            Multiply(&begout,&endout,*beg1,&help_is_negative,*_is_negative1);
        }
        struct Queue* t1=*beg1;
        Multiply(beg1,end1,t1,&help_is_negative,*_is_negative1);
        struct Queue* begit=NULL;
        struct Queue* endit=NULL;
        Push_back(&begit,&endit,2);
        Divide(&beg2,&end2,begit,& _is_negative2,help_is_negative);
        Delete_Queue(&begit);

    }
    Delete_Queue(&helpbeg);
    Delete_Queue(beg1);
    *beg1=begout;
    *end1=endout;

}




void gcd (struct Queue **beg1,struct Queue **end1,struct Queue **beg2,struct Queue **end2,int*  _is_negative1,int* _is_negative2) {
    struct Queue* helpbeg=NULL;
    struct Queue* helpend=NULL;
    int help_is_negative=0;
    Push_back(&helpbeg,&helpend,0);
    if(Equals(*beg1,helpbeg,*_is_negative1,help_is_negative)){
        *_is_negative1=0;
        *beg1=*beg2;
        *end1=*end2;
        Delete_Queue(&helpbeg);
        return;
    }
    if (Equals(*beg2,helpbeg,*_is_negative2,help_is_negative)){
        *_is_negative1=0;
        Delete_Queue(&helpbeg);
        return;
    }
    for ( ; ; ){
        Residue(beg1,end1,*beg2,*end2,_is_negative1,*_is_negative2);
        if(Equals(*beg1,helpbeg,*_is_negative1,help_is_negative)){
            *_is_negative1=0;
            *beg1=*beg2;
            *end1=*end2;
            Delete_Queue(&helpbeg);
            return;
        }
        else {
           Residue(beg2,end2,*beg1,*end1,_is_negative2,*_is_negative1);
           if (Equals(*beg2,helpbeg,*_is_negative2,help_is_negative)){
               *_is_negative1=0;
               Delete_Queue(&helpbeg);
               return;
           }
        }
    }
    Delete_Queue(&helpbeg);
}




void Perevod(struct Queue **beg1,struct Queue **end1,int*  _is_negative1,int n){
    int temp=* _is_negative1;
    * _is_negative1=0;
    struct Queue* beg=NULL;
    struct Queue* end=NULL;
    int _is_negative=0;
    Push_back(&beg,&end,0);
    struct Queue* helpbeg=NULL;
    struct Queue* helpend=NULL;
    int help_is_negative=0;
    Push_back(&helpbeg,&helpend,0);
    // из десятичного в двоичное
    for(int j=0;!Equals(*beg1,helpbeg,*_is_negative1,help_is_negative) ; j++){
        struct Queue* iterbeg=NULL;
        struct Queue* iterend=NULL;
        int iter_is_negative=0;
        struct Queue* powerbeg=NULL;
        struct Queue* powerend=NULL;
        int power_is_negative=0;
        if(j!=0){
           char s[154];
           Convert(j,s);
           iter_is_negative=CreateBigInt(&iterbeg,&iterend,s);
           char s1[154];
           Convert(10,s1);
           power_is_negative=CreateBigInt(&powerbeg,&powerend,s1);
           Power(&powerbeg,&powerend,iterbeg,iterend,&power_is_negative,iter_is_negative);
        }
        struct Queue* help1beg=NULL;
        struct Queue* help1end=NULL;
        int help1_is_negative=0;
        Push_back(&help1beg,&help1end,n);



        struct Queue* copybeg1=NULL;
        struct Queue* copyend1=NULL;
        int copy_is_negative=0;
        struct Queue* t=*beg1;
        while(t!=NULL){
            Push_back(&copybeg1,&copyend1,t->info);
            t=t->next;
        }
        Residue(&copybeg1,&copyend1,help1beg,help1end,&copy_is_negative,help1_is_negative);
        if(j!=0){
            Multiply(&copybeg1,&copyend1,powerbeg,&copy_is_negative,power_is_negative);
        }
        Add(&beg,&end,copybeg1,copyend1,&_is_negative,&copy_is_negative);
        Divide(beg1,end1,help1beg,_is_negative1,help1_is_negative);
        Delete_Queue(&help1beg);
        Delete_Queue(&copybeg1);
    }
    Delete_Queue(beg1);
    Delete_Queue(&helpbeg);
    *beg1=beg;
    *end1=end;
    *_is_negative1=temp;
}






int main(){




    char str2[154];
    struct Queue* beg1=NULL;
    struct Queue* end1=NULL;
    int _is_negative1=0;
    Push_back(&beg1,&end1,3);
    printf("Input pow of 3\n");
    scanf("%s",str2);
    for(unsigned long long int i=0;i<strlen(str2);i++){
        if(str2[i]=='-'&&i!=0){
            printf("wrong input \n");
            return -1;
        }
        if(str2[i]!='0'&&str2[i]!='1'&&str2[i]!='2'&&str2[i]!='3'&&str2[i]!='4'&&str2[i]!='5'&&str2[i]!='6'&&str2[i]!='7'&&str2[i]!='8'&&str2[i]!='9'&&str2[i]!='-'){
            printf("wrong input \n");
            return -1;
        }
    }
    struct Queue* beg2=NULL;
    struct Queue* end2=NULL;
    int _is_negative2=CreateBigInt(&beg2,&end2,str2);
    RemoveLeadingZeros(&beg2,&end2,&_is_negative2);
    Power(&beg1,&end1,beg2,end2,&_is_negative1,_is_negative2);
    printf("pow of 3: ");
    PrintBigInt(end1,_is_negative1);
    struct Queue* beg3=NULL;
    struct Queue* end3=NULL;
    int _is_negative3=0;
    Push_back(&beg3,&end3,1);
    for(int i=2;i<101;i++){
        struct Queue* factbeg=NULL;
        struct Queue* factend=NULL;
        char s[154];
        Convert(i,s);
        int fact_is_negative=CreateBigInt(&factbeg,&factend,s);
        Multiply(&beg3,&end3,factbeg,&_is_negative3,fact_is_negative);
        Delete_Queue(&factbeg);
    }
    printf("100!= ");
    PrintBigInt(end3,_is_negative3);
    char str5[154];
    char str6[154];
    struct Queue* beg5=NULL;
    struct Queue* end5=NULL;
    printf("Input first value \n");
    scanf("%s",str5);
    for(unsigned long long int i=0;i<strlen(str5);i++){
        if(str5[i]=='-'&&i!=0){
            printf("wrong input \n");
            return -1;
        }
        if(str5[i]!='0'&&str5[i]!='1'&&str5[i]!='2'&&str5[i]!='3'&&str5[i]!='4'&&str5[i]!='5'&&str5[i]!='6'&&str5[i]!='7'&&str5[i]!='8'&&str5[i]!='9'&&str5[i]!='-'){
            printf("wrong input \n");
            return -1;
        }
    }
    int _is_negative5=CreateBigInt(&beg5,&end5,str5);
    RemoveLeadingZeros(&beg5,&end5,&_is_negative5);
    printf("Input second value \n");
    scanf("%s",str6);
    for(unsigned long long int i=0;i<strlen(str6);i++){
        if(str6[i]=='-'&&i!=0){
            printf("wrong input \n");
            return -1;
        }
        if(str6[i]!='0'&&str6[i]!='1'&&str6[i]!='2'&&str6[i]!='3'&&str6[i]!='4'&&str6[i]!='5'&&str6[i]!='6'&&str6[i]!='7'&&str6[i]!='8'&&str6[i]!='9'&&str6[i]!='-'){
            printf("wrong input \n");
            return -1;
        }
    }
    struct Queue* beg6=NULL;
    struct Queue* end6=NULL;
    int _is_negative6=CreateBigInt(&beg6,&end6,str6);
    RemoveLeadingZeros(&beg6,&end6,&_is_negative6);
    gcd(&beg5,&end5,&beg6,&end6,&_is_negative5,&_is_negative6);
    printf("NOD of this  values: ");
    PrintBigInt(end5,_is_negative5);
    struct Queue* beg7=NULL;
    struct Queue* end7=NULL;
    int _is_negative7=CreateBigInt(&beg7,&end7,str5);
    RemoveLeadingZeros(&beg7,&end7,&_is_negative7);
    struct Queue* beg8=NULL;
    struct Queue* end8=NULL;
    int _is_negative8=CreateBigInt(&beg8,&end8,str6);
    RemoveLeadingZeros(&beg8,&end8,&_is_negative8);
    Multiply(&beg7,&end7,beg8,&_is_negative7,_is_negative8);
    Divide(&beg7,&end7,beg5,&_is_negative7,_is_negative5);
    printf("NOK of this  values: ");
    PrintBigInt(end7,_is_negative7);

    char str9[154];
    struct Queue* beg9=NULL;
    struct Queue* end9=NULL;
    struct Queue* beg10=NULL;
    struct Queue* end10=NULL;
    printf("input value\n");
    scanf("%s",str9);
    for(unsigned long long int i=0;i<strlen(str9);i++){
        if(str9[i]=='-'&&i!=0){
            printf("wrong input \n");
            return -1;
        }
        if(str9[i]!='0'&&str9[i]!='1'&&str9[i]!='2'&&str9[i]!='3'&&str9[i]!='4'&&str9[i]!='5'&&str9[i]!='6'&&str9[i]!='7'&&str9[i]!='8'&&str9[i]!='9'&&str9[i]!='-'){
            printf("wrong input \n");
            return -1;
        }
    }
    int _is_negative9=CreateBigInt(&beg9,&end9,str9);
    RemoveLeadingZeros(&beg9,&end9,&_is_negative9);
    Perevod(&beg9,&end9,&_is_negative9,2);
    printf("Value in 2 number system: ");
    PrintBigInt(end9,_is_negative9);
    int _is_negative10=CreateBigInt(&beg10,&end10,str9);
    RemoveLeadingZeros(&beg10,&end10,&_is_negative10);
    Perevod(&beg10,&end10,&_is_negative10,8);
    printf("Value in 8 number system: ");
    PrintBigInt(end10,_is_negative10);
    Delete_Queue(&beg1);
    Delete_Queue(&beg2);
    Delete_Queue(&beg3);
    Delete_Queue(&beg5);
    Delete_Queue(&beg6);
    Delete_Queue(&beg7);
    Delete_Queue(&beg8);
    Delete_Queue(&beg9);
    Delete_Queue(&beg10);

}




