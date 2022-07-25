#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <io.h>
#include <Windows.h>

int main(int argc, char *argv[]);
BOOL VSCodeExists();
void Start(int argc, char *argv[]);
void Replace(char *currentPath);

char *title = "���±��滻����";
char *vscodePath = "C:\\VSCode\\Code.exe";
char *notepadPath1 = "C:\\Windows\\notepad.exe";
char *notepadPath2 = "C:\\Windows\\System32\\notepad.exe";
char *notepadPath3 = "C:\\Windows\\SysWOW64\\notepad.exe";

int main(int argc, char *argv[])
{
    char *currentPath = argv[0];
    if (strcmp(currentPath, notepadPath1) == 0 ||
        strcmp(currentPath, notepadPath2) == 0 ||
        strcmp(currentPath, notepadPath3) == 0)
    {
        Start(argc, argv);
    }
    else
    {
        Replace(currentPath);
    }
    return 0;
}

BOOL VSCodeExists()
{
    if (_access(vscodePath, 6) == 0)
    {
        return TRUE;
    }
    else
    {
        char string[4096] = "";
        sprintf(string, "�Ҳ����ļ���%s", vscodePath);
        MessageBoxA(NULL, string, title, 16);
        return FALSE;
    }
}

void Start(int argc, char *argv[])
{
    if (VSCodeExists())
    {
        char cmdLine[4096] = "";
        for (int i = 0; i < argc; i++)
        {
            if (i == 0)
            {
                sprintf(cmdLine, "%s", vscodePath);
            }
            else
            {
                sprintf(cmdLine, "%s %s", cmdLine, argv[i]);
            }
        }
        sprintf(cmdLine, "%s\0", cmdLine);
        STARTUPINFO si = {
            0,
        };
        PROCESS_INFORMATION pi = {
            0,
        };
        si.cb = sizeof(si);
        if (CreateProcessA(
                NULL,
                cmdLine,
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi))
        {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else
        {
            printf("CreateProcessA failed (%d)\n", GetLastError());
            MessageBoxA(NULL, "��������ʱ��������", title, 0);
        }
    }
}

void Replace(char *currentPath)
{
    Wow64EnableWow64FsRedirection(FALSE);
    char string[4096] = "";
    if (CopyFileA(currentPath, notepadPath1, FALSE))
    {
        sprintf(string, "%s�滻�ɹ�", notepadPath1);
        MessageBoxA(NULL, string, title, 0);
    }
    else
    {
        sprintf(string, "%s�滻ʧ�ܣ���ʹ�û����ļ�������ɾ�����ļ������ԡ�", notepadPath1);
        MessageBoxA(NULL, string, title, 0);
    }

    if (CopyFileA(currentPath, notepadPath2, FALSE))
    {
        sprintf(string, "%s�滻�ɹ�", notepadPath2);
        MessageBoxA(NULL, string, title, 0);
    }
    else
    {
        sprintf(string, "%s�滻ʧ�ܣ���ʹ�û����ļ�������ɾ�����ļ������ԡ�", notepadPath2);
        MessageBoxA(NULL, string, title, 0);
    }

    if (CopyFileA(currentPath, notepadPath3, FALSE))
    {
        sprintf(string, "%s�滻�ɹ�", notepadPath3);
        MessageBoxA(NULL, string, title, 0);
    }
    else
    {
        sprintf(string, "%s�滻ʧ�ܣ���ʹ�û����ļ�������ɾ�����ļ������ԡ�", notepadPath3);
        MessageBoxA(NULL, string, title, 0);
    }
}