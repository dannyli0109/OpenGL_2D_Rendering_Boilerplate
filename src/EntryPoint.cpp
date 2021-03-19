//These includes are specific to the way we’ve set up GLFW and GLAD.
#include "ProgramManager.h"
#include "Debug.h"

int WinMain(void)
{
    {
        ProgramManager program;
        program.Init();
        program.Run();
        program.Destory();
    }
    _CrtDumpMemoryLeaks();
    
    return 0;
}
