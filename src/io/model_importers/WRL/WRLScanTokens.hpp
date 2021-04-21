#ifndef WRL_SCAN_TOKENS_HEADER
#define WRL_SCAN_TOKENS_HEADER
#include <string>
#include <vector>

bool isAttributeToken(const std::string & token);
void getScanTokensFromVRML(const std::string & content, std::vector<std::string> &tokens);

#endif
