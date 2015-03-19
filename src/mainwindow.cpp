#include <QMenuBar>
#include <QTabWidget>

#include "mainwindow.h"
#include "tabwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initMenuBar();

  qTabWidget = new QTabWidget(this);

  ui->gridLayout->addWidget(qTabWidget);
}

void MainWindow::initMenuBar() {
  QMenuBar *menuBar = this->menuBar();

  QMenu *menuFile = new QMenu("File", this);
  menuFile->addAction("Open Project", this, SLOT(openProject()),
                      QKeySequence(Qt::CTRL + Qt::Key_O));
  menuFile->addAction("Save Project", this, SLOT(saveProject()),
                      QKeySequence(Qt::CTRL + Qt::Key_S));

  menuFile->addSeparator();
  menuFile->addAction("Create Project", this, SLOT(createProject()),
                      QKeySequence(Qt::CTRL + Qt::Key_N));
  menuFile->addAction("Add Curve", this, SLOT(addCurve()),
                      QKeySequence(Qt::CTRL + Qt::Key_A));
  menuFile->addAction("Exit");

  QMenu *menuEdit = new QMenu("Edit", this);
  menuEdit->addAction("Copy Curve", this, SLOT(copyCurve()),
                      QKeySequence(Qt::CTRL + Qt::Key_C));
  menuEdit->addAction("Paste Curve", this, SLOT(pasteCurve()),
                      QKeySequence(Qt::CTRL + Qt::Key_V));
  menuEdit->addAction("Remove Curve", this, SLOT(removeCurve()),
                      QKeySequence(Qt::Key_Backspace));
  menuEdit->addSeparator();
  menuEdit->addAction("Redo", this, SLOT(undoCmd()),
                      QKeySequence(Qt::CTRL + Qt::Key_Z));
  menuEdit->addAction("Undo", this, SLOT(redoCmd()),
                      QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z));

  QMenu *menuView = new QMenu("View", this);
  menuView->addAction("Close Tab", this, SLOT(closeProject()),
                      QKeySequence(Qt::CTRL + Qt::Key_W));

  QMenu *menuAbout = new QMenu("Help", this);
  menuEdit->addAction("About");

  menuBar->addMenu(menuFile);
  menuBar->addMenu(menuEdit);
  menuBar->addMenu(menuView);
  menuBar->addMenu(menuAbout);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::addCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->addCurve();
}

void MainWindow::copyCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->copyCurve();
}

void MainWindow::pasteCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->pasteCurve();
}

void MainWindow::removeCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->removeCurve();
}

void MainWindow::redoCmd() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->redoCmd();
}
void MainWindow::openProject() {
  TabWidget *newTab = new TabWidget(qTabWidget);
  QString projectName = newTab->openProject(ioController);
  qTabWidget->addTab(newTab, projectName);
  qTabWidget->setCurrentWidget(newTab);
}

void MainWindow::saveProject() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->saveProject(ioController);
}

void MainWindow::createProject() {
  TabWidget *newTab = new TabWidget(qTabWidget);
  qTabWidget->addTab(newTab, "#");
  qTabWidget->setCurrentWidget(newTab);
}

void MainWindow::closeProject() {
  saveProject();
  qTabWidget->removeTab(qTabWidget->currentIndex());
}

void MainWindow::undoCmd() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->undoCmd();
}
