#include <iostream>
#include <string>
#include "scanner.h"
#include "parser.h"
#include "calc.h"
#include "exception.h"
#include "commandparser.h"

int main()
{
    STATUS status = STATUS_OK;
    Calc calc;
    do {
        std::cout <<"> ";
        Scanner scanner(std::cin);
        if (!scanner.IsEmpty()) {
            if (scanner.IsCommand()) {
                //parse command
                CommandParser cParser(scanner, calc);
                status = cParser.Excute();
            } else {
                Parser parser(scanner, calc);
                try {
                    status = parser.Parse();
                    if (status == STATUS_OK) {
                        std::cout << parser.Calculate() << std::endl;
                    } else {
                        std::cout << "Syntax Error" << std::endl;
                    }
                }
                catch (SyntaxError &se) {
                    std::cout << se.what() << std::endl;
                    std::cout << se.StackTrace() << std::endl;
                }
                catch (Exception& e) {
                    std::cout << e.what() << std::endl;
                }
                catch (std::bad_alloc& e) {
                    std::cout << e.what() << std::endl;
                }
                catch (...) {
                    std::cout << "Internal Error" << std::endl;
                }
                //clear the input buffer
                while (!scanner.IsDone()) {
                    scanner.Accept();
                }
            }
        } else {
            std::cout << "Expression is empty" << std::endl;
        }
    } while (status != STATUS_QUIT);
    return 0;
}

