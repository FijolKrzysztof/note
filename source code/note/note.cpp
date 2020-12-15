#include "note.h"

using namespace std;

note::note(QWidget *parent)
    : QMainWindow(parent)
{
    background.setColor(QPalette::Background, QColor(40,40,40));
    textBoxPalette.setColor(QPalette::Base, QColor(40,40,40));
    textBoxPalette.setColor(QPalette::Text, Qt::white);

    dateSheet = "QDateEdit{ background-color: rgb(40,40,40); color:rgb(255,255,255); "
                "border-style: solid; border-width: 1px; border-color: rgb(178,34,34); }"
                "QDateEdit::up-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); border-bottom-color: rgb(178,34,34);}"
                "QDateEdit::down-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); }";
    redDateSheet = "QDateEdit{ background-color:rgb(40,40,40); color:red;"
                   "border-style: solid; border-width: 1px; border-color: rgb(178,34,34); }"
                   "QDateEdit::up-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); border-bottom-color: rgb(178,34,34); }"
                   "QDateEdit::down-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); }";
    timeSheet = "QTimeEdit{ background-color:rgb(40,40,40); color:rgb(255,255,255);"
                "border-style: solid; border-width: 1px; border-color: rgb(178,34,34); }"
                "QTimeEdit::up-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); border-bottom-color: rgb(178,34,34); }"
                "QTimeEdit::down-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); }";
    redTimeSheet = "QTimeEdit{ background-color:rgb(40,40,40); color:red;"
                   "border-style: solid; border-width: 1px; border-color: rgb(178,34,34); }"
                   "QTimeEdit::up-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); border-bottom-color: rgb(178,34,34); }"
                   "QTimeEdit::down-button{ border-style: solid; border-width: 1px; border-left-color: rgb(178,34,34); }";

    leftScrollBar->setStyleSheet("QScrollBar:vertical{ background: #282828; }"
                                 "QScrollBar::handle:vertical{ background: rgb(178,34,34); }"
                                 "QScrollBar::add-line:vertical { background: #282828; }"
                                 "QScrollBar::sub-line:vertical { background: #282828; }");
    centralScrollBar->setStyleSheet("QScrollBar:vertical{ background: #282828; }"
                                    "QScrollBar::handle:vertical{ background: rgb(178,34,34); }"
                                    "QScrollBar::add-line:vertical { background: #282828; }"
                                    "QScrollBar::sub-line:vertical { background: #282828; }");
    rightScrollBar->setStyleSheet("QScrollBar:vertical{ background: #282828; }"
                                  "QScrollBar::handle:vertical{ background: rgb(178,34,34); }"
                                  "QScrollBar::add-line:vertical { background: #282828; }"
                                  "QScrollBar::sub-line:vertical { background: #282828; }");

    setCentralWidget(mainWidget);
    setGeometry(200,0,1550,400);
    setPalette(QColor(150,0,0));
    setFixedWidth(1550);

    mainWidget->setPalette(background);

    mainLayout->addWidget(leftScrollArea);
    mainLayout->setContentsMargins(2,2,2,2);
    mainLayout->setSpacing(0);

    leftScrollArea->setWidgetResizable(true);
    leftScrollArea->setVerticalScrollBar(leftScrollBar);
    leftScrollArea->setWidget(leftWidget);
    leftScrollArea->setAutoFillBackground(true);
    leftScrollArea->setStyleSheet("background-color:rgb(40,40,40); border-style: solid; border-width: 0px;");

    middleWidget->setFixedWidth(570);
    middleWidget->setAutoFillBackground(true);
    middleWidget->setPalette(background);

    middleLayout->addWidget(noteDeleteButton);
    middleLayout->addWidget(textBox);
    middleLayout->setContentsMargins(0,20,10,20);
    middleLayout->setSpacing(10);

    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setWidget(rightWidget);
    rightScrollArea->setFixedWidth(320);
    rightScrollArea->setVerticalScrollBar(rightScrollBar);
    rightScrollArea->setAutoFillBackground(true);
    rightScrollArea->setStyleSheet("background-color:rgb(40,40,40); border-style: solid; border-width: 0px;");

    leftLayout->setContentsMargins(20,20,20,20);
    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->setSpacing(10);

    connect(noteDeleteButton, SIGNAL(clicked(bool)), this, SLOT(delete_note()));
    connect(textBox, SIGNAL(textChanged()), this, SLOT(update_note()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_do()));
    connect(left_add_button, SIGNAL(clicked(bool)), this, SLOT(create_note()));
    connect(right_add_button, SIGNAL(clicked(bool)), this, SLOT(create_schedule()));

    vector<int> mainIDs = getMainIDs();
    int mainIDsSize = mainIDs.size();
    for(int i = 0; i < mainIDsSize; i++)
    {
        int c = mainIDs[i];
        ID = mainIDs[i];

        verticalNoteWidget[c] = new QWidget();
        verticalNoteLayout[c] = new QHBoxLayout(verticalNoteWidget[c]);
        noteButton[c] = new QPushButton();
        noteLabel[c] = new QLabel();
        noteMapper[c] = new QSignalMapper();

        verticalNoteLayout[c]->addWidget(noteLabel[c]);
        verticalNoteLayout[c]->addWidget(noteButton[c]);
        verticalNoteLayout[c]->setContentsMargins(0,0,0,0);
        verticalNoteLayout[c]->setSpacing(5);

        leftLayout->addWidget(verticalNoteWidget[c]);

        noteButton[c]->setFixedHeight(80);
        noteButton[c]->setStyleSheet("QPushButton{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white; }");

        noteLabel[c]->setAlignment(Qt::AlignCenter);
        noteLabel[c]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white;}");
        noteLabel[c]->setFixedWidth(180);

        noteMapper[c]->setMapping(noteButton[c], c);

        connect(noteButton[c], SIGNAL(clicked(bool)), noteMapper[c], SLOT(map()));
        connect(noteMapper[c], SIGNAL(mapped(int)), this, SLOT(switch_note(int)));

        first_note_button_update(c);

        link_in_main();
    }
    leftLayout->addWidget(left_add_button);

    rightLayout->setContentsMargins(10,20,20,20);
    rightLayout->setSpacing(20);
    rightLayout->setAlignment(Qt::AlignTop);

    left_add_button->setStyleSheet("QPushButton{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white; }");
    left_add_button->setFixedHeight(23);

    noteDeleteButton->setStyleSheet("QPushButton{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white; }");
    noteDeleteButton->setFixedSize(160,50);

    QFont font = QFont();
    font.setPointSize(13);

    textBox->setFont(font);
    textBox->setPalette(textBoxPalette);
    textBox->setVerticalScrollBar(centralScrollBar);
    textBox->setStyleSheet("QTextEdit{ border-style: solid; border-width: 0px; border-color: rgb(178,34,34); }");

    right_add_button->setStyleSheet("QPushButton{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white; }");
    right_add_button->setFixedHeight(23);

    if(mainIDsSize > 0)
    {
        ID = 10000;
        switch_note(mainIDs[0]);
    }
}
note::~note()
{
}
void note::create_note()
{
    delete_schedule_objects();

    int c = getFreeID("MAIN");
    ID = c;
    createTableAndInsertID(c);

    verticalNoteWidget[c] = new QWidget();
    verticalNoteLayout[c] = new QHBoxLayout(verticalNoteWidget[c]);
    noteButton[c] = new QPushButton();
    noteLabel[c] = new QLabel();
    noteMapper[c] = new QSignalMapper();

    verticalNoteLayout[c]->addWidget(noteLabel[c]);
    verticalNoteLayout[c]->addWidget(noteButton[c]);
    verticalNoteLayout[c]->setContentsMargins(0,0,0,0);
    verticalNoteLayout[c]->setSpacing(5);

    leftLayout->addWidget(verticalNoteWidget[c]);
    leftLayout->addWidget(left_add_button);

    rightLayout->addWidget(right_add_button);

    mainLayout->addWidget(middleWidget);
    mainLayout->addWidget(rightScrollArea);
    middleWidget->show();
    rightScrollArea->show();

    noteButton[c]->setFixedHeight(80);
    noteButton[c]->setStyleSheet("QPushButton{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white; }");

    noteLabel[c]->setAlignment(Qt::AlignCenter);
    noteLabel[c]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white;}");
    noteLabel[c]->setFixedWidth(180);

    noteMapper[c]->setMapping(noteButton[c], c);

    connect(noteButton[c], SIGNAL(clicked(bool)), noteMapper[c], SLOT(map()));
    connect(noteMapper[c], SIGNAL(mapped(int)), this, SLOT(switch_note(int)));

    textBox->clear();
}
void note::switch_note(int c)
{
    delete_schedule_objects();

    ID = c;

    mainLayout->addWidget(middleWidget);
    mainLayout->addWidget(rightScrollArea);
    middleWidget->show();
    rightScrollArea->show();

    disconnect(textBox, SIGNAL(textChanged()), this, SLOT(update_note()));
    textBox->clear();
    const QString text = getText(ID);
    textBox->setText(text);
    connect(textBox, SIGNAL(textChanged()), this, SLOT(update_note()));

    vector<int> ScheduleIDs = getScheduleIDs(ID);
    vector<QDate> dates = getDates(ID);
    vector<QTime> times = getTimes(ID);

    int IDsSize = ScheduleIDs.size();
    for(int i = 0; i < IDsSize; i++)
    {
        create_schedule_objects(ScheduleIDs[i]);
    }
    for(int i = 0; i < IDsSize; i++)
    {
        date[ScheduleIDs[i]]->setDate(dates[i]);
        time[ScheduleIDs[i]]->setTime(times[i]);
    }
    rightLayout->addWidget(right_add_button);

    update_schedule_position();
}
void note::update_note()
{
    if(proceed == true)
    {
        proceed = false;
        timer->start(1000);
    }
    other_note_button_update();
}
void note::timer_do()
{
    timer->stop();
    proceed = true;
    QString qtext = textBox->toPlainText();
    string text = qtext.toStdString();
    updateText(ID, text);
}
void note::delete_note()
{
    delete_schedule_objects();

    deleteTableAndID(ID);

    verticalNoteWidget[ID]->deleteLater();
    verticalNoteLayout[ID]->deleteLater();
    noteButton[ID]->deleteLater();
    noteLabel[ID]->deleteLater();
    noteMapper[ID]->deleteLater();

    mainLayout->removeWidget(middleWidget);
    mainLayout->removeWidget(rightScrollArea);
    middleWidget->hide();
    rightScrollArea->hide();
}
void note::delete_schedule_objects()
{
    vector<int> IDs = getScheduleIDs(ID);
    int scheduleIDsSize = IDs.size();
    for(int i = 0; i < scheduleIDsSize; i++)
    {
        delete_schedule_object(IDs[i]);
    }
}
void note::create_schedule()
{
    int c = getFreeID("Z" + to_string(ID));
    create_schedule_objects(c);

    QDate currentDate = QDate::currentDate();
    QTime currentTime = get_current_time();
    date[c]->setDate(currentDate);
    time[c]->setTime(currentTime);

    rightLayout->addWidget(right_add_button);

    insertScheduleInfo(ID, c, currentDate, currentTime);

    link_in_main();
    update_schedule_position();
    update_note_position();
}
void note::delete_schedule(int c)
{
    delete_schedule_object(c);
    deleteFromScheduleTable(ID, c);
    link_in_main();
}
void note::first_note_button_update(int c)
{
    QString text = getText(c);
    update_note_button(text, c);
}
void note::other_note_button_update()
{
    QString text = textBox->toPlainText();
    update_note_button(text, ID);
}
void note::update_note_button(QString qText, int c)
{
    QString getUpper = qText.toUpper();
    int maxTextSize = 80;
    if(qText.size() != 0)
    {
        QString text = replace_new_line(getUpper);
        if(text.size() > maxTextSize)
        {
            QString convertText = get_text_for_note_button(text, maxTextSize, true);
            noteButton[c]->setText(convertText + "...");
        }
        else
        {
            if(text.size() > maxTextSize/2)
            {
                QString convertText = get_text_for_note_button(text, maxTextSize, false);
                noteButton[c]->setText(convertText);
            }
            else
            {
                QStringRef cutText(&text, 0, text.size());
                QString convertText = cutText.toString();
                noteButton[c]->setText(convertText);
            }
        }
    }
    else
    {
        noteButton[c]->setText(" ");
    }
}
QString note::get_text_for_note_button(QString text, int maxTextSize, bool end)
{
    size_t found = 10;
    vector<int> locations;
    string sText = text.toStdString();
    while(true)
    {
        found = sText.find(" ", found + 1);
        locations.push_back(found - 0);
        int foundNumber = found;
        if(foundNumber == -1)
        {
            foundNumber = 100000;
        }
        if(foundNumber >= maxTextSize/2)
        {
            break;
        }
    }
    int bestLocation = maxTextSize/2;
    int lSize = locations.size();
    for(int i = 0; i < lSize; i++)
    {
        if(locations[i] <= maxTextSize/2)
        {
            bestLocation = locations[i];
        }
        else
        {
            break;
        }
    }
    if(bestLocation == -1)
    {
        bestLocation = maxTextSize/2;
    }
    QStringRef cutText(&text, 0, maxTextSize/2 - (maxTextSize/2 - bestLocation));
    if(end == true)
    {
        QStringRef cutSecond(&text, maxTextSize/2 - (maxTextSize/2 - bestLocation), maxTextSize - maxTextSize/2 + (maxTextSize/2 - bestLocation));
        QString convertText = cutText.toString() + "\n" + cutSecond.toString();
        return convertText;
    }
    else
    {
        QStringRef cutSecond(&text, maxTextSize/2 - (maxTextSize/2 - bestLocation), text.size() - maxTextSize/2 + (maxTextSize/2 - bestLocation));
        QString convertText = cutText.toString() + "\n" + cutSecond.toString();
        return convertText;
    }
}
void note::create_schedule_objects(int c)
{
    verticalScheduleWidget[c] = new QWidget();
    verticalScheduleLayout[c] = new QVBoxLayout(verticalScheduleWidget[c]);
    upperScheduleWidget[c] = new QWidget();
    upperScheduleLayout[c] = new QHBoxLayout(upperScheduleWidget[c]);
    lowerScheduleWidget[c] = new QWidget();
    lowerScheduleLayout[c] = new QHBoxLayout(lowerScheduleWidget[c]);
    date[c] = new QDateEdit();
    time[c] = new QTimeEdit();
    calendarButton[c] = new QPushButton("CALENDAR");
    scheduleDeleteButton[c] = new QPushButton("DELETE SCHEDULE");
    scheduleLabel[c] = new QLabel("poniedziałek");
    calendar[c] = new QCalendarWidget();
    dateMapper[c] = new QSignalMapper();
    timeMapper[c] = new QSignalMapper();
    calendarMapper[c] = new QSignalMapper();
    deleteScheduleMapper[c] = new QSignalMapper();

    upperScheduleLayout[c]->addWidget(date[c]);
    upperScheduleLayout[c]->addWidget(calendarButton[c]);
    upperScheduleLayout[c]->setContentsMargins(0,0,0,0);
    upperScheduleLayout[c]->setSpacing(5);

    lowerScheduleLayout[c]->addWidget(time[c]);
    lowerScheduleLayout[c]->addWidget(scheduleDeleteButton[c]);
    lowerScheduleLayout[c]->setContentsMargins(0,0,0,0);
    lowerScheduleLayout[c]->setSpacing(5);

    verticalScheduleLayout[c]->addWidget(upperScheduleWidget[c]);
    verticalScheduleLayout[c]->addWidget(lowerScheduleWidget[c]);
    verticalScheduleLayout[c]->addWidget(scheduleLabel[c]);
    verticalScheduleLayout[c]->setContentsMargins(0,0,0,0);
    verticalScheduleLayout[c]->setSpacing(5);

    rightLayout->addWidget(verticalScheduleWidget[c]);

    date[c]->setFixedSize(120,40);
    date[c]->setAlignment(Qt::AlignCenter);
    time[c]->setFixedSize(120,40);
    time[c]->setAlignment(Qt::AlignCenter);

    calendarButton[c]->setStyleSheet("QPushButton{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white; }");
    calendarButton[c]->setFixedHeight(40);

    scheduleDeleteButton[c]->setStyleSheet("QPushButton{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white; }");
    scheduleDeleteButton[c]->setFixedHeight(40);

    scheduleLabel[c]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white;}");
    scheduleLabel[c]->setFixedHeight(40);
    scheduleLabel[c]->setAlignment(Qt::AlignCenter);

    calendar[c]->setLocale( QLocale::English );

    dateMapper[c]->setMapping(date[c], c);
    timeMapper[c]->setMapping(time[c], c);
    calendarMapper[c]->setMapping(calendarButton[c], c);
    deleteScheduleMapper[c]->setMapping(scheduleDeleteButton[c], c);

    connect(date[c], SIGNAL(dateChanged(QDate)), dateMapper[c], SLOT(map()));
    connect(dateMapper[c], SIGNAL(mapped(int)), this, SLOT(save_date_and_time(int)));
    connect(time[c], SIGNAL(timeChanged(QTime)), timeMapper[c], SLOT(map()));
    connect(timeMapper[c], SIGNAL(mapped(int)), this, SLOT(save_date_and_time(int)));
    connect(calendarButton[c], SIGNAL(clicked(bool)), calendar[c], SLOT(show()));
    connect(calendarButton[c], SIGNAL(clicked(bool)), calendarMapper[c], SLOT(map()));
    connect(calendarMapper[c], SIGNAL(mapped(int)), this, SLOT(set_current_date(int)));
    connect(scheduleDeleteButton[c], SIGNAL(clicked(bool)), deleteScheduleMapper[c], SLOT(map()));
    connect(deleteScheduleMapper[c], SIGNAL(mapped(int)), this, SLOT(delete_schedule(int)));
    connect(calendar[c], SIGNAL(clicked(QDate)), date[c], SLOT(setDate(QDate)));
}
void note::delete_schedule_object(int c)
{
    verticalScheduleWidget[c]->deleteLater();
    verticalScheduleLayout[c]->deleteLater();
    upperScheduleWidget[c]->deleteLater();
    upperScheduleLayout[c]->deleteLater();
    lowerScheduleWidget[c]->deleteLater();
    lowerScheduleLayout[c]->deleteLater();
    date[c]->deleteLater();
    time[c]->deleteLater();
    calendarButton[c]->deleteLater();
    scheduleDeleteButton[c]->deleteLater();
    scheduleLabel[c]->deleteLater();
    calendar[c]->deleteLater();
    dateMapper[c]->deleteLater();
    timeMapper[c]->deleteLater();
    calendarMapper[c]->deleteLater();
    deleteScheduleMapper[c]->deleteLater();
}
void note::link_in_main()
{
    string firstDate = getFirstDateTime(ID);
    if(firstDate != "none")
    {
        update_visible_schedule(firstDate);
        string linkDate = getDateFromMain(ID);
        if(firstDate != linkDate)
        {
            updateDateTime(ID, firstDate);
        }
    }
    else
    {
        updateDateTime(ID, "9999.99.99 99:99");
        update_visible_schedule(" ");
    }
}
void note::update_note_position()
{
    vector<int> IDs = getMainIDs();
    int IDsSize = IDs.size();
    for(int i = 0; i < IDsSize; i++)
    {
        leftLayout->addWidget(verticalNoteWidget[IDs[i]]);
    }
    leftLayout->addWidget(left_add_button);
}
void note::update_schedule_position()
{
    vector<int> scheduleIDs = getScheduleIDs(ID);
    int scheduleIDsSize = scheduleIDs.size();
    for(int i = 0; i < scheduleIDsSize; i++)
    {
        rightLayout->addWidget(verticalScheduleWidget[scheduleIDs[i]]);
    }
    rightLayout->addWidget(right_add_button);
}
QTime note::get_current_time()
{
    QTime qTime = QTime::currentTime();
    int intTime = qTime.hour();
    QTime qIntTime(intTime + 1, 0);
    return qIntTime;
}
void note::save_date_and_time(int c)
{
    updateDateAndTime(ID, c, date[c]->date(), time[c]->time());

    if(date[c]->date() == QDate::currentDate())
    {
        date[c]->setStyleSheet(dateSheet);
        if(time[c]->time() <= QTime::currentTime())
        {
            time[c]->setStyleSheet(redTimeSheet);
            scheduleLabel[c]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: red;}");
        }
        else
        {
            time[c]->setStyleSheet(timeSheet);
            scheduleLabel[c]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white;}");
        }
    }
    if(date[c]->date() > QDate::currentDate())
    {
        date[c]->setStyleSheet(dateSheet);
        time[c]->setStyleSheet(timeSheet);
        scheduleLabel[c]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white;}");
    }
    if(date[c]->date() < QDate::currentDate())
    {
        date[c]->setStyleSheet(redDateSheet);
        time[c]->setStyleSheet(redTimeSheet);
        scheduleLabel[c]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: red;}");
    }

    update_schedule_note(c);
    link_in_main();
    update_note_position();
    color_label();
}
void note::set_current_date(int c)
{
    calendar[c]->setSelectedDate(QDate::currentDate());

    QPoint d = calendarButton[c]->mapToGlobal(QPoint(0,0));
    int x = d.x();
    int y = d.y();
    calendar[c]->setGeometry(x - 465, y - 23, 460, 200);
}
void note::update_visible_schedule(string date)
{
    QString convertDate = QString::fromStdString(date);
    if(convertDate != " ")
    {
        vector<QDate> dates = getDates(ID);
        vector<QTime> times = getTimes(ID);
        QLocale locale  = QLocale(QLocale::English, QLocale::UnitedStates);
        QString sDate = locale.toString(dates[0], "dddd");
        QString sTime = times[0].toString("hh:mm");
        QString sDateTime = sDate + " " + sTime;
        QString getUpper = sDateTime.toUpper();
        noteLabel[ID]->setText(getUpper);
    }
    else
    {
        noteLabel[ID]->setText(convertDate);
    }
}
void note::color_label()
{
    string dateTime = getDateFromMain(ID);
    if(dateTime != "none")
    {
        QDateTime currentDate = QDateTime::currentDateTime();
        QString convert = currentDate.toString("yyyy.MM.dd hh:mm");
        string date = convert.toStdString();
        if(date > dateTime)
        {
            noteLabel[ID]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: red;}");
        }
        else
        {
            noteLabel[ID]->setStyleSheet("QLabel{ border: 1px solid rgb(178,34,34); background: rgb(40,40,40); color: white;}");
        }
    }
}
void note::update_schedule_note(int c)
{
    QDate getDate = date[c]->date();
    QTime getTime = time[c]->time();
    QLocale locale  = QLocale(QLocale::English, QLocale::UnitedStates);
    QString sDate = locale.toString(getDate, "dddd");
    QString sTime = getTime.toString("hh:mm");
    QString sDateTime = sDate + " " + sTime;
    QString getUpper = sDateTime.toUpper();
    scheduleLabel[c]->setText(getUpper);
}
QString note::replace_new_line(QString text)
{
    string from = "\n";
    string to = " ";
    string nText = text.toStdString();
    while(nText.find(from) != string::npos)
    {
        nText.replace(nText.find(from), from.length(), to);
    }
    QString output = QString::fromStdString(nText);
    return output;
}
