#include "ToolBar.h"
#include "ui_texteditor.h"
#include <QDebug>

class TextEditor;

ToolBar::ToolBar(Ui::TextEditor *ui)
{
    this->ui = ui;
    this->setIconSize(QSize(40, 40));
    this->setMovable(false);
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    InitBarItem();
}

// set ToolBar item picture and connect signal & slot
void ToolBar::InitBarItem()
{
    AddToolBarAct(openFile,"Open File", ":/Icon/Icon/OpenFile.png", &ToolBar::onOpenFileClicked);

    AddToolBarAct(saveFile,"Save File", ":/Icon/Icon/SaveFile.png", &ToolBar::onSaveFileClicked);
    AddToolBarAct(saveFile,"Clear", ":/Icon/Icon/Clear.png", &ToolBar::onClearClicked);
    AddToolBarLabel("Text Editing ➔ ");
    AddToolBarAct(setBold, "Bold",":/Icon/Icon/Bold.png", &ToolBar::onBoldClicked);
    AddToolBarAct(setItalic, "Italic",":/Icon/Icon/Italic.png", &ToolBar::onItalicClicked);
    AddToolBarAct(setUnderLine, "UnderLine", ":/Icon/Icon/UnderLine.png", &ToolBar::onUnderLineClicked);
    AddToolBarAct(setTextColor, "Text Color", ":/Icon/Icon/TextColor.png", &ToolBar::onTextColorClicked);
    AddToolBarAct(setBackGroundColor, "BackGround\nColor", ":/Icon/Icon/BgColor.png", &ToolBar::onBackGroundColorClicked);
    AddToolBarSpinBox(setFontSize, 4, 72, 9, "Font Size: ", &ToolBar::onSetFontSizeChanged);
    AddToolBarFontComboBox(setFontStyle,"Font Style: ", &ToolBar::onSetFontStyleChanged);

}

// add a new action to ToolaBar
void ToolBar::AddToolBarAct(QAction *action, QString name, QString path, void (ToolBar::*triggeredFunc)())
{
    action = new QAction(name, this);
    action ->setIcon(QIcon(path));
    connect (action, &QAction::triggered, this, triggeredFunc);

    this->addAction(action);
    addSeparator();
}

// add a new action to ToolBar
void ToolBar::AddToolBarAct(QAction *action, QString name, QString path, void (ToolBar::*triggeredFunc)(bool))
{
    action = new QAction(name, this);
    action ->setIcon(QIcon(path));
    action->setCheckable(true);
    connect (action, &QAction::toggled, this, triggeredFunc);

    this->addAction(action);
    addSeparator();
}

// add a new label to ToolBar
void ToolBar::AddToolBarLabel(QString text)
{
    QLabel *label = new QLabel(text, this);
    label->resize(300, 100);
    label->setFont(QFont("微軟正黑體",12,QFont::Bold, true));
    label->setStyleSheet("QLabel{background-color:QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #007500, stop: 1 #0055ff); color:white}");
    label->setMargin(10);
    this->addWidget(label);
    addSeparator();
}

// add a new spinbox to ToolBar
void ToolBar::AddToolBarSpinBox(QSpinBox *spinBox, int min, int max, int initValue, QString title, void (ToolBar::*triggeredFunc)(int))
{
    spinBox = new QSpinBox();
    spinBox->setValue(initValue);
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setGeometry(100, 100, 120, 100);
    connect (spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, triggeredFunc);

    this->addWidget(new QLabel(title));
    this->addWidget(spinBox);
    addSeparator();
}

// add a new fontcombobox to ToolBar
void ToolBar::AddToolBarFontComboBox(QFontComboBox *fontComboBox, QString title, void (ToolBar::*triggeredFunc)(const QString &))
{
    fontComboBox = new QFontComboBox();
    connect(fontComboBox, QOverload<const QString &>::of(&QFontComboBox::currentIndexChanged), this, triggeredFunc);

    this->addWidget(new QLabel(title));
    this->addWidget(fontComboBox);
}

// open file action
void ToolBar::onOpenFileClicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Text File"), QDir::currentPath(), tr("Text File(*.txt);; Json File(*.json)"));
    qDebug() << path;
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->plainTextEdit->setPlainText(file.readAll());
        file.close();
        QLabel *l = ui->statusBar->findChild<QLabel* >("CurrentLocation");
        l->setText("Current File : " + path + " ");
    }
}

//save file action
void ToolBar::onSaveFileClicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Text File"), QDir::currentPath(), tr("Text (*.txt);;Json File(*.json)"));
    qDebug() << path;
    QFile file(path);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << ui->plainTextEdit->toPlainText();
        file.close();
        QLabel *l = ui->statusBar->findChild<QLabel* >("CurrentLocation");
        l->setText("Current File : " + path + " ");
    }
}

// clear text action
void ToolBar::onClearClicked()
{
    ui->plainTextEdit->clear();
}

// text editing:bold action
void ToolBar::onBoldClicked(bool status)
{
    QTextCharFormat fmt;
    if(status)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);

    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// text editing:italic action
void ToolBar::onItalicClicked(bool status)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(status);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// text editing:underline action
void ToolBar::onUnderLineClicked(bool status)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(status);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// text editing:text color change action
void ToolBar::onTextColorClicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor textColor = pal.color(QPalette::Text);
    QColor color = QColorDialog::getColor(textColor, this, "Choose Text Color");

    if(!color.isValid()) return;

    QTextCharFormat fmt;
    fmt.setForeground(color);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// text editing:background color change action
void ToolBar::onBackGroundColorClicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor bgColor = pal.color(QPalette::Window);
    QColor color = QColorDialog::getColor(bgColor, this, "Choose BackGround Color");

    if(!color.isValid()) return;

    QTextCharFormat fmt;
    fmt.setBackground(color);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// text editing:text size change action
void ToolBar::onSetFontSizeChanged(int size)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(size);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// text editing:text style change action
void ToolBar::onSetFontStyleChanged(const QString &style)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(style);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}
