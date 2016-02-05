/*
 * Ants2016z.h
 *
 *  Created on: Dec 27, 2015
 *      Author: motey
 *      This doesn't really need to be in a separate file
 *      just to see how it works
 */
#ifndef ANTS2016Z_H_
#define ANTS2016Z_H_
#include <iostream>
#include <string>
#include <SDL.h>
std::string getResourcePath(const std::string &subDir = "") {
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}
#endif /* ANTS2016Z_H_ */
