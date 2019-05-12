#include "KeyCode.h"

KeyCode* KeyCode::instance = nullptr;

KeyCode* KeyCode::leftMouse = new KeyCode(1);
KeyCode* KeyCode::middleMouse = new KeyCode(2);
KeyCode* KeyCode::rightMouse = new KeyCode(3);

KeyCode* KeyCode::key0 = new KeyCode(SDL_SCANCODE_0);
KeyCode* KeyCode::key1 = new KeyCode(SDL_SCANCODE_1);
KeyCode* KeyCode::key2 = new KeyCode(SDL_SCANCODE_2);
KeyCode* KeyCode::key3 = new KeyCode(SDL_SCANCODE_3);
KeyCode* KeyCode::key4 = new KeyCode(SDL_SCANCODE_4);
KeyCode* KeyCode::key5 = new KeyCode(SDL_SCANCODE_5);
KeyCode* KeyCode::key6 = new KeyCode(SDL_SCANCODE_6);
KeyCode* KeyCode::key7 = new KeyCode(SDL_SCANCODE_7);
KeyCode* KeyCode::key8 = new KeyCode(SDL_SCANCODE_8);
KeyCode* KeyCode::key9 = new KeyCode(SDL_SCANCODE_9);

KeyCode* KeyCode::A = new KeyCode(SDL_SCANCODE_A);
KeyCode* KeyCode::B = new KeyCode(SDL_SCANCODE_B);
KeyCode* KeyCode::C = new KeyCode(SDL_SCANCODE_C);
KeyCode* KeyCode::D = new KeyCode(SDL_SCANCODE_D);
KeyCode* KeyCode::E = new KeyCode(SDL_SCANCODE_E);
KeyCode* KeyCode::F = new KeyCode(SDL_SCANCODE_F);
KeyCode* KeyCode::G = new KeyCode(SDL_SCANCODE_G);
KeyCode* KeyCode::H = new KeyCode(SDL_SCANCODE_H);
KeyCode* KeyCode::I = new KeyCode(SDL_SCANCODE_I);
KeyCode* KeyCode::J = new KeyCode(SDL_SCANCODE_J);
KeyCode* KeyCode::K = new KeyCode(SDL_SCANCODE_K);
KeyCode* KeyCode::L = new KeyCode(SDL_SCANCODE_L);
KeyCode* KeyCode::M = new KeyCode(SDL_SCANCODE_M);
KeyCode* KeyCode::N = new KeyCode(SDL_SCANCODE_N);
KeyCode* KeyCode::O = new KeyCode(SDL_SCANCODE_O);
KeyCode* KeyCode::P = new KeyCode(SDL_SCANCODE_P);
KeyCode* KeyCode::Q = new KeyCode(SDL_SCANCODE_Q);
KeyCode* KeyCode::R = new KeyCode(SDL_SCANCODE_R);
KeyCode* KeyCode::S = new KeyCode(SDL_SCANCODE_S);
KeyCode* KeyCode::T = new KeyCode(SDL_SCANCODE_T);
KeyCode* KeyCode::U = new KeyCode(SDL_SCANCODE_U);
KeyCode* KeyCode::V = new KeyCode(SDL_SCANCODE_V);
KeyCode* KeyCode::W = new KeyCode(SDL_SCANCODE_W);
KeyCode* KeyCode::X = new KeyCode(SDL_SCANCODE_X);
KeyCode* KeyCode::Y = new KeyCode(SDL_SCANCODE_Y);
KeyCode* KeyCode::Z = new KeyCode(SDL_SCANCODE_Z);


int KeyCode::getCode()
{
	return this->code;
}

KeyCode* KeyCode::getInstance()
{
	if (instance == nullptr)
	{
		instance = new KeyCode();
		instance->masterControl = true;
	}
	return instance;
}

KeyCode::KeyCode()
{
}

KeyCode::KeyCode(int code)
{
	this->code = code;
}

void KeyCode::cleanUp()
{
	if (!masterControl)
		return;
	delete leftMouse; delete middleMouse; delete rightMouse;
	delete key0; delete key1; delete key2; delete key3; delete key4; delete key5; delete key6;
	delete key7; delete key8; delete key9;
	delete A; delete B; delete C; delete D; delete E; delete F; delete G; delete H; delete I;
	delete J; delete K; delete L; delete M; delete N; delete O; delete P; delete Q; delete R;
	delete S; delete T; delete U; delete V; delete W; delete X; delete Y; delete Z;
}

KeyCode::~KeyCode()
{

}
