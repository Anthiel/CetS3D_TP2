#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected slots:
    void settingsAction();

private:
	Ui::MainWindow *ui;
    Settings* settings = nullptr;
};

#endif // MAINWINDOW_H
