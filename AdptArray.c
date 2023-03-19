#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC printFunc_){
PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL){
        printf("malloc didnt work");
		return NULL;
	}
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr){
	if (pArr == NULL)
		return;
	for(int i = 0; i < pArr->ArrSize; ++i){
        if(pArr->pElemArr[i]!=NULL)
		    pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem){
PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;
	if (idx >= pArr->ArrSize){	

		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}
	if(pArr->pElemArr[idx]!=NULL)
	    pArr->delFunc((pArr->pElemArr)[idx]);
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if (pArr==NULL || idx < 0 || idx >= pArr->ArrSize) {
        printf("array not found");
        return NULL;
    }
    PElement temp = pArr->pElemArr[idx];
    if (temp==NULL) {
        return NULL;
    }
    return pArr->copyFunc(temp);
}

int GetAdptArraySize(PAdptArray pArr){
    if (pArr==NULL || pArr->ArrSize < 1) {
        printf("array not found");
        return -1;
    }
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr){
    if (pArr==NULL) {
        printf("array not found");
        return;
    }
    for(int i=0;i<pArr->ArrSize;i++){
        if(pArr->pElemArr[i]!=NULL){
            printf("the %d element -> " , i);
            pArr->printFunc(pArr->pElemArr[i]);
        }
    }
}


