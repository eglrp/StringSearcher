#ifndef SEARCHERDIALOG_H
#define SEARCHERDIALOG_H

#include <QtGui>

namespace Ui {
class SearcherDialog;
}

class SearchThread;

class SearcherDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SearcherDialog(QWidget *parent = 0);
    ~SearcherDialog();
    
private slots:
    void on_BTN_Browse_clicked();

    void on_BTN_Search_clicked();

    void on_BTN_Stop_clicked();

    void slot_show_result(const QString filePath, const int line, const QString context);
    void slot_update_label(const int fileMatched, const int fileFailed);
    void slot_thread_stopped();

    void on_BTN_Option_clicked();

private:
    Ui::SearcherDialog *ui;

    void readSettings();
    void saveSettings();
    void updateComboBox(QComboBox *comboBox, QString &text);
    void scanDirectory(QDir &dir, QStringList &filterInList,
                         QStringList &filterOutList, QString &key);
    void collectFiles(QStringList filePathList, QStringList &filterInList,
                         QStringList &filterOutList, QString &key);

    QTime ElapsedTime;
    QFutureWatcher<void> cntWatcher;
    QList<SearchThread *> searchThreads;
    bool stopScanDir;
    int WorkingThreadNum;
    int fileScanned;
    int fileMatched;
    int fileFailed;
};

class SearchThread : public QThread
{
    Q_OBJECT

public:
    explicit SearchThread(QString k);
    ~SearchThread();

    void stop();

signals:
    void signal_show_result(const QString filePath, const int line, const QString context);
    void signal_update_label(const int fileMatched, const int fileFailed);

private:
    void run();
    int searchString(const QString &filePath, const QString &key);

    QString key;
    bool stopSearchStr;
};

#endif // SEARCHERDIALOG_H
