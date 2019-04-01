#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "myopenglwidget.h"
#include <QIcon>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0, myOpenGLWidget* glarea = nullptr);
    ~Settings();

private slots:
    void on_pasHomogeneSpinbox_valueChanged(int arg1);

    void on_uSpinbox_valueChanged(double arg1);

    void on_vSpinbox_valueChanged(double arg1);

    void on_uSlider_valueChanged(int value);

    void on_vSlider_valueChanged(int value);

    void on_controlTranslationForward_clicked();

    void on_controlTranslationLeft_clicked();

    void on_controlTranslationRight_clicked();

    void on_controlTranslationBackward_clicked();

    void on_controlRotationForward_clicked();

    void on_controlRotationLeft_clicked();

    void on_controlRotationRight_clicked();

    void on_controlRotationBackward_clicked();

    void on_resetButton_clicked();

    void on_editModeButton_clicked();

    void on_nextPointButton_clicked();

    void on_previousPointButton_clicked();

    void on_checkShow_clicked(bool checked);

private:
    Ui::Settings *ui;

    const QIcon icon_up_arrow = QIcon(":/icons/up-arrow.png");
    const QIcon icon_down_arrow = QIcon(":/icons/down-arrow.png");
    const QIcon icon_left_arrow = QIcon(":/icons/left-arrow.png");
    const QIcon icon_right_arrow = QIcon(":/icons/right-arrow.png");

signals:
    void pasHomogeneValueChanged(int value);
    void uValueChanged(double value);
    void vValueChanged(double value);
    void translationForward();
    void translationLeft();
    void translationRight();
    void translationBackward();
    void rotationForward();
    void rotationLeft();
    void rotationRight();
    void rotationBackward();
    void reset();
    void editMode();
    void previousPoint();
    void nextPoint();
    void showIntervalParametrique(bool);


};

#endif // SETTINGS_H
