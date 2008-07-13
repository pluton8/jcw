TEMPLATE = app
CONFIG += qt warn_on debug
QT = core gui xml
SOURCES = \
	src/main.cpp \
	src/mainwnd.cpp \
	src/abstractcrossword.cpp \
	src/rectcrossword.cpp \
	src/classiccw.cpp \
	src/crosswordinfo.cpp \
	src/fieldcheckerthread.cpp
HEADERS = \
	src/mainwnd.h \
	src/abstractcrossword.h \
	src/rectcrossword.h \
	src/classiccw.h \
	src/crosswordinfo.h \
	src/fieldcheckerthread.h
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RESOURCES = jcw.qrc
TRANSLATIONS = jcw_ru.ts
