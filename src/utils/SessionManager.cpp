#include "../include/utils/SessionManager.h"

void SessionManager::clear() {
    currentUser = User();
    loggedIn = false;
    current_otp.clear();
}
 User SessionManager::getCurrentUser() {
    return currentUser;
 }
 bool SessionManager::isLoggedIn() {
    return loggedIn;
 }
bool SessionManager::isAdminUser() {
    return currentUser.getIsAdmin();
}
void SessionManager::setCurrentUser(const User& user) {
    currentUser = user;
}
void SessionManager::setLoggedIn(bool status) {
    loggedIn = status;
}
void SessionManager::setCurrentOTP(const std::string& otp) {
    current_otp = otp;
}
std::string SessionManager::getCurrentOTP() {
    return current_otp;
}