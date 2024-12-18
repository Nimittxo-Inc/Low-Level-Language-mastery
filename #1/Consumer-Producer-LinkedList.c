#include <windows.h>
#include <stdio.h>
#include <stddef.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


#define NBFR    64                      /* number of buffers */
#define BFRSZ   0x10000                 /* buffer size */

typedef struct _NODE                    /* node structure */
{
  struct _NODE pNext;                  /* ptr to next node */
    BYTE       pBfr;                   /* ptr to buffer */
    DWORD       dwCnt;                  /* # bytes in buffer */
}NODE;

typedef struct _LIST                    /* linked List structure */
{
    NODE       pFirst;                 /* ptr to 1st  node */
    NODE       pLast;                  /* ptr to last node */
    HANDLE      hMtxSem[2];             /* mutex and semaphore handles */
}LIST;
#define hMtx hMtxSem[0]                 /* mutex        == ownership */
#define hSem hMtxSem[1]                 /* semaphore    == list count */

/*----------------------------------------------------------------------*/
/*      data                                                            */
/*----------------------------------------------------------------------*/
static HANDLE   htT1;                   /* thread handles */
static LIST     llT0;                   /* thread 0 list */
static LIST     llT1;                   /* thread 1 list */
static NODE     aNode[NBFR];            /* array of nodes */
static DWORD    fExitThread;            /* flag to indicate thread exit */
static DWORD    dwThreadT1;             /* thread id's (not used) */
static DWORD    dwExitCode;             /* exit code */
static HANDLE   hSrc;                   /* file I/O */
static HANDLE   hDst;                   /*HANDLE type is a pointer used by Windows API*/
static PBYTE    pMem;                   /* ptr to allocated memory */
/*----------------------------------------------------------------------/
/      code                                                            /
/----------------------------------------------------------------------*/
static DWORD    WINAPI Thread0(LPVOID);
static DWORD    WINAPI Thread1(LPVOID);
static void     InitThread0List(void);
static NODE *   GetNode(LIST *);
static DWORD    PutNode(LIST *, NODE *);
/*----------------------------------------------------------------------/
/*      main                                                            /
/----------------------------------------------------------------------*/
DWORD main(DWORD argc, BYTE **argv)
{
    hSrc    = INVALID_HANDLE_VALUE;     /* init file handles to not open */
    hDst    = INVALID_HANDLE_VALUE;
    if(argc != 3){
        printf("usage is mtcopy <src> <dst>\n");
        goto exit0;}
    pMem = malloc(BFRSZ*NBFR);          /* allocate memory */
    if(!pMem){
        _cputs("can't allocate enough memory\r\n");
        goto exit0;}
    hSrc = CreateFile(argv[1],          /* open src file */
            GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    if(hSrc == INVALID_HANDLE_VALUE){
        printf("Can't open %s\n", argv[1]);
        goto exit0;}
    hDst = CreateFile(argv[2],          /* open dst file */
        GENERIC_ALL , 0, NULL, CREATE_ALWAYS, FILE_FLAG_BACKUP_SEMANTICS, 0);
    if(hDst == INVALID_HANDLE_VALUE){
        printf("Can't create %s\n", argv[2]);
        goto exit0;}
    /*  create mutex and semaphore for each list */
    if((llT0.hSem = CreateSemaphore(NULL,0,NBFR+1,NULL))==NULL){
        _cputs("can't create semaphore\r\n");
        goto exit0;}
    if((llT0.hMtx = CreateMutex(NULL,FALSE,NULL))==NULL){
        _cputs("can't create mutex\r\n");
        goto exit0;}
    if((llT1.hSem = CreateSemaphore(NULL,0,NBFR+1,NULL))==NULL){
        _cputs("can't create semaphore\r\n");
        goto exit0;}
    if((llT1.hMtx = CreateMutex(NULL,FALSE,NULL))==NULL){
        _cputs("can't create mutex\r\n");
        goto exit0;}
    /*  create threads */
    htT1 = CreateThread(NULL, 0, Thread1, 0, 0, &dwThreadT1);
    if(!htT1){
        _cputs("can't create thread\r\n");
        goto exit0;}
    InitThread0List();                  /* init Thread 0 list */
    Thread0((LPVOID)NULL);              /* start Thread 0 */
exit0:
    if(htT1){                           /* close thread */
        WaitForSingleObject(htT1, INFINITE);
        CloseHandle(htT1);}
    if(llT1.hSem){                      /* close mutex, semaphore */
        CloseHandle(llT1.hSem);}
    if(llT1.hMtx){
        CloseHandle(llT1.hMtx);}
    if(llT0.hSem){
        CloseHandle(llT0.hSem);}
    if(llT0.hMtx){
        CloseHandle(llT0.hMtx);}
    if(hDst != INVALID_HANDLE_VALUE){   /* close files */
        CloseHandle(hDst);}
    if(hSrc != INVALID_HANDLE_VALUE){
        CloseHandle(hSrc);}
    if(pMem){                           /* free memory */
        free(pMem);}
    return(0);
}
/*----------------------------------------------------------------------/
/*      Thread0         read bfr from file 0                            /
/----------------------------------------------------------------------*/
static DWORD WINAPI Thread0(LPVOID lpvoid)
{
NODE *pNode;
    while(1){
        pNode = GetNode(&llT0);         /* get node */
        ReadFile(hSrc, pNode->pBfr, BFRSZ, &(pNode->dwCnt), NULL);
        PutNode(&llT1, pNode);          /* send node to thread 1 */
        if(pNode->dwCnt == 0){          /* exit if end of file */
            return(0);}}
}
/*----------------------------------------------------------------------/
/*      Thread1         write bfr to file 1                             /
/----------------------------------------------------------------------*/
static DWORD WINAPI Thread1(LPVOID lpvoid)
{
NODE *pNode;
DWORD dwWrite;
DWORD dwCnt = 1;
    while(dwCnt){
        pNode = GetNode(&llT1);         /* get node */
        dwCnt = pNode->dwCnt;           /* localize count */
        if(dwCnt)                       /* write data if count != 0 */
            WriteFile(hDst, pNode->pBfr, dwCnt, &dwWrite, NULL);
        PutNode(&llT0, pNode);}         /* return node to thread 0 */
    return(0);
}
/*----------------------------------------------------------------------/
/*      InitThread0List init thread 0 list                              /
/----------------------------------------------------------------------*/
static void InitThread0List(void)
{
BYTE * pBfr;
DWORD i;
    pBfr = pMem;
    for(i = 0; i < NBFR; i++){
        aNode[i].pBfr = pBfr;
        PutNode(&llT0, &aNode[i]);
        pBfr += BFRSZ;}
}
/*----------------------------------------------------------------------*/
/*      GetNode     get first node from list                            */
/*                                                                      */
/*  WaitForMultipleObjects eliminates any thread priority issues        */
/*----------------------------------------------------------------------*/

// Assuming NODE and LIST structs are defined as follows:
typedef struct _NODE {
    BYTE *pBfr;        // Pointer to a buffer
    DWORD dwCnt;       // Some count
    struct _NODE *pNext; // Pointer to the next node
} NODE;

typedef struct _LIST {
    NODE *pFirst; // Pointer to the first node
    NODE *pLast;  // Pointer to the last node
    HANDLE hMtx;  // Mutex handle
    HANDLE hSem;  // Semaphore handle
} LIST;

// Function to get a node from the list
static NODE *GetNode(LIST *pList)
{
    NODE *pNode = NULL; // Initialize pNode to NULL

    // Wait for ownership of the list mutex and semaphore
    DWORD dwWaitResult = WaitForMultipleObjects(2, &pList->hMtx, TRUE, INFINITE);
    if (dwWaitResult == WAIT_FAILED) {
        // Handle the error
        printf("WaitForMultipleObjects failed in GetNode. Error: %lu\n", GetLastError());
        return NULL; // Return NULL to indicate failure
    }

    if (pList->pFirst == NULL) {
        // No node available in the list
        ReleaseMutex(pList->hMtx); // Release ownership before returning
        return NULL;
    }

    // Get the first node in the list
    pNode = pList->pFirst;
    pList->pFirst = pNode->pNext; // Move the first pointer to the next node

    if (pList->pFirst == NULL) {
        // If the list is now empty, reset the last pointer
        pList->pLast = NULL;
    }

    // Release ownership of the list mutex
    ReleaseMutex(pList->hMtx);
    return pNode; // Return the node
}

// Function to append a node to the end of the list
static DWORD PutNode(LIST *pList, NODE *pNode)
{
    DWORD dwPrevCount = 0;

    // Wait for ownership of the list mutex
    DWORD dwWaitResult = WaitForSingleObject(pList->hMtx, INFINITE);
    if (dwWaitResult == WAIT_FAILED) {
        // Handle the error
        printf("WaitForSingleObject failed in PutNode. Error: %lu\n", GetLastError());
        return (DWORD)-1; // Indicate failure
    }

    // If the list is empty, set the first pointer to the new node
    if (pList->pFirst == NULL) {
        pList->pFirst = pNode;
    } else {
        // Otherwise, add the new node to the end of the list
        pList->pLast->pNext = pNode;
    }

    // Update the last pointer to the new node
    pList->pLast = pNode;
    pNode->pNext = NULL; // Ensure the new node's next pointer is NULL

    // Increment the semaphore count to signal that a node has been added
    if (!ReleaseSemaphore(pList->hSem, 1, &dwPrevCount)) {
        // Handle the error if ReleaseSemaphore fails
        printf("ReleaseSemaphore failed in PutNode. Error: %lu\n", GetLastError());
    }

    // Release ownership of the list mutex
    ReleaseMutex(pList->hMtx);
    return dwPrevCount; // Return the previous semaphore count
}