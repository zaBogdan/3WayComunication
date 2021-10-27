#include "InternalAPI.h"

std::string InternalAPI::ReadFile(const char* filePath)
{
    //maybe here i can fstat to read the file size and dynamically alloc the buffer
    std::cout << "[InternalAPI::ReadFile] Reading the file: " << filePath << "\n";
    
    int fd = open(filePath, O_RDONLY);
    std::cout << "[InternalAPI::ReadFile] FD status: " << fd << "\n";
    if(fd == -1)
    {
        std::cout << "[InternalAPI::ReadFile] Failed to read file " << filePath << "\n";
        return std::string("");
    }
    char buf[2*1024];
    int len = read(fd, buf, sizeof(buf));
    buf[len] = '\0';
    std::cout << "[InternalAPI::ReadFile] Length: " << len << '\n';

    return std::string(buf);
}

// Code got from: https://www.geeksforgeeks.org/convert-unix-timestamp-to-dd-mm-yyyy-hhmmss-format/
std::string InternalAPI::unixTimeToDate(long int seconds)
{
 
    std::string ans = "";
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
 
    long int currYear, daysTillNow, extraTime,
        extraDays, index, date, month, hours,
        minutes, secondss, flag = 0;
 
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;
 
    // Calculating current year
    while (daysTillNow >= 365) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0
                && currYear % 100 != 0)) {
            daysTillNow -= 366;
        }
        else {
            daysTillNow -= 365;
        }
        currYear += 1;
    }
 
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;
 
    if (currYear % 400 == 0
        || (currYear % 4 == 0
            && currYear % 100 != 0))
        flag = 1;
 
    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {
 
            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays
                        - daysOfMonth[index]
                    < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {
 
            if (extraDays
                    - daysOfMonth[index]
                < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }
 
    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }
 
    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;
 
    ans += std::to_string(date);
    ans += "/";
    ans += std::to_string(month).insert(0,1-(month/10 == 0 ? 0 : 1),'0');
    ans += "/";
    ans += std::to_string(currYear);
    ans += " ";
    ans += std::to_string(hours).insert(0,1-(hours/10 == 0 ? 0 : 1),'0');
    ans += ":";
    ans += std::to_string(minutes).insert(0,1-(minutes/10 == 0 ? 0 : 1),'0');
    ans += ":";
    ans += std::to_string(secondss).insert(0,1-(secondss/10 == 0 ? 0 : 1),'0');
 
    // Return the time
    return ans;
}