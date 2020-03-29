#include "widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout;

    QLabel *keyFile = new QLabel("File");
    keyFileEdit = new QLineEdit();
    QPushButton *find1 = new QPushButton("Find");
    QLabel *monitorID = new QLabel("Add index");
    monitorIDEdit = new QLineEdit();
//    QLabel *encrypedRawFile = new QLabel("Encrypted Raw File");
//    encryptedRawFileEdit = new QLineEdit();
//    QPushButton *find2 = new QPushButton("Find");
    decryption = new QPushButton("Generate");
    closebtn = new QPushButton("Close");

    keyFile->setStyleSheet("QLabel {margin-top: 70px;width:100px; height: 30px;font:18px bold Tahoma;}");
    keyFileEdit->setStyleSheet("QLineEdit {margin-top: 70px;width:260px; height: 30px;font:18px bold Tahoma;}");
    find1->setStyleSheet("QPushButton {margin-top: 70px;height: 30px; font:18px bold Tahoma; width:100px;}");

    monitorID->setStyleSheet("QLabel {margin-top: 20px;width:100px; height: 30px;font:18px bold Tahoma;}");
    monitorIDEdit->setStyleSheet("QLineEdit {margin-top: 20px;width:260px; height: 30px;font:18px bold Tahoma;}");

//    encrypedRawFile->setStyleSheet("QLabel {margin-top: 20px;width:100px; height: 30px;font:18px bold Tahoma;}");
//    encryptedRawFileEdit->setStyleSheet("QLineEdit {margin-top: 20px;width:260px; height: 30px;font:18px bold Tahoma;}");
//    find2->setStyleSheet("QPushButton {margin-top: 20px;height: 30px; font:18px bold Tahoma; width:100px;}");

    decryption->setStyleSheet("QPushButton {margin-top: 20px;height: 45px; font:18px bold Tahoma; width:100px;}");
    closebtn->setStyleSheet("QPushButton {margin-top: 20px;height: 45px; font:18px bold Tahoma; width:100px;}");


    connect(find1, SIGNAL(pressed()), this, SLOT(SetKeyFile()));
//    connect(find2, SIGNAL(pressed()), this, SLOT(findRawFile()));
    connect(decryption, SIGNAL(pressed()), this, SLOT(decryptRawFile()));
//    connect(closebtn, SIGNAL(pressed()), this, SLOT(closeApp()));


    layout->addWidget(keyFile, 0, 0);
    layout->addWidget(keyFileEdit, 0, 1);
    layout->addWidget(find1, 0, 2);
    layout->addWidget(monitorID, 1,0);
    layout->addWidget(monitorIDEdit, 1, 1);
//    layout->addWidget(encrypedRawFile, 2, 0);
//    layout->addWidget(encryptedRawFileEdit, 2, 1);
//    layout->addWidget(find2, 2,2);
    layout->addWidget(decryption,3,1);
//    layout->addWidget(closebtn,4,1);

    setLayout(layout);

    setMinimumSize(200,200);

    setWindowTitle(tr("Add index GUi"));
}

Widget::~Widget()
{

    delete keyFileEdit; // line edit for select key file
    delete monitorIDEdit;   // line edit for monitor id
    delete encryptedRawFileEdit;   // line edit for encrypted File
    delete decryption;
    delete closebtn;
    delete ui;
}

//void Widget::closeApp(){

//    this->close();
//}

void Widget::decryptRawFile(){

    qInfo()<<"go to decryption procedure";
   // decryption->setEnabled(false);

    if( keyFileEdit->text() == "" or monitorIDEdit->text() == "" ){

        QMessageBox box(this);
        box.setText("Find file and add index first");
        box.exec();
        return;

    }



//    MoveToObject( target=pal.HDX, index=18)
//    WaitForTimer(timer=2,time=103s)
//    PenetrateObject( target=pal.HDX, index=18,  depth=29mm,speed=50mm/s)

//QString teststr = "MoveToObject(target=pal.HDX,index=18)";
//int first = (teststr).indexOf(',');
//int second =(teststr).indexOf(',',first+1);
//qInfo() << "second INdex :: " <<second;
//qInfo() << "length::" << teststr.length();
//if (second == -1){
// second =(teststr).indexOf(')',first+1);
//}
////qInfo() << QString::number(teststr.mid(first+1, second-first-1).remove(QRegExp( "\\D" )).toInt() + monitorIDEdit->text().toInt());
//QString newindex = "index=" + QString::number(teststr.mid(first+1, second-first-1).remove(QRegExp( "\\D" )).toInt() + monitorIDEdit->text().toInt());
//qInfo() << teststr.replace(teststr.mid(first+1, second-first-1), newindex);






    QString filepath = keyFileEdit->text().left(keyFileEdit->text().lastIndexOf("."))+ "Add" +monitorIDEdit->text() ;
    QString outfilename = filepath + ".PALscript";





    QFile FileEncryptedCSV(keyFileEdit->text());
    if (!FileEncryptedCSV.open(QIODevice::ReadOnly)) {
        qDebug() << FileEncryptedCSV.errorString();
        throw QException();
    }


     QFile fileout(outfilename);




     if (fileout.open(QIODevice::ReadWrite)) {

         QTextStream stream(&fileout);
         //header
         QByteArray line = FileEncryptedCSV.readLine();
         stream << line.data();

         while (!FileEncryptedCSV.atEnd()) {

             QByteArray line = FileEncryptedCSV.readLine();
             QString linedata = QString::fromStdString(line.toStdString());
             if (linedata.contains("pal.HDX")){
//                (QString::fromStdString(line.toStdString())).indexOf(',',1);
                 int first = linedata.indexOf(',');
                 int second =linedata.indexOf(',',first+1);
                 if (second == -1){
                  second =(linedata).indexOf(')',first+1);
                 }

                 QString newindex = "index=" + QString::number(linedata.mid(first+1, second-first-1).remove(QRegExp( "\\D" )).toInt() + monitorIDEdit->text().toInt());
                 linedata = linedata.replace(linedata.mid(first+1, second-first-1),newindex);


             }
             stream << linedata;

         }
     }
     fileout.close();
     FileEncryptedCSV.close();




//    RMISecurityManage manage;
//    QByteArray cpuID  =manage.readCPUIDfromFile(monitorIDEdit->text());
//    qDebug()<<"read CPU ID"<<cpuID;

//    QByteArray keyAfterDecryption = manage.decrypt(keyFileEdit->text());
//    qDebug()<<"read key After Decryption"<<keyAfterDecryption;


//    QByteArray decryptionKey = manage.combine(keyAfterDecryption, cpuID);
//    qDebug()<<"create symmetric Key"<<decryptionKey;


//    RMISecurity security;

//    QString filepath = encryptedRawFileEdit->text().left(encryptedRawFileEdit->text().lastIndexOf("."))+ "_decrypt";

//    if (encryptedRawFileEdit->text().right(4) == ".csv")
//    {
//        qDebug()<< encryptedRawFileEdit->text();

//        QFile FileEncryptedCSV(encryptedRawFileEdit->text());
//        if (!FileEncryptedCSV.open(QIODevice::ReadOnly)) {
//            qDebug() << FileEncryptedCSV.errorString();
//            throw QException();
//        }


//        QString readContent;
//        QByteArray decryptedText;


////        QString time = QDateTime::currentDateTime().toString("yyyyMMdd_hhmm");
////        QString filename = filepath + "_" + time + "_" +"rmi.csv";
//        QString filename = filepath + ".csv";
//        qDebug()<<filename;
//        QFile fileout(filename);
//        if (fileout.open(QIODevice::ReadWrite)) {

//            QTextStream stream(&fileout);
//            //header
//            QByteArray line = FileEncryptedCSV.readLine();
//            stream << line;

//            while (!FileEncryptedCSV.atEnd()) {

//                QByteArray line = FileEncryptedCSV.readLine();
//                decryptedText = security.decrypt(security.hexStringToBytes(line), decryptionKey);
//                stream << decryptedText.data()<<endl;

//            }
//        }
//        fileout.close();
//        FileEncryptedCSV.close();

//    }
//    else if(encryptedRawFileEdit->text().right(4) == ".dat"){


//        QFile FileEncryptedRaw(encryptedRawFileEdit->text());
//        QByteArray decryptedText;
//        if (!FileEncryptedRaw.open(QIODevice::ReadOnly)) {
//           throw QException();
//        }

//        QDataStream stream(&FileEncryptedRaw);

//        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

//        QString filename = filepath + ".dat";
//        QFile fileout(filename);

//        if (!fileout.open(QIODevice::WriteOnly)) {
//            throw QException();

//        }
//        QDataStream streamwrite(&fileout);
//        streamwrite.setFloatingPointPrecision(QDataStream::SinglePrecision);

//        //add one new function: to decrypt data and save it to the text stream file

//        QString txtFileName =  filepath + ".txt";
//        qDebug()<<"text file name = "<<txtFileName;

//        //create text file
//        QFile txtfileout(txtFileName);

//        if (!txtfileout.open(QIODevice::WriteOnly)) {
//            throw QException();

//        }
//        QTextStream txtwrite(&txtfileout);

//        QByteArray EncrytHeader;
//        EncrytHeader.resize(4);

//        stream >> EncrytHeader;
//        QByteArray decryptedHeader = security.decrypt(EncrytHeader, decryptionKey);
//        qDebug() << decryptedHeader;

//        int8_t IMP_DATA_VERSION;
//        stream >> IMP_DATA_VERSION;

//        //start to write the decrpted file
//        streamwrite << IMP_DATA_VERSION;
//        txtwrite << " [Version Section] " <<endl;
//        txtwrite << IMP_DATA_VERSION<<endl;


//        //here we need to process 0x03 version
//        if (IMP_DATA_VERSION == 0x03 )
//        {
//            txtwrite << " [Header Section] " <<endl;

//            //read the new header
//            //read monitor id
//            QString monitorID;
//            monitorID.resize(8);
//            stream >> monitorID;
//            //write to stream
//            streamwrite << monitorID;
//            //write to txt file
//            txtwrite <<monitorID<<endl;

//            //read fw-version
//            uint16_t FW_version;
//            stream >> FW_version;
//            //write to stream
//            streamwrite << FW_version;
//            //write to txt file
//            txtwrite <<FW_version<<endl;

//            //read software version
//            QString softwareVersion;
//            softwareVersion.resize(16);
//            stream >> softwareVersion;
//            //write to stream
//            streamwrite << softwareVersion;
//            //write to txt file
//            txtwrite <<softwareVersion<<endl;

//            // the following is the encrypted content in the header section
//            // read size
//            int16_t encryptedHeadDataSize;
//            stream >> encryptedHeadDataSize;

//            //read buffer
//            QByteArray encryptedHeadData;
//            encryptedHeadData.resize(encryptedHeadDataSize);
//            stream >> encryptedHeadData;

//            //decrypt the buffer
//            QByteArray decryptedHeadBuffer = security.decrypt(encryptedHeadData, decryptionKey);
//            // parse the buffer
//            qlonglong patientID = static_cast<qlonglong>(security.bytesToInt64(decryptedHeadBuffer.mid(0,8)));
//            streamwrite << patientID;
//            txtwrite << patientID <<endl;

//            float heightVal = security.bytesToFloat(decryptedHeadBuffer.mid(8,4));
//            streamwrite << heightVal;
//            txtwrite << heightVal <<endl;

//            float weightVal = security.bytesToFloat(decryptedHeadBuffer.mid(12,4));
//            streamwrite << weightVal;
//            txtwrite << weightVal <<endl;

//            float sexVal = security.bytesToFloat(decryptedHeadBuffer.mid(16,4));
//            streamwrite << sexVal;
//            txtwrite << sexVal <<endl;

//        }


//        uint16_t EncrytTFSize;
//        stream >> EncrytTFSize;

//        QByteArray EncryptedTF;
//        EncryptedTF.resize(EncrytTFSize);
//        stream >> EncryptedTF;
//        QByteArray decryptedTF = security.decrypt(EncryptedTF, decryptionKey);

//        streamwrite << static_cast <uint16_t> (decryptedTF.size());
//        qDebug() << "decrypt tf size:" <<decryptedTF.size() << "encrypted TF size = "<< EncryptedTF.size();
////        streamwrite << decryptedTF;

//        txtwrite << " [Transfer function Section] " <<endl;
//        txtwrite << static_cast <uint16_t> (decryptedTF.size())<<endl;
////        txtwrite << decryptedTF<<endl;
//        QVector <uint8_t> tt;
//        for(int i=0; i<decryptedTF.size(); i++){
//            tt.append(static_cast<uint8_t>(decryptedTF[i]));
//            streamwrite << tt[i];
//            txtwrite << tt[i] <<",";
//        }
//        qDebug()<<tt;
//        txtwrite << endl;

//        txtwrite << " [Data Section] " <<endl;

//        //from here the data format is different
//        if (IMP_DATA_VERSION == 0x02 || IMP_DATA_VERSION == 0x03 )
//        {
//            // while loop for reading data samples
//            int k=0;
//            while(!stream.atEnd())
//            {
//                // read tag
//                QByteArray tag;
//                tag.resize(3);
//                stream >> tag;

//                qDebug()<< tag;

//                if(tag == "TAG") {
//                    // read size
//                    int16_t encryptedDataSize;
//                    stream >> encryptedDataSize;

//                    //read buffer
//                    QByteArray encryptedSampleData;
//                    encryptedSampleData.resize(encryptedDataSize);
//                    stream >> encryptedSampleData;

//                    //decrypt the buffer
//                    QByteArray decryptedBuffer = security.decrypt(encryptedSampleData, decryptionKey);

//                    qDebug()<<k++<<"encrypted data size = "<<encryptedSampleData.size()<<"decrypted buffer size ="<<decryptedBuffer.size();

//                    // parse the buffer
//                    int8_t status = security.bytesToInt8(decryptedBuffer.mid(0,1));
//                    streamwrite << status;
//                    txtwrite << status <<",";


//                    int8_t channelIndex = security.bytesToInt8(decryptedBuffer.mid(1,1));
//                    streamwrite << channelIndex;
//                    txtwrite << channelIndex <<",";

//                    int8_t frequencyIndex = security.bytesToInt8(decryptedBuffer.mid(2,1));
//                    streamwrite << frequencyIndex;
//                    txtwrite << frequencyIndex <<",";

//                    qlonglong times = static_cast<qlonglong>(security.bytesToInt64(decryptedBuffer.mid(3,8)));
//                    streamwrite << times;
//                    txtwrite << times <<",";

//                    float sourceI_0 = security.bytesToFloat(decryptedBuffer.mid(11,4));
//                    streamwrite << sourceI_0;
//                    txtwrite << sourceI_0 <<",";

//                    float sourceI_1 = security.bytesToFloat(decryptedBuffer.mid(15,4));
//                    streamwrite << sourceI_1;
//                    txtwrite << sourceI_1 <<",";

//                    float impedance = security.bytesToFloat(decryptedBuffer.mid(19,4));
//                    streamwrite << impedance;
//                    txtwrite << impedance <<",";

//                    float real1 = security.bytesToFloat(decryptedBuffer.mid(23,4));
//                    float imag1 = security.bytesToFloat(decryptedBuffer.mid(27,4));
//                    streamwrite << real1;
//                    streamwrite << imag1;

//                    txtwrite << real1 <<",";
//                    txtwrite << imag1 <<",";


//                    float real2 = security.bytesToFloat(decryptedBuffer.mid(31,4));
//                    float imag2 = security.bytesToFloat(decryptedBuffer.mid(35,4));
//                    streamwrite << real2;
//                    streamwrite << imag2;

//                    txtwrite << real2 <<",";
//                    txtwrite << imag2 <<",";

//                    float real3 = security.bytesToFloat(decryptedBuffer.mid(39,4));
//                    float imag3 = security.bytesToFloat(decryptedBuffer.mid(43,4));
//                    streamwrite << real3;
//                    streamwrite << imag3;

//                    txtwrite << real3 <<",";
//                    txtwrite << imag3 <<",";

//                    float real4 = security.bytesToFloat(decryptedBuffer.mid(47,4));
//                    float imag4 = security.bytesToFloat(decryptedBuffer.mid(51,4));
//                    streamwrite << real4;
//                    streamwrite << imag4;

//                    txtwrite << real4 <<",";
//                    txtwrite << imag4 <<",";

//                    float real5 = security.bytesToFloat(decryptedBuffer.mid(55,4));
//                    float imag5 = security.bytesToFloat(decryptedBuffer.mid(59,4));
//                    streamwrite << real5;
//                    streamwrite << imag5;

//                    txtwrite << real5 <<",";
//                    txtwrite << imag5 <<",";

//                    float real6 = security.bytesToFloat(decryptedBuffer.mid(63,4));
//                    float imag6 = security.bytesToFloat(decryptedBuffer.mid(67,4));
//                    streamwrite << real6;
//                    streamwrite << imag6;

//                    //                    qDebug()<<"real1="<<real1<<"imag1="<<imag1;
//                    //                    qDebug()<<"real2="<<real2<<"imag2="<<imag2;
//                    //                    qDebug()<<"real3="<<real3<<"imag3="<<imag3;
//                    //                    qDebug()<<"real4="<<real4<<"imag4="<<imag4;
//                    //                    qDebug()<<"real5="<<real5<<"imag5="<<imag5;
//                    //                    qDebug()<<"real6="<<real6<<"imag6="<<imag6;

//                    txtwrite << real6 <<",";
//                    txtwrite << imag6 <<",";
//                    txtwrite<<endl;
//                }
//                else
//                {
//                    // it may should be done with an algorithm by step moving search to the next tag
//                    // currently we just exit for the corrupted encrypted file
//                    qInfo()<<"some encrypted infor is missing. Break;";
//                    break;
//                }

//                txtwrite << endl;
//            }
//        }
//        else{
//            //default 0x01

//            // while loop for reading data samples
//            int k=0;
//            while(!stream.atEnd())
//            {
//                // read timestamp
//                qlonglong time;
//                stream >> time;

//                streamwrite << time;
//                txtwrite << time <<",";

//                uint8_t numOfChannels;
//                stream >> numOfChannels;

//                streamwrite << numOfChannels;
//                txtwrite << numOfChannels <<endl;

//                // read channel

//                for (int i=0;i<numOfChannels;i++) {

//                    // read tag
//                    QByteArray tag;
//                    tag.resize(3);
//                    stream >> tag;

//                    qDebug()<< tag;

//                    if(tag == "TAG") {
//                        // read size
//                        int16_t encryptedDataSize;
//                        stream >> encryptedDataSize;

//                        //read buffer
//                        QByteArray encryptedSampleData;
//                        encryptedSampleData.resize(80);
//                        stream >> encryptedSampleData;

//                        //decrypt the buffer
//                        QByteArray decryptedBuffer = security.decrypt(encryptedSampleData, decryptionKey);

//                        qDebug()<<k++<<i<<"encrypted data size = "<<encryptedSampleData.size()<<"decrypted buffer size ="<<decryptedBuffer.size();

//                        // parse the buffer
//                        int8_t status = security.bytesToInt8(decryptedBuffer.mid(0,1));
//                        streamwrite << status;
//                        txtwrite << status <<",";


//                        int8_t channelIndex = security.bytesToInt8(decryptedBuffer.mid(1,1));
//                        streamwrite << channelIndex;
//                        txtwrite << channelIndex <<",";

//                        int32_t ticks = security.bytesToInt32(decryptedBuffer.mid(2,4));
//                        streamwrite << ticks;
//                        txtwrite << ticks <<",";

//                        qlonglong times = static_cast<qlonglong>(security.bytesToInt64(decryptedBuffer.mid(6,8)));
//                        streamwrite << times;
//                        txtwrite << times <<",";

//                        float sourceI_0 = security.bytesToFloat(decryptedBuffer.mid(14,4));
//                        streamwrite << sourceI_0;
//                        txtwrite << sourceI_0 <<",";

//                        float sourceI_1 = security.bytesToFloat(decryptedBuffer.mid(18,4));
//                        streamwrite << sourceI_1;
//                        txtwrite << sourceI_1 <<",";

//                        float impedance = security.bytesToFloat(decryptedBuffer.mid(22,4));
//                        streamwrite << impedance;
//                        txtwrite << impedance <<",";

//                        float real1 = security.bytesToFloat(decryptedBuffer.mid(26,4));
//                        float imag1 = security.bytesToFloat(decryptedBuffer.mid(30,4));
//                        streamwrite << real1;
//                        streamwrite << imag1;

//                        txtwrite << real1 <<",";
//                        txtwrite << imag1 <<",";


//                        float real2 = security.bytesToFloat(decryptedBuffer.mid(34,4));
//                        float imag2 = security.bytesToFloat(decryptedBuffer.mid(38,4));
//                        streamwrite << real2;
//                        streamwrite << imag2;

//                        txtwrite << real2 <<",";
//                        txtwrite << imag2 <<",";

//                        float real3 = security.bytesToFloat(decryptedBuffer.mid(42,4));
//                        float imag3 = security.bytesToFloat(decryptedBuffer.mid(46,4));
//                        streamwrite << real3;
//                        streamwrite << imag3;

//                        txtwrite << real3 <<",";
//                        txtwrite << imag3 <<",";

//                        float real4 = security.bytesToFloat(decryptedBuffer.mid(50,4));
//                        float imag4 = security.bytesToFloat(decryptedBuffer.mid(54,4));
//                        streamwrite << real4;
//                        streamwrite << imag4;

//                        txtwrite << real4 <<",";
//                        txtwrite << imag4 <<",";

//                        float real5 = security.bytesToFloat(decryptedBuffer.mid(58,4));
//                        float imag5 = security.bytesToFloat(decryptedBuffer.mid(62,4));
//                        streamwrite << real5;
//                        streamwrite << imag5;

//                        txtwrite << real5 <<",";
//                        txtwrite << imag5 <<",";

//                    float real6 = security.bytesToFloat(decryptedBuffer.mid(66,4));
//                    float imag6 = security.bytesToFloat(decryptedBuffer.mid(70,4));
//                    streamwrite << real6;
//                    streamwrite << imag6;

////                    qDebug()<<"real1="<<real1<<"imag1="<<imag1;
////                    qDebug()<<"real2="<<real2<<"imag2="<<imag2;
////                    qDebug()<<"real3="<<real3<<"imag3="<<imag3;
////                    qDebug()<<"real4="<<real4<<"imag4="<<imag4;
////                    qDebug()<<"real5="<<real5<<"imag5="<<imag5;
////                    qDebug()<<"real6="<<real6<<"imag6="<<imag6;

//                    txtwrite << real6 <<",";
//                    txtwrite << imag6 <<",";
//                    txtwrite<<endl;
//                }
//                else
//                {
//                    // it may should be done with an algorithm by step moving search to the next tag
//                    // currently we just exit for the corrupted encrypted file
//                    qInfo()<<"some encrypted infor is missing. Break;";
//                    break;
//                }
//            }
//            txtwrite << endl;
//        }
//        }
//        fileout.close();
//        txtfileout.close();
//        FileEncryptedRaw.close();

//    }
//    else
//    {

//        QSettings settings(encryptedRawFileEdit->text(), QSettings::IniFormat);
//        QStringList keys = settings.allKeys();

//        QString filepath = encryptedRawFileEdit->text().left(encryptedRawFileEdit->text().lastIndexOf("."))+ "_decrypt";
//        QString filename = filepath + ".properties";

//        QSettings settingsWrite(filename, QSettings::IniFormat);

//        for(auto key: keys){
//            QString stringBeforeDecryption = settings.value(key).toString();
//            QString stringAfterDecryption = security.decrypt( stringBeforeDecryption, decryptionKey);
//            settingsWrite.setValue(key, stringAfterDecryption);
//        }


//    }


//    decryption->setEnabled(true);

//    qInfo()<<"File is decrypted successfully!";
}



void Widget::SetKeyFile(){

    QString securityDir = QDir::currentPath();

    QString keyFileName = QFileDialog::getOpenFileName(this,
                                                       tr("Find File"), securityDir, tr("Key Files (*.PALscript)"));

    keyFileEdit->setText(keyFileName);
}



//void Widget::findRawFile(){
//    RMISecurityManage manage;
//    encryptedRawFileEdit->setText( manage.findEncryptedRawFile());

//}

