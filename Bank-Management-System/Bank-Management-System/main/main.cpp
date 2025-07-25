#include <iostream>
#include "../Presentation/cls_main_screen.h"
#include "../Presentation/auth/screens/login_screen.h"
#include "../di/view_model_provider/view_model_provider.h"
using namespace std;

int main() {
    // Counter for failed login attempts
    short numberOfAttemps = 0;

    // Allow up to 3 login attempts
    while (numberOfAttemps != 3)
    {
        // Show login screen and check credentials
        if (LoginScreen::ShowLogin(ViewModelProvider::getAuthViewModel()) == ResultStatus::Success) {
            // If login is successful, show the main menu
            clsMainScreen::ShowMainMenue();
        }
        else
        {
            // If login fails, increment the attempt counter
            numberOfAttemps++;
        }
    }

    // If the user failed to login 3 times, exit with error
    if (numberOfAttemps == 3) {
        cout << "You have entered wrong credentials 3 times. Exiting..." << endl;
        return 1;
    }

    return 0;
}
