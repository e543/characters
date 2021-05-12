#pragma once

#define cptrwc const wchar_t*

#define ch_height 30
#define ch_width 25

struct Sprites {
	static cptrwc space;
	static cptrwc a;
	static cptrwc b;
	static cptrwc c;
	static cptrwc d;
	static cptrwc e;
	static cptrwc f;
	static cptrwc g;
	static cptrwc h;
	static cptrwc i;
	static cptrwc j;
	static cptrwc k;
	static cptrwc l;
	static cptrwc m;
	static cptrwc n;
	static cptrwc o;
	static cptrwc p;
	static cptrwc q;
	static cptrwc r;
	static cptrwc s;
	static cptrwc t;
	static cptrwc u;
	static cptrwc v;
	static cptrwc w;
	static cptrwc x;
	static cptrwc y;
	static cptrwc z;
	static cptrwc exclamation;
	static cptrwc question;
	static cptrwc point;
	static cptrwc comma;
};

cptrwc Sprites::space = L"res\\space.bmp";
cptrwc Sprites::a = L"res\\a.bmp";
cptrwc Sprites::b = L"res\\b.bmp";
cptrwc Sprites::c = L"res\\c.bmp";
cptrwc Sprites::d = L"res\\d.bmp";
cptrwc Sprites::e = L"res\\e.bmp";
cptrwc Sprites::f = L"res\\f.bmp";
cptrwc Sprites::g = L"res\\g.bmp";
cptrwc Sprites::h = L"res\\h.bmp";
cptrwc Sprites::i = L"res\\i.bmp";
cptrwc Sprites::j = L"res\\j.bmp";
cptrwc Sprites::k = L"res\\k.bmp";
cptrwc Sprites::l = L"res\\l.bmp";
cptrwc Sprites::m = L"res\\m.bmp";
cptrwc Sprites::n = L"res\\n.bmp";
cptrwc Sprites::o = L"res\\o.bmp";
cptrwc Sprites::p = L"res\\p.bmp";
cptrwc Sprites::q = L"res\\q.bmp";
cptrwc Sprites::r = L"res\\r.bmp";
cptrwc Sprites::s = L"res\\s.bmp";
cptrwc Sprites::t = L"res\\t.bmp";
cptrwc Sprites::u = L"res\\u.bmp";
cptrwc Sprites::v = L"res\\v.bmp";
cptrwc Sprites::w = L"res\\w.bmp";
cptrwc Sprites::x = L"res\\x.bmp";
cptrwc Sprites::y = L"res\\y.bmp";
cptrwc Sprites::z = L"res\\z.bmp";
cptrwc Sprites::exclamation = L"res\\exclamation.bmp";
cptrwc Sprites::question = L"res\\question.bmp";
cptrwc Sprites::point = L"res\\point.bmp";
cptrwc Sprites::comma = L"res\\comma.bmp";

struct Sprite {
	cptrwc path;
	Sprite(cptrwc _path) :path(_path) {};
	~Sprite() {
		delete path;
	}
};



struct Character
{
	HBITMAP bmp;

	Character(Sprite* _spr) {
		bmp = (HBITMAP)LoadImage(NULL, (LPCWSTR)_spr->path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	};
};
