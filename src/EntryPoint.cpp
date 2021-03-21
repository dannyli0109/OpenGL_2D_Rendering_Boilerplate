//These includes are specific to the way we’ve set up GLFW and GLAD.
//#include "ProgramManager.h"
#include "Debug.h"
#include "App.h"

int WinMain(void)
{
    {
        App* program = new App();
        while (program->IsRunning())
        {
            program->Run();
        }
        program->Destory();
        delete program;
    }
    _CrtDumpMemoryLeaks();
    
    return 0;
}
