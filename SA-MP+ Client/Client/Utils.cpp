/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CUtils.cpp
 *  PURPOSE:     Util functions
 *
 *****************************************************************************/

#include <StdInc.h>

#include "Utils.h"

using namespace std;

char* ReplaceAnyStringOccurrence(char* szBuffer, const char* szWhat, const char* szWith, size_t sizeMax)
{
	// TODO: Check for max size
	// Copy the input buffer
	char* szTemp = new char[strlen(szBuffer) + 1];
	strcpy(szTemp, szBuffer);

	// Clear the original string
	strcpy(szBuffer, "");

	// Grab the size of what to replace and what to replace with
	size_t sizeWhat = strlen(szWhat);
	size_t sizeWith = strlen(szWith);

	// Iterate through the original string
	char*        szSourceIterator = szTemp;
	char*        szDestIterator = szBuffer;
	unsigned int uiCurrentSize = 0;
	while (*szSourceIterator)
	{
		if (strncmp(szSourceIterator, szWhat, sizeWhat) == 0)
		{
			strcpy(szDestIterator, szWith);

			// Inc the stuff
			uiCurrentSize += static_cast<unsigned int>(sizeWith);
			szSourceIterator += sizeWhat;
			szDestIterator += sizeWith;
		}
		else
		{
			*szDestIterator = *szSourceIterator;
			++uiCurrentSize;
			++szSourceIterator;
			++szDestIterator;
		}
	}

	// Free the copy and return the buffer
	delete[] szTemp;
	return szBuffer;
}

unsigned int StripUnwantedCharacters(char* szText, unsigned char cReplace)
{
	// Replace any unwanted character with a space
	unsigned int uiReplaced = 0;
	char*        szTemp = szText;
	while (*szTemp != 0)
	{
		if (!IsWantedCharacter(*szTemp))
		{
			*szTemp = cReplace;
			++uiReplaced;
		}

		++szTemp;
	}

	// Return how many characters we replaced
	return uiReplaced;
}

unsigned int StripControlCodes(char* szText, unsigned char cReplace)
{
	// Replace any unwanted character with a space
	unsigned int uiReplaced = 0;
	char*        szTemp = szText;
	while (*szTemp != 0)
	{
		if (IsControlCode(*szTemp))
		{
			*szTemp = cReplace;
			++uiReplaced;
		}

		++szTemp;
	}

	// Return how many characters we replaced
	return uiReplaced;
}

bool IsWantedCharacter(unsigned char c)
{
	// 32..126 are visible characters
	return c >= 32 && c <= 126;
}

bool IsControlCode(unsigned char c)
{
	return c < 32;
}

bool IsValidFilePath(const char* szDir)
{
	if (szDir == NULL)
		return false;

	unsigned int  uiLen = strlen(szDir);
	unsigned char c, c_d;

	// iterate through the char array
	for (unsigned int i = 0; i < uiLen; i++)
	{
		c = szDir[i];                                          // current character
		c_d = (i < (uiLen - 1)) ? szDir[i + 1] : 0;            // one character ahead, if any
		if (!IsWantedCharacter(c) || c == ':' || (c == '.' && c_d == '.') || (c == '\\' && c_d == '\\'))
			return false;
	}
	return true;
}

void ReplaceOccurrencesInString(std::string& s, const char* a, const char* b)
{
	int idx = 0;
	while ((idx = s.find_first_of(a, idx)) >= 0)
		s.replace(idx, 1, b);
}

void RotateVector(CVector& vecLine, const CVector& vecRotation)
{
	// Rotate it along the X axis
	// [ 1     0        0    0 ]
	// [ 0   cos a   sin a   0 ]
	// [ 0  -sin a   cos a   0 ]

	float fLineY = vecLine.fY;
	vecLine.fY = cos(vecRotation.fX) * fLineY + sin(vecRotation.fX) * vecLine.fZ;
	vecLine.fZ = -sin(vecRotation.fX) * fLineY + cos(vecRotation.fX) * vecLine.fZ;

	// Rotate it along the Y axis
	// [ cos a   0   -sin a   0 ]
	// [   0     1     0      0 ]
	// [ sin a   0    cos a   0 ]

	float fLineX = vecLine.fX;
	vecLine.fX = cos(vecRotation.fY) * fLineX - sin(vecRotation.fY) * vecLine.fZ;
	vecLine.fZ = sin(vecRotation.fY) * fLineX + cos(vecRotation.fY) * vecLine.fZ;

	// Rotate it along the Z axis
	// [  cos a   sin a   0   0 ]
	// [ -sin a   cos a   0   0 ]
	// [    0       0     1   0 ]

	fLineX = vecLine.fX;
	vecLine.fX = cos(vecRotation.fZ) * fLineX + sin(vecRotation.fZ) * vecLine.fY;
	vecLine.fY = -sin(vecRotation.fZ) * fLineX + cos(vecRotation.fZ) * vecLine.fY;
}

void AttachedMatrix(const CMatrix& matrix, CMatrix& returnMatrix, const CVector& vecPosition, const CVector& vecRotation)
{
	returnMatrix = CMatrix(vecPosition, vecRotation) * matrix;
}

void LongToDottedIP(unsigned long ulIP, char* szDottedIP)
{
	in_addr in;
	in.s_addr = ulIP;
	char* szTemp = inet_ntoa(in);
	if (szTemp)
	{
		strncpy(szDottedIP, szTemp, 22);
	}
	else
	{
		szDottedIP[0] = 0;
	}
}

float GetRandomFloat(void)
{
	return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);
}

double GetRandomDouble(void)
{
	return static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1.0);
}

unsigned int GetRandom(unsigned int uiLow, unsigned int uiHigh)
{
	double dLow = static_cast<double>(uiLow);
	double dHigh = static_cast<double>(uiHigh);

	return static_cast<unsigned int>(floor((dHigh - dLow + 1.0) * GetRandomDouble())) + uiLow;
}

SString GetDataUnit(unsigned long long ullInput)
{
	// Convert it to a float
	float fInput = static_cast<float>(ullInput);

	// Bytes per sec?
	if (fInput < 1024)
	{
		return SString("%u B", (uint)ullInput);
	}

	// Kilobytes per sec?
	fInput /= 1024;
	if (fInput < 1024)
	{
		return SString("%.2f kB", fInput);
	}

	// Megabytes per sec?
	fInput /= 1024;
	if (fInput < 1024)
	{
		return SString("%.2f MB", fInput);
	}

	// Gigabytes per sec?
	fInput /= 1024;
	if (fInput < 1024)
	{
		return SString("%.2f GB", fInput);
	}

	// Terrabytes per sec?
	fInput /= 1024;
	if (fInput < 1024)
	{
		return SString("%.2f TB", fInput);
	}

	// Unknown
	SString strUnknown = "X";
	return strUnknown;
}

#ifdef MTA_DEBUG
HMODULE RemoteLoadLibrary(HANDLE hProcess, const char* szLibPath)
{
	/* Called correctly? */
	if (szLibPath == NULL)
	{
		return 0;
	}

	/* Allocate memory in the remote process for the library path */
	HANDLE  hThread = 0;
	void*   pLibPathRemote = NULL;
	HMODULE hKernel32 = GetModuleHandle("Kernel32");
	pLibPathRemote = VirtualAllocEx(hProcess, NULL, strlen(szLibPath) + 1, MEM_COMMIT, PAGE_READWRITE);

	if (pLibPathRemote == NULL)
	{
		DWORD dwError = GetLastError();
		return 0;
	}

	/* Make sure pLibPathRemote is always freed */
	__try
	{
		/* Write the DLL library path to the remote allocation */
		DWORD byteswritten = 0;
		WriteProcessMemory(hProcess, pLibPathRemote, (void*)szLibPath, strlen(szLibPath) + 1, &byteswritten);

		if (byteswritten != strlen(szLibPath) + 1)
		{
			return 0;
		}

		/* Start a remote thread executing LoadLibraryA exported from Kernel32. Passing the
		   remotly allocated path buffer as an argument to that thread (and also to LoadLibraryA)
		   will make the remote process load the DLL into it's userspace (giving the DLL full
		   access to the game executable).*/
		hThread =
			CreateRemoteThread(hProcess, NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(hKernel32, "LoadLibraryA")), pLibPathRemote, 0, NULL);

		if (hThread == 0)
		{
			return 0;
		}
	}
	__finally
	{
		VirtualFreeEx(hProcess, pLibPathRemote, strlen(szLibPath) + 1, MEM_RELEASE);
	}

	/*  We wait for the created remote thread to finish executing. When it's done, the DLL
		is loaded into the game's userspace, and we can destroy the thread-handle. We wait
		5 seconds which is way longer than this should take to prevent this application
		from deadlocking if something goes really wrong allowing us to kill the injected
		game executable and avoid user inconvenience.*/
	WaitForSingleObject(hThread, INFINITE);

	/* Get the handle of the remotely loaded DLL module */
	DWORD hLibModule = 0;
	GetExitCodeThread(hProcess, &hLibModule);

	// Wait for the LoadLibrary thread to finish
	WaitForSingleObject(hThread, INFINITE);

	/* Clean up the resources we used to inject the DLL */
	VirtualFreeEx(hProcess, pLibPathRemote, strlen(szLibPath) + 1, MEM_RELEASE);

	/* Success */
	return (HINSTANCE)(1);
}

#endif

unsigned int HexToInt(const char* szHex)
{
	unsigned int value = 0;

	if (szHex[0] == '0' && (szHex[0] == 'x' || szHex[0] == 'X'))
	{
		szHex += 2;
	}

	while (*szHex != 0)
	{
		char c = *szHex++;

		value <<= 4;

		if (c >= 'A' && c <= 'F')
		{
			value += c - 'A' + 10;
		}
		else if (c >= 'a' && c <= 'f')
		{
			value += c - 'a' + 10;
		}
		else
		{
			value += c - '0';
		}
	}

	return value;
}

bool XMLColorToInt(const char* szColor, unsigned long& ulColor)
{
	const char validHexChars[] = "0123456789ABCDEFabcdef";

	unsigned int uiLength = strlen(szColor);
	// Make sure it starts with #
	if (szColor[0] == '#')
	{
		// #RGB #RGBA #RRGGBB #RRGGBBAA
		if (uiLength >= 4 && szColor[4] == 0)
		{
			// Make a RRGGBBAA string
			unsigned char szTemp[12];
			szTemp[0] = 'F';
			szTemp[1] = 'F';
			szTemp[2] = szColor[3];
			szTemp[3] = szColor[3];
			szTemp[4] = szColor[2];
			szTemp[5] = szColor[2];
			szTemp[6] = szColor[1];
			szTemp[7] = szColor[1];
			szTemp[8] = 0;

			// Make sure it only contains 0-9 and A-F
			if (strspn((const char*)szTemp, validHexChars) == 8)
			{
				ulColor = HexToInt((const char*)szTemp);
				return true;
			}
		}
		else if (uiLength >= 5 && szColor[5] == 0)
		{
			// Make a RRGGBBAA string
			unsigned char szTemp[12];
			szTemp[0] = szColor[4];
			szTemp[1] = szColor[4];
			szTemp[2] = szColor[3];
			szTemp[3] = szColor[3];
			szTemp[4] = szColor[2];
			szTemp[5] = szColor[2];
			szTemp[6] = szColor[1];
			szTemp[7] = szColor[1];
			szTemp[8] = 0;

			// Make sure it only contains 0-9 and A-F
			if (strspn((const char*)szTemp, validHexChars) == 8)
			{
				ulColor = HexToInt((const char*)szTemp);
				return true;
			}
		}
		else if (uiLength >= 7 && szColor[7] == 0)
		{
			// Make a RRGGBBAA string
			unsigned char szTemp[12];
			szTemp[0] = 'F';
			szTemp[1] = 'F';
			szTemp[2] = szColor[5];
			szTemp[3] = szColor[6];
			szTemp[4] = szColor[3];
			szTemp[5] = szColor[4];
			szTemp[6] = szColor[1];
			szTemp[7] = szColor[2];
			szTemp[8] = 0;

			// Make sure it only contains 0-9 and A-F
			if (strspn((const char*)szTemp, validHexChars) == 8)
			{
				ulColor = HexToInt((const char*)szTemp);
				return true;
			}
		}
		else if (uiLength >= 9 && szColor[9] == 0)
		{
			// Copy the string without the pre-#
			unsigned char szTemp[12];
			szTemp[0] = szColor[7];
			szTemp[1] = szColor[8];
			szTemp[2] = szColor[5];
			szTemp[3] = szColor[6];
			szTemp[4] = szColor[3];
			szTemp[5] = szColor[4];
			szTemp[6] = szColor[1];
			szTemp[7] = szColor[2];
			szTemp[8] = 0;

			// Make sure it only contains 0-9 and A-F
			if (strspn((const char*)szTemp, validHexChars) == 8)
			{
				ulColor = HexToInt((const char*)szTemp);
				return true;
			}
		}
	}

	return false;
}

bool XMLColorToInt(const char* szColor, unsigned char& ucRed, unsigned char& ucGreen, unsigned char& ucBlue, unsigned char& ucAlpha)
{
	// Convert it to an integer first
	unsigned long ulColor;
	if (!XMLColorToInt(szColor, ulColor))
	{
		return false;
	}

	// Convert it to red, green, blue and alpha
	ucRed = static_cast<unsigned char>(ulColor);
	ucGreen = static_cast<unsigned char>(ulColor >> 8);
	ucBlue = static_cast<unsigned char>(ulColor >> 16);
	ucAlpha = static_cast<unsigned char>(ulColor >> 24);
	return true;
}

// RX(theta)
// | 1              0               0       |
// | 0              c(theta)    -s(theta)   |
// | 0              s(theta)    c(theta)    |

// RY(theta)
// | c(theta)       0               s(theta)    |
// | 0              1               0           |
// | -s(theta)  0               c(theta)        |

// RZ(theta)
// | c(theta)       -s(theta)   0               |
// | s(theta)       c(theta)    0               |
// | 0              0               1           |

// ZXY = RZ(z).RX(x).RY(y)
// | c(y)*c(z)-s(x)*s(y)*s(z)       -c(x)*s(z)                          s(x)*c(y)*s(z)+s(y)*c(z)        |
// | c(y)*s(z)+s(x)*s(y)*c(z)       c(x)*c(z)                               s(y)*s(z)-s(x)*c(y)*c(z)    |
// | -c(x)*s(y)                             s(x)                                        c(x)*c(y)       |

// ZYX = RZ(z).RY(y).RX(x)
// | c(y)*c(z)                              s(x)*s(y)*c(z)-c(x)*s(z)        s(x)*s(z)+c(x)*s(y)*c(z)    |
// | c(y)*s(z)                              s(x)*s(y)*s(z)+c(x)*c(z)        c(x)*s(y)*s(z)-s(x)*c(z)    |
// | -s(y)                                      s(x)*c(y)                               c(x)*c(y)       |

CVector euler_ZXY_to_ZYX(const CVector& a_vZXY)
{
	CVector vZXY(a_vZXY);
	ConvertDegreesToRadiansNoWrap(vZXY);            // NoWrap for this conversion since it's used for cos/sin only

	float cx = cos(vZXY.fX);
	float sx = sin(vZXY.fX);
	float cy = cos(vZXY.fY);
	float sy = sin(vZXY.fY);
	float cz = cos(vZXY.fZ);
	float sz = sin(vZXY.fZ);

	CVector vZYX;

	// ZYX (unknown)     => A = s(x)*c(y)    /   c(x)*c(y)   = t(x)
	// ZXY (known)       => A = s(x)     /   c(x)*c(y)
	vZYX.fX = atan2(sx, cx * cy);

	// ZYX (unknown)     => B = c(y)*s(z)                    /   c(y)*c(z)                   = t(z)
	// ZXY (known)       => B = c(y)*s(z)+s(x)*s(y)*c(z)     /   c(y)*c(z)-s(x)*s(y)*s(z)
	vZYX.fZ = atan2(cy * sz + sx * sy * cz, cy * cz - sx * sy * sz);

	// ZYX (unknown)     => C = -s(y)
	// ZXY (known)       => C = -c(x)*s(y)
	// Isn't asin not as good as atan2 ? solution tried with atan2 doesn't work that well though
	vZYX.fY = asin(cx * sy);

	ConvertRadiansToDegrees(vZYX);

	return vZYX;
}

CVector euler_ZYX_to_ZXY(const CVector& a_vZYX)
{
	CVector vZYX(a_vZYX);
	ConvertDegreesToRadiansNoWrap(vZYX);            // NoWrap for this conversion since it's used for cos/sin only

	float cx = cos(vZYX.fX);
	float sx = sin(vZYX.fX);
	float cy = cos(vZYX.fY);
	float sy = sin(vZYX.fY);
	float cz = cos(vZYX.fZ);
	float sz = sin(vZYX.fZ);

	CVector vZXY;

	// ZXY (unknown)     => A = -c(x)*s(z)               /   c(x)*c(z)                   => t(z) = -A
	// ZYX (known)       => A = s(x)*s(y)*c(z)-c(x)*s(z) /   s(x)*s(y)*s(z)+c(x)*c(z)
	vZXY.fZ = atan2(-(sx * sy * cz - cx * sz), sx * sy * sz + cx * cz);

	// ZXY (unknown)     => B = -c(x)*s(y)   /       c(x)*c(y) => t(y) = -B
	// ZYX (known)       => B =  -s(y)       /       c(x)*c(y)
	vZXY.fY = atan2(sy, cx * cy);

	// ZXY (unknown)     => C = s(x)
	// ZYX (known)       => C =  s(x)*c(y)
	// Isn't asin not as good as atan2 ? solution tried with atan2 doesn't work that well though
	vZXY.fX = asin(sx * cy);

	ConvertRadiansToDegrees(vZXY);
	return vZXY;
}

CVector ConvertEulerRotationOrder(const CVector& a_vRotation, eEulerRotationOrder a_eSrcOrder, eEulerRotationOrder a_eDstOrder)
{
	if (a_eSrcOrder == a_eDstOrder || a_eSrcOrder == EULER_DEFAULT || a_eDstOrder == EULER_DEFAULT)
	{
		return a_vRotation;
	}

	if (a_eSrcOrder == EULER_ZXY && a_eDstOrder == EULER_ZYX)
	{
		return euler_ZXY_to_ZYX(a_vRotation);
	}
	else if (a_eSrcOrder == EULER_ZYX && a_eDstOrder == EULER_ZXY)
	{
		return euler_ZYX_to_ZXY(a_vRotation);
	}
	else if (a_eSrcOrder == EULER_MINUS_ZYX)
	{
		CVector vZYX;
		vZYX.fX = -a_vRotation.fX;
		vZYX.fY = -a_vRotation.fY;
		vZYX.fZ = -a_vRotation.fZ;
		return ConvertEulerRotationOrder(vZYX, EULER_ZYX, a_eDstOrder);
	}
	else if (a_eDstOrder == EULER_MINUS_ZYX)
	{
		CVector vZYX = ConvertEulerRotationOrder(a_vRotation, a_eSrcOrder, EULER_ZYX);
		vZYX.fX = -vZYX.fX;
		vZYX.fY = -vZYX.fY;
		vZYX.fZ = -vZYX.fZ;
		return vZYX;
	}
	else
	{
		return a_vRotation;
	}
}
