#include <stdio.h>
#include <switch.h>

void WaitButtonB()
{
    printf("\nPress B.");
    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_B) break;
    }
    consoleClear();
}

void printInfo()
{
    consoleClear();
    printf("A : Enable VR Mode\n");
    printf("B : Exit\n");
}

int main(int argc, char **argv)
{
    Result rc;
    gfxInitDefault();
    consoleInit(NULL);
    
    printInfo();
    
    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        
        if (kDown & KEY_B) break;
        
        if(kDown & KEY_A)
        {
            rc = appletSetVrModeEnabled(true);
            if (R_FAILED(rc))
            {
                printf("appletSetVrModeEnabled failed : 0x%X", rc);
                WaitButtonB();
                break;
            }
            printInfo();
        }
        
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    
    gfxExit();
    return 0;
}