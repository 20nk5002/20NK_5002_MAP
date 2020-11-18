#include<Windows.h>
#include"error.h"

void Error::showDialog( const char* Message ) {
    MessageBox( NULL, Message, "ERROR", MB_OK | MB_ICONERROR );
}