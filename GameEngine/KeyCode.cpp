#include "KeyCode.h"

const KeyCode* const KeyCode::leftMouse = new KeyCode(1);
const KeyCode* const KeyCode::middleMouse = new KeyCode(2);
const KeyCode* const KeyCode::rightMouse = new KeyCode(3);

const KeyCode* const KeyCode::key0 = new KeyCode(SDL_SCANCODE_0);
const KeyCode* const KeyCode::key1 = new KeyCode(SDL_SCANCODE_1);
const KeyCode* const KeyCode::key2 = new KeyCode(SDL_SCANCODE_2);
const KeyCode* const KeyCode::key3 = new KeyCode(SDL_SCANCODE_3);
const KeyCode* const KeyCode::key4 = new KeyCode(SDL_SCANCODE_4);
const KeyCode* const KeyCode::key5 = new KeyCode(SDL_SCANCODE_5);
const KeyCode* const KeyCode::key6 = new KeyCode(SDL_SCANCODE_6);
const KeyCode* const KeyCode::key7 = new KeyCode(SDL_SCANCODE_7);
const KeyCode* const KeyCode::key8 = new KeyCode(SDL_SCANCODE_8);
const KeyCode* const KeyCode::key9 = new KeyCode(SDL_SCANCODE_9);

const KeyCode* const KeyCode::A = new KeyCode(SDL_SCANCODE_A);
const KeyCode* const KeyCode::B = new KeyCode(SDL_SCANCODE_B);
const KeyCode* const KeyCode::C = new KeyCode(SDL_SCANCODE_C);
const KeyCode* const KeyCode::D = new KeyCode(SDL_SCANCODE_D);
const KeyCode* const KeyCode::E = new KeyCode(SDL_SCANCODE_E);
const KeyCode* const KeyCode::F = new KeyCode(SDL_SCANCODE_F);
const KeyCode* const KeyCode::G = new KeyCode(SDL_SCANCODE_G);
const KeyCode* const KeyCode::H = new KeyCode(SDL_SCANCODE_H);
const KeyCode* const KeyCode::I = new KeyCode(SDL_SCANCODE_I);
const KeyCode* const KeyCode::J = new KeyCode(SDL_SCANCODE_J);
const KeyCode* const KeyCode::K = new KeyCode(SDL_SCANCODE_K);
const KeyCode* const KeyCode::L = new KeyCode(SDL_SCANCODE_L);
const KeyCode* const KeyCode::M = new KeyCode(SDL_SCANCODE_M);
const KeyCode* const KeyCode::N = new KeyCode(SDL_SCANCODE_N);
const KeyCode* const KeyCode::O = new KeyCode(SDL_SCANCODE_O);
const KeyCode* const KeyCode::P = new KeyCode(SDL_SCANCODE_P);
const KeyCode* const KeyCode::Q = new KeyCode(SDL_SCANCODE_Q);
const KeyCode* const KeyCode::R = new KeyCode(SDL_SCANCODE_R);
const KeyCode* const KeyCode::S = new KeyCode(SDL_SCANCODE_S);
const KeyCode* const KeyCode::T = new KeyCode(SDL_SCANCODE_T);
const KeyCode* const KeyCode::U = new KeyCode(SDL_SCANCODE_U);
const KeyCode* const KeyCode::V = new KeyCode(SDL_SCANCODE_V);
const KeyCode* const KeyCode::W = new KeyCode(SDL_SCANCODE_W);
const KeyCode* const KeyCode::X = new KeyCode(SDL_SCANCODE_X);
const KeyCode* const KeyCode::Y = new KeyCode(SDL_SCANCODE_Y);
const KeyCode* const KeyCode::Z = new KeyCode(SDL_SCANCODE_Z);


int KeyCode::getCode() const
{
	return this->code;
}

KeyCode::KeyCode()
{
}

KeyCode::KeyCode(int code)
{
	this->code = code;
}