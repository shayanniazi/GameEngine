#pragma once
#include <SDL\SDL.h>

class KeyCode
{
public:
	static KeyCode* leftMouse;
	static KeyCode* middleMouse;
	static KeyCode* rightMouse;
	static KeyCode* key0;
	static KeyCode* key1;
	static KeyCode* key2;
	static KeyCode* key3;
	static KeyCode* key4;
	static KeyCode* key5;
	static KeyCode* key6;
	static KeyCode* key7;
	static KeyCode* key8;
	static KeyCode* key9;
	static KeyCode* A;
	static KeyCode* B;
	static KeyCode* C;
	static KeyCode* D;
	static KeyCode* E;
	static KeyCode* F;
	static KeyCode* G;
	static KeyCode* H;
	static KeyCode* I;
	static KeyCode* J;
	static KeyCode* K;
	static KeyCode* L;
	static KeyCode* M;
	static KeyCode* N;
	static KeyCode* O;
	static KeyCode* P;
	static KeyCode* Q;
	static KeyCode* R;
	static KeyCode* S;
	static KeyCode* T;
	static KeyCode* U;
	static KeyCode* V;
	static KeyCode* W;
	static KeyCode* X;
	static KeyCode* Y;
	static KeyCode* Z;

	static KeyCode* getInstance();
	void cleanUp(); bool masterControl = false;
	~KeyCode();
	int getCode();

private:
	KeyCode();
	KeyCode(int code);
	static KeyCode* instance;
	int code;
};

