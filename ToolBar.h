#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <Qt>
#include <qdir.h>
#include <QFileDialog>
#include <QPainter>
#include <QLabel>
#include <QColorDialog>
#include <QSpinBox>
#include <QFontComboBox>

#endif // TOOLBAR_H

using namespace std;
namespace Ui { class TextEditor; }

class ToolBar : public QToolBar
{
    Q_OBJECT

    public:
        ToolBar(Ui::TextEditor *ui);
        void InitBarItem();

    private:
        void AddToolBarAct(QAction *action, QString name, QString path, void (ToolBar::*triggeredFunc)());
        void AddToolBarAct(QAction *action, QString name, QString path, void (ToolBar::*triggeredFunc)(bool));
        void AddToolBarLabel(QString text);
        void AddToolBarSpinBox(QSpinBox *spinBox, int min, int max, int initValue, QString title, void (ToolBar::*triggeredFunc)(int));
        void AddToolBarFontComboBox(QFontComboBox *fontComboBox, QString title, void (ToolBar::*triggeredFunc)(const QString &));

        Ui::TextEditor *ui;

        QAction *openFile;
        QAction *saveFile;
        QAction *clear;
        QAction *setBold;
        QAction *setItalic;
        QAction *setUnderLine;
        QAction *setTextColor;
        QAction *setBackGroundColor;

        QSpinBox *setFontSize;
        QFontComboBox *setFontStyle;

    private slots:
        void onOpenFileClicked();
        void onSaveFileClicked();
        void onClearClicked();
        void onBoldClicked(bool status);
        void onItalicClicked(bool status);
        void onUnderLineClicked(bool status);
        void onTextColorClicked();
        void onBackGroundColorClicked();
        void onSetFontSizeChanged(int size);
        void onSetFontStyleChanged(const QString &style);

};
