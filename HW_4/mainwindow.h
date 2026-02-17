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

private:
    Ui::MainWindow *ui;
    Network network_;

    //user logged in
    User* loggedInUser_;
    //user focused on
    User* currentUser_;

    //pre: 1 to show, 0 to hide
    //post: login elements are toggled to either show with 1, or hide with 0 for input
    void toggleLogin(int tog);

    void toggleProfile(int tog);

    void loginUser();

    void updateCurrentProfile();
};
#endif // MAINWINDOW_H
