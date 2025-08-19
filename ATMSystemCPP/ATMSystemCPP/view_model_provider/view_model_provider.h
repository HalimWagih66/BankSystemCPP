#pragma once
#include "../presentation/auth/view_model/auth_view_model.h"
#include "../presentation/atm/view_model/atm_view_model.h"
class ViewModelProvider {
public:
	static AuthViewModel* getAuthViewModel();

	static ATMViewModel* getATMViewMoel();
};