//
//  main.cpp
//  ringBuffer
//
//  Created by Артем on 04.03.2018.
//  Copyright © 2018 Артем. All rights reserved.
//

#include <iostream>
class RingBuffer{
private:
    int lengthRingBuffer;
    int *ringBuffer;
    int *ptrHead, *ptrEnd;
    bool change = 0;
public:
    RingBuffer(int lengthRingBuffer);
    bool pushItem(int);
    int  popItem();
    void print();
};
RingBuffer::RingBuffer(int length){
    lengthRingBuffer = length;
    ringBuffer = new int [lengthRingBuffer];
    ptrEnd = ringBuffer;
    ptrHead = ringBuffer;
};
bool RingBuffer::pushItem(int item){
    if (change && (ptrEnd == ptrHead))
    {
        return 1;
    };
    *ptrEnd = item;
    long newIndexEnd = (ptrEnd - ringBuffer + 1 );
    if (newIndexEnd >= lengthRingBuffer )
        change = 1;
    ptrEnd = ringBuffer + (newIndexEnd % lengthRingBuffer);
    return 0;
}
int RingBuffer::popItem(){
    if (!change && (ptrEnd == ptrHead))
        return INT_MIN;
    int item = *ptrHead;
    long newIndexBegin = ptrHead - ringBuffer +1 ;
    if (newIndexBegin >= lengthRingBuffer)
        change = 0;
    ptrHead = ringBuffer + (newIndexBegin % lengthRingBuffer);
    return item;
}
void RingBuffer::print(){
    long numberItems = change? lengthRingBuffer - (ptrHead-ptrEnd):ptrEnd-ptrHead;
    if (numberItems == 0)
        printf("Буфер пуст");
    for (int i=0; i<numberItems; i++){
        printf("%d ",*(ringBuffer + (((ptrHead - ringBuffer) + i)%lengthRingBuffer)));
    }
}

int main(int argc, const char * argv[]) {
    printf("Имитация работы кольцевого буфера\n");
    printf("Введите размерность буфера: ");
    int length = 0;
    scanf("%i",&length);
    RingBuffer ring(length);
    int commandSelection = 0;
    do {
        printf("1. Добавить элемент в буфер\n");
        printf("2. Взять элемент из буфера\n");
        printf("0. Выход\n");
        printf("Выберите команду: ");
        scanf("%i",&commandSelection);
        printf("\n");
        switch (commandSelection) {
            case 1:{
                int item = 0;
                printf("Введите элемент который хотите добавить: ");
                scanf("%i",&item);
                if (ring.pushItem(item)){
                    printf("Буфер переполнен. Добавление не произведено \n");
                }
                break;
            }
            case 2:{
                int item = ring.popItem();
                if (item == INT_MIN)
                    printf("Буфер пуст. Команда не выполнена \n");
                else
                    printf("Взятый элемент: %d \n",item);
                break;
            }
            default:
                printf("Выберите верную команду!:");
                break;
        }
        printf("Буфер: ");
        ring.print();
        printf("\n");
    } while (commandSelection != 0);
    
    
    
    
    return 0;
}

