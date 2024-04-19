// fork() creates a new process by duplicating the calling process
// The new process is referred as the child process. The calling process is called as the parent process

// The child and parent processes run in separate memory spaces. At the time of fork() both have
// the same content. Memory writing file mapping and unmapping of one process won't affect the
// other one
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t p;
    cout << "before fork\n";
    p = fork();
    if (p < 0)
        cout << "error";
    if (p == 0) // child process
    {
        cout << "I am child having id " << getpid() << endl;
        cout << "My parent's id is " << getppid() << endl;
    }
    else // p > 0 (parent process)
    {
        // wait(NULL); // it makes parent wait for the child process to complete
        cout << "My child's id is " << p << endl;
        cout << "I am parent having id " << getpid() << endl;
    }
    cout << "Common\n";
    return 0;
}
