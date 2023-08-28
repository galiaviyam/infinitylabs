/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Logger                  */
/*   Date:      07/06/23                */
/*   Reviewer:  Eliran                  */
/*                                      */
/****************************************/

#define I_AM_THE_HANDLETON_IMPLEMENTER

#include <iostream>         //cin
#include <string>           //string

#include "handleton.hpp"    //handleton header
#include "logger.hpp"       //logger header

using namespace ilrd;

void TestLogger(void);

int main() 
{
    TestLogger();

    return 0;
}

void TestLogger(void)
{
    auto logger = Handleton<ilrd::Logger>::GetInstance();

    logger->Log("error!");
    logger->Log("warning!");

    std::string buff = "\0";

    while ("q" != buff)
    {
        std::cout << "enter a message to log. type \"q\" to exit" << std::endl;
        std::getline(std::cin, buff);
        logger->Log(buff);
    }
}