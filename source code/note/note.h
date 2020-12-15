#ifndef NOTE_H
#define NOTE_H

#include "data.h"
#include <fstream>
#include <algorithm>
#include <thread>
#include <QTimer>
#include <QScrollBar>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QDateEdit>
#include <QTimeEdit>
#include <QCalendarWidget>
#include <QSignalMapper>
#include <QPalette>

class note : public QMainWindow
{
    Q_OBJECT

public:
    note(QWidget *parent = nullptr);
    ~note();

    QPalette background = QPalette();
    QPalette textBoxPalette = QPalette();

    QString dateSheet;
    QString redDateSheet;
    QString timeSheet;
    QString redTimeSheet;

    int ID;
    bool proceed = true;

    QTimer* timer = new QTimer();

    QScrollBar* leftScrollBar = new QScrollBar();
    QScrollBar* centralScrollBar = new QScrollBar();
    QScrollBar* rightScrollBar = new QScrollBar();

    QWidget* mainWidget = new QWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout(mainWidget);

    QScrollArea* leftScrollArea = new QScrollArea();
    QWidget* leftWidget = new QWidget();
    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);
    QPushButton* left_add_button = new QPushButton("+");
    QWidget* verticalNoteWidget[10];
    QHBoxLayout* verticalNoteLayout[10];
    QPushButton* noteButton[10];
    QLabel* noteLabel[10];
    QSignalMapper* noteMapper[10];

    QWidget* middleWidget = new QWidget();
    QVBoxLayout* middleLayout = new QVBoxLayout(middleWidget);
    QPushButton* noteDeleteButton = new QPushButton("DELETE NOTE");
    QTextEdit* textBox = new QTextEdit();

    QScrollArea* rightScrollArea = new QScrollArea();
    QWidget* rightWidget = new QWidget();
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    QWidget* verticalScheduleWidget[10];
    QVBoxLayout* verticalScheduleLayout[10];
    QWidget* upperScheduleWidget[10];
    QHBoxLayout* upperScheduleLayout[10];
    QWidget* lowerScheduleWidget[10];
    QHBoxLayout* lowerScheduleLayout[10];

    QDateEdit* date[10];
    QTimeEdit* time[10];
    QPushButton* calendarButton[10];
    QPushButton* scheduleDeleteButton[10];
    QLabel* scheduleLabel[10];
    QCalendarWidget* calendar[10];
    QSignalMapper* dateMapper[10];
    QSignalMapper* timeMapper[10];
    QSignalMapper* calendarMapper[10];
    QSignalMapper* deleteScheduleMapper[10];
    QPushButton* right_add_button = new QPushButton("+");

public slots:
    void create_note();
    void switch_note(int);
    void update_note();
    void timer_do();
    void delete_note();
    void delete_schedule_objects();
    void create_schedule();
    void delete_schedule(int);
    void first_note_button_update(int c);
    void other_note_button_update();
    void update_note_button(QString, int);
    QString get_text_for_note_button(QString, int, bool);
    void create_schedule_objects(int);
    void delete_schedule_object(int);
    void link_in_main();
    void update_note_position();
    void update_schedule_position();
    QTime get_current_time();
    void save_date_and_time(int);
    void set_current_date(int);
    void update_visible_schedule(string);
    void color_label();
    void update_schedule_note(int);
    QString replace_new_line(QString);
};
#endif // NOTE_H
