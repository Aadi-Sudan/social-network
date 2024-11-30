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
    ui->privacyDropdown->setVisible(false);
    ui->privacyButton->setVisible(false);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginButtonClick);
    connect(ui->friendsTable, &QTableWidget::cellClicked, this, &MainWindow::friendClick);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::returnButtonClick);
    connect(ui->suggestedTable, &QTableWidget::cellClicked, this, &MainWindow::suggestedClick);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &MainWindow::addFriendButtonClick);
    connect(ui->privacyButton, &QPushButton::clicked, this, &MainWindow::privacyButtonClick);
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
    ui->privacyDropdown->setVisible(false);
    ui->privacyButton->setVisible(false);
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
        ui->privacyDropdown->setVisible(true);
        ui->privacyButton->setVisible(true);

        ui->privacyDropdown->clear();
        ui->privacyDropdown->addItem("Public");
        ui->privacyDropdown->addItem("Semi-public");
        ui->privacyDropdown->addItem("Private");

    } else {
        ui->returnButton->setVisible(true);
        ui->addFriendButton->setVisible(true);
        ui->privacyDropdown->setVisible(false);
        ui->privacyButton->setVisible(false);
    }
}

void MainWindow::privacyButtonClick() {
    int selectedPrivacy = ui->privacyDropdown->currentIndex();
    if (loggedInUser == displayedUser) {
        displayedUser->setPrivacy(selectedPrivacy);
        network.writeUsers("/Users/aadisudan/Desktop/CS62/socialnetwork/users.txt");
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

void MainWindow::displayPosts() {
    // Retrieve the privacy level of the displayed user
    int privacyLevel = displayedUser->getPrivacy();

    // Determine if the logged-in user can view the posts
    bool canView = false;

    if (loggedInUser == displayedUser) {
        canView = true; // Always view own posts
    } else if (privacyLevel == 0) {
        canView = true; // Public
    } else if (privacyLevel == 1) {
        // Semi-public: Friends and friends of friends can view
        std::set<int> friendsOfDisplayedUser = displayedUser->getFriends();
        if (friendsOfDisplayedUser.find(loggedInUser->getId()) != friendsOfDisplayedUser.end()) {
            canView = true; // Direct friend
        } else {
            // Check if loggedInUser is a friend of a friend
            for (int friendId : friendsOfDisplayedUser) {
                User* friendUser = network.getUser(friendId);
                if (friendUser && friendUser->getFriends().find(loggedInUser->getId()) != friendUser->getFriends().end()) {
                    canView = true;
                    break;
                }
            }
        }
    } else if (privacyLevel == 2) {
        // Private: Only friends can view
        canView = displayedUser->getFriends().find(loggedInUser->getId()) != displayedUser->getFriends().end();
    }

    if (canView) {
        // Retrieve and display posts
        std::string recentPosts = displayedUser->getPostsString(5, privacyLevel != 0);
        ui->postsLabel->setText(QString::fromStdString(recentPosts));
        ui->postsLabel->setVisible(true);
        ui->postsIndicator->setVisible(true);
    } else {
        // Hide posts if user doesn't meet criteria
        ui->postsLabel->clear();
        ui->postsLabel->setVisible(false);
        ui->postsIndicator->setVisible(false);
    }
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
