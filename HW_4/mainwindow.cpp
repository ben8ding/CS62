#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "network.h"
#include "user.h"
#include "post.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , network_(Network())
{
    ui->setupUi(this);

    //setup network
    network_.readUsers("cycle5.txt");
    //network_.readPosts("posts.txt");

    loggedInUser_ = nullptr;
    currentUser_ = nullptr;

    ui->profileFriendList->setColumnCount(1);
    //dynamic resize friendlist to name length
    ui->profileFriendList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->profileFriendSuggest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->profileFriendSuggest->setColumnCount(1);


    toggleProfile(0);

    //connect(ui->debugButton, &QPushButton::clicked, this, &MainWindow::loginUser);
    connect(ui->loginButton,
        &QPushButton::clicked,
        this,
        &MainWindow::loginUser);
    connect(ui->profileFriendList,
            &QTableWidget::cellClicked,
            this,
            &MainWindow::setUserFromTable);
}

void MainWindow::loginUser(){

    std::string name = ui->loginBox->toPlainText().toStdString();

    if(network_.getId(name) != -1){
        loggedInUser_ = network_.getUser(network_.getId(name));

        ui->debugLabel1->setText(QString::fromStdString(loggedInUser_->getName()));
        ui->debugLabel2->setText(QString::fromStdString(std::to_string(loggedInUser_->getId())));

        currentUser_ = network_.getUser(network_.getId(name));

        toggleLogin(0);
        updateCurrentProfile();
        toggleProfile(1);
    }
    else{
        ui->loginLabel->setText("Invalid Name.");
    }
}

//todo: set current user as the selected user and update the profile
void MainWindow::setUserFromTable(int row, int column){
    //QTableWidgetItem *tempFriend = ui->profileFriendList->item(row, column);
    //tempFriend->text();
    ui->debugLabel1->setText(ui->profileFriendList->item(row, column)->text());
}

void MainWindow::toggleLogin(int tog){
    ui->loginButton->setVisible(tog);
    ui->loginBox->setVisible(tog);
    ui->loginLabel->setVisible(tog);
}

void MainWindow::toggleProfile(int tog){
    ui->profileTitle->setVisible(tog);
    ui->profileFriendListLabel->setVisible(tog);
    ui->profileFriendList->setVisible(tog);
    ui->profileFriendSuggest->setVisible(tog);
    ui->profileFriendSuggestLabel->setVisible(tog);
}

void MainWindow::updateCurrentProfile(){
    //friendlist updater
    int numFriends = currentUser_->getFriends().size();
    ui->profileFriendList->setRowCount(numFriends);
    int iterator = 0;
    for(int friends : currentUser_->getFriends()){
        QTableWidgetItem *tempFriend = new QTableWidgetItem(QString::fromStdString(network_.getUser(friends)->getName()));
        ui->profileFriendList->setItem(iterator, 0, tempFriend);
        iterator++;
    }
    //friend suggestions updater
    int score;
    std::vector<int> friendSuggestions = network_.suggestFriends(currentUser_->getId(), score);
    ui->profileFriendSuggest->setRowCount(friendSuggestions.size());

    for(int i = 0; i < friendSuggestions.size(); i++){
        QTableWidgetItem *tempFriend = new QTableWidgetItem(QString::fromStdString(network_.getUser(friendSuggestions[i])->getName()));
        ui->profileFriendSuggest->setItem(i, 0, tempFriend);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
