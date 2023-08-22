#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <ToolBar.h>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class TextEditor : public QMainWindow
{
    Q_OBJECT

    public:
        TextEditor(QWidget *parent = nullptr);
        ~TextEditor();
        ToolBar *toolBar;
        Ui::TextEditor *ui;

        void InitStatusBar();
        void InitLabel(QLabel *label, QString msg, QString name);
        void AddBlank();

        QLabel *fileLocation;
        QLabel *lineCount;
        QLabel *charCount;

    private slots:
        void onPlainTextChanged();
};
#endif // TEXTEDITOR_H
