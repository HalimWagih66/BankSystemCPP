#pragma once
#include <memory>
#include "../../data/models/user_model.h"

class CurrentSession {
public:
    static std::unique_ptr<UserModel> UserLogged;

    CurrentSession() = delete;
};
