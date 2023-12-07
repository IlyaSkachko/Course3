
#include <Windows.h>
#include <iostream>

#define READ_BYTES 1024

LPCWSTR getFileType(HANDLE file)
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN:
        return L"FILE_TYPE_UNKNOWN";
    case FILE_TYPE_DISK:
        return L"FILE_TYPE_DISK";
    case FILE_TYPE_CHAR:
        return L"FILE_TYPE_CHAR";
    case FILE_TYPE_PIPE:
        return L"FILE_TYPE_PIPE";
    case FILE_TYPE_REMOTE:
        return L"FILE_TYPE_REMOTE";
    default:
        return L"[ERROR]: WRITE FILE TYPE";
    }
}


BOOL printFileTxt(LPWSTR path)
{
    HANDLE file = CreateFile(path, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    char buf[1024];

    DWORD bytes = NULL;
    ZeroMemory(buf, sizeof(buf));

    BOOL readFile = ReadFile(file, &buf, READ_BYTES, &bytes, NULL);

    if (!readFile)
    {
        throw "Read file failed";
    }


    std::cout << buf << std::endl;

    CloseHandle(file);
}

BOOL printFileInfo(LPWSTR path, char* fileName)
{
    try
    {
        HANDLE file = CreateFile(path, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (file == INVALID_HANDLE_VALUE)
        {
            throw "Create file failed";
        }


        BY_HANDLE_FILE_INFORMATION fi;
        BOOL fileInfo = GetFileInformationByHandle(file, &fi);

        if (!fileInfo)
        {
            throw "Get file info failed";
        }

        SYSTEMTIME sysTime;

        std::cout << "File name:\t" << fileName;
        std::wcout << "\nFile type:\t" << getFileType(file);
        std::cout << "\nFile size:\t" << fi.nFileSizeLow << " bytes";
        FileTimeToSystemTime(&fi.ftCreationTime, &sysTime);
        std::cout << "\nCreate time:\t" << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear << " " << sysTime.wHour + 3 << '.' << sysTime.wMinute << '.' << sysTime.wSecond;
        FileTimeToSystemTime(&fi.ftLastWriteTime, &sysTime);
        std::cout << "\nUpdate time:\t" << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear << " " << sysTime.wHour + 3 << '.' << sysTime.wMinute << '.' << sysTime.wSecond;
        std::cout << std::endl;

        CloseHandle(file);

    }
    catch (char* em)
    {
        std::cout << "-- Error: " << em << std::endl;
    }
}

int main()
{


    auto path = L"D://UNIVER//Course3//ОС//Лабы//Lab9//x64//Debug//OS09_01.txt";

    LPWSTR file = (LPWSTR)path;

    char fileName[] = "OS09_01.txt";


    std::cout << "\n\n---------------------------------\n\n";
    printFileInfo(file, fileName);
    std::cout << "\n\n---------------------------------\n\n";
    printFileTxt(file);

    system("pause");
    return 0;
}

