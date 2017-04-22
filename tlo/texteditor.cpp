#include "tlo/texteditor.hpp"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "tlo/ui_texteditor.h"

namespace tlo {
namespace {
const char *defaultWindowTitle = "Unsaved Document [*]";
}  // namespace

bool TextEditor::saveOrDiscardChanges() {
  if (!isWindowModified()) {
    return true;
  }

  const auto result = QMessageBox::warning(
      this, tr("Save changes?"),
      tr("The document has been modified.\nDo you want to save your changes?"),
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (result) {
    case QMessageBox::Save:
      saveOrSaveAs();
      return true;
    case QMessageBox::Cancel:
      return false;
    default:
      break;
  }

  return true;
}

void TextEditor::setFilePath(const QString &newFilePath) {
  filePath = newFilePath;

  if (filePath.isEmpty()) {
    setWindowTitle(defaultWindowTitle);
  } else {
    filePath = QFileInfo(filePath).absoluteFilePath();
    setWindowTitle(QString("%1 [*]").arg(filePath));
  }
}

void TextEditor::newFile() {
  if (!saveOrDiscardChanges()) {
    return;
  }

  setFilePath(QString());
  ui->textEdit->clear();
  setWindowModified(true);
}

namespace {
QString getFilePath(QFileDialog::AcceptMode acceptMode,
                    QWidget *parent = nullptr,
                    const QString &caption = QString(),
                    const QString &directory = QString(),
                    const QString &filter = QString()) {
  QFileDialog fileDialog(parent, caption, directory, filter);
  fileDialog.setAcceptMode(acceptMode);
  fileDialog.setFileMode(QFileDialog::AnyFile);
  fileDialog.setViewMode(QFileDialog::Detail);
  fileDialog.setWindowModality(Qt::WindowModal);

  auto result = fileDialog.exec();
  if (result != QDialog::Accepted) {
    return QString();
  }

  return fileDialog.selectedFiles().first();
}
}  // namespace

void TextEditor::open(bool usingFileDialog) {
  if (!saveOrDiscardChanges()) {
    return;
  }

  QString fallbackFilePath = filePath;

  if (usingFileDialog) {
    // unlike QFileDialog::getOpenFileName, this function allows user to select
    // a nonexistent file
    QString newFilePath = getFilePath(QFileDialog::AcceptOpen, this);
    if (newFilePath.isEmpty()) {
      return;
    }
    setFilePath(newFilePath);
  }

  if (filePath.isEmpty()) {
    return;
  }

  QFile file(filePath);
  if (!file.exists()) {
    ui->textEdit->clear();
    setWindowModified(true);
    return;
  }

  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
    setFilePath(fallbackFilePath);
    return;
  }

  QTextStream fileStream(&file);
  ui->textEdit->setText(fileStream.readAll());
  file.close();

  setWindowModified(false);
}

void TextEditor::save(bool usingFileDialog) {
  QString fallbackFilePath = filePath;

  if (usingFileDialog) {
    QString newFilePath = getFilePath(QFileDialog::AcceptSave, this);
    if (newFilePath.isEmpty()) {
      return;
    }
    setFilePath(newFilePath);
  }

  if (filePath.isEmpty()) {
    return;
  }

  QFile file(filePath);
  if (!file.open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
    setFilePath(fallbackFilePath);
    return;
  }

  QTextStream fileStream(&file);
  fileStream << ui->textEdit->toPlainText();
  fileStream.flush();
  file.close();

  setWindowModified(false);
}

void TextEditor::saveOrSaveAs() {
  if (filePath.isEmpty()) {
    save(true);
  } else {
    save(false);
  }
}

void TextEditor::quit() {
  if (!saveOrDiscardChanges()) {
    return;
  }

  QCoreApplication::quit();
}

void TextEditor::setWindowModifiedTrue() { setWindowModified(true); }
void TextEditor::on_newButton_clicked() { newFile(); }
void TextEditor::on_openButton_clicked() { open(true); }
void TextEditor::on_saveButton_clicked() { saveOrSaveAs(); }
void TextEditor::on_saveAsButton_clicked() { save(true); }
void TextEditor::on_quitButton_clicked() { quit(); }
void TextEditor::on_actionNew_triggered() { newFile(); }
void TextEditor::on_actionOpen_triggered() { open(true); }
void TextEditor::on_actionSave_triggered() { saveOrSaveAs(); }
void TextEditor::on_actionSaveAs_triggered() { save(true); }
void TextEditor::on_actionQuit_triggered() { quit(); }

TextEditor::TextEditor(const QString &newFilePath, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TextEditor) {
  ui->setupUi(this);
  connect(ui->textEdit->document(), SIGNAL(contentsChanged()), this,
          SLOT(setWindowModifiedTrue()));

  setFilePath(newFilePath);
  if (!filePath.isEmpty()) {
    open(false);
  } else {
    setWindowModified(true);
  }
}

TextEditor::~TextEditor() { delete ui; }
}  // namespace tlo
