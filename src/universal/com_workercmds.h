#pragma once

enum jqWorkerType : __int32
{                                       // XREF: jqModule/r _jqWorker/r
    JQ_WORKER_GENERIC = 0x0,            // XREF: .data:jqModule bp_env_jq_module1Module/s
                                        // .data:jqModule bp_env_jq_module2Module/s ...
    JQ_WORKER_MAX     = 0x1,
    JQ_WORKER_DEFAULT = 0x0,
};

struct jqBatchGroup // sizeof=0x8
{                                       // XREF: jqModule/r
                                        // GfxDrawSurfListInfo/r
    //$F761E618955D9ED935731AE37AFEF266 ___u0;
    union //$F761E618955D9ED935731AE37AFEF266 // sizeof=0x8
    {                                       // XREF: jqGetQueuedBatchCount(jqBatchGroup *)+A/r
                                            // jqGetExecutingBatchCount(jqBatchGroup *)+A/r ...
        //$2BD02F38FBEBD854EF9A531D8B9F9671 __s0;
        struct //$2BD02F38FBEBD854EF9A531D8B9F9671 // sizeof=0x8
        {                                       // XREF: $F761E618955D9ED935731AE37AFEF266/r
            int QueuedBatchCount;
            int ExecutingBatchCount;
        };
        unsigned __int64 BatchCount;
    };

    jqBatchGroup();
};

struct jqModule // sizeof=0x18
{                                       // XREF: .data:jqModule bp_env_jq_module1Module/r
                                        // .data:jqModule bp_env_jq_module2Module/r ...
    const char *Name;                   // XREF: _dynamic_initializer_for__fx_add_markModule__+6/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+6/w ...
    jqWorkerType Type;                  // XREF: _dynamic_initializer_for__fx_add_markModule__+10/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+10/w ...
    int (__cdecl *Code)(jqBatch *);     // XREF: _dynamic_initializer_for__fx_add_markModule__+1A/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+1A/w ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    jqBatchGroup Group;                 // XREF: R_FinishedFrontendWorkerCmds(void)+3/o
                                        // R_FinishedFrontendWorkerCmds(void):loc_7B97EE/o ...
};

struct _jqBatch // sizeof=0x0
{                                       // XREF: jqBatch/r
};

struct __declspec(align(4)) jqBatch // sizeof=0x7C
{                                       // XREF: .data:jqBatch g_phys_task_manager_batch/r
                                        // jqAtomicQueue<jqBatch,32>::NodeType/r ...
    void *p3x_info;                     // XREF: jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+19/w
                                        // jqWorkerLoop(jqWorker *,jqBatchGroup *,bool,unsigned __int64 *)+50/w ...
    void *Input;                        // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+2E/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+2E/w ...
    void *Output;                       // XREF: jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+31/w
                                        // jqWorkerLoop(jqWorker *,jqBatchGroup *,bool,unsigned __int64 *)+5C/w ...
    jqModule *Module;                   // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+39/w
                                        // R_InitWorkerCmds(void)+34/w ...
    jqBatchGroup *GroupID;              // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+3C/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+34/w ...
    void *ConditionalAddress;           // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+4E/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+20/w ...
    unsigned int ConditionalValue;      // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+57/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+27/w ...
    unsigned int ParamData[23];         // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+5D/w
                                        // Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+6F/w ...
    _jqBatch _Batch;
    // padding byte
    // padding byte
    // padding byte

    jqBatch();
};

struct jqModule // sizeof=0x18
{                                       // XREF: .data:jqModule bp_env_jq_module1Module/r
                                        // .data:jqModule bp_env_jq_module2Module/r ...
    const char *Name;                   // XREF: _dynamic_initializer_for__fx_add_markModule__+6/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+6/w ...
    jqWorkerType Type;                  // XREF: _dynamic_initializer_for__fx_add_markModule__+10/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+10/w ...
    int (__cdecl *Code)(jqBatch *);     // XREF: _dynamic_initializer_for__fx_add_markModule__+1A/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+1A/w ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    jqBatchGroup Group;                 // XREF: R_FinishedFrontendWorkerCmds(void)+3/o
                                        // R_FinishedFrontendWorkerCmds(void):loc_7B97EE/o ...
};

struct tlSharedAtomicMutex // sizeof=0x10
{                                       // XREF: jqAtomicQueue<jqBatch,32>/r
    volatile unsigned __int64 ThreadId; // XREF: jqInit(void)+31/w
                                        // jqInit(void)+37/w ...
    volatile int LockCount;             // XREF: jqInit(void)+42/w
                                        // _dynamic_initializer_for__jqPool__+11/w ...
    tlSharedAtomicMutex *ThisPtr;       // XREF: jqInit(void)+27/w
};

struct tlAtomicMutex // sizeof=0x10
{                                       // XREF: .data:tlAtomicMutex g_prolog_task_mutex/r
                                        // .data:lightGridMutex/r ...
    unsigned __int64 ThreadId;          // XREF: jqInit(void)+58/w
                                        // jqInit(void)+5E/w ...
    int LockCount;                      // XREF: jqInit(void)+64/w
                                        // jqInit(void)+80/w ...
    tlAtomicMutex *ThisPtr;             // XREF: jqInit(void)+4E/w
                                        // jqInit(void)+6A/w ...
};

struct tlAtomicMutexLocker // sizeof=0x4
{
    tlAtomicMutex *Mutex;
};

template <typename T, int SIZE>
struct __declspec(align(8)) jqAtomicQueue//<jqBatch,32> // sizeof=0x50
{                                       // XREF: jqQueue/r
                                        // jqAtomicQueueType/r
    struct NodeType // sizeof=0x80
    {
        jqAtomicQueue<T, SIZE>::NodeType *Next;
        jqBatch Data;
    };

    struct jqAtomicQueue//<jqBatch,32>::NodeBlockEntry // sizeof=0x8
    {
        void *Addr;
        jqAtomicQueue<T,SIZE>::NodeBlockEntry *Next;
    };

    jqAtomicQueue<T,SIZE>::NodeType **FreeListPtr;
    jqAtomicQueue<T,SIZE>::NodeType *_FreeList;
    jqAtomicQueue<T,SIZE>::NodeBlockEntry *NodeBlockListHead;
    jqAtomicQueue<T,SIZE>::NodeType *Head; // XREF: jqInit(void)+9C/w
    jqAtomicQueue<T,SIZE>::NodeType *Tail; // XREF: jqInit(void)+97/w
    tlSharedAtomicMutex FreeLock;       // XREF: jqInit(void)+27/w
    tlAtomicMutex HeadLock;             // XREF: jqInit(void)+4E/w
    tlAtomicMutex TailLock;             // XREF: jqInit(void)+6A/w
    jqAtomicQueue<T,SIZE> *ThisPtr; // XREF: jqInit(void)+D/w
};

typedef jqAtomicQueue<jqBatch, 32> jqAtomicQueueType;

struct jqQueue // sizeof=0x60
{                                       // XREF: .data:jqQueue jqGlobalQueue/r
                                        // .data:jqQueue localQueue/r ...
    jqQueue *ThisPtr;                   // XREF: jqPopNextBatch+22/r
                                        // jqStart(void)+2C6/w ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    jqAtomicQueue<jqBatch,32> Queue;    // XREF: jqInit(void)+D/w
                                        // jqInit(void)+17/w ...
    int QueuedBatchCount;               // XREF: jqInit(void)+A1/w
                                        // jqStart(void)+2D0/w ...
    unsigned int ProcessorsMask;        // XREF: jqStart(void)+2E5/w
                                        // jqStart(void)+31C/w
};


struct __declspec(align(8)) jqWorkerCmd // sizeof=0x20
{                                       // XREF: .data:jqWorkerCmd fx_add_markWorkerCmd/r
                                        // .data:jqWorkerCmd nuge_physicsWorkerCmd/r ...
    jqModule *module;
    unsigned int dataSize;
    volatile int ppu_fence;
    volatile int spu_fence;
    volatile int *spuThreadLimit;
    jqQueue *queue;
    unsigned int string_table;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct WorkerCmdConditional // sizeof=0x8
{
    void *address;
    unsigned int value;
};


void __cdecl Sys_WorkerCmdInit();
unsigned __int8 *__cdecl jqCommitMemory(jqBatch *batch, unsigned __int8 *input, unsigned int dataSize);
void __cdecl jqSafeFlush(jqBatchGroup *group, unsigned __int64 batchCount);
unsigned int *__cdecl jqLockData(jqBatch *batch);
void __cdecl jqUnlockData(jqBatch *batch);
void __cdecl Sys_AddWorkerCmdInternal(jqWorkerCmd *name, unsigned __int8 *data, WorkerCmdConditional *cond);
void __cdecl Sys_WaitWorkerCmdInternal(jqWorkerCmd *name);
void __cdecl Sys_AssistAndWaitWorkerCmdInternal(jqWorkerCmd *name);
bool __cdecl Sys_AssistAndWaitWorkerCmdInternalCallback(jqBatchGroup *context);
void __cdecl Sys_AssistSingle();
bool __cdecl Sys_AssistSingleCallback(unsigned int *context);
bool __cdecl Sys_AssistNeeded();
bool __cdecl R_FinishedFrontendWorkerCmds();
void __cdecl R_WaitFrontendWorkerCmds();
void __cdecl R_WaitWorkerCmds();
