#pragma once
#include <Windows.h>
#include <Psapi.h>

#include <vector>
#include <string>

#include <filesystem>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <functional>
#include <random>
#include <chrono>

#include <map>

#include <MinHook.h>

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

struct Vec2 {
	union {
		struct {
			float x, y;
		};
		float arr[2];
	};
	Vec2() { x = y = 0; };
	Vec2(float x = 0, float y = 0) { this->x = x; this->y = y; };
};

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float arr[3];
	};
	Vec3() { x = y = 0; };
	Vec3(float x = 0, float y = 0, float z = 0) { this->x = x; this->y = y; this->z = z; };
};

struct Vec3_i {
	union {
		struct {
			int x, y, z;
		};
		int arr[3];
	};
	Vec3_i() { x = y = 0; };
	Vec3_i(int x = 0, int y = 0, int z = 0) { this->x = x; this->y = y; this->z = z; };
};

class Utils {
public:
	static HMODULE hModule;
	static bool hasExtension(std::string fileName);
	static bool doesPathExist(std::string);
	static void CreateDir(std::string);
	static void DeletePath(std::string);
	static void WriteToFile(std::string, std::string);
	static void DebugLogOutput(std::string);
	static uintptr_t FindAddr(uintptr_t, std::vector<unsigned int>);
	static uintptr_t FindSig(const char*);
	static std::string addrToStr(uintptr_t);
};