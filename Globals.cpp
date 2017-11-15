#include "Globals.h"

std::string GetFile(const char * path, bool take_extension)
{
	std::string ret;

	for (int i = 0; path[i] != '\0'; i++) {
		if (take_extension == false) {
			if (path[i] == '.')
				break;
		}
		if (path[i] == '\\' || path[i] == '/') {
			ret.clear();
			continue;
		}
		ret += path[i];
	}

	return ret;
}

std::string GetExtension(const char * path)
{
	std::string extension;

	for (int i = 0; path[i] != '\0'; i++) {
		if (path[i] == '.') {
			extension.clear();
			continue;
		}
		extension += path[i];
	}

	return extension;
}

const char* GetCExtension(const char * path)
{
	std::string extension;

	for (int i = 0; path[i] != '\0'; i++) {
		if (path[i] == '.') {
			extension.clear();
			continue;
		}
		extension += path[i];
	}

	const char* ret = extension.c_str();

	return ret;
}