QT      += core
QT      += gui
QT      += sql
QT      += charts
QT      += printsupport
QT      += widgets
QT      += quickcontrols2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    admin.cpp \
    admintableviewaction.cpp \
    adminwindow.cpp \
    authwindow.cpp \
    client.cpp \
    clienttableviewaction.cpp \
    clientwindow.cpp \
    createadminwindow.cpp \
    createclientwindow.cpp \
    createsubscriptionwindow.cpp \
    editadminwindow.cpp \
    editclientwindow.cpp \
    editsubscriptionwindow.cpp \
    initials.cpp \
    main.cpp \
    mainwindow.cpp \
    medicaldata.cpp \
    medicaldatatableviewaction.cpp \
    mymessagebox.cpp \
    myvalidator.cpp \
    personaladmin.cpp \
    personaladmintableviewaction.cpp \
    personalclient.cpp \
    personalclienttableviewaction.cpp \
    reportwindow.cpp \
    resetmedicaldatawindow.cpp \
    subscription.cpp \
    subscriptionclient.cpp \
    subscriptionclienttableviewaction.cpp \
    subscriptiontableviewaction.cpp \
    subscriptionwindow.cpp

HEADERS += \
    admin.h \
    admintableviewaction.h \
    adminwindow.h \
    authwindow.h \
    client.h \
    clienttableviewaction.h \
    clientwindow.h \
    createadminwindow.h \
    createclientwindow.h \
    createsubscriptionwindow.h \
    editadminwindow.h \
    editclientwindow.h \
    editsubscriptionwindow.h \
    headers.h \
    initials.h \
    mainwindow.h \
    medicaldata.h \
    medicaldatatableviewaction.h \
    mymessagebox.h \
    myvalidator.h \
    personaladmin.h \
    personaladmintableviewaction.h \
    personalclient.h \
    personalclienttableviewaction.h \
    reportwindow.h \
    resetmedicaldatawindow.h \
    subscription.h \
    subscriptionclient.h \
    subscriptionclienttableviewaction.h \
    subscriptiontableviewaction.h \
    subscriptionwindow.h

FORMS += \
    adminwindow.ui \
    authwindow.ui \
    clientwindow.ui \
    createadminwindow.ui \
    createclientwindow.ui \
    createsubscriptionwindow.ui \
    editadminwindow.ui \
    editclientwindow.ui \
    editsubscriptionwindow.ui \
    mainwindow.ui \
    reportwindow.ui \
    resetmedicaldatawindow.ui \
    subscriptionwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fonts.qrc \
    icons.qrc
