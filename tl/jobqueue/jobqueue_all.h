#pragma once

unsigned int __cdecl tlAtomicAdd(volatile signed __int32 *var, unsigned int value);
unsigned __int64 __cdecl tlAtomicAnd(volatile unsigned __int64 *var, unsigned __int64 value);
unsigned __int64 __cdecl tlAtomicOr(volatile unsigned __int64 *var, unsigned __int64 value);
void __thiscall tlAtomicMutex::Unlock(tlAtomicMutex *this);
void __thiscall tlSharedAtomicMutex::Lock(tlSharedAtomicMutex *this);
bool __thiscall jqAtomicHeap::GetAvailableBlock(jqAtomicHeap *this, jqAtomicHeap::LevelInfo *FitLevel, int *FitSlot);
char __thiscall jqAtomicHeap::AllocBlock(jqAtomicHeap *this, jqAtomicHeap::LevelInfo **FitLevel, int *FitSlot);
int __thiscall jqAtomicHeap::SplitBlock(
        jqAtomicHeap *this,
        jqAtomicHeap::LevelInfo *Level,
        int Slot,
        jqAtomicHeap::LevelInfo *LevelTo);
unsigned __int8 *__thiscall jqAtomicHeap::AllocLevel(jqAtomicHeap *this, int LevelIdx);
int __thiscall jqAtomicHeap::FindLevelForSize(jqAtomicHeap *this, unsigned int Size);
unsigned __int8 *__thiscall jqAtomicHeap::Alloc(jqAtomicHeap *this, unsigned int Size, unsigned int Align);
void __thiscall jqAtomicHeap::FindAllocatedBlock(
        jqAtomicHeap *this,
        unsigned int Offset,
        jqAtomicHeap::LevelInfo **FitLevel,
        int *FitSlot);
void __thiscall jqAtomicHeap::MergeBlocks(jqAtomicHeap *this, jqAtomicHeap::LevelInfo **FitLevel, int *FitSlot);
void __thiscall jqAtomicHeap::Free(jqAtomicHeap *this, jqAtomicHeap::LevelInfo *Ptr);
void __cdecl jqAttachQueueToWorkers(jqQueue *Queue, unsigned int ProcessorMask);
void __cdecl jqEnableWorkers(unsigned int ProcessorsMask);
int __cdecl jqGetNumWorkers();
unsigned __int64 __cdecl jqGetCurrentThreadID();
unsigned __int64 __cdecl jqGetMainThreadID();
jqBatch *__cdecl jqGetCurrentBatch();
jqWorker *__cdecl jqGetCurrentWorker();
jqQueue *__cdecl jqGetWorkerQueue(int worker);
void __cdecl jqShutdownWorker();
int __cdecl jqGetQueuedBatchCount(jqBatchGroup *GroupID);
int __cdecl jqGetExecutingBatchCount(jqBatchGroup *GroupID);
jqWorker *__cdecl jqFindWorkerForProcessor(jqProcessor Processor);
bool __cdecl jqPoll(jqBatchGroup *GroupID);
bool __cdecl jqAreJobsQueued(jqBatchGroup *GroupID);
void __cdecl jqSetWorkerInitFunction(void (__cdecl *fn)(int));
void __cdecl jqLetWorkersSleep();
unsigned __int8 *__cdecl jqAllocBatchData(unsigned int Size);
void __cdecl jqFreeBatchData(jqAtomicHeap::LevelInfo *Ptr);
unsigned int __cdecl jqGetBatchDataAvailable();
int __cdecl jqExecuteBatch(jqWorker *Worker, jqBatch *Batch);
char __cdecl jqCanBatchExecute();
bool __cdecl jqWorkerSleep();
void __cdecl jqSetCheckContext(const char *desc);
void __cdecl jqCheckDMALS(const void *addr);
void __cdecl jqCheckDMAMain(const void *addr);
void __cdecl jqCheckDMASize(unsigned int size);
void __cdecl jqCheckDMATag(unsigned int tag);
void __cdecl jqCheckRange(int val, int mn, int mx);
void __cdecl jqCheckStack();
unsigned __int8 *__cdecl jqFetch(unsigned __int8 *dest, unsigned __int8 *src, unsigned int size);
void __cdecl jqStore(unsigned __int8 *dest, unsigned __int8 *src, unsigned int size);
unsigned __int8 *__cdecl jqFetchAsync(unsigned __int8 *dest, unsigned __int8 *src, unsigned int size);
void __cdecl jqStoreAsync(unsigned __int8 *dest, unsigned __int8 *src, unsigned int size);
void __cdecl jqWait();
void __cdecl jqWaitMultiple();
void __cdecl jqSetMemBase();
void __cdecl jqSetStackSize();
int __cdecl jqGetMemAvailable();
void *__cdecl jqAlloc();
void *__cdecl jqGetMemBase();
void __cdecl _jqInit();
void __cdecl _jqShutdown();
void __cdecl _jqStop();
void __cdecl _jqAddBatch();
void __cdecl jqAlertWorkers();
void __thiscall jqLockBatchPoolInternal(void *this);
void __cdecl jqUnlockBatchPoolInternal();
void __cdecl jqKeepWorkersAwake();
void __thiscall jqLockBatchPool(void *this);
void __cdecl jqUnlockBatchPool();
void __cdecl jqSetBatchDataHeapSize(unsigned int Size, unsigned int BlockSize);
void __cdecl jqInit();
void __cdecl jqInitQueue(jqQueue *Queue);
void __cdecl jqInitWorker(jqWorker *Worker);
void __cdecl jqAddBatchToQueue(jqBatch *Batch, jqQueue *Queue);
void __cdecl jqAddBatch(jqBatch *Data, jqQueue *Queue);
void __cdecl jqAddBatch(
        jqModule *Module,
        void *Input,
        void *Output,
        jqBatchGroup *GroupID,
        jqQueue *Queue,
        unsigned __int8 *ParamData,
        unsigned int ParamSize);
void __cdecl jqSkipBatch();
char __cdecl jqPopNextBatchFromQueue(jqQueue *Worker, jqBatchGroup *Queue, jqBatch *GroupID);
char  jqPopNextBatch@<al>(
        jqWorker *Worker@<ecx>,
        bool *doHighPriority@<eax>,
        jqBatchGroup *GroupID,
        jqBatch *PoppedBatch);
void __cdecl jqWorkerLoop(jqWorker *Worker, jqBatchGroup *GroupID, bool BreakWhenEmpty, unsigned __int64 *batchCount);
void __cdecl jqTempWorkerLoop(jqWorker *Worker, jqBatchGroup *GroupID, bool (__cdecl *callback)(void *), void *context);
unsigned int __stdcall jqWorkerThread(jqWorker *_this);
void __cdecl _jqStart();
void __cdecl jqFlush(jqBatchGroup *GroupID, unsigned __int64 batchCount);
void __cdecl jqStop();
void __cdecl jqAssistWithBatches(bool (__cdecl *callback)(void *), void *context, jqBatchGroup *GroupID);
void __cdecl jqShutdown();
void __cdecl jqStart();
void __thiscall jqAtomicQueue<jqBatch,32>::AllocateNodeBlock(jqAtomicQueue<jqBatch,32> *this, int Count);
jqAtomicQueue<jqBatch,32>::NodeType *__thiscall jqAtomicQueue<jqBatch,32>::AllocateNode(
        jqAtomicQueue<jqBatch,32> *this);
void __thiscall tlAtomicMutex::~tlAtomicMutex(tlAtomicMutex *this);
void __thiscall jqAtomicHeap::~jqAtomicHeap(jqAtomicHeap *this);
void __thiscall jqAtomicHeap::Init(
        jqAtomicHeap *this,
        unsigned __int8 *_HeapBase,
        unsigned int _HeapSize,
        unsigned int _BlockSize);
void __thiscall jqAtomicQueue<jqBatch,32>::Init(
        jqAtomicQueue<jqBatch,32> *this,
        jqAtomicQueue<jqBatch,32> *SharedFreeList);
void __thiscall jqAtomicQueue<jqBatch,32>::Push(jqAtomicQueue<jqBatch,32> *this, jqBatch *Data);
char __thiscall jqAtomicQueue<jqBatch,32>::Pop(jqAtomicQueue<jqBatch,32> *this, jqBatch *p);
void __thiscall jqQueue::~jqQueue(jqQueue *this);
void __thiscall jqBatchPool::~jqBatchPool(jqBatchPool *this);
