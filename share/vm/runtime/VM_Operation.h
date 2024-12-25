//
// Created by ziya on 2024/12/25.
//

#ifndef XVM_CPP_VM_OPERATION_H
#define XVM_CPP_VM_OPERATION_H


#include "../adlc/CHeapObj.h"

#define VM_OP_ENUM(type)    VMOp_##type,

// Note: When new VM_XXX comes up, add 'XXX' to the template table.
#define VM_OPS_DO(template)                     \
    template(Dummy)                             \
    template(ThreadStop)                        \
    template(ThreadDump)                        \
    template(PrintThreads)                      \
    template(FindDeadlocks)                     \
    template(ForceSafepoint)                    \
    template(ForceAsyncSafepoint)               \
    template(Deoptimize)                        \
    template(DeoptimizeFrame)                   \
    template(DeoptimizeAll)                     \
    template(ZombieAll)                         \
    template(UnlinkSymbols)                     \
    template(Verify)                            \
    template(PrintJNI)                          \
    template(HeapDumper)                        \
    template(DeoptimizeTheWorld)                \
    template(CollectForMetadataAllocation)      \
    template(GC_HeapInspection)                 \
    template(GenCollectFull)                    \
    template(GenCollectFullConcurrent)          \
    template(GenCollectForAllocation)           \
    template(ParallelGCFailedAllocation)        \
    template(ParallelGCSystemGC)                \
    template(CGC_Operation)                     \
    template(CMS_Initial_Mark)                  \
    template(CMS_Final_Remark)                  \
    template(G1CollectFull)                     \
    template(G1CollectForAllocation)            \
    template(G1IncCollectionPause)              \
    template(DestroyAllocationContext)          \
    template(EnableBiasedLocking)               \
    template(RevokeBias)                        \
    template(BulkRevokeBias)                    \
    template(PopulateDumpSharedSpace)           \
    template(JNIFunctionTableCopier)            \
    template(RedefineClasses)                   \
    template(GetOwnedMonitorInfo)               \
    template(GetObjectMonitorUsage)             \
    template(GetCurrentContendedMonitor)        \
    template(GetStackTrace)                     \
    template(GetMultipleStackTraces)            \
    template(GetAllStackTraces)                 \
    template(GetThreadLisstStackTraces)         \
    template(GetFrameCount)                     \
    template(GetFrameLocation)                  \
    template(ChangeBreakpoints)                 \
    template(GetOrSetLocal)                     \
    template(GetCurrentLocation)                \
    template(EnterInterpOnlyMode)               \
    template(ChangeSingleStep)                  \
    template(HeapWalkOperation)                 \
    template(HeapIterateOperation)              \
    template(ReportJavaOutOfMemory)             \
    template(JFRCheckpoint)                     \
    template(Exit)                              \
    template(LinuxDllLoad)                      \
    template(RoteteGCLog)                       \
    template(WhiteBOxOperation)                 \

class VM_Operation : public CHeapObj {

public:
    enum Mode {
        _safepoint,         // blocking,        safepoint, vm_op C-Heap allocated
        _no_safepoint,      // blocking,     no safepoint, vm_op C-Heap allocated
        _concurrent,        // non-blocking, no safepoint, vm_op C-Heap allocated
        _async_safepoint    // non-blocking,    safepoint, vm_op C-Heap allocated
    };

    enum VMOp_Type {
        VM_OPS_DO(VM_OP_ENUM)
        VMOp_Terminating
    };

public:
    void evaluate();

};


#endif //XVM_CPP_VM_OPERATION_H
