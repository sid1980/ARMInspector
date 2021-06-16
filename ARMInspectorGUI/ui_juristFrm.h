/********************************************************************************
** Form generated from reading UI file 'juristFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JURISTFRM_H
#define UI_JURISTFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_juristFrm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *label_Mro;
    QComboBox *comboBox;
    QTableView *tableView;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label_Period;
    QGridLayout *gridLayout_2;
    QDateEdit *dateEdit;
    QLabel *label_Data;
    QPushButton *pushButton_Report;
    QPushButton *pushButton_Excel;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *juristFrm)
    {
        if (juristFrm->objectName().isEmpty())
            juristFrm->setObjectName(QString::fromUtf8("juristFrm"));
        juristFrm->resize(1215, 558);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(juristFrm->sizePolicy().hasHeightForWidth());
        juristFrm->setSizePolicy(sizePolicy);
        juristFrm->setMaximumSize(QSize(16777204, 16777211));
        juristFrm->setLayoutDirection(Qt::LeftToRight);
        juristFrm->setStyleSheet(QString::fromUtf8("QHeaderView {\n"
"    background-color: #fff;\n"
"    font-size:11px;\n"
"}\n"
"QHeaderView::section:horizontal {\n"
"    color: #fff;\n"
"    border-style: solid;\n"
"    background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                        stop: 0 #4287ff, stop: 1 #356ccc);\n"
" }\n"
"QTableView {\n"
"    border: 2px solid #3873d9;\n"
"    border-top-color: #4287ff;\n"
"    border-radius: 4px;\n"
"    background-color: #fff;\n"
"    background-image: url(:/img/other/background.png);\n"
"    gridline-color: #777;\n"
"    selection-background-color: royalblue;\n"
"    color:#333;\n"
"    font-size:11px;\n"
" }\n"
"\n"
"QScrollBar:vertical {\n"
"     background: #e4e4e4;\n"
"     border-top-right-radius: 4px;\n"
"     border-bottom-right-radius: 4px;\n"
"     width: 12px;\n"
"     margin: 0px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"    background-color: qlineargradient( x1: 0, y1: 0, x2: 1, y2: 0,\n"
"                                    stop: 0 #4287ff, stop: 1 #356cc"
                        "c);\n"
"     border-radius: 4px;\n"
"     min-height: 20px;\n"
"     margin: 0px 2px 0px 2px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"     background: none;\n"
"     height: 0px;\n"
"     subcontrol-position: right;\n"
"     subcontrol-origin: margin;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"     background: none;\n"
"     height: 0px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"QMenuBar {\n"
"  background-color:rgb(89,87,87);\n"
" min-width: 20px;\n"
" min-height: 20px;\n"
" }\n"
"QMenuBar::item {\n"
"     spacing: 3px; /* \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273 \320\274\320\265\320\266\320\264\321\203 \320\277\321\203\320\275\320\272\321\202\320\260\320\274\320\270 \320\274\320\265\320\275\321\216 */\n"
"                     font-size: 10pt; \n"
"                     color: rgb(225,225,225);\n"
"                     border: 1px solid rgb(60,60,60);   \n"
"                     background-color:rgb(89,87,87);\n"
"                   "
                        "  padding:2px 2px; \n"
"                     margin:2px 2px;\n"
" }\n"
"\n"
" QMenuBar::item:selected { /* \320\272\320\276\320\263\320\264\320\260 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\276 \321\201 \320\277\320\276\320\274\320\276\321\211\321\214\321\216 \320\274\321\213\321\210\320\270 \320\270\320\273\320\270 \320\272\320\273\320\260\320\262\320\270\320\260\321\202\321\203\321\200\321\213 */\n"
"                     background-color:rgb(235,110,36);\n"
" }\n"
"\n"
" QMenuBar::item:pressed {\n"
"                                           border: 1px solid rgb(60,60,61); \n"
"                                           background-color: rgb(220,80,6);\n"
" }\n"
"QMenu {\n"
"                     background-color:rgb(89,87,87);\n"
"                     border: 3px solid rgb(235,110,36);\n"
"                     }\n"
"                 QMenu::item {                    \n"
"                     font-size: 10pt; \n"
"                     color: rgb(225,225,225);\n"
"                     border"
                        ": 3px solid rgb(60,60,60);   \n"
"                     background-color:rgb(89,87,87);\n"
"                     padding:6px 6px; \n"
"                     margin:2px 2px;\n"
"                      }\n"
"                QMenu::item:selected {\n"
"                     background-color:rgb(235,110,36);\n"
"                     }\n"
"                 QMenu::item:pressed {\n"
"                                           border: 1px solid rgb(60,60,61); \n"
"                                           background-color: rgb(220,80,6);\n"
"                                       }\n"
""));
        juristFrm->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        centralwidget = new QWidget(juristFrm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, -1, 10, -1);
        label_Mro = new QLabel(centralwidget);
        label_Mro->setObjectName(QString::fromUtf8("label_Mro"));
        sizePolicy.setHeightForWidth(label_Mro->sizePolicy().hasHeightForWidth());
        label_Mro->setSizePolicy(sizePolicy);
        label_Mro->setLayoutDirection(Qt::LeftToRight);
        label_Mro->setAutoFillBackground(false);
        label_Mro->setStyleSheet(QString::fromUtf8(""));
        label_Mro->setFrameShadow(QFrame::Sunken);
        label_Mro->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_Mro, 0, 0, 1, 1);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMaximumSize(QSize(16777215, 16777205));
        comboBox->setAutoFillBackground(false);
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"   background: qlineargradient(\n"
"   x1:0, y1:0, x2:0, y2:1,\n"
"   stop:0 #f9f9f9,\n"
"   stop: 0.5 #c6c6c6,\n"
"   stop: 0.6 #dfdfdf,\n"
"   stop:1 #f9f9f9 );\n"
"   border-style: solid;\n"
"   border-width: 1px;\n"
"   border-color: rgb(0, 93, 168);\n"
"   border-radius: 8px;\n"
"   color: rgb(0, 93, 168);\n"
"   min-width: 230px;\n"
"   min-height: 30px;\n"
"   padding-left: 15px;\n"
"}\n"
"QComboBox:on {\n"
"   border-radius: 30px;\n"
"   background:transparent;\n"
"}\n"
"QComboBox::drop-down {\n"
"   image: url(Icons/combobox_down_arrow1.png);\n"
"   subcontrol-position: center right;\n"
"   margin-right: 10px;\n"
"}\n"
"QComboBox QAbstractItemView::item {\n"
"   padding: 10px 10px 10px 10px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"   color: rgb(0, 93, 168);\n"
"   background: transparent;\n"
"}\n"
"QComboBox QListView::item {\n"
"   background: qradialgradient(\n"
"   cx: 0.5, cy: -1.6, fx: 0.5, fy: 0,\n"
"   radius: 2,\n"
"   stop: 0 #C4C4C4,\n"
"   stop: 1 #DBDBDB );\n"
"   borde"
                        "r-style: solid;\n"
"   border-width: 1px;\n"
"   border-color: rgb(0, 93, 168);\n"
"   border-radius: 20px;\n"
"}"));
        comboBox->setEditable(false);

        gridLayout_4->addWidget(comboBox, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_5->addWidget(tableView, 1, 0, 1, 6);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_3->setHorizontalSpacing(6);
        gridLayout_3->setContentsMargins(-1, -1, 0, -1);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(323, 0));
        groupBox->setMaximumSize(QSize(16777215, 16777211));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"    border: 2px solid gray;\n"
"    border-radius: 5px;\n"
"    margin-top: 1ex; /* leave space at the top for the title */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center; /* position at the top center */\n"
"    padding: 0 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"}\n"
"\n"
""));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 10, 52, 17));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(80, 10, 65, 17));
        radioButton_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"    border: 2px solid gray;\n"
"    border-radius: 5px;\n"
"    margin-top: 1ex; /* leave space at the top for the title */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center; /* position at the top center */\n"
"    padding: 0 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"}\n"
"\n"
""));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(150, 10, 97, 17));

        gridLayout_3->addWidget(groupBox, 0, 1, 1, 1);

        label_Period = new QLabel(centralwidget);
        label_Period->setObjectName(QString::fromUtf8("label_Period"));
        sizePolicy.setHeightForWidth(label_Period->sizePolicy().hasHeightForWidth());
        label_Period->setSizePolicy(sizePolicy);
        label_Period->setMaximumSize(QSize(16777215, 16777211));

        gridLayout_3->addWidget(label_Period, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 0, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setEnabled(true);
        sizePolicy.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy);
        dateEdit->setMaximumSize(QSize(16777213, 16777214));
        dateEdit->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"	border: 2px solid lightgray;\n"
"	border-radius: 8px;\n"
"	height: 30px;\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"	subcontrol-origin: padding;\n"
"	subcontrol-position: top right;\n"
"	width: 25px;\n"
"\n"
"	border-left-width: 1px;\n"
"	border-left-color: darkgray;\n"
"	border-left-style: solid;\n"
"	border-top-right-radius: 3px;\n"
"	border-bottom-right-radius: 3px;\n"
"}\n"
"\n"
"QDateEdit::down-arrow {\n"
"	image: url(Icons/combobox_down_arrow1.png);\n"
"}\n"
"\n"
"QDateEdit::drop-down:hover {\n"
"	/* Does this work with QDateEdit??? */\n"
"	background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d8d7d7, stop: 1 #e9e9e9);\n"
"}\n"
""));
        dateEdit->setWrapping(false);
        dateEdit->setFrame(true);
        dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateEdit->setProperty("showGroupSeparator", QVariant(true));
        dateEdit->setDateTime(QDateTime(QDate(2021, 1, 1), QTime(0, 0, 0)));
        dateEdit->setCurrentSection(QDateTimeEdit::MonthSection);
        dateEdit->setCalendarPopup(true);

        gridLayout_2->addWidget(dateEdit, 0, 1, 1, 1);

        label_Data = new QLabel(centralwidget);
        label_Data->setObjectName(QString::fromUtf8("label_Data"));
        sizePolicy.setHeightForWidth(label_Data->sizePolicy().hasHeightForWidth());
        label_Data->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_Data, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 1, 1, 1);

        pushButton_Report = new QPushButton(centralwidget);
        pushButton_Report->setObjectName(QString::fromUtf8("pushButton_Report"));
        sizePolicy.setHeightForWidth(pushButton_Report->sizePolicy().hasHeightForWidth());
        pushButton_Report->setSizePolicy(sizePolicy);
        pushButton_Report->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 150px;\n"
"max-width: 150px;\n"
"min-height: 30px;\n"
"max-height: 30px;\n"
"}\n"
""));
        pushButton_Report->setFlat(true);

        gridLayout_5->addWidget(pushButton_Report, 0, 3, 1, 1);

        pushButton_Excel = new QPushButton(centralwidget);
        pushButton_Excel->setObjectName(QString::fromUtf8("pushButton_Excel"));
        pushButton_Excel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 150px;\n"
"max-width: 150px;\n"
"min-height: 30px;\n"
"max-height: 30px;\n"
"}\n"
""));

        gridLayout_5->addWidget(pushButton_Excel, 0, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        gridLayout_5->addLayout(horizontalLayout, 0, 5, 1, 1);

        juristFrm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(juristFrm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1215, 31));
        juristFrm->setMenuBar(menubar);
        statusbar = new QStatusBar(juristFrm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        juristFrm->setStatusBar(statusbar);

        retranslateUi(juristFrm);

        QMetaObject::connectSlotsByName(juristFrm);
    } // setupUi

    void retranslateUi(QMainWindow *juristFrm)
    {
        juristFrm->setWindowTitle(QCoreApplication::translate("juristFrm", "juristFrm", nullptr));
        label_Mro->setText(QCoreApplication::translate("juristFrm", "\320\234\320\240\320\236", nullptr));
        groupBox->setTitle(QString());
        radioButton->setText(QCoreApplication::translate("juristFrm", "\320\274\320\265\321\201\321\217\321\206", nullptr));
        radioButton_2->setText(QCoreApplication::translate("juristFrm", "\320\272\320\262\320\260\321\200\321\202\320\260\320\273", nullptr));
        radioButton_3->setText(QCoreApplication::translate("juristFrm", " \321\201 \320\275\320\260\321\207\320\260\320\273\320\260 \320\263\320\276\320\264\320\260", nullptr));
        label_Period->setText(QCoreApplication::translate("juristFrm", "\320\237\320\265\321\200\320\270\320\276\320\264", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("juristFrm", "MM.yyyy", nullptr));
        label_Data->setText(QCoreApplication::translate("juristFrm", "\320\264\320\260\321\202\320\260", nullptr));
        pushButton_Report->setText(QCoreApplication::translate("juristFrm", "\320\241\321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\276\321\202\321\207\321\221\321\202", nullptr));
        pushButton_Excel->setText(QCoreApplication::translate("juristFrm", "\320\222\321\213\320\263\321\203\320\267\320\270\321\202\321\214 \320\262 EXCEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class juristFrm: public Ui_juristFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JURISTFRM_H
