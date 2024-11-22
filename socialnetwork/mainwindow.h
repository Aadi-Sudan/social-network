#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "post.h"
#include "user.h"
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void clearScreen();
    void configureScreen();
    void loginButtonClick();
    void displayProfile();
    void displayFriendsTable();
    void displayPosts();
    void friendClick(int row, int col);
    void returnButtonClick();
    void displaySuggestedTable();
    void suggestedClick(int row, int col);
    void addFriendButtonClick();


private:
    Ui::MainWindow* ui;
    Network network;
    User* loggedInUser;
    User* displayedUser;
};
#endif // MAINWINDOW_H
