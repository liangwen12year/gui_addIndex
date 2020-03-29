#include "ui_widget.h"
#include <QWidget>
#include <QtWidgets>
//#include "../../ExSpiron2Xi/Security/RMISecurityManage.h"
//#include "../../ExSpiron2Xi/Security/RMISecurity.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Widget::Widget()
     * construct the interface for the decryption
     */
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


    QLineEdit   *keyFileEdit = nullptr; // line edit for select key file
    QLineEdit   *monitorIDEdit = nullptr;   // line edit for monitor id
    QLineEdit   *encryptedRawFileEdit = nullptr;   // line edit for encrypted File

    QPushButton *decryption = nullptr;
    QPushButton *closebtn = nullptr;


public slots:


    /**
     * @brief Widget::SetKeyFile()
     * select key file from designated path
     */
    void SetKeyFile();



//    /**
//     * @brief Widget::findRawFile()
//     * find the EncryptedFile from designated path
//     */
//    void findRawFile();


    /**
     * @brief Widget::decryptRawFile()
     * based on the key file and monitor ID, decrypt EncryptedFile,
     * and write out the decrypted file
     */
    void decryptRawFile();

//    /**
//     * @brief closeApp()
//     * close the application
//     */
//    void closeApp();

private:
    Ui::Widget *ui;
};

