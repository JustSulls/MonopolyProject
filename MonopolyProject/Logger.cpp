#include "Logger.h"
#include "Logger.h"
#include"Utilities.h"
#include <stdio.h>
const string CLogger::m_sFileName = "Log.txt";
const string CLogger::m_sFileNameDiceLog = "DiceLog.txt";
CLogger* CLogger::m_pThis = NULL;
CLogger* CLogger::m_pDThis = NULL;
ofstream CLogger::m_Logfile;
ofstream CLogger::m_DLogfile;
CLogger::CLogger()
{

}
CLogger* CLogger::GetLogger() {
    if (m_pThis == NULL) {
        m_pThis = new CLogger();
        m_Logfile.open(m_sFileName.c_str(), ios::out | ios::trunc);
    }
    return m_pThis;
}
CLogger* CLogger::GetDLogger()
{
  if (m_pDThis == NULL)
  {
    m_pDThis = new CLogger();
    m_DLogfile.open(m_sFileNameDiceLog.c_str(), ios::out | ios::trunc);
  }
  return m_pDThis;
}
void CLogger::LogDiceRolls(const string& sMessage)
{
  m_DLogfile << sMessage << "\n";
}

void CLogger::Log(const char* format, ...)
{
    char* sMessage = NULL;
    int nLength = 0;
    va_list args;
    va_start(args, format);
    //  Return the number of characters in the string referenced the list of arguments.
    // _vscprintf doesn't count terminating '\0' (that's why +1)
    nLength = _vscprintf(format, args) + 1;
    sMessage = new char[nLength];
    vsprintf_s(sMessage, nLength, format, args);
    //vsprintf(sMessage, format, args);
    m_Logfile << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    std::cout << sMessage << "\n";
    va_end(args);

    delete[] sMessage;
}

void CLogger::DLog(const char* format, ...)
{
  char* sMessage = NULL;
  int nLength = 0;
  va_list args;
  va_start(args, format);
  //  Return the number of characters in the string referenced the list of arguments.
  // _vscprintf doesn't count terminating '\0' (that's why +1)
  nLength = _vscprintf(format, args) + 1;
  sMessage = new char[nLength];
  vsprintf_s(sMessage, nLength, format, args);
  //vsprintf(sMessage, format, args);
  m_DLogfile << sMessage << "\n";
  va_end(args);

  delete[] sMessage;
}

void CLogger::Log(const string& sMessage)
{
    m_Logfile << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    std::cout << sMessage << "\n";
}

CLogger& CLogger::operator<<(const string& sMessage)
{
    m_Logfile << "\n" << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    std::cout << sMessage << "\n";
    return *this;
}