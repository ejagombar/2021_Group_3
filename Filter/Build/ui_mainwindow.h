/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openButton;
    QAction *saveButton;
    QAction *actionHelp;
    QAction *actionPrint;
    QAction *disk;
    QAction *arrow;
    QAction *cone;
    QAction *CFilter;
    QAction *SFilter;
    QAction *ColorChoose;
    QAction *Color;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QVTKOpenGLWidget *qvtkWidget;
    QVBoxLayout *verticalLayout_2;
    QListView *listView;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *BoxClip;
    QCheckBox *BoxShrink;
    QCheckBox *smooth;
    QCheckBox *curvatures;
    QPushButton *SSS;
    QPushButton *Filter;
    QPushButton *Filter_T;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuPreloaded;
    QMenu *menuFilter;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1037, 717);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        openButton = new QAction(MainWindow);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        openButton->setIcon(icon);
        saveButton = new QAction(MainWindow);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon1);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon2);
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon3);
        disk = new QAction(MainWindow);
        disk->setObjectName(QString::fromUtf8("disk"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        disk->setIcon(icon4);
        arrow = new QAction(MainWindow);
        arrow->setObjectName(QString::fromUtf8("arrow"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icons/arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        arrow->setIcon(icon5);
        cone = new QAction(MainWindow);
        cone->setObjectName(QString::fromUtf8("cone"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icons/slz.png"), QSize(), QIcon::Normal, QIcon::Off);
        cone->setIcon(icon6);
        CFilter = new QAction(MainWindow);
        CFilter->setObjectName(QString::fromUtf8("CFilter"));
        SFilter = new QAction(MainWindow);
        SFilter->setObjectName(QString::fromUtf8("SFilter"));
        ColorChoose = new QAction(MainWindow);
        ColorChoose->setObjectName(QString::fromUtf8("ColorChoose"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icons/dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        ColorChoose->setIcon(icon7);
        Color = new QAction(MainWindow);
        Color->setObjectName(QString::fromUtf8("Color"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        qvtkWidget = new QVTKOpenGLWidget(centralwidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setMinimumSize(QSize(800, 600));

        verticalLayout_3->addWidget(qvtkWidget);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMaximumSize(QSize(200, 500));

        verticalLayout_2->addWidget(listView);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

        verticalLayout_2->addLayout(verticalLayout_5);

        BoxClip = new QCheckBox(centralwidget);
        BoxClip->setObjectName(QString::fromUtf8("BoxClip"));

        verticalLayout_2->addWidget(BoxClip);

        BoxShrink = new QCheckBox(centralwidget);
        BoxShrink->setObjectName(QString::fromUtf8("BoxShrink"));

        verticalLayout_2->addWidget(BoxShrink);

        smooth = new QCheckBox(centralwidget);
        smooth->setObjectName(QString::fromUtf8("smooth"));

        verticalLayout_2->addWidget(smooth);

        curvatures = new QCheckBox(centralwidget);
        curvatures->setObjectName(QString::fromUtf8("curvatures"));

        verticalLayout_2->addWidget(curvatures);

        SSS = new QPushButton(centralwidget);
        SSS->setObjectName(QString::fromUtf8("SSS"));

        verticalLayout_2->addWidget(SSS);

        Filter = new QPushButton(centralwidget);
        Filter->setObjectName(QString::fromUtf8("Filter"));
        Filter->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout_2->addWidget(Filter);

        Filter_T = new QPushButton(centralwidget);
        Filter_T->setObjectName(QString::fromUtf8("Filter_T"));
        Filter_T->setEnabled(true);

        verticalLayout_2->addWidget(Filter_T);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1037, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuPreloaded = new QMenu(menubar);
        menuPreloaded->setObjectName(QString::fromUtf8("menuPreloaded"));
        menuFilter = new QMenu(menubar);
        menuFilter->setObjectName(QString::fromUtf8("menuFilter"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuPreloaded->menuAction());
        menubar->addAction(menuFilter->menuAction());
        menuFile->addAction(openButton);
        menuFile->addAction(saveButton);
        menuPreloaded->addAction(disk);
        menuPreloaded->addAction(arrow);
        menuPreloaded->addAction(cone);
        menuFilter->addAction(ColorChoose);
        menuFilter->addAction(Color);
        toolBar->addAction(openButton);
        toolBar->addAction(saveButton);
        toolBar->addAction(disk);
        toolBar->addAction(arrow);
        toolBar->addAction(cone);
        toolBar->addAction(ColorChoose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        disk->setText(QCoreApplication::translate("MainWindow", "Disk Item", nullptr));
        arrow->setText(QCoreApplication::translate("MainWindow", "Arrow Item", nullptr));
        cone->setText(QCoreApplication::translate("MainWindow", "Cone Item", nullptr));
        CFilter->setText(QCoreApplication::translate("MainWindow", "Clip Filter", nullptr));
        SFilter->setText(QCoreApplication::translate("MainWindow", "Shrink Filter", nullptr));
        ColorChoose->setText(QCoreApplication::translate("MainWindow", "BaackGround Color", nullptr));
        Color->setText(QCoreApplication::translate("MainWindow", "Actor Color", nullptr));
        BoxClip->setText(QCoreApplication::translate("MainWindow", "Clip Filter", nullptr));
        BoxShrink->setText(QCoreApplication::translate("MainWindow", "Shrink Filter", nullptr));
        smooth->setText(QCoreApplication::translate("MainWindow", "Smooth Filter", nullptr));
        curvatures->setText(QCoreApplication::translate("MainWindow", "Curvatures Filter", nullptr));
        SSS->setText(QCoreApplication::translate("MainWindow", "Smooth", nullptr));
        Filter->setText(QCoreApplication::translate("MainWindow", "Reset Cam", nullptr));
        Filter_T->setText(QCoreApplication::translate("MainWindow", "Filter Test", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuPreloaded->setTitle(QCoreApplication::translate("MainWindow", "Preloaded", nullptr));
        menuFilter->setTitle(QCoreApplication::translate("MainWindow", "Color", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
