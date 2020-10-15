#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 10

void slot_value(int *slot, int *value){
    do{
        printf("Please enter a slot between 0 - 9:\n");
        scanf("%d", slot);
    }while(*slot > 9 || *slot < 0);
    printf("Enter how much:\n");
    scanf("%d", value);
}

void add(int **data, int *datasize){
    int slot = 0, value = 0;
    slot_value(&slot, &value);
    if(datasize[slot] <= 0){
        printf("NOT ENOUGHT SPACE");
        return;
    }
    for(int count = 0; count < datasize[slot]; count++){
        if(data[slot][count] == '\0'){
            data[slot][count] = value;
            return;
        }
    }
    printf("ALL FILLED\n");
}

void pop(int **data, int *datasize){
    int slot = 0, value = 0;
    slot_value(&slot, &value);
    for(int count = 0; count < datasize[slot]; count++){
        if(data[slot][count] == value){
            data[slot][count] = '\0';
            printf("NUMBER REMOVED\n");
            return;
        }
    }
    printf("NOTHING WAS REMOVED\n");
}

void increase(int **data, int *datasize){
    int slot = 0, value = 0, oldsize = 0;
    slot_value(&slot, &value);
    oldsize = datasize[slot];
    datasize[slot] += value;
    if(datasize[slot] == value) data[slot] = malloc(sizeof(int)*datasize[slot]);
    else data[slot] = realloc(data[slot], sizeof(int)*datasize[slot]);
    for(int count = oldsize; count < datasize[slot]; count++){
        data[slot][count] = '\0';
    }
}

void list_unordered(int **data, int* datasize){
    printf("Unordered\n");
    for(int countX = 0; countX < DATASIZE; countX++){
        printf("Column number %d with size %d:\n", countX, datasize[countX]);
        for(int countY = 0; countY < datasize[countX]; countY++){
            printf("%d  ", data[countX][countY]);
        }
        printf("\n");
    }
}

void orderer(int *start, int size){
    if (size < 1)return;
    for (int count = 0; count < size; count++){
        if (start[count] > start[count + 1]){
            int temp = start[count];
            printf("&%d", start[count]);
            start[count] = start[count + 1];
            start[count + 1] = temp;
            printf("#%d\t%d\t",temp, start[count]);
        }
    }
    printf("\n");
    orderer(start, size - 1);
}

void list_aux_ordered(int **data, int* datasize){
    printf("Ordered by column\n");
    for(int countX = 0; countX < DATASIZE; countX++){
        printf("Column number %d with size %d:\n", countX, datasize[countX]);
        int column[datasize[countX]];
        for(int countY = 0; countY < datasize[countX]; countY++){
            column[countY] = data[countX][countY];
        }
        orderer(column, datasize[countX] - 1);
        for(int count = 0; count < datasize[countX]; count++){
            printf("%d  ", column[count]);
        }
        printf("\n");
    }
}

void list_ordered(int **data, int* datasize){
    printf("Ordered\n");
    int size = 0;
    for(int count = 0; count < DATASIZE; count++){
        size += datasize[count];
    }
    int column[size];
    int counter = 0;
    for(int countX = 0; countX < DATASIZE; countX++){
        for(int countY = 0; countY < datasize[countX]; countY++){
            column[counter] = data[countX][countY];
            counter++;
        }
    }
    orderer(column, size);
    for(int count = 0; count < size; count++){
        printf("%d  ", column[count]);
    }
    printf("\n");
}

void load(int **data, int *datasize){
    FILE *arq;
    arq = fopen("save.config","r");
    if(!arq){
        printf("\nFILE NOT FOUND\n");
        return;
    }

    for(int count = 0; count < DATASIZE; count++){
        fread(&datasize[count], sizeof(int), 1, arq);
    }
    for(int countX = 0; countX < DATASIZE; countX++){
        data[countX] = malloc(sizeof(int)*datasize[countX]);
        for(int countY = 0; countY < datasize[countX]; countY++){
            fread(&data[countX][countY], sizeof(int), 1, arq);
        }
    }

    fclose(arq);
}

void save(int **data, int *datasize){
    FILE *arq;
    arq = fopen("save.config","w");
    if(!arq){
        printf("\nSAVE ERROR\n");
        return;
    }

    for(int count = 0; count < DATASIZE; count++){
        fwrite(&datasize[count], sizeof(int), 1, arq);
    }
    for(int countX = 0; countX < DATASIZE; countX++){
        for(int countY = 0; countY < datasize[countX]; countY++){
            fwrite(&data[countX][countY], sizeof(int), 1, arq);
        }
    }

    fclose(arq);
}

int main()
{
    int *data[DATASIZE], datasize[DATASIZE] = {}, choose = '\0';
    load(data, datasize);
    do{
        printf("1 - Add\n\nList:\n2 - Unordered\n3 - Ordered by Structure\n4 - Ordered\n\n5 - Remove\n6 - Increase\n\n7 - Exit\n\n");
        choose = getchar();
        system("cls");
        switch(choose){
            case '1':
                add(data, datasize);
                break;
            case '2':
                list_unordered(data, datasize);
                break;
            case '3':
                list_aux_ordered(data, datasize);
                break;
            case '4':
                list_ordered(data, datasize);
                break;
            case '5':
                pop(data, datasize);
                break;
            case '6':
                increase(data, datasize);
                break;
            case '7':
                save(data, datasize);
                exit(0);
        }
        system("pause");
    }while(1);
    return 0;
}
