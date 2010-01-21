/**
*
* Copyright © 2004 Michael Maguire.
* 
* You are hereby granted free use of the software in this file,
* provided you maintain this entire copyright notice at the top.
*
* This software is provided "as is," and the copyright holder 
* makes no representations or warranties, express or implied,
* including but not limited to warranties of merchantability or 
* fitness for any particular purpose or that the use of this software
* or documentation will not infringe any third party patents, 
* copyrights, trademarks or other rights.
*
* The copyright holder will not be liable for any direct, indirect
* special or consequential damages arising out of any use of this
* software or documentation.
*
*/


#include <e32cons.h>
#include <TestInterface.h>
#include "EcomPlus.h"

_LIT(KTxt1,"dynamically linked DLL example \n\n");
_LIT(KTxt2,"checking UID\n");
_LIT(KTxt3,"DLL has incorrect UID... \n");

LOCAL_D CConsoleBase* console;

LOCAL_C void DoExampleL()
{
	MTestInterface * testInterface = DiL( MTestInterface );
	CleanupReleasePushL(*testInterface);

	TInt answer = testInterface->foo(4, 5);

	if( answer != 9 )
	{
		User::Leave(KErrGeneral);
	}

	MTestInterface2 * testInterface2 = QiL( testInterface, MTestInterface2 );
	CleanupReleasePushL(*testInterface2);

	answer = testInterface2->bar(3,2);
	
	if( answer != 6 )
	{
		User::Leave(KErrGeneral);
	}

	CleanupStack::PopAndDestroy(testInterface2);
	CleanupStack::PopAndDestroy(testInterface);



	MTestInterface * testInterface3 = reinterpret_cast<MTestInterface *>( REComPlusSession::CreateImplementationL(KImplUid_MTestInterface, TUid::Uid(KIID_MTestInterface), (TAny *) 0xCAFEBABE) );
	CleanupReleasePushL(*testInterface3);
	CleanupStack::PopAndDestroy(testInterface3);

}

_LIT(KTxtECOMPLUS, "ECOMPLUS");
_LIT(KTxtConsoleName,"EcomPlus test client");
_LIT(KFormatError,"error: leave code=%d");


LOCAL_C TInt CallExampleL()
{
	console=Console::NewL(KTxtConsoleName,TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	TRAPD(error,DoExampleL());
	if (error)
	{
		console->Printf(KFormatError, error);
	}
	else
	{
		console->Printf(_L("Passed"));
	}
	console->Printf(_L("[press any key]"));
	console->Getch();
	CleanupStack::PopAndDestroy();
	return error;
}

GLDEF_C TInt E32Main()
{
	__UHEAP_MARK;
	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	TRAPD(error, error = CallExampleL()); // more initialization, then do example
	delete cleanup;
	__UHEAP_MARKEND;
	return error;
}

