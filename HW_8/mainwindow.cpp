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

    //Setup network
    network_.readUsers("users.txt");
    network_.readPosts("posts.txt");

    loggedInUser_ = nullptr;
    currentUser_ = nullptr;

    //Setup profile friends list, dynamic resize friendlist to name length
    ui->profileFriendList->setColumnCount(1);
    ui->profileFriendSuggest->setColumnCount(1);
    ui->profileFriendList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->profileFriendSuggest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //More Formatting
    ui->profileTitle->setAlignment(Qt::AlignCenter);
    ui->profilePosts->setAlignment(Qt::AlignTop);
    ui->profilePosts->setWordWrap(true);
    ui->profileBio->setAlignment(Qt::AlignTop);
    ui->profileBio->setWordWrap(true);


    toggleProfile(0);

    connect(ui->loginButton,
        &QPushButton::clicked,
        this,
        &MainWindow::loginUser);
    //Visit friend list on table click
    connect(ui->profileFriendList,
        &QTableWidget::cellClicked,
        this,
        &MainWindow::setUserFromTable);
    connect(ui->profileFriendSuggest,
        &QTableWidget::cellClicked,
        this,
        &MainWindow::setUserFromSuggestions);

    //Return to friends list button
    connect(ui->profileReturnButton,
        &QPushButton::clicked,
        this,
        &MainWindow::returnToProfile);
    //Adds current user as friend to logged in user
    connect(ui->profileAddFriendButton,
        &QPushButton::clicked,
        this,
        &MainWindow::addFriend);
    //Add post
    connect(ui->profileAddPostButton,
        &QPushButton::clicked,
        this,
        &MainWindow::addPost);
}

void MainWindow::loginUser(){
    std::string name = ui->loginBox->toPlainText().toStdString();
    if(network_.getId(name) != -1){
        loggedInUser_ = network_.getUser(network_.getId(name));
        currentUser_ = network_.getUser(network_.getId(name));
        toggleLogin(0);
        updateCurrentProfile();
        toggleProfile(1);
    }
    else{
        ui->loginLabel->setText("Invalid Name.");
    }
}

void MainWindow::setUserFromTable(int row, int column){
    QTableWidgetItem *tempFriend = ui->profileFriendList->item(row, column);
    std::string name = tempFriend->text().toStdString();
    currentUser_ = network_.getUser(network_.getId(name));
    updateCurrentProfile();
}

void MainWindow::setUserFromSuggestions(int row, int column){
    QTableWidgetItem *tempFriend = ui->profileFriendSuggest->item(row, column);
    std::string name = tempFriend->text().toStdString();
    currentUser_ = network_.getUser(network_.getId(name));
    updateCurrentProfile();
}

void MainWindow::returnToProfile(){
    currentUser_ = loggedInUser_;
    updateCurrentProfile();
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
    ui->profilePostsLabel->setVisible(tog);
    ui->profilePosts->setVisible(tog);
    ui->profilePostEdit->setVisible(tog);
    ui->profileAddPostButton->setVisible(tog);
    ui->profileBio->setVisible(tog);
    ui->profileBioLabel->setVisible(tog);

    //Toggle other user posts (really only relevant for initializing the window)
    if(currentUser_ == loggedInUser_){
        ui->profileReturnButton->setVisible(false);
        ui->profileFriendSuggest->setVisible(tog);
        ui->profileFriendSuggestLabel->setVisible(tog);
        ui->profileAddFriendButton->setVisible(false);
    }
    else{
        ui->profileReturnButton->setVisible(tog);
        ui->profileFriendSuggest->setVisible(false);
        ui->profileFriendSuggestLabel->setVisible(false);
        ui->profileAddFriendButton->setVisible(tog);
    }
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

    std::string testBio = currentUser_->getName() + "'s Bio";
    ui->profileBio->setText(QString::fromStdString(testBio));


    //todo unspaghetti by dedicating functions for showing/hiding non main profile stuff
    if(currentUser_ == loggedInUser_){
        //Friend suggestions updater
        ui->profileTitle->setText("My Profile");
        ui->profileFriendSuggest->setVisible(true);
        ui->profileFriendSuggestLabel->setVisible(true);
        int score;
        //Setup size of friendSuggestions page
        std::vector<int> friendSuggestions = network_.suggestFriends(currentUser_->getId(), score);
        ui->profileFriendSuggest->setRowCount(friendSuggestions.size());
        //Filling friendSuggestions
        for(int i = 0; i < friendSuggestions.size(); i++){
            QTableWidgetItem *tempFriend = new QTableWidgetItem(QString::fromStdString(network_.getUser(friendSuggestions[i])->getName()));
            ui->profileFriendSuggest->setItem(i, 0, tempFriend);
        }
        ui->profileReturnButton->setVisible(false);
    }
    else{
        std::string title = currentUser_->getName() + "'s Profile";
        ui->profileTitle->setText(QString::fromStdString(title));
        ui->profileFriendSuggest->setVisible(false);
        ui->profileFriendSuggestLabel->setVisible(false);
        ui->profileReturnButton->setVisible(true);
        ui->profileAddFriendButton->setVisible(true);
    }

    //Debug panel stuff
    ui->debugLabel1->setText(QString::fromStdString(currentUser_->getName()));
    ui->debugLabel2->setText(QString::fromStdString(std::to_string(currentUser_->getId())));

    updatePosts();
    ui->profilePostEdit->clear();
}

void MainWindow::updatePosts(){
    ui->profilePosts->setText(QString::fromStdString(network_.getPostsString(currentUser_->getId(),5)));
}

void MainWindow::addFriend(){
    network_.addConnection(loggedInUser_->getName(), currentUser_->getName());
    updateCurrentProfile();
    network_.writeUsers("users.txt");
}

void MainWindow::addPost(){
    if(ui->profilePostEdit->toPlainText() == ""){

    }
    else {
    QString postText = ui->profilePostEdit->toPlainText();
    network_.addPost(new Post(currentUser_->getId(), loggedInUser_->getId(), postText.toStdString(), 0));
    updateCurrentProfile();
    network_.writePosts("posts.txt");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
