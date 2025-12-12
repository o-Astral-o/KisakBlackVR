#pragma once
#include "cscr_variable.h"
#include <bgame/bg_local.h>
#include <universal/dvar.h>

struct function_stack_t // sizeof=0x14
{                                       // XREF: .data:gFs/r
                                        // function_frame_t/r ...
    const char *pos;                    // XREF: Scr_DebugTerminateThread(scriptInstance_t,int)+12/r
                                        // Scr_DebugTerminateThread(scriptInstance_t,int)+60/w ...
    unsigned int localId;               // XREF: Scr_ScriptWatch::EvaluateWatchChildren(scriptInstance_t,Scr_WatchElement_s *)+2F1/r
                                        // Scr_ScriptWatch::EvaluateWatchChildren(scriptInstance_t,Scr_WatchElement_s *)+31F/r ...
    unsigned int localVarCount;         // XREF: VM_Execute+219/w
                                        // VM_Execute_0+39/w ...
    VariableValue *top;                 // XREF: VM_Execute+1FE/w
                                        // VM_Execute_0+3F/w ...
    VariableValue *startTop;            // XREF: VM_Execute+E8/w
                                        // VM_Execute_0+45/w ...
};

struct scrVmGlob_t // sizeof=0x2028
{                                       // XREF: .data:scrVmGlob_t * gScrVmGlob/r
    VariableValue eval_stack[2];        // XREF: IncInParam+155/o
                                        // GetEntityFieldValue(scriptInstance_t,uint,int,ushort,int)+9A/w ...
    const char *dialog_error_message;   // XREF: Scr_ClearErrorMessage(scriptInstance_t)+1C/w
                                        // VM_Notify+597/r ...
    int loading;                        // XREF: Scr_VM_Init+18F/w
                                        // Scr_SetLoading(int,scriptInstance_t)+F/w ...
    int starttime;                      // XREF: Scr_VM_Init+87/o
                                        // Scr_ExecThread(scriptInstance_t,int,uint)+48/o ...
    unsigned int localVarsStack[2048];
    bool recordPlace;                   // XREF: Scr_VM_Init+1A2/w
                                        // VM_Execute_0+3144/r
    // padding byte
    // padding byte
    // padding byte
    const char *lastFileName;           // XREF: Scr_VM_Init+1B2/w
                                        // VM_Execute_0+3168/o
    int lastLine;                       // XREF: Scr_VM_Init+1C5/w
                                        // VM_Execute_0+3158/o
};

struct function_frame_t // sizeof=0x18
{                                       // XREF: scrVmPub_t/r
    function_stack_t fs;                // XREF: Scr_ScriptWatch::EvaluateWatchChildren(scriptInstance_t,Scr_WatchElement_s *)+2F1/r
                                        // Scr_ScriptWatch::EvaluateWatchChildren(scriptInstance_t,Scr_WatchElement_s *)+31F/r ...
    int topType;
};

struct scrVmPub_t // sizeof=0x4328
{                                       // XREF: .data:scrVmPub_t * gScrVmPub/r
    unsigned int *localVars;            // XREF: Scr_HitAssignmentBreakpoint(scriptInstance_t,VariableValue *,char const *,uint,int)+6D1/r
                                        // Scr_VM_Init+96/w ...
    VariableValue *maxstack;            // XREF: Scr_PreEvalBuiltin+E3/r
                                        // Scr_PreEvalBuiltin+14D/r ...
    int function_count;                 // XREF: Scr_ScriptWindow::RunToCursor(scriptInstance_t)+3B/r
                                        // Scr_ScriptCallStack::UpdateStack(scriptInstance_t)+12/r ...
    function_frame_t *function_frame;   // XREF: Scr_HitBreakpoint(scriptInstance_t,VariableValue *,char const *,uint,int)+4B6/r
                                        // Scr_DebugKillThread(scriptInstance_t,uint,char const *)+1A8/r ...
    VariableValue *top;                 // XREF: Scr_CheckBreakonNotify(scriptInstance_t,uint,uint,VariableValue *,char const *,uint)+4A/w
                                        // Scr_HitBreakpoint(scriptInstance_t,VariableValue *,char const *,uint,int)+252/w ...
    bool debugCode;                     // XREF: Scr_PreEvalBuiltin+233/r
                                        // Scr_PreEvalBuiltin+26D/w ...
    bool abort_on_error;                // XREF: RuntimeError(scriptInstance_t,char const *,uint,char const *,char const *)+CA/r
                                        // Scr_Settings(int,int,int,scriptInstance_t)+71/w ...
    bool terminal_error;                // XREF: RuntimeError(scriptInstance_t,char const *,uint,char const *,char const *)+67/r
                                        // RuntimeError(scriptInstance_t,char const *,uint,char const *,char const *)+A7/r ...
    // padding byte
    unsigned int inparamcount;          // XREF: Scr_ScriptWatch::Evaluate(scriptInstance_t)+81/r
                                        // Scr_CheckBreakonNotify(scriptInstance_t,uint,uint,VariableValue *,char const *,uint)+F/r ...
    unsigned int outparamcount;         // XREF: Scr_ScriptWatch::Evaluate(scriptInstance_t)+49/r
                                        // Scr_SpecialBreakpoint+73/w ...
    unsigned int breakpointOutparamcount;
                                        // XREF: Scr_HitBuiltinBreakpoint(scriptInstance_t,VariableValue *,char const *,uint,int,int,uint)+120/w
                                        // Scr_GetValue+12/r
    bool showError;                     // XREF: Scr_BeginLoadScripts(scriptInstance_t,int)+16A/w
                                        // VM_Execute_0+2929/r ...
    // padding byte
    // padding byte
    // padding byte
    function_frame_t function_frame_start[32];
                                        // XREF: Scr_ScriptCallStack::UpdateStack(scriptInstance_t)+AE/o
                                        // Scr_ScriptWatch::EvaluateWatchChildren(scriptInstance_t,Scr_WatchElement_s *)+2F1/r ...
    VariableValue stack[2048];          // XREF: Scr_PreEvalBuiltin+97/o
                                        // Scr_VM_Init+1C/o ...
};

struct FuncDebugData // sizeof=0x4
{                                       // XREF: scrVmDebugPub_t/r
    int breakpointCount;                // XREF: AddFunction+E4/w
};

struct scrVmDebugPub_t // sizeof=0x120C
{                                       // XREF: .data:scrVmDebugPub_t * gScrVmDebugPub/r
                                        // scrVmDebugPubArray_t/r
    FuncDebugData func_table[1024];     // XREF: AddFunction+E4/w
                                        // Scr_ScriptWindow::AddBreakpointAtSourcePos(scriptInstance_t,Scr_WatchElement_s *,uchar,bool,Scr_Breakpoint * *,uint,uint)+170/r ...
    int checkBreakon;                   // XREF: Scr_CompilePrimitiveExpression+222/r
                                        // Scr_CompilePrimitiveExpression+234/w ...
    const char *jumpbackHistory[128];   // XREF: VM_Execute_0+4514/w
                                        // VM_PrintJumpHistory+58/r ...
    int jumpbackHistoryIndex;           // XREF: VM_Execute_0+450B/r
                                        // VM_Execute_0+4524/r ...
    int dummy;
};

void __cdecl Scr_AddStruct();
void __cdecl Scr_ResetTimeout();
void __cdecl RemoveRefToValue(scriptInstance_t inst, int type, VariableUnion u);
void __cdecl Scr_ClearErrorMessage(scriptInstance_t inst);
void __cdecl Scr_Init(scriptInstance_t inst);
void __cdecl Scr_VM_Init(scriptInstance_t inst);
void __cdecl Scr_Settings(int developer, int developer_script, int abort_on_error, scriptInstance_t inst);
void __cdecl Scr_Shutdown(scriptInstance_t inst);
void __cdecl VM_Shutdown(scriptInstance_t inst);
void __cdecl Scr_SetLoading(int bLoading, scriptInstance_t inst);
int __cdecl Scr_GetNumScriptThreads(scriptInstance_t inst);
void __cdecl Scr_ClearOutParams(scriptInstance_t inst);
char *__cdecl Scr_GetReturnPos(scriptInstance_t inst, unsigned int *localId);
char *__cdecl Scr_GetNextCodepos(
                scriptInstance_t inst,
                VariableValue *top,
                const char *pos,
                int opcode,
                int mode,
                unsigned int *localId);
void __cdecl VM_CancelNotify(scriptInstance_t inst, unsigned int notifyListOwnerId, unsigned int startLocalId);
void __cdecl VM_CancelNotifyInternal(
                scriptInstance_t inst,
                unsigned int notifyListOwnerId,
                unsigned int startLocalId,
                unsigned int notifyListId,
                unsigned int notifyNameListId,
                unsigned int stringValue);
bool __cdecl Scr_IsEndonThread(scriptInstance_t inst, unsigned int localId);
unsigned int __cdecl Scr_GetWaittillThreadStackId(
                scriptInstance_t inst,
                unsigned int localId,
                unsigned int startLocalId);
char *__cdecl Scr_GetThreadPos(scriptInstance_t inst, unsigned int localId);
const char *__cdecl Scr_GetStackThreadPos(
                scriptInstance_t inst,
                unsigned int endLocalId,
                VariableStackBuffer *stackValue,
                bool killThread);
char *__cdecl Scr_GetRunningThreadPos(scriptInstance_t inst, unsigned int localId);
unsigned int __cdecl Scr_GetWaitThreadStackId(scriptInstance_t inst, unsigned int localId, unsigned int startLocalId);
void __cdecl Scr_NotifyNum_Internal(
                scriptInstance_t inst,
                int clientNum,
                unsigned int entnum,
                unsigned int classnum,
                unsigned int stringValue,
                unsigned int paramcount);
void __cdecl VM_Notify(
                scriptInstance_t inst,
                unsigned int notifyListOwnerId,
                unsigned int stringValue,
                VariableValue *top);
void __cdecl Scr_TerminateThread(scriptInstance_t inst, unsigned int localId);
void __cdecl Scr_TerminateRunningThread(scriptInstance_t inst, unsigned int localId);
void __cdecl Scr_TerminateWaitThread(scriptInstance_t inst, unsigned int localId, unsigned int startLocalId);
void __cdecl VM_TerminateStack(
                scriptInstance_t inst,
                unsigned int endLocalId,
                unsigned int startLocalId,
                VariableStackBuffer *stackValue);
void __cdecl Scr_TerminateWaittillThread(scriptInstance_t inst, unsigned int localId, unsigned int startLocalId);
void __cdecl Scr_NotifyNum(
                unsigned int entnum,
                unsigned int classnum,
                unsigned int stringValue,
                unsigned int paramcount);
void __cdecl CScr_NotifyNum(
                int clientNum,
                unsigned int entnum,
                unsigned int classnum,
                unsigned int stringValue,
                unsigned int paramcount);
void __cdecl Scr_CancelNotifyList(scriptInstance_t inst, unsigned int notifyListOwnerId);
void __cdecl VM_TrimStack(
                scriptInstance_t inst,
                unsigned int startLocalId,
                VariableStackBuffer *stackValue,
                bool fromEndon);
void __cdecl Scr_CancelWaittill(scriptInstance_t inst, unsigned int startLocalId);
unsigned __int16 __cdecl Scr_ExecThread(scriptInstance_t inst, int handle, unsigned int paramcount);
unsigned int __cdecl VM_Execute(scriptInstance_t inst, unsigned int localId, char *pos, unsigned int paramcount);
void __cdecl RemoveRefToValue(scriptInstance_t inst, VariableValue *value);
unsigned int __cdecl Scr_GetLocalVar(scriptInstance_t inst, const char *pos);
unsigned __int16 __cdecl Scr_ReadUnsignedShort(const char **pos);
const char *__cdecl Scr_ReadCodePos(scriptInstance_t inst, const char **pos);
unsigned int __cdecl GetDummyObject(scriptInstance_t inst);
int __cdecl GetDummyFieldValue(scriptInstance_t inst);
void __cdecl VM_PrintJumpHistory(scriptInstance_t inst);
VariableStackBuffer *__cdecl VM_ArchiveStack(scriptInstance_t inst, function_stack_t *stack);
unsigned __int16 __cdecl Scr_ExecEntThreadNum(
                scriptInstance_t inst,
                unsigned int entnum,
                unsigned int classnum,
                int handle,
                unsigned int paramcount,
                unsigned __int16 localClientNum);
void __cdecl Scr_AddExecThread(scriptInstance_t inst, int handle, unsigned int paramcount);
void __cdecl Scr_FreeThread(unsigned __int16 handle, scriptInstance_t inst);
void __cdecl Scr_ExecCode(scriptInstance_t inst, char *pos, unsigned int localId);
bool __cdecl Scr_IsSystemInitied(scriptInstance_t inst);
void __cdecl Scr_InitSystem(scriptInstance_t inst, int sys);
void __cdecl Scr_ShutdownSystem(scriptInstance_t inst, unsigned __int8 sys, int bComplete);
void __cdecl VM_TerminateTime(scriptInstance_t inst, unsigned int timeId);
bool __cdecl Scr_IsSystemActive(unsigned __int8 sys, scriptInstance_t inst);
VariableUnion __cdecl Scr_GetInt(unsigned int index, scriptInstance_t inst);
scr_anim_s __cdecl Scr_GetAnim(unsigned int index, XAnimTree_s *tree, scriptInstance_t inst);
void __cdecl Scr_ErrorInternal(scriptInstance_t inst);
scr_animtree_t __cdecl Scr_GetAnimTree(unsigned int index, unsigned int user, scriptInstance_t inst);
double __cdecl Scr_GetFloat(unsigned int index, scriptInstance_t inst);
VariableUnion __cdecl Scr_GetConstString(unsigned int index, scriptInstance_t inst);
VariableUnion __cdecl Scr_GetConstLowercaseString(unsigned int index, scriptInstance_t inst);
char *__cdecl Scr_GetString(unsigned int index, scriptInstance_t inst);
VariableUnion __cdecl Scr_GetConstStringIncludeNull(unsigned int index, scriptInstance_t inst);
char *__cdecl Scr_GetDebugString(unsigned int index, scriptInstance_t inst);
VariableUnion __cdecl Scr_GetConstIString(unsigned int index, scriptInstance_t inst);
char *__cdecl Scr_GetIString(unsigned int index, scriptInstance_t inst);
void __cdecl Scr_GetVector(unsigned int index, float *vectorValue, scriptInstance_t inst);
int __cdecl Scr_GetFunc(unsigned int index, scriptInstance_t inst);
scr_entref_t *__cdecl Scr_GetEntityRef(unsigned int index, scriptInstance_t inst);
VariableUnion __cdecl Scr_GetObject(unsigned int index, scriptInstance_t inst);
int __cdecl Scr_GetType(unsigned int index, scriptInstance_t inst);
const char *__cdecl Scr_GetTypeName(unsigned int index, scriptInstance_t inst);
unsigned int __cdecl Scr_GetPointerType(unsigned int index, scriptInstance_t inst);
int __cdecl Scr_GetNumParam(scriptInstance_t inst);
void __cdecl Scr_AddBool(unsigned int value, scriptInstance_t inst);
void __cdecl IncInParam(scriptInstance_t inst);
void __cdecl Scr_AddInt(int value, scriptInstance_t inst);
void __cdecl Scr_AddFloat(float value, scriptInstance_t inst);
void __cdecl Scr_AddAnim(scr_anim_s value, scriptInstance_t inst);
void __cdecl Scr_AddUndefined(scriptInstance_t inst);
void __cdecl Scr_AddObject(unsigned int id, scriptInstance_t inst);
void __cdecl Scr_AddEntityNum(unsigned int entnum, unsigned int classnum, scriptInstance_t inst, int clientNum);
void __cdecl Scr_AddStruct(scriptInstance_t inst);
void __cdecl Scr_AddString(char *value, scriptInstance_t inst);
void __cdecl Scr_AddIString(char *value, scriptInstance_t inst);
void __cdecl Scr_AddConstString(unsigned int value, scriptInstance_t inst);
void __cdecl Scr_AddVector(float *value, scriptInstance_t inst);
void __cdecl Scr_MakeArray(scriptInstance_t inst);
void __cdecl Scr_AddArray(scriptInstance_t inst);
void __cdecl Scr_AddArrayStringIndexed(unsigned int stringValue, scriptInstance_t inst);
void __cdecl Scr_Error(const char *error, bool force_terminal);
void __cdecl Scr_Error(scriptInstance_t inst, const char *error, bool force_terminal);
void __cdecl Scr_SetErrorMessage(scriptInstance_t inst, const char *error);
void __cdecl Scr_TerminalError(const char *error, scriptInstance_t inst);
void __cdecl Scr_NeverTerminalError(const char *error, scriptInstance_t inst);
void __cdecl Scr_ParamError(unsigned int index, const char *error, scriptInstance_t inst);
void __cdecl Scr_ObjectError(const char *error, scriptInstance_t inst);
char __cdecl SetEntityFieldValue(
                scriptInstance_t inst,
                unsigned int classnum,
                unsigned int entnum,
                unsigned __int16 clientNum,
                unsigned int offset,
                VariableValue *value);
VariableValue __cdecl GetEntityFieldValue(
                scriptInstance_t inst,
                unsigned int classnum,
                unsigned int entnum,
                unsigned __int16 clientNum,
                unsigned int offset);
void __cdecl Scr_SetStructField(unsigned int structId, unsigned int index, scriptInstance_t inst);
void __cdecl Scr_SetDynamicEntityField(
                unsigned int entnum,
                unsigned int classnum,
                unsigned int index,
                scriptInstance_t inst,
                unsigned __int16 localClientNum);
void __cdecl Scr_IncTime(scriptInstance_t inst);
void __cdecl Scr_DecTime(scriptInstance_t inst);
void __cdecl Scr_RunCurrentThreads(scriptInstance_t inst);
void __cdecl VM_SetTime(scriptInstance_t inst);
void __cdecl VM_Resume(scriptInstance_t inst, unsigned int timeId);
void __cdecl VM_UnarchiveStack(scriptInstance_t inst, unsigned int startLocalId, VariableStackBuffer *stackValue);
int __cdecl Scr_AddLocalVars(scriptInstance_t inst, unsigned int localId);
void __cdecl Scr_ResetTimeout(scriptInstance_t inst);
bool __cdecl Scr_IsStackClear(scriptInstance_t inst);
void __cdecl Scr_StackClear(scriptInstance_t inst);

extern const dvar_t *logScriptTimes;
extern const dvar_t *scrVmEnableScripts;
extern const dvar_t *scrShowVarUseage;
extern const dvar_t *scrShowStrUsage;
extern const dvar_t *sv_clientside;

extern scrVmGlob_t gScrVmGlob[2];
extern scrVmPub_t gScrVmPub[2];
extern scrVmDebugPub_t gScrVmDebugPub[2];