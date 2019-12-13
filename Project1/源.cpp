#include <windows.h>
#include <stdio.h>
//----------- Error Handling Function -------------------
void error(LPSTR lpszFunction)
{
	CHAR szBuf[80];
	DWORD dw = GetLastError();

	sprintf_s(szBuf, "%s failed: GetLastError returned %u\n",
		lpszFunction, dw);

	MessageBox(NULL, szBuf, "Error", MB_OK);
	ExitProcess(dw);
}
//--------------------------------------------------------

BOOL GetFileTime(HANDLE hFile, LPSTR lpszCreationTime, LPSTR lpszLastAccessTime, LPSTR lpszLastWriteTime)
{
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTC1, stLocal1, stUTC2, stLocal2, stUTC3, stLocal3;

	// -------->获取 FileTime
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)){
		error("GetFileTime()");
		return FALSE;
	}
	//---------> 转换: FileTime --> LocalTime
	FileTimeToSystemTime(&ftCreate, &stUTC1);
	FileTimeToSystemTime(&ftAccess, &stUTC2);
	FileTimeToSystemTime(&ftWrite, &stUTC3);

	SystemTimeToTzSpecificLocalTime(NULL, &stUTC1, &stLocal1);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC2, &stLocal2);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC3, &stLocal3);

	// ---------> Show the  date and time.
	wsprintf(lpszCreationTime, "创建时间:\t%02d/%02d/%d  %02d:%02d:%02d:%03d",
		stLocal1.wDay, stLocal1.wMonth, stLocal1.wYear,
		stLocal1.wHour, stLocal1.wMinute, stLocal1.wSecond, stLocal1.wMilliseconds);
	wsprintf(lpszLastAccessTime, "最后访问时间:\t%02d/%02d/%d  %02d:%02d:%02d:%03d",
		stLocal2.wDay, stLocal2.wMonth, stLocal2.wYear,
		stLocal2.wHour, stLocal2.wMinute, stLocal2.wSecond, stLocal2.wMilliseconds);
	wsprintf(lpszLastWriteTime, "最后修改时间:\t%02d/%02d/%d  %02d:%02d:%02d:%03d",
		stLocal3.wDay, stLocal3.wMonth, stLocal3.wYear,
		stLocal3.wHour, stLocal3.wMinute, stLocal3.wSecond, stLocal3.wMilliseconds);
	return TRUE;
}
//----------------------------------------------------------------
int main()
{

	HANDLE hFile;
	TCHAR szCreationTime[30], szLastAccessTime[30], szLastWriteTime[30];
	hFile = CreateFile("F:\\internship_in_cas\\5.CompleteTime_ms\\WX0527\\EMG_20190731_straight_lizhu_4.hpf", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	GetFileTime(hFile, szCreationTime, szLastAccessTime, szLastWriteTime);
	if (hFile == INVALID_HANDLE_VALUE){
		error("GetLastWriteTime()");
		return 0;
	}
	printf("%s\n%s\n%s\n", szCreationTime, szLastAccessTime, szLastWriteTime);
	CloseHandle(hFile);
	system("pause");

	return 0;
 }