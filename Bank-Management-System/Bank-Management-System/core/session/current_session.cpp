#include "current_session.h"

std::unique_ptr<UserModel> CurrentSession::UserLogged = std::make_unique<UserModel>("","","","","","",0);
