#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ImageView.h"
#include <memory>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    using SharedPtr = std::shared_ptr<MainWindow>;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ImageView *view() { return m_view; }
private:
    ImageView *m_view;
};

#endif // MAINWINDOW_H
