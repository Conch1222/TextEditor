#include "texteditor.h"
#include "ui_texteditor.h"

#include<QDebug>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    InitStatusBar();

    toolBar = new ToolBar(ui);
    addToolBar(Qt::TopToolBarArea, toolBar);

    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &TextEditor::onPlainTextChanged);
}

void TextEditor::InitStatusBar()
{
    InitLabel(lineCount, "Line Count : 1", "LineCount");
    InitLabel(charCount, "Character Count : 0", "CharCount");
    InitLabel(fileLocation, "Current File : ", "CurrentLocation");
}

void TextEditor::InitLabel(QLabel *label, QString msg, QString name)
{
    label = new QLabel();
    label->setObjectName(name);
    label->setText(msg);
    ui->statusBar->addWidget(label);
    AddBlank();
}

void TextEditor::AddBlank()
{
    QWidget *Blank = new QWidget;
    Blank->setFixedWidth(20);
    Blank->setHidden(1);
    Blank->setVisible(1);
    ui->statusBar->addWidget(Blank);
}

void TextEditor::onPlainTextChanged()
{
    QString content = ui->plainTextEdit->toPlainText();
    QString charCnt = QString::number(content.count());
    QString lineCnt = QString::number(content.count('\n')+1);

    // chars
    QLabel *c = ui->statusBar->findChild<QLabel* >("CharCount");
    c->setText("Character Count : " + charCnt + " ");

    //lines
    QLabel *l = ui->statusBar->findChild<QLabel* >("LineCount");
    l->setText("Line Count : " + lineCnt + " ");

}

TextEditor::~TextEditor()
{
    delete ui;
}

