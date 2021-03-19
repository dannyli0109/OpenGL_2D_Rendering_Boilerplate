//These includes are specific to the way we’ve set up GLFW and GLAD.
//#include "ProgramManager.h"
#include "Debug.h"
#include "App.h"

int WinMain(void)
{
    {
        App program;
        program.Init();
        while (program.IsRunning())
        {
            program.Run();
        }
        program.Destory();
    }
    _CrtDumpMemoryLeaks();
    
    return 0;
}
