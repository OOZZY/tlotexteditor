#include <QApplication>
#include <tlo/texteditor.hpp>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QStringList arguments = QCoreApplication::arguments();
  QString filePath = arguments.size() >= 2 ? arguments.at(1) : QString();
  tlo::TextEditor textEditor(filePath);
  textEditor.show();
  return app.exec();
}
