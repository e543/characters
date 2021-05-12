#pragma once
#include "Character.h"
#include <unordered_map>

class CharacterFactory
{
	Sprites sprites;
	Sprite* cur_sprite;
	std::unordered_map<char,Character> unique_chs;
	bool findSprite(char ch);
	void setSprite(cptrwc selected_ch);
public:
	CharacterFactory() {
	}
	~CharacterFactory() {
		delete cur_sprite;
	}

	bool CreateCharacter(char ch);
	std::unordered_map<char, Character> getUniqueChs();
};

std::unordered_map<char, Character> CharacterFactory::getUniqueChs() {
	return unique_chs;
}

bool CharacterFactory::CreateCharacter(char ch) {
    if (unique_chs.find(ch) == unique_chs.end())
    {
		if (findSprite(ch)) {
			unique_chs.insert(std::make_pair(ch, Character(cur_sprite)));
			return true;
		}
		return false;
    }
	return true;
}


inline void CharacterFactory::setSprite(cptrwc wch) {
	cur_sprite = new Sprite(wch);
}

bool CharacterFactory::findSprite(char ch) {
	switch (ch)
	{
	default:
		return false;
		break;
	case ' ':
		setSprite(sprites.space);
		break;
	case 'A': case 'a':
		setSprite(sprites.a);
		break;
	case 'B': case 'b':
		setSprite(sprites.b);
		break;
	case 'C': case 'c':
		setSprite(sprites.c);
		break;
	case 'D': case 'd':
		setSprite(sprites.d);
		break;		
	case 'E': case 'e':
		setSprite(sprites.e);
		break;
	case 'F': case 'f':
		setSprite(sprites.f);
		break;
	case 'G': case 'g':
		setSprite(sprites.g);
		break;
	case 'H': case 'h':
		setSprite(sprites.h);
		break;
	case 'I': case 'i':
		setSprite(sprites.i);
		break;
	case 'J': case 'j':
		setSprite(sprites.j);
		break;
	case 'K': case 'k':
		setSprite(sprites.k);
		break;
	case 'L': case 'l':
		setSprite(sprites.l);
		break;
	case 'M': case 'm':
		setSprite(sprites.m);
		break;
	case 'N': case 'n':
		setSprite(sprites.n);
		break;
	case 'O': case 'o':
		setSprite(sprites.o);
		break;
	case 'P': case 'p':
		setSprite(sprites.p);
		break;
	case 'Q': case 'q':
		setSprite(sprites.q);
		break;
	case 'R': case 'r':
		setSprite(sprites.r);
		break;
	case 'S': case 's':
		setSprite(sprites.s);
		break;
	case 'T': case 't':
		setSprite(sprites.t);
		break;
	case 'U': case 'u':
		setSprite(sprites.u);
		break;
	case 'V': case 'v':
		setSprite(sprites.v);
		break;
	case 'W': case 'w':
		setSprite(sprites.w);
		break;
	case 'X': case 'x':
		setSprite(sprites.x);
		break;
	case 'Y': case 'y':
		setSprite(sprites.y);
		break;
	case 'Z': case 'z':
		setSprite(sprites.z);
		break;
	case '.':
		setSprite(sprites.point);
		break;
	case ',':
		setSprite(sprites.comma);
		break;
	case '!': 
		setSprite(sprites.exclamation);
		break;
	case '?': 
		setSprite(sprites.question);
		break;
	}
	return true;
}