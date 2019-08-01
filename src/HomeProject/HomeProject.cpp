#include <algorithm>
#include <array>
#include <chrono>
#include <ctime>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <spawn.h>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <thread>
#include <vector>

using namespace std;

static std::string _developmentBuild;
static std::string _FirmwareLoad;

static uint8_t _majorVersion;
static uint8_t _minorVersion;
static uint8_t _buildFlag;
static uint8_t _releaseCand;

static std::vector<int> newVec;

bool isAlsoDigit(char c)
{
    return isdigit(c);
}

void something();

vector<string> split (std::string s, std::string d) {
    size_t start = 0, pos_end;
    vector<string> res;

    while ((pos_end = s.find (d, start)) != string::npos)
    {
        res.push_back (s.substr (start, pos_end - start));
        start = pos_end + d.length();
    }

    res.push_back (s.substr (start));
    return res;
}

int parseString(std::string testString)
{
    const std::string delim = ".";

    std::vector<std::string> splitedString = split(testString , delim);

    if (splitedString.size() != 4)
    {
        std::cerr << "Invalid string size, size=" << splitedString.size();
        return -1;
    }

    auto firstSection = splitedString.at(0);

    if((firstSection.size() < 3) ||
       (firstSection.size() > 5))
    {
        std::cerr << "Invalid initial string size, size=" << firstSection.size();
        return -1;
    }

    _developmentBuild = firstSection.substr(0, 1);
    _FirmwareLoad = firstSection.substr(1, 1);

    splitedString.at(0) = firstSection.substr(2);

    for (auto s: splitedString)
    {
        if ((0 != s.size()) && (s.size() <= 3) &&
            all_of(s.begin(), s.end(), ::isAlsoDigit))
        {
            newVec.push_back(std::atoi(s.c_str()));
            if (newVec.at(newVec.size() -1) > 255)
            {
                std::cerr << "error";
                return -1;
            }
        }
        else
        {
            cerr << "characters in the string " << " s.size=" << s.size() << endl;
            return -1;
        }
    }

    _majorVersion = newVec.at(0);
    _minorVersion = newVec.at(1);
    _buildFlag    = newVec.at(2);
    _releaseCand  = newVec.at(3);

    cerr << "String output = " << splitedString.at(0) << "."
                               << splitedString.at(1) << "."
                               << splitedString.at(2) << "."
                               << splitedString.at(3) << endl;

    cerr << "vector output = " << newVec.at(0) << "."
                               << newVec.at(1) << "."
                               << newVec.at(2) << "."
                               << newVec.at(3) << endl;

    cerr << "Final output  = " << +_majorVersion << "."
                               << +_minorVersion << "."
                               << +_buildFlag    << "."
                               << +_releaseCand  << endl;

    return 0;
}

enum
{
    JANUARY, FEBUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,
};

void getTimeDiff()
{
    struct TimeConst
    {
        int day;
        int month;
        int year;
    };

    const TimeConst a =
    {
        .day = 1,
        .month = 6,
        .year = 2013,
    };

    const TimeConst b =
    {
        .day = 1,
        .month = 9,
        .year = 2019,
    };

    std::tm timeA = {0, 0, 0, a.day, (a.month - 1), (a.year - 1900), 0, 0, 0, 0, 0};
    std::time_t ATime = std::mktime(&timeA);

    std::tm timeB = {0, 0, 0, b.day, (b.month - 1), (b.year - 1900), 0, 0, 0, 0, 0};
    std::time_t BTime = std::mktime(&timeB);

    uint64_t diff = std::difftime(BTime, ATime) ;
    std::cout << "difference = " << +diff << std::endl;

    std::cerr << "timeA:" << ctime(&ATime)<< std::endl << "\b";
    std::cerr << "timeA:" << ctime(&ATime)<< std::endl << "\b";
    std::cerr << "this";
}

void calcTimeInSec()
{
    enum
    {
        CM_UNKNOWN,
        CM_SECONDARY_AUTH_V1_0,
        CM_SECONDARY_AUTH_V2_0,
        CM_SECONDARY_AUTH_V2_1,
        CM_SECONDARY_AUTH_V2_2,
        CM_SUPPLY_RECON_V1_1,
        CM_SUPPLY_RECON_V1_2,
        CM_ECDSA_SIGNATURE,
        CM_CID,
    };

    struct TriggerEnabled
       {
           bool DFW0;
           bool DFW1;
           bool TFW0;
       };

       struct TriggerTime
       {
           unsigned int test;
           unsigned int day;
           unsigned int month;
           unsigned int year;
           struct TriggerEnabled tr;
       };

       const TriggerTime EPOCH           = {CM_UNKNOWN, 1, 6, 2013,
                                            {true,  true,  true}};  // 1st June 2013
       const TriggerTime SEC_AUTH_V1_0   = {CM_SECONDARY_AUTH_V1_0, 1, 9, 2019,
                                            {true,  false, false}}; // 1st Sept 2019
       const TriggerTime SEC_AUTH_V2_0   = {CM_SECONDARY_AUTH_V2_0, 1, 7, 2020,
                                            {false, true,  false}}; // 1st July 2020
       const TriggerTime SEC_AUTH_V2_1   = {CM_SECONDARY_AUTH_V2_1, 1, 7, 2022,
                                            {false, true,  false}}; // 1st July 2022
       const TriggerTime SEC_AUTH_V2_2   = {CM_SECONDARY_AUTH_V2_2, 1, 7, 2024,
                                            {false, true,  false}}; // 1st July 2024
       const TriggerTime SUP_RECON_V1_1  = {CM_SUPPLY_RECON_V1_1, 1, 7, 2021,
                                            {false, true,  false}}; // 1st July 2021
       const TriggerTime SUP_RECON_V1_2  = {CM_SUPPLY_RECON_V1_2, 1, 7, 2023,
                                            {false, true,  false}}; // 1st July 2023
       const TriggerTime ECDSA_SIGNATURE = {CM_ECDSA_SIGNATURE, 1, 1, 2022,
                                            {false, true,  false}}; // 1st Jan  2022
       const TriggerTime CID             = {CM_CID, 1, 1, 2024,
                                            {true,  true,  false}}; // 1st Jan  2024

       (void)getTimeDiff();
       std::tm timeA = {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0};
}

void sendTmpVec(const std::vector<int>& tmpV = {})
{
    std::cerr << "tv:";
    for (auto a: tmpV)
    {

        std::cerr << +a;
    }

    std::cerr << std::endl;
}

void getArrayOutput(std::array<unsigned int, 4>& fs)
{
    for (auto i : fs)
    {
        std::cout << i << std::endl;
    }
}

void useCpp11()
{
    enum
    {
        DFW0,
        DFW1,
        DFW2,
        TFW0,
    };

    enum
    {
        TEST_CHANGE_DFW0,
        TEST_CHANGE_DFW1,
    };

    std::vector<unsigned int> fsDfw0 = {DFW0, DFW1, DFW2, TFW0};
    std::vector<unsigned int> fsDfw1 = {DFW0, DFW1};

    std::vector<unsigned int> fsDfw;

    std::map<unsigned int, std::vector<unsigned int>> respMap =
    {
        {TEST_CHANGE_DFW0, fsDfw0},
        {TEST_CHANGE_DFW1, fsDfw1},
    };

    std::map<unsigned int, std::vector<unsigned int>>::const_iterator itr = respMap.find(TEST_CHANGE_DFW1);
    if (itr != respMap.end())
    {
        fsDfw = itr->second;
    }

    std::cerr << "size=" << fsDfw.size();
}

void _createfile()
{
    std::ifstream tsf ("/users/aanaik/test/timestore.bin", std::ofstream::binary);
    if (!tsf.is_open())
    {
        std::cerr << "not open: " << strerror(errno);
    }
}

class Base
{
public:
    virtual void printVariable();
protected:
    static const int VARIABLE_TMP = 10;
private:
};

class Derived : public Base
{
public:
    virtual void printVariable();
protected:
private:
};

void Base::printVariable()
{
    std::cerr << "In Base class, variable=" << VARIABLE_TMP << std::endl;
}

void Derived::printVariable()
{
    std::cerr << "In Derived class, variable=" << VARIABLE_TMP << std::endl;
}

void testPrintVariable()
{
    Base b;
    Derived d;
    Base *pb = new Base();
    Base *pd = new Derived();


    b.printVariable();
    d.printVariable();
    pb->printVariable();
    pd->printVariable();
}

void testFuncPtra(int a)
{
    std::cerr << "Printing a=" << a << "\n\n";
}

void testFuncPtrb(int a, int b)
{
    std::cerr << "Printing a=" << a << " and b=" << b << "\n\n";
}

void useStdFunctionforFucnPtr()
{
    int a = 0;
    int b = 1;

    using std::placeholders::_1;
    std::function<void(int)> funca, funcb;

    funca = std::bind(testFuncPtra, a);
    funcb = std::bind(testFuncPtrb, a, _1);

    //std::cerr << "\nLoading funca without argument\n" << std::endl;
    //funca();
    std::cerr << "\nLoading funca with 1 argument\n" << std::endl;
    funca(b);
    std::cerr << "\nLoading funcb with 1 argument\n" << std::endl;
    funcb(b);
    //std::cerr << "Loading funcb without argument\n" << std::endl;
    //funcb();
}

void startSmallApp()
{
    std::cerr << "Started\n";
    std::string processName = "/bonus/scratch/aanaik/Aakash-Test/slickedit-proj-files/Debug/smallApp/smallApp";

    std::string _featureSet = "0";
    _featureSet = std::to_string(3);

    std::string op1 = "-f";

    const char* args[] =
    {
        processName.c_str(),
        op1.c_str(),
        _featureSet.c_str(),
        nullptr
    };

    pid_t pid = 0;

    const int rc = posix_spawnp(&pid,
                                processName.c_str(),
                                nullptr,
                                nullptr,
                                const_cast<char**>(args),
                                nullptr);
    if (rc)
    {
        std::cerr << processName << " posix_spawnp failed, rc=" << rc << "\n";
    }
}

void writeBinary()
{
    std::ofstream fout;
    fout.open("/users/aanaik/Downloads/test.bin", ios::binary | ios::out);

    std::vector<uint8_t> test
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    };

    fout.write(reinterpret_cast<const char *>(&test[0]), test.size());
    fout.close();
}

void vectorAssignInsert()
{
    std::vector<uint8_t> v1(100, 1);
    std::vector<uint8_t> v2(5, 2);

//    v1.insert(v1.begin() + 22, v2.begin(), v2.end());
//    std::copy(v2.begin(), v2.end(), v1.begin() + 99);

    v1.assign(v2.begin(), v2.end());
    std::cerr << "size  of v1 is " << v1.size() << std::endl;

    for (const auto &v : v1 )
    {
        std::cerr << "Value of v1 is " << +v << std::endl;
    }


    v1.insert(v1.begin() + 22, v2.begin(), v2.end());
}

int main (int argc, char *argv[])
{
  std::string pfid3("0x23c3");
  pfid3.erase(0, 2);

  unsigned int        platformId, platformId2;
  std::stringstream   ssPfid, ssPfid2;


  ssPfid << std::hex << pfid3;
  ssPfid2 << pfid3;

  std::cerr << "ssPfid :" << ssPfid.str() << std::endl;
  std::cerr << "ssPfid2:" << ssPfid2.str() << std::endl;

  ssPfid >> platformId;
  ssPfid2 >> platformId2;

  std::cerr << "platform  Id=" << std::hex << platformId << std::endl;
  std::cerr << "platform Id2=" << std::hex << platformId2 << std::endl;
}

