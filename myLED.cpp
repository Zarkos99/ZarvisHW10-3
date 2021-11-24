#include <iostream>         // for the input/output
#include <stdlib.h>         // for the getenv call
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/FormEntry.h>
#include <unistd.h>		//for sleep delay
#include "GPIO.h"
using namespace exploringBB;
using namespace std;
using namespace cgicc;

int main(){
   Cgicc form;                      // the CGI form object
   string cmd;                      // the Set LED command
   GPIO ledGPIO(60);
   ledGPIO.setDirection(OUTPUT);

   // get the state of the form that was submitted - script calls itself
   bool isStatus = form.queryCheckbox("cmd");
   form_iterator it = form.getElement("cmd");  // the button command
   form_iterator numBlinks = form.getElement("blinks");
   if (it == form.getElements().end() || it->getValue()==""){
      cmd = "off";                     // if it is invalid use "off"
   }
   else { cmd = it->getValue(); }      // otherwise use submitted value
   char *value = getenv("REMOTE_ADDR");    // The remote IP address
 
   // generate the form but use states that are set in the submitted form
   cout << HTTPHTMLHeader() << endl;       // Generate the HTML form
   cout << html() << head() << title("LED Example") << head() << endl;
   cout << body() << h1("CPE 422 Post LED Example") << endl;
   cout << h2("Controlling a GPIO pin via a Web Browser") << endl;
   cout << "<form action=\"/cgi-bin/myLED.cgi\" method=\"POST\">\n";
   cout << "<div>Set LED: <input type=\"radio\" name=\"cmd\" value=\"on\""
        << ( cmd=="on" ? "checked":"") << "/> On ";
   cout << "<input type=\"radio\" name=\"cmd\" value=\"off\""
        << ( cmd=="off" ? "checked":"") << "/> Off ";
   cout << "<input type=\"radio\" name=\"cmd\" value=\"blink\""
        << ( cmd=="blink" ? "checked":"") << "/> Blink ";
   cout << "<input type=\"submit\" value=\"Set LED\"/>";
   cout << "<br><br>Number of Blinks:<input type=\"text\" name=\"blinks\" size=\"10\"";
   cout << "</div></form>";
 
   if(cmd=="on")ledGPIO.setValue(HIGH);
   else if(cmd=="off")ledGPIO.setValue(LOW);
   else if(cmd=="blink"){
   	for(int i=0; i<numBlinks->getIntegerValue(); i++){
		ledGPIO.setValue(HIGH);
		sleep(1);
		ledGPIO.setValue(LOW);
	     	sleep(1);	
	}
   }
   cout << body() << html();
   return 0;
}
