#pragma once
#include "SDL.h"

class KeyCode
{
public:
	const static KeyCode* const  leftMouse;
	const static KeyCode* const middleMouse;
	const static KeyCode* const rightMouse;
	const static KeyCode* const key0;
	const static KeyCode* const key1;
	const static KeyCode* const key2;
	const static KeyCode* const key3;
	const static KeyCode* const key4;
	const static KeyCode* const key5;
	const static KeyCode* const key6;
	const static KeyCode* const key7;
	const static KeyCode* const key8;
	const static KeyCode* const key9;
	const static KeyCode* const A;
	const static KeyCode* const B;
	const static KeyCode* const C;
	const static KeyCode* const D;
	const static KeyCode* const E;
	const static KeyCode* const F;
	const static KeyCode* const G;
	const static KeyCode* const H;
	const static KeyCode* const I;
	const static KeyCode* const J;
	const static KeyCode* const K;
	const static KeyCode* const L;
	const static KeyCode* const M;
	const static KeyCode* const N;
	const static KeyCode* const O;
	const static KeyCode* const P;
	const static KeyCode* const Q;
	const static KeyCode* const R;
	const static KeyCode* const S;
	const static KeyCode* const T;
	const static KeyCode* const U;
	const static KeyCode* const V;
	const static KeyCode* const W;
	const static KeyCode* const X;
	const static KeyCode* const Y;
	const static KeyCode* const Z;

	int getCode() const; 

private:
	KeyCode();
	KeyCode(int code);
	static KeyCode* instance;
	int code;
};

