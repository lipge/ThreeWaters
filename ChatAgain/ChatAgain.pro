QT       += core gui
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

DESTDIR = ./bin
TARGET = ThreeWaters
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adduseritem.cpp \
    authenfriend.cpp \
    bubbleframe.cpp \
    chatdialog.cpp \
    chatitembase.cpp \
    chatpage.cpp \
    chatuserlist.cpp \
    chatuserwid.cpp \
    chatview.cpp \
    clickbtn.cpp \
    clickedlabel.cpp \
    clickedoncelabel.cpp \
    contactitem.cpp \
    contactslist.cpp \
    customizeedit.cpp \
    findresdlg.cpp \
    friendinfopage.cpp \
    friendlabel.cpp \
    global.cpp \
    groupitem.cpp \
    httpmgr.cpp \
    listitembase.cpp \
    logindialog.cpp \
    loginfailed.cpp \
    main.cpp \
    mainwindow.cpp \
    messageedit.cpp \
    newfrienditem.cpp \
    newfriendlist.cpp \
    newfriendpage.cpp \
    picturebubble.cpp \
    registerdialog.cpp \
    requestaddfriendsdlg.cpp \
    resetdialog.cpp \
    searchlist.cpp \
    statewidget.cpp \
    tcpmgr.cpp \
    textbubble.cpp \
    timerbtn.cpp \
    usermgr.cpp

HEADERS += \
    Singleton.h \
    adduseritem.h \
    authenfriend.h \
    bubbleframe.h \
    chatdialog.h \
    chatitembase.h \
    chatpage.h \
    chatuserlist.h \
    chatuserwid.h \
    chatview.h \
    clickbtn.h \
    clickedlabel.h \
    clickedoncelabel.h \
    contactitem.h \
    contactslist.h \
    customizeedit.h \
    findresdlg.h \
    friendinfopage.h \
    friendlabel.h \
    global.h \
    groupitem.h \
    httpmgr.h \
    listitembase.h \
    logindialog.h \
    loginfailed.h \
    mainwindow.h \
    messageedit.h \
    newfrienditem.h \
    newfriendlist.h \
    newfriendpage.h \
    picturebubble.h \
    registerdialog.h \
    requestaddfriendsdlg.h \
    resetdialog.h \
    searchlist.h \
    statewidget.h \
    tcpmgr.h \
    textbubble.h \
    timerbtn.h \
    userdata.h \
    usermgr.h

FORMS += \
    adduseritem.ui \
    authenfriend.ui \
    chatdialog.ui \
    chatpage.ui \
    chatuserwid.ui \
    chatview.ui \
    contactitem.ui \
    findresdlg.ui \
    friendinfopage.ui \
    friendlabel.ui \
    groupitem.ui \
    logindialog.ui \
    loginfailed.ui \
    mainwindow.ui \
    newfrienditem.ui \
    newfriendpage.ui \
    registerdialog.ui \
    requestaddfriendsdlg.ui \
    resetdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    config.ini

CONFIG(debug, debug | release){
    #指定要拷贝的文件目录为工程目录下release目录下的所有dll、lib文件，例如工程目录在D:\QT\Test
    #PWD就为D:/QT/Test，DllFile = D:/QT/Test/release/*.dll
    TargetConfig = $${PWD}/config.ini
    #将输入目录中的"/"替换为"\"
    TargetConfig = $$replace(TargetConfig, /, \\)
    #将输出目录中的"/"替换为"\"
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    //执行copy命令
    QMAKE_POST_LINK += copy /Y \"$$TargetConfig\" \"$$OutputDir\" &
    # 首先，定义static文件夹的路径
    StaticDir = $${PWD}/static
    # 将路径中的"/"替换为"\"
    StaticDir = $$replace(StaticDir, /, \\)
    #message($${StaticDir})
    # 使用xcopy命令拷贝文件夹，/E表示拷贝子目录及其内容，包括空目录。/I表示如果目标不存在则创建目录。/Y表示覆盖现有文件而不提示。
    QMAKE_POST_LINK += xcopy /Y /E /I \"$$StaticDir\" \"$$OutputDir\\static\\\"
}else{
    # release
    #指定要拷贝的文件目录为工程目录下release目录下的所有dll、lib文件，例如工程目录在D:\QT\Test
    #PWD就为D:/QT/Test，DllFile = D:/QT/Test/release/*.dll
    TargetConfig = $${PWD}/config.ini
    #将输入目录中的"/"替换为"\"
    TargetConfig = $$replace(TargetConfig, /, \\)
    #将输出目录中的"/"替换为"\"
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    //执行copy命令
    QMAKE_POST_LINK += copy /Y \"$$TargetConfig\" \"$$OutputDir\"

    # static文件夹
    StaticDir = $${PWD}/static
    # 替换路径中的"/"
    StaticDir = $$replace(StaticDir,/,\\)
    QMAKE_POST_LINK += xcopy /Y /E /I \"$$StaticDir\" \"$$OutputDir\\static\\\"
}

# 手动显式指定utf-8
win32-msvc*:QMAKE_CXXFLAGS += /wd"4819" /utf-8
