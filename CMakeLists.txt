cmake_minimum_required(VERSION 3.16)

project(Zied VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Zied
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        loanmeth.cpp
        loanmeth.h
        customermeth.cpp
        customermeth.h

        pics.qrc

        afterregistering.h afterregistering.cpp afterregistering.ui
        archieve.h archieve.cpp archieve.ui
        dailytransaction.h dailytransaction.cpp dailytransaction.ui
        deposit.h deposit.cpp deposit.ui
        displayemployee.h displayemployee.cpp displayemployee.ui
        displayloans.h displayloans.cpp displayloans.ui
        employeemenu.h employeemenu.cpp employeemenu.ui



        listaccount.h listaccount.cpp listaccount.ui
        loans1.h loans1.cpp loans1.ui
        manageloans.h manageloans.cpp manageloans.ui
        managermenu.h managermenu.cpp managermenu.ui
        modify.h modify.cpp modify.ui
        money.h money.cpp money.ui
        requestloan.h requestloan.cpp requestloan.ui
        secondwindow1.h secondwindow1.cpp secondwindow1.ui
        secondwindow2.h secondwindow2.cpp secondwindow2.ui
        secondwindow3.h secondwindow3.cpp secondwindow3.ui
        showloans.h showloans.cpp showloans.ui
        stats.h stats.cpp stats.ui
        thirdwindow11.h thirdwindow11.cpp thirdwindow11.ui
        thirdwindow12.h thirdwindow12.cpp thirdwindow12.ui
        fire.h fire.cpp fire.ui
        account.h
        accountmeth.h
        customer.h
        data.h
        datae.h
        employee.h
        employeemeth.h
        functions.h
        loan.h
        statisticsmeth.h
        transaction.h
        transactionmeth.h
        accountmeth.cpp

        data.cpp
        datee.cpp
        functions.cpp

        statisticsmeth.cpp
        transactionmeth.cpp
        loanlist.h
        employeemeth.cpp
        add.h add.cpp add.ui
        addcustomer.h addcustomer.cpp addcustomer.ui


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Zied APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Zied SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Zied
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Zied PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Zied)
endif()
set_target_properties(Zied PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Zied
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Zied)
endif()
