#include <syslog.h>
#include <string>

int main() {
    std::string MSG_EMERG = "MSG_EMERG";
    std::string MSG_ALERT = "MSG_ALERT";
    std::string MSG_CRIT = "MSG_CRIT";
    std::string MSG_ERR = "MSG_ERR";
    std::string MSG_WARNING = "MSG_WARNING";
    std::string MSG_NOTICE = "MSG_NOTICE";
    std::string MSG_INFO = "MSG_INFO";
    std::string MSG_DEBUG = "MSG_DEBUG";

    syslog(LOG_EMERG, "%s", MSG_EMERG.c_str());
    syslog(LOG_ALERT, "%s", MSG_ALERT.c_str());
    syslog(LOG_CRIT, "%s", MSG_CRIT.c_str());
    syslog(LOG_ERR, "%s", MSG_ERR.c_str());
    syslog(LOG_WARNING, "%s", MSG_WARNING.c_str());
    syslog(LOG_NOTICE, "%s", MSG_NOTICE.c_str());
    syslog(LOG_INFO, "%s", MSG_INFO.c_str());
    syslog(LOG_DEBUG, "%s", MSG_DEBUG.c_str());
}
