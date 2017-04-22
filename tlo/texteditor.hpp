#ifndef TLO_TEXTEDITOR_HPP
#define TLO_TEXTEDITOR_HPP

#include <QMainWindow>

namespace tlo {
namespace Ui {
class TextEditor;
}  // namespace Ui

class TextEditor : public QMainWindow {
  Q_OBJECT

 private:
  Ui::TextEditor *ui;
  QString filePath;

  // returns true if changes were saved or discarded
  bool saveOrDiscardChanges();
  void setFilePath(const QString &newFilePath);
  void newFile();
  void open(bool usingFileDialog);
  void save(bool usingFileDialog);
  void saveOrSaveAs();
  void quit();

 private slots:
  void setWindowModifiedTrue();
  void on_newButton_clicked();
  void on_openButton_clicked();
  void on_saveButton_clicked();
  void on_saveAsButton_clicked();
  void on_quitButton_clicked();
  void on_actionNew_triggered();
  void on_actionOpen_triggered();
  void on_actionSave_triggered();
  void on_actionSaveAs_triggered();
  void on_actionQuit_triggered();

 public:
  explicit TextEditor(const QString &newFilePath = QString(),
                      QWidget *parent = 0);
  ~TextEditor();
};
}  // namespace tlo

#endif  // TLO_TEXTEDITOR_HPP
