#include "CSmtp.h"
#include <iostream>

int main()
{
	bool bError = false;

	try
	{
		CSmtp mail;

		mail.SetSMTPServer("smtp.exmail.qq.com",465);
		mail.SetSecurityType(USE_SSL);

		mail.SetLogin("admin@coyangjr.cn");
		mail.SetPassword("Whu2020");
  		mail.SetSenderName("Co");
  		mail.SetSenderMail("admin@coyangjr.cn");
  		mail.SetSubject("The message");
  		mail.AddRecipient("1114738346@qq.com");
  		mail.SetXPriority(XPRIORITY_NORMAL);
  		mail.SetXMailer("The Bat! (v3.02) Professional");
  		mail.AddMsgLine("Hello,");
		mail.AddMsgLine("");
		mail.AddMsgLine("...");
		mail.AddMsgLine("How are you today?");
		mail.AddMsgLine("");
		mail.AddMsgLine("Regards");
		mail.ModMsgLine(5,"regards");
		mail.DelMsgLine(2);
		mail.AddMsgLine("User");

  		//mail.AddAttachment("../test1.jpg");
  		//mail.AddAttachment("c:\\test2.exe");
		mail.AddAttachment("D:\\test.txt");
		mail.Send();
	}
	catch(ECSmtp e)
	{
		std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		bError = true;
	}
	if(!bError)
		std::cout << "Mail was send successfully.\n";
	return 0;
}
