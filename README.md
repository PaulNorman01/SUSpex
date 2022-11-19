# SUSpex
A Simple Code Snippet To Suspend And Resume Threads In An External Process.

Must Be In The Same Privilege Group as The Specified Process. Can Be Used With Certain Services That Might Restart The Process If It Ever Runs to Exit(0). Can Also Be Used To Stop And Debug Processes With Anti-Debug Capabilities and Anti-Breakpoint Features. 

## Usage
To Suspend Threads:                 suspex.exe \<pid\>

To Resume The Suspended Threads:    suspex.exe \<pid\> /continue


## Screenshot

Notepad Process Has been Suspended In The Below Image:

![Screenshot](suspex.png)
