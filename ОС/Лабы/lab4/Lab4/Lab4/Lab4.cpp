#include <iostream>
#include <Windows.h>



int main()
{
    while (true)
    {
        // Получение идентификатора текущего процесса и текущего потока
        DWORD process_id = GetCurrentProcessId();
        DWORD thread_id = GetCurrentThreadId();
        std::cout << "Process ID: " << process_id << ", Thread ID: " << thread_id << std::endl;

        // Длинная операция
        Sleep(1000);
    }

    return 0;
}


/*

$processName = "OS04_01"
$process = Get-Process -Name $processName
$threads = $process.Threads

foreach ($thread in $threads) {
    $threadId = $thread.Id
    $startTime = $thread.StartTime
    $cpuTime = $thread.TotalProcessorTime
    $threadInfo = "Thread ID: $threadId, Start Time: $startTime, CPU Time: $cpuTime"
    Write-Host $threadInfo
}

*/