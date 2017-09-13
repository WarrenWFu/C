/**
 * @file        
 * @brief       
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/
#include <regex>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    struct tm tm;
    time_t t;
        string data("On 2015-12-23, the shop will be closed, but on 2016-01-03, it will be open. Invalid date: 2016-13-32. ID: 1022015-12-233333.");
        std::regex pattern("\\b\\d{4}[-]\\d{2}[-]\\d{2}\\b");
        std::smatch result;

        while (regex_search(data, result, pattern)) {
            if (strptime(result[0].str().c_str(), "%Y-%m-%d", &tm) != NULL) {
              std::cout << result[0] << std::endl;
            }
            data = result.suffix().str();
        }
}
