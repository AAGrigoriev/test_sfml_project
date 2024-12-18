#include "string.hpp"

namespace utility {

std::string_view to_string_view(const sf::Keyboard::Key key) {
#define GET_KEY_NAME(KEY) \
  case sf::Keyboard::KEY:          \
    return #KEY;

  switch (key) {
    GET_KEY_NAME(Unknown)
    GET_KEY_NAME(A)
    GET_KEY_NAME(B)
    GET_KEY_NAME(C)
    GET_KEY_NAME(D)
    GET_KEY_NAME(E)
    GET_KEY_NAME(F)
    GET_KEY_NAME(G)
    GET_KEY_NAME(H)
    GET_KEY_NAME(I)
    GET_KEY_NAME(J)
    GET_KEY_NAME(K)
    GET_KEY_NAME(L)
    GET_KEY_NAME(M)
    GET_KEY_NAME(N)
    GET_KEY_NAME(O)
    GET_KEY_NAME(P)
    GET_KEY_NAME(Q)
    GET_KEY_NAME(R)
    GET_KEY_NAME(S)
    GET_KEY_NAME(T)
    GET_KEY_NAME(U)
    GET_KEY_NAME(V)
    GET_KEY_NAME(W)
    GET_KEY_NAME(X)
    GET_KEY_NAME(Y)
    GET_KEY_NAME(Z)
    GET_KEY_NAME(Num0)
    GET_KEY_NAME(Num1)
    GET_KEY_NAME(Num2)
    GET_KEY_NAME(Num3)
    GET_KEY_NAME(Num4)
    GET_KEY_NAME(Num5)
    GET_KEY_NAME(Num6)
    GET_KEY_NAME(Num7)
    GET_KEY_NAME(Num8)
    GET_KEY_NAME(Num9)
    GET_KEY_NAME(Escape)
    GET_KEY_NAME(LControl)
    GET_KEY_NAME(LShift)
    GET_KEY_NAME(LAlt)
    GET_KEY_NAME(LSystem)
    GET_KEY_NAME(RControl)
    GET_KEY_NAME(RShift)
    GET_KEY_NAME(RAlt)
    GET_KEY_NAME(RSystem)
    GET_KEY_NAME(Menu)
    GET_KEY_NAME(LBracket)
    GET_KEY_NAME(RBracket)
    GET_KEY_NAME(SemiColon)
    GET_KEY_NAME(Comma)
    GET_KEY_NAME(Period)
    GET_KEY_NAME(Quote)
    GET_KEY_NAME(Slash)
    GET_KEY_NAME(BackSlash)
    GET_KEY_NAME(Tilde)
    GET_KEY_NAME(Equal)
    GET_KEY_NAME(Dash)
    GET_KEY_NAME(Space)
    GET_KEY_NAME(Return)
    GET_KEY_NAME(BackSpace)
    GET_KEY_NAME(Tab)
    GET_KEY_NAME(PageUp)
    GET_KEY_NAME(PageDown)
    GET_KEY_NAME(End)
    GET_KEY_NAME(Home)
    GET_KEY_NAME(Insert)
    GET_KEY_NAME(Delete)
    GET_KEY_NAME(Add)
    GET_KEY_NAME(Subtract)
    GET_KEY_NAME(Multiply)
    GET_KEY_NAME(Divide)
    GET_KEY_NAME(Left)
    GET_KEY_NAME(Right)
    GET_KEY_NAME(Up)
    GET_KEY_NAME(Down)
    GET_KEY_NAME(Numpad0)
    GET_KEY_NAME(Numpad1)
    GET_KEY_NAME(Numpad2)
    GET_KEY_NAME(Numpad3)
    GET_KEY_NAME(Numpad4)
    GET_KEY_NAME(Numpad5)
    GET_KEY_NAME(Numpad6)
    GET_KEY_NAME(Numpad7)
    GET_KEY_NAME(Numpad8)
    GET_KEY_NAME(Numpad9)
    GET_KEY_NAME(F1)
    GET_KEY_NAME(F2)
    GET_KEY_NAME(F3)
    GET_KEY_NAME(F4)
    GET_KEY_NAME(F5)
    GET_KEY_NAME(F6)
    GET_KEY_NAME(F7)
    GET_KEY_NAME(F8)
    GET_KEY_NAME(F9)
    GET_KEY_NAME(F10)
    GET_KEY_NAME(F11)
    GET_KEY_NAME(F12)
    GET_KEY_NAME(F13)
    GET_KEY_NAME(F14)
    GET_KEY_NAME(F15)
    GET_KEY_NAME(Pause)
    default:
      return "";
  }

  return "";
}

}  // namespace utility
