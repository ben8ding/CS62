#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setUserFromTable(int row, int column);
    void setUserFromSuggestions(int row, int column);
    void returnToProfile();
    void addFriend();
    void addPost();
    void editBio();
    void likePost();

private:
    Ui::MainWindow *ui;
    Network network_;

    //user logged in
    User* loggedInUser_;
    //user focused on
    User* currentUser_;

    //Pre: 1 to show, 0 to hide
    //Post: Login elements are toggled to either show with 1, or hide with 0 for input
    void toggleLogin(int tog);

    //Pre: 1 to show, 0 to hide
    //Post: (Some) profile elements are toggled to either show with 1, or hide with 0 for input
    void toggleProfile(int tog);

    //Pre: The function is called (usually by a login user signal
    //Post: The current user and logged in user are set to the given name and the main profile page is
    //Todo: change this to a slot
    void loginUser();

    //Pre: Takes into account the current viewed user
    //Post: Updates the post section with the 5 most recent posts with the user's profile id
    void updatePosts();

    //Pre: Takes into account the current user and whether or not the current user is also the logged in user.
    //Post: Updates all relevant user profile data.
    void updateCurrentProfile();
};
#endif
