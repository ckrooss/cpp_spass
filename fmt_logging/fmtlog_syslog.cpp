#include "fmtlog.h"
#include <syslog.h>

namespace fmtlog {
void output(std::string_view message) {
  syslog(LOG_ALERT, "%s", message.data());
}
}