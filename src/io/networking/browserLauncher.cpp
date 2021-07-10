#include "browserLauncher.hpp"

#include "HTTPServer.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <windows.h>
#include <cstdio>

void launchRelativeDocument(const char *relPath)
{
  char s[300];

  sprintf(s, "http://localhost:%d/%s", getHttpServerPort(), relPath);
  launchURL(s);
}

void launchURL(const char *url)
{
   ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}