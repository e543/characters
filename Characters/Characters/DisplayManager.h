#pragma once
#include "Display.h"
#include "CharacterFactory.h"
#include "Character.h"
#include <vector>
class DisplayManager
{
	Display* display;
	CharacterFactory* factoryCh;

	std::string text;
	size_t text_size = 0;
	int start_x, start_y;
	std::vector<std::pair<Vector2, Character*>> chs;
	std::unordered_map<char, Character> unique;

	bool tryText();
	bool fillChs();
public:
	DisplayManager(Display* _display, LONG _start_x, LONG _start_y) :
		display(_display), 
		start_x(_start_x), 
		start_y(_start_y),
		factoryCh(new CharacterFactory())
	{
	}
	~DisplayManager() {
		delete display, factoryCh;
	}
	void changeDisplay(Display* _display);
	bool renderChs(HDC hDC, std::string text);
	static void DrawBitmap(HDC hDC, LONG x, LONG y, HBITMAP hBitmap);
};

inline bool DisplayManager::tryText() {
	for (auto ch : text) {
		if (!factoryCh->CreateCharacter(ch))
			return false;
	}
}

void DisplayManager::changeDisplay(Display* _display) {
	delete display;
	display = _display;
}

bool DisplayManager::fillChs() {
	auto va  = display->getVa(text_size, start_x, start_y);
	if (va.size() == text_size) {
		for (size_t i = 0; i < text_size; ++i) {
			chs.push_back({ va[i], &unique.find(text[i])->second });
		}
		return true;
	}
	return false;
}


bool DisplayManager::renderChs(HDC hDC, std::string _text) {
	text = _text;
	text_size = text.size();
	if (tryText()) {
		unique = factoryCh->getUniqueChs();
		fillChs();
		for (auto m : chs) {
			DrawBitmap(hDC, m.first.x, m.first.y, m.second->bmp);
		}
		chs.clear();
		unique.clear();
		return true;
	}
	return false;
}


void DisplayManager::DrawBitmap(HDC hDC, LONG x, LONG y, HBITMAP hBitmap)
{
    HBITMAP hbm, hOldbm;
    HDC hMemDC;
    BITMAP bm;
    POINT ptSize, ptOrg;
	size_t s = sizeof(hbm);
    hMemDC = CreateCompatibleDC(hDC);
    hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);
    if (hOldbm)
    {
        SetMapMode(hMemDC, GetMapMode(hDC));
        GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

        ptSize.x = bm.bmWidth;  
        ptSize.y = bm.bmHeight; 

        DPtoLP(hDC, &ptSize, 1);

        ptOrg.x = 0;
        ptOrg.y = 0;

        DPtoLP(hMemDC, &ptOrg, 1);
        BitBlt(hDC, x, y, ptSize.x, ptSize.y,
            hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);
        SelectObject(hMemDC, hOldbm);
    }
	DeleteObject(hMemDC);
}

