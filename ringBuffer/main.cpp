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
    int numberItem;
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
    numberItem = 0;
};
bool RingBuffer::pushItem(int item){
    if (numberItem == lengthRingBuffer)
    {
        return 1;
    };
    ptrEnd++;
    *(ptrEnd-1) = item;
    numberItem++;
    return 0;
}
int RingBuffer::popItem(){
    if (numberItem == 0)
        return INT_MIN;
    int item = *ptrHead;
    ptrHead++;
    numberItem--;
    return item;
}
void RingBuffer::print(){
    for (int i=0; i<numberItem;i++){
        printf("%d ",*(ptrHead+i));
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
        printf("3. Выход\n");
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
                    printf("Буфер пуст");
                else
                    printf("Взятый элемент: %d \n",item);
            }
            default:
                break;
        }
        ring.print();
        printf("\n");
    } while (commandSelection != 0);
    
    
    
    
    return 0;
}

