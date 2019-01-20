#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include "fstream"
#include <fstream>

#include "SerialPort.h"

std::string todaysDate();
void eventLogger(std::string msg);

#define POLL 500
#define DEBUGG
void Send(std::string msg); 
void userAuth(std::string finalpin);

char portNo[] = "\\\\.\\COM6";
char *port_name = portNo;

char inData[MAX_DATA_LENGTH];
SerialPort arduino(port_name);

int main()
{
    //std::ofstream out;

    if (arduino.isConnected())
    {
        std::cout << "Alarm Central is connected" << std::endl;
    }
    else
    {
        std::cout << "Alarm Central is not connected" << std::endl;
    }

    //out.open("measure.dat", std::ios::app);
    while (arduino.isConnected())
    {   
        

        Sleep(POLL);

        int read_result = arduino.readSerialPort(inData, MAX_DATA_LENGTH); 
        if (read_result > 0)
        {
            
            if (inData[0] == 'A')
            {
                //std::cout << "OK";// Debugg
                std::string pin(inData);              // Convert char to string
                std::string finalPin = pin.substr(1); // Removes 'A' from string and sends to userAuth

                //send pin to userAuth
                userAuth(finalPin); 
            }

            /*time_t now = time(0);
            char* dt = ctime(&now);
            out << dt << ";" << inData;*/
        }

        Sleep(POLL);
    }

    //out.close();
   
}

void Send(std::string msg)
{
    char outData[msg.length()];
    std::size_t len = msg.copy(outData, msg.length(), 0);
    outData[len] = '\0';

    bool res = arduino.writeSerialPort(outData, sizeof(outData));
}
 // Get pin and sends OK to alarmcentral
void userAuth(std::string finalpin)
{
    bool noMatch = true;
    std::string id;
    std::string pincode;
    std::string oPin;
    std::string tag;
    std::string status;
    std::string reserved;
    //open the file
    std::ifstream fin;
    fin.open("users.dat");
    if (!fin.is_open())
    {
        // If users.dat isnt found
        std::cout << "Userfile failed to open." << std::endl;
        //return 0;
    }
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, id, ';');
            getline(fin, pincode, ';');
            getline(fin, oPin, ';');
            getline(fin, tag, ';');
            getline(fin, status, ';');
            getline(fin, reserved, '\n');

            //if regular pin is activated
            if (finalpin == pincode)
            {
                eventLogger("Alarm deactivated");
                noMatch = false;
                std::cout << "Welcome home ID: " << id << std::endl;
                break;
            }
            //If Assault pin is activated
            if (finalpin == oPin)
            {
                eventLogger("Assault PIN Used");
                noMatch = false;
                std::cout << "Assault PIN Activated by ID: " << id <<  " Sending officers."  << std::endl;
                break;
            }
        }
    }
    fin.close();
    memset(inData,0,sizeof(inData));
    if (noMatch == true)
    {
        Send("0");
    }
    Send("1");
}


//Function to log events
void eventLogger(std::string msg)
{
    std::ofstream outFile;
    std::ifstream inFile;
    std::string daysDate = todaysDate();
    char c;
    int rows = 0;

    inFile.open("system.log");

        if(inFile.is_open())
        {
            while(inFile.get(c))
            {   //Checks rows in file
                if(c == '\n'){
                    rows++;
                }
            }
            
            inFile.close();
        }
        outFile.open("system.log", std::ofstream::app);
        outFile << rows+1 << ";" << daysDate << ";" << msg << '\n';
        outFile.close();
}


//Function to get todays date from PC 
std::string todaysDate()
{
   time_t now = time(0);
   struct tm tstruct;
   char       date[80];
   tstruct = *localtime(&now);

   strftime(date, sizeof(date), "%Y%m%d %X", &tstruct);

   return date;
}