#include "view_model_provider.h"
#include "../data/data_source/clients/implementations/txt/client_txt_data_source.h"
#include "../data/data_source/auth/implementations/txt/auth_txt_data_source.h"

AuthViewModel* ViewModelProvider::getAuthViewModel()
{
	return AuthViewModel::getInstance(AuthTxtDataSource::getInstance());
}

ATMViewModel* ViewModelProvider::getATMViewMoel()
{
	return ATMViewModel::getInstance(ClientTxtDataSource::getInstance());
}
