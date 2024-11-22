#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (ui->loginLineEdit == nullptr) {
        std::cout << "loginLineEdit is nullptr!" << std::endl;
    }
    if (ui->loginButton == nullptr) {
        std::cout << "loginButton is nullptr!" << std::endl;
    }
    network.readUsers("/Users/aadisudan/Desktop/CS62/socialnetwork/users.txt");
    network.readPosts("/Users/aadisudan/Desktop/CS62/socialnetwork/posts.txt");

    ui->profileLabel->setVisible(false);
    ui->returnButton->setVisible(false);
    ui->friendsTable->setVisible(false);
    ui->postsIndicator->setVisible(false);
    ui->postsLabel->setVisible(false);
    ui->suggestedTable->setVisible(false);
    ui->addFriendButton->setVisible(false);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginButtonClick);
    connect(ui->friendsTable, &QTableWidget::cellClicked, this, &MainWindow::friendClick);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::returnButtonClick);
    connect(ui->suggestedTable, &QTableWidget::cellClicked, this, &MainWindow::suggestedClick);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &MainWindow::addFriendButtonClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearScreen(){
    ui->returnButton->setVisible(false);
    ui->friendsTable->setVisible(false);
    ui->loginLineEdit->setVisible(false);
    ui->loginButton->setVisible(false);
    ui->loginLabel->setVisible(false);
    ui->profileLabel->setVisible(false);
    ui->postsIndicator->setVisible(false);
    ui->postsLabel->setVisible(false);
    ui->addFriendButton->setVisible(false);
    ui->suggestedTable->setVisible(false);
}

void MainWindow::configureScreen(){
    ui->loginLineEdit->setVisible(false);
    ui->loginButton->setVisible(false);
    ui->loginLabel->setVisible(false);
    ui->friendsTable->setVisible(true);
    ui->profileLabel->setVisible(true);
    ui->postsIndicator->setVisible(true);
    ui->postsLabel->setVisible(true);
    ui->suggestedTable->setVisible(true);

    if (loggedInUser == displayedUser){
        ui->returnButton->setVisible(false);
        ui->addFriendButton->setVisible(false);

    } else {
        ui->returnButton->setVisible(true);
        ui->addFriendButton->setVisible(true);
    }
}

void MainWindow::loginButtonClick(){
    QString username = ui->loginLineEdit->text();
    std::string userString = username.toStdString();
    int userId = network.getId(userString);

    if (userId != -1){
        loggedInUser = network.getUser(userId);
        displayedUser = network.getUser(userId);
        displayProfile();
    }
    else {
        ui->loginLabel->setText("Username not found. Try again:");
        return;
    }
}

void MainWindow::displayProfile(){
    if (loggedInUser->getId() == -1) {
        return;
    }
    if (loggedInUser->getId() == displayedUser->getId()) {
        ui->profileLabel->setText("My Profile");
    } else {
        ui->profileLabel->setText(QString::fromStdString(displayedUser->getName() + "'s Profile"));

    }
    configureScreen();
    displayFriendsTable();
    displayPosts();
    displaySuggestedTable();
}

void MainWindow::displayFriendsTable(){
    std::set<int> friendID = displayedUser->getFriends();
    int size = friendID.size();
    ui->friendsTable->setRowCount(size);
    ui->friendsTable->setColumnCount(1);
    int row = 0;

    for (int id : friendID) {
        User *user = network.getUser(id);
        QTableWidgetItem* i = new QTableWidgetItem(QString::fromStdString(user->getName()));
        ui->friendsTable->setItem(row, 0, i);
        row++;
    }
}

void MainWindow::displayPosts(){
    std::string recentPosts;
    bool privacy;

    if (loggedInUser == displayedUser){
        privacy = false;
    } else {
        privacy = true;
    }
    recentPosts = network.getPostsString(displayedUser->getId(), 5, privacy);
    ui->postsLabel->setText(QString::fromStdString(recentPosts));
}

void MainWindow::friendClick(int row, int col) {
    QTableWidgetItem* i = ui->friendsTable->item(row, col);

    if (i) {
        QString name = i->text();
        std::string nameString = name.toStdString();
        int id = network.getId(nameString);
        User* friendUser = network.getUser(id);
        displayedUser = network.getUser(id);
        displayedUser = friendUser;
        displayProfile();
    }
}

void MainWindow::returnButtonClick(){
    clearScreen();
    displayedUser = loggedInUser;
    displayProfile();
}

void MainWindow::displaySuggestedTable(){
    std::vector<int> suggestedID;
    int score;
    suggestedID = network.suggestFriends(displayedUser->getId(), score);
    int size = suggestedID.size();
    ui->suggestedTable->setRowCount(size);
    ui->suggestedTable->setColumnCount(1);
    int row = 0;
    for (int id : suggestedID) {
        User* user = network.getUser(id);
        if (user != nullptr) {
            QTableWidgetItem *i = new QTableWidgetItem(QString::fromStdString(user->getName()));
            ui->suggestedTable->setItem(row, 0, i);
            row++;
        }
    }
}

void MainWindow::suggestedClick(int row, int col){
    QTableWidgetItem* i = ui->suggestedTable->item(row, col);
    if (i) {
        QString name = i->text();
        std::string nameString = name.toStdString();
        int id = network.getId(nameString);
        User* user = network.getUser(id);
        displayedUser = network.getUser(id);
        displayedUser = user;
        displayProfile();
    }
}

void MainWindow::addFriendButtonClick(){
    std::string yourName = loggedInUser->getName();
    std::string theirName = displayedUser->getName();
    if (yourName != theirName){
        network.addConnection(yourName, theirName);
        network.writeUsers("/Users/aadisudan/Desktop/CS62/socialnetwork/users.txt");
    }
}
